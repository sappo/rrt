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
    /*
    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!image.data)                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow("Map", WINDOW_AUTOSIZE );   // Create a window for display.
    imshow("Map", image);                   // Show our image inside it.
    //while (waitKey(0) != 27);
    //return 0;
    */
    QApplication a(argc, argv);
    Window w;
    w.show();

    return a.exec();
}
