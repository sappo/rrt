#ifndef RRT_H
#define RRT_H

#include <QObject>
#include <QDebug>
#include <QPointF>
#include <QLineF>
#include <QString>
#include <QTime>
#include <QCryptographicHash>
#include "zgraph.h"

class RRT : public QObject
{
    Q_OBJECT
public:
    explicit RRT(QObject *parent = 0);
    ~RRT();

    void buildRRT (QPointF qinit, int steps, qreal delta);
    QPointF randomConf (int max);
    QPointF nearestVertex (QPointF rand);
    QPointF newConf (QPointF qnear, QPointF qrand, qreal delta);

    zgraph_t * graph();

private:
    zgraph_t *_graph;

signals:

public slots:

};

#endif // RRT_H