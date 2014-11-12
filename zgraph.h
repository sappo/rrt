/*  =========================================================================
    zgraph -

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is part of CZMQ, the high-level C binding for 0MQ:       
    http://czmq.zeromq.org.                                            
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef __ZGRAPH_H_INCLUDED__
#define __ZGRAPH_H_INCLUDED__

#include <czmq.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _zgraph_t zgraph_t;
typedef struct _zvertex_t zvertex_t;
typedef struct _zedge_t zedge_t;

//  @interface

//  Create a new drs_server
CZMQ_EXPORT zgraph_t *
    zgraph_new ();

//  Destroy the drs_server
CZMQ_EXPORT void
    zgraph_destroy (zgraph_t **self_p);

//  Add a new vertex to the graph. The name is used to query the vertex e.g. to
//  add edges.
CZMQ_EXPORT int
    zgraph_add_vertex (zgraph_t *self, const char *name, zhash_t *attributes);

//  Add a new edge between two vertices. The vertices are identified by their
//  name.
CZMQ_EXPORT int
    zgraph_add_edge (zgraph_t *self, const char *from, const char *to, zhash_t *attributes);

//  First vertex in graph
CZMQ_EXPORT zvertex_t *
    zgraph_first (zgraph_t *self);

//  Next vertex in graph or NULL
CZMQ_EXPORT zvertex_t *
    zgraph_next (zgraph_t *self);

//  Vertex attribute
CZMQ_EXPORT void *
    zvertex_attribute (zvertex_t *self, const void *key);

//  Vertex name
CZMQ_EXPORT char *
    zvertex_name (zvertex_t *self);

//  First edge for vertex
CZMQ_EXPORT zedge_t *
    zvertex_first (zvertex_t *self);

//  Next edge for vertex or NULL
CZMQ_EXPORT zedge_t *
    zvertex_next (zvertex_t *self);

//  Edge attribute
CZMQ_EXPORT zvertex_t *
    zedge_connects (zedge_t *self);

//  Edge attribute
CZMQ_EXPORT void *
    zedge_attribute (zedge_t *self, const void *key);

//  Print properties of object
CZMQ_EXPORT void
    zgraph_print (zgraph_t *self);

//  Self test of this class
CZMQ_EXPORT int
    zgraph_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
