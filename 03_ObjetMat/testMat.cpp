/*************************************************************************************/
/*!
    \file     testMat.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \brief    Programme pour comprendre et manipuler les objets de la classe Mat
    \detail   Utilisation des différents constructeurs
    \compilation
	      g++ $(pkg-config --libs --cflags opencv) -o testMat  testMat.cpp
              g++ -ggdb testMat.cpp -o testMat `pkg-config --cflags --libs opencv`
    \version    1.0 - First release
*/
/**************************************************************************************/


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
 {
    Mat ImgSource;    // création d'une matrice vide seulement les entêtes
    ImgSource = imread("Penguins.jpg", CV_LOAD_IMAGE_COLOR);   // Lecture du fichier Pingouins.jpg
    imshow("Img Source", ImgSource);
//    cout << "Refcount : " << ImgSource.u->refcount << " Adresse du premier pixel: " << hex << (long)ImgSource.data << endl;
    cout << "Nombre de canaux : " << ImgSource.channels() << endl;
    cout << "Résolution : " << ImgSource.depth() << endl;
    cout << "Dimensions : " << dec << ImgSource.cols << " x " << dec << ImgSource.rows << " px" << endl;
    waitKey(0);

    Mat ImgDest1(ImgSource);   // utilise le constructeur de copie seul les entêtes sont copiés
    imshow("Img Destination 1", ImgDest1);
//    cout << "Refcount: " << ImgSource.u->refcount << " Adresse du premier pixel: " << hex << ImgDest1.data << endl;
    waitKey(0);

    Mat ImgDest2 = ImgDest1;   // Opérateur d’assignation. copie uniquement de l'entête
    imshow("Img Destination 2", ImgDest1);
//    cout << "Refcount: " << ImgSource.u->refcount << " Adresse du premier pixel: " << hex << ImgDest2.data << endl;
    waitKey(0);

    // Extraction d'une zone d’intérêt
    Mat ImgDest3 = ImgDest1(Range(100,200), Range(0,200));  // Les données ne sont pas copiées (la matrice ImgDest3 pointe vers les pixels de la matrice source).
    imshow("Img Destination 3", ImgDest3);
    cout << "Refcount: " << ImgSource.u->refcount << " Adresse du premier pixel: " << hex << ImgDest3.data << endl;
    waitKey(0);

    Mat ImgGray;
    Mat ImgDest4 = ImgSource(Rect(100, 300, 25 , 25));
    cvtColor( ImgDest4, ImgGray, CV_RGB2GRAY);
//    cout << "Refcount: " << ImgSource.u->refcount << " Adresse du premier pixel: " << hex << (int)ImgDest4.data << endl;
    cout << ImgGray << endl;   // affichage des données numériques sur le terminal
    imshow("Img Gray", ImgGray);
    waitKey(0);

    Mat ImgDest6 = ImgDest3.clone();
    return 0;
}
