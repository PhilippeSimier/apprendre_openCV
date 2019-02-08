/*
 compilation linux
 g++ -ggdb test.cpp -o test `pkg-config --cflags --libs opencv`

 compilation raspberry debian
 g++ $(pkg-config --libs --cflags opencv) -o test  test.cpp
*/

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv)
{
    // Rectangle vert 300 par 200
    Mat img(200,300,CV_8UC3, Scalar(64,10,64));
    imshow("Test", img);
    // Attente appui sur une touche
    waitKey(0);
    return 0;
}

