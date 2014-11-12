#include "window.h"
#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <unistd.h>

using namespace cv;

int main(int argc, char *argv[])
{
    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!image.data)                              // Check for invalid input
    {
        qDebug() <<  "Could not open or find the image";
        return -1;
    }

    namedWindow("Map", WINDOW_AUTOSIZE );   // Create a window for display.
    imshow("Map", image);                   // Show our image inside it.
    Vec3d temp = image.at<Vec3d>(12 ,44);
    qDebug() << temp.val[0]; // R
    qDebug() << temp.val[1]; // G
    qDebug() << temp.val[2]; // B
    //while (waitKey(0) != 27);
    //return 0;

    QApplication a(argc, argv);
    Window w;
    w.show();

    return a.exec();
}
