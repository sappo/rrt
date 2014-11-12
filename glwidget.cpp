#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    startTimer(16);
    setWindowTitle(tr("Sample Buffers"));

    Mat image;
    image = imread("../rrt_project/cage.png", CV_LOAD_IMAGE_COLOR);
    if (!image.data)                              // Check for invalid input
    {
        qDebug() <<  "Could not open or find the image";
        return;
    }

    //namedWindow("Map", WINDOW_AUTOSIZE );   // Create a window for display.
    //imshow("Map", image);

    // Horizontal Lines
    for(int y=0;y<image.rows;y++) {
        bool isLine = false;
        QPointF first;
        for(int x=0;x<image.cols;x++) {
             Vec3b color = image.at<Vec3b>(Point(x,y));
             if (color.val[0] == 0 && color.val[1] == 0 && color.val[2] == 0) {
                if (!isLine) {
                   isLine = true;
                   first = QPointF(x, y);
                }

             }
             else if(isLine) {
                isLine = false;
                objects.append(QLineF(first, QPoint(x-1, y)));
             }
          }
    }
    // Vertical Lines
    for(int x = 0; x < image.rows; x++) {
        bool isLine = false;
        QPointF first;
        for(int y = 0; y < image.cols; y++) {
             Vec3b color = image.at<Vec3b>(Point(x,y));
             if (color.val[0] == 0 && color.val[1] == 0 && color.val[2] == 0) {
                if (!isLine) {
                   isLine = true;
                   first = QPointF(x, y);
                }

             }
             else if(isLine) {
                isLine = false;
                objects.append(QLineF(first, QPoint(x, y-1)));
             }
          }
    }

    rrt = new RRT(objects);
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

    //  Draw objects
    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        QLineF obj;
        foreach (obj, objects) {
           glVertex2d(obj.x1(), obj.y1());
           glVertex2d(obj.x2(), obj.y2());
        }
    glEnd();

    //  Target
    glPointSize(14.0f);
    glBegin(GL_POINTS);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2d(20, 20);
    glEnd();

    //  RRT-vertices
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

    //  RRT-edges
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

    glPopMatrix();

    glFlush();
}

void GLWidget::timerEvent(QTimerEvent *)
{
    if (!rrt->isDone()) {
        rrt->stepRRT(100, 5.0);
        update();
    }
}
