#include "rrt.h"
#include <QRectF>

RRT::RRT(QList<QLineF> objects, QObject *parent) :
    QObject(parent)
{
    _graph = zgraph_new ();
    _objects = objects;
    _done = false;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

RRT::~RRT()
{
    zgraph_destroy (&_graph);
}


static const char * pointStr (QPointF point)
{
    QString str = "" + QString::number(point.rx(), 'f', 5) + QString::number(point.ry(), 'f', 5);
    QString strHash = QString(QCryptographicHash::hash(str.toLatin1(), QCryptographicHash::Md5).toHex());
    return qstrdup(strHash.toLatin1().data());
}

void RRT::buildRRT(QPointF qinit, int steps, qreal delta)
{
    zhash_t *qinit_attributes = zhash_new ();
    zhash_insert (qinit_attributes, "p", new QPointF(qinit.rx(), qinit.ry()));
    zgraph_add_vertex (_graph, pointStr(qinit), qinit_attributes);

    //  Enter start into graph
    stepRRT(steps, delta);
}

void RRT::stepRRT (int steps, qreal delta)
{
    for (int i = 0; i < steps; i++) {
        QPointF qrand = randomConf(300);
        QPointF qnear = nearestVertex(qrand);
        QPointF qnew =  newConf(qnear, qrand, delta);

        // Collision dectection
        QLineF edge(qnear, qnew);
        QLineF obj;
        QLineF::IntersectType intersection = QLineF::UnboundedIntersection;
        foreach (obj, _objects) {
            intersection = edge.intersect(obj, NULL);
            if (intersection == QLineF::BoundedIntersection) {
               break;
            }
        }

        if (intersection == QLineF::UnboundedIntersection) {
           // Add vertex
           zhash_t *qattr = zhash_new ();
           zhash_insert (qattr, "p", new QPointF(qnew.rx(), qnew.ry()));
           zgraph_add_vertex (_graph, pointStr(qnew), qattr);
           // Add edge
           zhash_t *eattr = zhash_new ();
           zhash_insert (eattr, "d", &delta);
           zgraph_add_edge(_graph, pointStr(qnear), pointStr(qnew), eattr);
        }


        // Target reached
        int tx = round(qnew.rx());
        int ty = round(qnew.ry());

        if (tx > 20-delta && tx < 20+delta && ty > 20-delta && ty < 20+delta){
            _done = true;
            QPointF qtarget(20, 20);
            // Add vertex
            zhash_t *qattr = zhash_new ();
            zhash_insert (qattr, "p", new QPointF(qtarget.rx(), qtarget.ry()));
            zgraph_add_vertex (_graph, pointStr(qtarget), qattr);
            // Add edge
            zhash_t *eattr = zhash_new ();
            zhash_insert (eattr, "d", &delta);
            zgraph_add_edge(_graph, pointStr(qnew), pointStr(qtarget), eattr);
        }

    }
}

QPointF RRT::randomConf(int max)
{
    int randx = qrand() % max;
    int randy = qrand() % max;
    return QPointF(randx, randy);
}

QPointF RRT::nearestVertex(QPointF qrand)
{
    QPointF closest;
    qreal closest_len = 0;

    zvertex_t *vert = zgraph_first (_graph);
    while (vert) {
        QPointF *point = (QPointF *) zvertex_attribute (vert, "p");
        QLineF edge(*point, qrand);

        // is closest ???
        qreal edge_len = edge.length();
        if (closest.isNull() || closest_len > edge_len) {
            closest = *point;
            closest_len = edge.length();
        }
        //  next vertex in graph
        vert = zgraph_next (_graph);
    }
    return closest;
}

QPointF RRT::newConf (QPointF qnear, QPointF qrand, qreal delta)
{
    QLineF edge(qnear, qrand);
    if (edge.length() > delta)
        edge.setLength(delta);
    return edge.p2();
}

zgraph_t * RRT::graph()
{
    return _graph;
}

bool RRT::isDone()
{
    return _done;
}
