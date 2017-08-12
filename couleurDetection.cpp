/*************************************************************************************/
/*!
    \file     couleurDetection.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)

    \brief    Programme pour tester la détection de couleur avec openCV 3 et la raspiCam
    \detail   Ce programme ouvre la camera puis affiche l'image obtenue avec threshold
	      https://www.youtube.com/watch?v=bSeFrPrqZ2A

    \compilation
	      g++ $(pkg-config --libs --cflags opencv) -o couleurDetection  couleurDetection.cpp

    \version    1.0 - First release
*/
/**************************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

//minimum and maximum object area
const int MIN_OBJECT_AREA = 20*20;
const int MAX_OBJECT_AREA = 5;
const int FRAME_HEIGHT = 380;
const int FRAME_WIDTH = 480;
const int MAX_NUM_OBJECTS=50;

string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}

void drawObject(int x, int y,Mat &frame){

   //use some of the openCV drawing functions to draw crosshairs

    circle(frame,Point(x,y),20,Scalar(0,255,0),2);
    if(y-25>0)
    line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
    if(y+25<FRAME_HEIGHT)
    line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(x,FRAME_HEIGHT),Scalar(0,255,0),2);
    if(x-25>0)
    line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
    if(x+25<FRAME_WIDTH)
    line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(FRAME_WIDTH,y),Scalar(0,255,0),2);

	putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);

}

void morphOps(Mat &thresh){
  Mat erodeElement = getStructuringElement( MORPH_RECT, Size(3,3));
  Mat dilateElement = getStructuringElement( MORPH_RECT, Size(8,8));

  erode(thresh, thresh,erodeElement);
  erode(thresh, thresh,erodeElement);

  dilate(thresh, thresh,dilateElement);
}

void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed){

  Mat temp;
  threshold.copyTo(temp);
  //these two vectors needed for output of findContours
  vector< vector<Point> > contours;
  vector<Vec4i> hierarchy;
  //find contours of filtered image using openCV findContours function
  findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
  //use moments method to find our filtered object
  double refArea = 0;
  bool objectFound = false;
  if (hierarchy.size() > 0) {
    int numObjects = hierarchy.size();
    //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
      if(numObjects<MAX_NUM_OBJECTS){
	for (int index = 0; index >= 0; index = hierarchy[index][0]) {

        	Moments moment = moments((cv::Mat)contours[index]);
		double area = moment.m00;
			//if the area is less than 20 px by 20px then it is probably just noise
			//if the area is the same as the 3/2 of the image size, probably just a bad filter
			//we only want the object with the largest area so we safe a reference area each
			//iteration and compare it to the area in the next iteration.
                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
			x = moment.m10/area;
			y = moment.m01/area;
			objectFound = true;
			refArea = area;
		}else objectFound = false;


	}
	//let user know you found an object
	if(objectFound ==true){
		putText(cameraFeed,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
		//draw object location on screen
		drawObject(x,y,cameraFeed);}
	}else
		putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
	}
}

int main(int argc,char ** argv)
{
  bool useMorphOps = true;
  bool trackObjets = true;
  Mat image, image1, image2, imageHSV;
  double largeur,hauteur;
  //x and y values for the location of the object
  int x=0, y=0;



  VideoCapture cap(0);
  if (!cap.isOpened()) {
    cerr << "ERREUR: Impossible d'ouvrir la camera" << endl;
    return -1;
  }

  largeur = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  hauteur = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  cout << "Taille image : " << largeur << " x " << hauteur << endl;

  cout << "Démarrage de la capture, appuyer sur une touche du clavier pour quitter" << endl;
  namedWindow("Control",1);

  int iLowH = 39;
  int iHighH = 54;  // teinte verte

  int iLowS = 143;
  int iHighS = 255;

  int iLowV = 78;
  int iHighV = 255;

  //Create trackbars in "Control" window
  cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
  cvCreateTrackbar("HighH", "Control", &iHighH, 179);

  cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
  cvCreateTrackbar("HighS", "Control", &iHighS, 255);

  cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
  cvCreateTrackbar("HighV", "Control", &iHighV, 255);

  do{
    cap >> image;
    if (image.empty()) {
        cerr << "ERREUR: Impossible de capturer une image" << endl;
        return -1;
    }

    flip( image, image1, -1); // mirroir horizontal
    cvtColor( image1, imageHSV, CV_BGR2HSV);
    inRange(imageHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), image2);

    // Morphological Operation
    if (useMorphOps){
	morphOps(image2);
    }

    if (trackObjets){
    	trackFilteredObject(x,y,image2,image1);
    }
    imshow("morpho", image2);
    imshow("couleur", image1);
  }
  while(waitKey(25) !='x');

  cout << "Fermeture de la  camera" << endl;
  cap.release();
  destroyAllWindows();
  cout << "bye!" <<endl;
  return 0;
}
