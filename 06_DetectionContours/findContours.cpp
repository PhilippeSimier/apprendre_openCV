/*************************************************************************************/
/*!
    \file     findContours.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans) <philaure@wanadoo.fr>

    \brief    Trouver les contours des objets (findContours)
    \detail   Cette fonction permet de trouver les contours en remplissant un vecteur de point qui correspond
              aux points qui sont définis sur le contour extérieur de l'objet. En fait plusieurs constantes sont
              définies dans OpenCV et permettent de trouver les points extérieurs de l'objet mais aussi ceux qui
              font parties des trous internes de l'objet. On peut aussi vouloir créer une hiérarchie d'objet en
	      passant au travers une liste des contours extérieurs jusqu'au contours intérieurs.


    \compilation
	      g++ $(pkg-config --libs --cflags opencv) -o findContours  findContours.cpp

    \version    1.0 - First release
*/
/**************************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int seuilA = 5;


int main(int argc,char ** argv)
{
  Mat imgSource, image_RGB, image_gray, image_CNY;
  vector<vector<Point> > contours;      // contours est un vecteur de vecteurs de points
  vector<Vec4i> hierarchy;
  RNG rng(12345);

  double largeur,hauteur;


    imgSource = imread("blob.jpg", CV_LOAD_IMAGE_COLOR);
    if (!imgSource.data) {
      	cerr << "ERREUR: Impossible d'ouvrir le fichier" << endl;
    	return -1;
    }

    blur( imgSource, imgSource, Size(5,5) );
    cvtColor( imgSource, image_gray, CV_RGB2GRAY);
    threshold(image_gray, image_gray, 230, 255, CV_THRESH_BINARY_INV);
    Canny( image_gray, image_CNY, seuilA,2 * seuilA, 3, true );
    imshow("Canny", image_CNY);

    // findContours( image_CNY, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    findContours( image_CNY, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE );
    cout << "Nombre d'objets trouvés :" << contours.size() << endl;

    // Dessine les  contours des objets trouvés
    /* La fonction drawContours permet  de tracer les contours qui ont été trouvés. On parcours le 
	vecteur contours et pour chaque objet trouvé, on dessine la séquence de points de l'objet.
    */
    Mat drawing = Mat::zeros( image_CNY.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
       	Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       	drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, Point() );
	imshow("contours", drawing);
	cout << "Objet id : " << i << " perimetre : " << arcLength(contours[i], true) << " Aire : " << contourArea(contours[i]) << endl;
	waitKey(0);
    }

    destroyAllWindows();
    cout << "bye!" <<endl;

  return 0;
}
