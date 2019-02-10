/**
   Compilation
   g++ -ggdb imageWritePNG.cpp -o imageWritePNG `pkg-config --cflags --libs opencv`
*/

#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void createAlphaMat(Mat &mat)
{
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            Vec4b& rgba = mat.at<Vec4b>(i, j);
            rgba[0] = UCHAR_MAX;
            rgba[1] = saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX);
            rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
        }
    }
}

int main(int argv, char **argc)
{
    // Creation de l'objet mat avec un canal alpha
    Mat mat(480, 640, CV_8UC4);
    createAlphaMat(mat);

    vector<int> compression;
    compression.push_back ( CV_IMWRITE_PNG_COMPRESSION );
    compression.push_back(0); // 0 (sans compression) -> 9 (compression max)


    bool isSuccess = imwrite("alpha.png", mat, compression);
    if (isSuccess){
    	cout <<  "Fichier PNG  enregistré avec alpha data.\n" << endl;
        return 0;
    }else{
        cout << "Erreur d'enregistrement.\n" << endl;
        return 1;
    }
}
