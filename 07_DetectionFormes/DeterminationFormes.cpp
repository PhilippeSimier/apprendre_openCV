/*************************************************************************************/
/*!
    \file     DeterminationFormes.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans) <philaure@wanadoo.fr>

    \brief    Détermination des formes géométriques des objets (carre triangle rectangle polygone)
    \detail   Nous allons nous attarder à trouver le nombre de segments qui composent une figure géométrique
	      simple (rectangle, cercle, polygone). Pour ce faire, nous utiliserons à nouveau la fonction
	      findContours pour trouver les contours et nous approximerons le nombre de points qui forment les
	      contours, (la forme est approximée par des segments de droite).
              et pour finir nous déterminerons pour chaque forme, les coordonnées du centre de masse ainsi que
	      l'aire de sa surface.


    \compilation
	      g++ $(pkg-config --libs --cflags opencv) -o DeterminationFormes  DeterminationFormes.cpp

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
    float precision = 0.03;       	  // precision des approximations 3 %

    if (argc == 2) {
    	precision = atof(argv[1]); 
    }

    imgSource = imread("blob2.png", CV_LOAD_IMAGE_COLOR);
    if (!imgSource.data) {
      	cerr << "ERREUR: Impossible d'ouvrir le fichier" << endl;
    	return -1;
    }

    imshow("Original", imgSource);

    cvtColor( imgSource, image_gray, CV_RGB2GRAY);
    threshold(image_gray, image_gray, 230, 255, CV_THRESH_BINARY_INV);
    Canny( image_gray, image_CNY, seuilA,2 * seuilA, 3, true );


    findContours( image_CNY, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE );
    cout << "Nombre d'objets trouvés :" << contours.size() << endl;

    // Dessine les  contours des objets trouvés
    /* La fonction drawContours permet  de tracer les contours qui ont été trouvés. On parcours le
	vecteur contours et pour chaque objet trouvé, on dessine la séquence de points de l'objet.
    */
    Mat drawing = Mat::zeros( image_CNY.size(), CV_8UC3 );
    Mat drawing2 = Mat::zeros( image_CNY.size(), CV_8UC3 );

    vector<Point> approximation;   // Un vecteur de point qui recevra les points approximés

    for( int i = 0; i< contours.size(); i++ )
    {
       	Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       	drawContours( drawing, contours, i, color, 1, CV_AA, hierarchy, 0, Point() );
	imshow("contours", drawing);

	approxPolyDP(contours[i], approximation, arcLength(contours[i], true) * precision, true);
        contours[i] = approximation;

        drawContours( drawing2, contours, i, color, 1, CV_AA, hierarchy, 0, Point() );
        imshow("approximation", drawing2);
        cout << "L'objet id : " << i << " est approximé par " << approximation.size() << " segments" << endl;

        // Calcul des moments
        Moments lesMoments = moments(contours[i], true);
	double Aire = lesMoments.m00;
	double Xcentre = lesMoments.m10 / Aire;
	double Ycentre = lesMoments.m01 / Aire;
	cout << "L'objet id : " << i << " a son centre de masse situé à (" << Xcentre << "," << Ycentre << ") "<< endl;
	cout << "L'objet id : " << i << " a une aire de " << Aire << endl << endl;

	waitKey(0);
    }

    destroyAllWindows();
    cout << "bye!" <<endl;

  return 0;
}
