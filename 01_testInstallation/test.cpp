/*
 \compilation
	      g++ $(pkg-config --libs --cflags opencv) -o test  test.cpp
*/
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv)
{
    // Rectangle vert 300 par 200
    Mat img(200,300,CV_8UC3, Scalar(0,255,0));
    imshow("Essai", img);
    // Attente appui sur une touche
    waitKey(0);
    return 0;
}

