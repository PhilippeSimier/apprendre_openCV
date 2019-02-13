/**
 * OpenCV SimpleBlobDetector Example
 *
 * Programme original écrit par Satya Mallick <spmallick@gmail.com>
 * Merci à lui pour toute l'aide qu'il m'a apportée.
 * Compilation
 *      g++ bee.cpp -o bee `pkg-config --cflags --libs opencv`
 */

#include "opencv2/opencv.hpp"
#include <sstream>
#include <string>

using namespace cv;
using namespace std;



void showControle(int *seuil1, int *seuil2, int *seuil3){
  //Création des trackbars dans la fenêtre "Control"
  namedWindow("Control",1);
  cvCreateTrackbar("minThreshold", "Control", seuil1, 255);
  cvCreateTrackbar("maxThreshold", "Control", seuil2, 255);
  cvCreateTrackbar("minArea", "Control", seuil3, 5000);
}

string intToString(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}

int main( int argc, char** argv )
{

	int minThreshold = 25;
        int maxThreshold = 250;
        int minArea = 2200;
	showControle(&minThreshold, &maxThreshold, &minArea);

	// Lecture du fichier image
	Mat im = imread( "bees.jpg", IMREAD_GRAYSCALE );

	// Initialisation des parametres d'un  SimpleBlobDetector.
	SimpleBlobDetector::Params params;

    do{
	// Définition du niveau seuillage
	params.minThreshold = minThreshold;
	params.maxThreshold = maxThreshold;

	// Filtrage par aire
	params.filterByArea = true;
	params.minArea = minArea;

	// Filtrage par Circularité
	params.filterByCircularity = false;
	params.minCircularity = 0.1;

	// Filtrage par Convexité
	params.filterByConvexity = false;
	params.minConvexity = 0.87;

	// Filtrage par rapport Inertie
	params.filterByInertia = false;
	params.minInertiaRatio = 0.01;

	// Tableau de points clés
	vector<KeyPoint> keypoints;

	// création d'un SimpleBlobDetector avec ses paramètres
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
	// Appel de la méthode detect pour obtnenir la position des blobs
	detector->detect( im, keypoints);


	// Dessine un cercle jaune pour chaque blobs détectés.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
	// Le centre et le diametre du cercle correspond à la position et à la taille du  blob

	Mat im_with_keypoints;
	drawKeypoints( im, keypoints, im_with_keypoints, Scalar(0,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

	// Affichage des blobs avec en légende le nb de blobs détectés
        putText(im_with_keypoints, "Nb : " + intToString(keypoints.size()), Point(20, 20), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,0,0), 2.0);
	imshow("keypoints", im_with_keypoints );

        // Affichage en console des coordonées
        for (unsigned i = 0; i < keypoints.size(); i++){
             cout << i << " : " << keypoints.at(i).pt.x << " " << keypoints.at(i).pt.y << endl;
        }
        cout << endl;


	}
  while(waitKey(0) != 27);

}

