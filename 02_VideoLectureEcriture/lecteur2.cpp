/***********************************************************************************************/
/*!
    \file     lecteur2.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans) <philippe.simier@ac-nantes.fr>
    \brief    Programme pour lire et afficher un flux vidéo à partir d'un fichier vidéo uniquement
    \detail   Ce programme ouvre le flux vidéo issu d'un fichier
	      ce programme s'inspire de l'exemple 4 du chapitre 2 du livre learning openCV
	      de Gary Bradski aux éditions Oreilly
    \compilation
	      g++ $(pkg-config --libs --cflags opencv) -o lecteur2 lecteur2.cpp
              g++ -ggdb lecteur2.cpp -o lecteur2 `pkg-config --cflags --libs opencv`

    \version    1.0 - First release
    \exécution	./lecteur2 chaplin.mp4

*/
/*************************************************************************************************/

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int slider_position = 0;
int run = 1, dontset = 0; //start out in single step mode
int current_pos = 0;
VideoCapture cap;

void onTrackbarSlide( int pos, void *) {

    cap.set( CV_CAP_PROP_POS_FRAMES, pos );
    current_pos = pos;
    if( !dontset ) run = 1;
    dontset = 0;
}

void help(char** argv ) {
	cout << "\n"
	<< "Ajout d'un trackbar pour se déplacer dans une vidéo\n"
	<< argv[0] <<" <path/video>\n"
	<< "Par exemple:\n"
	<< argv[0] << " chaplin.mp4\n"
	<< endl;
}

int main( int argc, char** argv ) {

    if (argc != 2) {
	help(argv);
	return 0;
    }

    namedWindow( "lecteur2", cv::WINDOW_AUTOSIZE );

    cap.open( string(argv[1]) );

    int frames = (int) cap.get( CV_CAP_PROP_FRAME_COUNT  );
    int tmpw   = (int) cap.get( CV_CAP_PROP_FRAME_WIDTH  );
    int tmph   = (int) cap.get( CV_CAP_PROP_FRAME_HEIGHT );

    cout << "La video a " << frames << " frames de dimensions("
       << tmpw << ", " << tmph << ")." << endl;

    if(frames == 0){
	frames = 100;
    }
    createTrackbar( "Position",  "lecteur2",  &slider_position, frames, onTrackbarSlide );

    Mat frame;

    current_pos = (int)cap.get( CV_CAP_PROP_POS_FRAMES );
    int fps = (int)cap.get(CAP_PROP_FPS);
    int delai = 1000/fps;

    for(;;) {

    if( run != 0 ) {
      	cap >> frame;

  	if(frame.empty()) break;

 	current_pos +=1;
        dontset = 1;
        if ((current_pos % fps) == 0){
        	setTrackbarPos("Position", "lecteur2", current_pos);
		delai = 1;
        }
        else
		delai = 1000/fps;

        imshow( "lecteur2", frame );
        run-=1;
    }

    char c = (char) waitKey(delai);

    if( c == 's' ) { // un seul pas
      	    run = 1;
            cout << "mode pas à pas, run = " << run << endl;
    }

    if( c == 'r' ) { // mode lecture
            run = -1;
            cout << "mode lecture, run = " << run <<endl;
       	}

    if( c == 27 ) break;
  }

  return(0);

}

