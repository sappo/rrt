/*  =========================================================================
    zgraph - My classes description

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is part of CZMQ, the high-level C binding for 0MQ:       
    http://czmq.zeromq.org.                                            
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    zgraph -
@discuss
@end
*/

#include "zgraph.h"

//  Structure of our class

struct _zvertex_t {
    zlist_t *edges;          //  All edges of this vertex
    zhash_t *attributes;
};

struct _zedge_t {
    zvertex_t *connects;
    zhash_t *attributes;
};

struct _zgraph_t {
    zhash_t *vertices;       //  All vertices of this graph
};

static zvertex_t *
s_zvertex_new (zhash_t *attributes)
{
    zvertex_t *self = (zvertex_t *) zmalloc (sizeof (zvertex_t));
    assert (self);
    assert (attributes);

    self->edges = zlist_new ();
    self->attributes = attributes;

    return self;
}

static zedge_t *
s_zedge_new (zvertex_t *connects, zhash_t *attributes)
{
    zedge_t *self = (zedge_t *) zmalloc (sizeof (zedge_t));
    assert (self);
    assert (attributes);

    self->connects = connects;
    self->attributes = attributes;

    return self;

}

//  --------------------------------------------------------------------------
//  Create a new zgraph

zgraph_t *
zgraph_new ()
{
    zgraph_t *self = (zgraph_t *) zmalloc (sizeof (zgraph_t));
    assert (self);

    self->vertices = zhash_new ();

    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the zgraph

void
zgraph_destroy (zgraph_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zgraph_t *self = *self_p;

        //  Free class properties
        
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Add vertex

int
zgraph_add_vertex (zgraph_t *self, const char *name, zhash_t *attributes)
{
    assert (self);
    assert (attributes);
    zhash_insert(attributes, "name", name);
    return zhash_insert(self->vertices, name, s_zvertex_new (attributes));
}

//  --------------------------------------------------------------------------
//  Add edge

int
zgraph_add_edge (zgraph_t *self, const char *from, const char *to, zhash_t *attributes)
{
    assert (self);
    assert (attributes);

    zvertex_t *from_vert = (zvertex_t *) zhash_lookup (self->vertices, from);
    zvertex_t *to_vert = (zvertex_t *) zhash_lookup (self->vertices, to);
    if (from_vert && to_vert)
        return zlist_append (from_vert->edges, s_zedge_new (to_vert, attributes));
    else
        return -1;
}


//  --------------------------------------------------------------------------
//  First vertex in graph

zvertex_t *
zgraph_first (zgraph_t *self)
{
    assert (self);
    if (zhash_size (self->vertices) == 0)
        return NULL;
    return (zvertex_t *) zhash_first (self->vertices);
}


//  --------------------------------------------------------------------------
//  Next vertex in graph or NULL

zvertex_t *
zgraph_next (zgraph_t *self)
{
    assert (self);
    return (zvertex_t *) zhash_next (self->vertices);
}


//  --------------------------------------------------------------------------
//  Vertex attribute

void *
zvertex_attribute (zvertex_t *self, const void *key)
{
    assert (self);
    return zhash_lookup (self->attributes, key);
}

//  --------------------------------------------------------------------------
//  Vertex name

char *
zvertex_name (zvertex_t *self)
{
    assert (self);
    return zhash_lookup (self->attributes, "name");
}


//  --------------------------------------------------------------------------
//  First edge for vertex

zedge_t *
zvertex_first (zvertex_t *self)
{
    assert (self);
    if (zlist_size (self->edges) == 0)
        return NULL;
    return (zedge_t *) zlist_first (self->edges);
}


//  --------------------------------------------------------------------------
//  Next edge for vertex or NULL

zedge_t *
zvertex_next (zvertex_t *self)
{
    assert (self);
    return (zedge_t *) zlist_next (self->edges);
}


//  --------------------------------------------------------------------------
//  Edge attribute

zvertex_t *
zedge_connects (zedge_t *self)
{
    assert (self);
    return self->connects;
}

//  --------------------------------------------------------------------------
//  Edge attribute

void *
zedge_attribute (zedge_t *self, const void *key)
{
    assert (self);
    return zhash_lookup (self->attributes, key);
}


//  --------------------------------------------------------------------------
//  Print properties of object

void
zgrap_print (zgraph_t *self)
{
    assert (self);
}


//  --------------------------------------------------------------------------
//  Selftest

int
zgraph_test (bool verbose)
{
    printf (" * zgraph: ");

    //  @selftest

    zgraph_t *self = zgraph_new ();
    assert (self);

    zgraph_add_vertex (self, "A", zhash_new ());
    zgraph_add_vertex (self, "B", zhash_new ());
    zgraph_add_vertex (self, "C", zhash_new ());
    zgraph_add_vertex (self, "D", zhash_new ());

    zhash_t *e1_attr = zhash_new ();
    zhash_insert (e1_attr, "name", "e1");
    zgraph_add_edge (self, "A", "D", e1_attr);

    zvertex_t *vert = zgraph_first (self);
    while (vert) {
        char *name = zvertex_name (vert);
        zedge_t *edge = zvertex_first (vert);
        while (edge) {
            char *ename = (char *) zedge_attribute (edge, "name");
            char *econn = zvertex_name (zedge_connects (edge));
            edge = zvertex_next (vert);
        }
        vert = zgraph_next (self);
    }

    zgraph_destroy (&self);
    //  @end

    printf ("OK\n");
    return 0;
}
