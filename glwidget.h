#ifndef GLWIDGET_H
#define GLWIDGET_H

//  Qt
#include <QDebug>
#include <QtOpenGL>
//  freeglut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//  stuff
#include <math.h>
#include <iostream>
#include "rrt.h"

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
    GLfloat offset;
    RRT *rrt;
};

#endif // GLWIDGET_H
