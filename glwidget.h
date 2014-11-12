#ifndef GLWIDGET_H
#define GLWIDGET_H

//  Qt
#include <QDebug>
#include <QtOpenGL>
#include <QList>
#include <QLineF>
//  freeglut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//  stuff
#include <math.h>
#include <iostream>
#include "rrt.h"
//  opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class GLWidget : public QGLWidget
{
public:
    GLWidget(QWidget *parent);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void timerEvent(QTimerEvent *);

private:
    RRT *rrt;
    QList<QLineF> objects;
};

#endif // GLWIDGET_H
