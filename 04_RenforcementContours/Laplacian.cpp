/*************************************************************************************/
/*!
    \file     Laplacian.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans) <philaure@wanadoo.fr>

    \brief    Programme pour tester le renforcement des contours par la méthode de Laplace
    \detail   le filtre Laplacien est un filtre de convolution particulier utilisé pour mettre en valeur les détails qui
              ont une variation rapide de luminosité. Il est donc idéal pour rendre visible les contours des objets.
	      Le laplacien est la somme des dérivées secondes d'une image suivant x et y.
              On peut obtenir la dérivée seconde (soit le laplacien) avec une bonne approximation grace au noyau de
	      convolution suivant :

		1  1  1
		1 -8  1
                1  1  1

              Il peut être utilisé pour rendre plus net les contours d'une image.
              Pour cela, on soustrait à l'image une fraction du laplacien.

    \compilation
	      g++  Laplacian.cpp -o Laplacian `pkg-config --cflags --libs opencv`

    \version    1.0 - First release
*/
/**************************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc,char ** argv)
{
    Mat image, image1;
    double largeur,hauteur;

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "ERREUR: Impossible d'ouvrir la camera" << endl;
        return -1;
    }

    largeur = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    hauteur = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    cout << "Taille image : " << largeur << " x " << hauteur << endl;

    cout << "Démarrage de la capture, appuyer sur la touche Echape du clavier pour quitter" << endl;
    do{
        cap >> image;
        if (image.empty()) {
            cerr << "ERREUR: Impossible de capturer une image" << endl;
            return -1;
        }


        cvtColor( image, image1, CV_RGB2GRAY);	// Conversion en niveau de gris
        blur( image1, image, Size( 5, 5 ));   	// applique une matrice de convolution de 5 par 5 pour le blur
        Laplacian( image, image1, CV_16S, 3, 1, 0, BORDER_DEFAULT );  // applique le Laplacian
        convertScaleAbs( image1, image );
        imshow("Laplacian", image);
        threshold(image, image1, 20, 255, THRESH_BINARY);
        imshow("Laplacian plus threshold", image1);
    }
    while(waitKey(1) != 27);

    cout << "Fermeture de la  camera" << endl;
    cap.release();
    destroyAllWindows();
    cout << "bye!" <<endl;
    return 0;
}
