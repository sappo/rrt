#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    startTimer(16);
    setWindowTitle(tr("Sample Buffers"));
    rrt = new RRT();
    rrt->buildRRT(QPointF(150, 150), 1, 5.0);
}

void GLWidget::initializeGL()
{
    glutInitDisplayMode(GLUT_RGB);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,300,300,0,0.0f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, (GLint) width(), (GLint) height());

    qDebug () << "initializeGL";
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, (GLint) w, (GLint) h);

    qDebug () << "resizeGL";

}

void GLWidget::paintGL()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,300,300,0,0.0f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    //  glTranslatef(offset, 0.0f, 0.0f);

    glPointSize(7.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        zgraph_t *graph = rrt->graph();
        zvertex_t *vert = zgraph_first(graph);
        while (vert) {
            QPointF *point = (QPointF *) zvertex_attribute (vert, "p");
            glVertex2d(point->x(), point->y());
            //  next vertex
            vert = zgraph_next(graph);
        }
    glEnd();

    glLineWidth(1.0f);
    glBegin(GL_LINES);
        graph = rrt->graph();
        vert = zgraph_first(graph);
        while (vert) {
            QPointF *point_from = (QPointF *) zvertex_attribute (vert, "p");
            zedge_t *edge = zvertex_first (vert);
            while (edge) {
                QPointF *point_to = (QPointF *) zvertex_attribute(zedge_connects(edge), "p");
                glVertex2d(point_from->x(), point_from->y());
                glVertex2d(point_to->x(), point_to->y());
                //  next edge
                edge = zvertex_next (vert);
            }
            //  next vertex
            vert = zgraph_next(graph);
        }
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2d(100, 100);
        glVertex2d(100, 250);
    glEnd();
    glPopMatrix();

    glFlush();
}

void GLWidget::timerEvent(QTimerEvent *)
{
    rrt->stepRRT(1, 5.0);
    update();
}
