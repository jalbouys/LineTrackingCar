#include <iostream>
#include <stdio.h>
#include "Robot.h"
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace std;
using namespace cv;

#define sign(x) ((x) > 0 ? 1 : -1)
 
// Step mooving for object min & max
#define STEP_MIN 5
#define STEP_MAX 100 


#define iLowHBLACK 0;
#define iHighHBLACK  179;

#define iLowSBLACK  0; 
#define iHighSBLACK  50;
 
#define iLowVBLACK 0;
#define iHighVBLACK  100;


#define iLowHBLUE 100;
#define iHighHBLUE 120;

#define iLowSBLUE 120; 
#define iHighSBLUE 255;

#define iLowVBLUE 0;
#define iHighVBLUE 255;

#define iLowHRED 0;
#define iHighHRED 30;

#define iLowSRED 95; 
#define iHighSRED 255;

#define iLowVRED 95;
#define iHighVRED 255;

String color = "BLACK";
clock_t arrivee = 0;

/**
 * Fonction de démonstration
 */
void demoRobot()
{
    Robot robot;
    /*while (true) {
        cout << "Ne bouge pas" << endl;
        robot.sendOrder(0, 0);
        getchar();
        cout << "Roues gauche" << endl;
        robot.sendOrder(0.1, 0);
        getchar();
        cout << "Roues droites" << endl;
        robot.sendOrder(0, 0.1);
        getchar();
        cout << "Roues gauche à contre-sens des droites" << endl;
        robot.sendOrder(-0.1, 0.1);
        getchar();
        cout << "Roues gauche et droite à même allure" << endl;
        robot.sendOrder(0.1, 0.1);
        getchar();
    }*/
	for (char i = 0; i < 100; i++)
	{
		robot.sendBarycenter(i);
		usleep(100000);
	}
	
        //getchar();
}

bool checkYellow(Mat Img)
{
	 int iLowHY = 20;
	 int iHighHY = 30;

	 int iLowSY = 100; 
	 int iHighSY = 255;

	 int iLowVY = 100;
	 int iHighVY = 255;
	 
	 Mat imgThresholdedYellow;
	 
	 inRange(Img, Scalar(iLowHY, iLowSY, iLowVY), Scalar(iHighHY, iHighSY, iHighVY), imgThresholdedYellow);
	       
	  //morphological opening (remove small objects from the foreground)
	  erode(imgThresholdedYellow, imgThresholdedYellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	  dilate( imgThresholdedYellow, imgThresholdedYellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

	  //morphological closing (fill small holes in the foreground)
	  dilate( imgThresholdedYellow, imgThresholdedYellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
	  erode(imgThresholdedYellow, imgThresholdedYellow, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

	 // imshow("Yellow Image", imgThresholdedYellow); //show the thresholded image
	  
	  int nbPixelsY = 0;
	  IplImage *maskY = new IplImage(imgThresholdedYellow);
	  
	  for(int x = 0; x < maskY->width; x++) {
        for(int y = 400; y < maskY->height; y++) { 
 
            // If its a tracked pixel, count it to the center of gravity's calcul
            if(((uchar *)(maskY->imageData + y*maskY->widthStep))[x] == 255) {
                (nbPixelsY)++;
            }
        }
    }
    
    if(nbPixelsY >= 10000 && clock()>= arrivee)
    {
		
		cout << "New Lap" << endl;
		if(color == "BLACK")
		{
			color = "RED";
			arrivee = clock()+(10*CLOCKS_PER_SEC);
			
		}
		else if (color == "RED")
		{
			arrivee = clock()+(10*CLOCKS_PER_SEC);
			color = "BLUE";
			
		}
		else if (color == "BLUE")
		{
			arrivee = clock()+(10*CLOCKS_PER_SEC);
			color = "FINISH";
			return false;
		}
	}
	
	return true;
} 


CvPoint demoCV(VideoCapture cap)
{
    

 

//namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH;
	int iHighH;
	int iLowS;
	int iHighS;
	int iLowV;
	int iHighV;

	if(color == "BLACK")
	{
	 iLowH = iLowHBLACK;
	 iHighH = iHighHBLACK;

	 iLowS = iLowSBLACK; 
	 iHighS = iHighSBLACK;

	 iLowV = iLowVBLACK;
	 iHighV = iHighVBLACK;
	}
	else if(color == "RED")
	{
	 iLowH = iLowHRED;
	 iHighH = iHighHRED;

	 iLowS = iLowSRED; 
	 iHighS = iHighSRED;

	 iLowV = iLowVRED;
	 iHighV = iHighVRED;
	}
	else if(color == "BLUE")
	{
	 iLowH = iLowHBLUE;
	 iHighH = iHighHBLUE;

	 iLowS = iLowSBLUE; 
	 iHighS = iHighSBLUE;

	 iLowV = iLowVBLUE;
	 iHighV = iHighVBLUE;
	}



    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

  Mat imgHSV;

  clock_t debutConvertion = clock();
  cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
  clock_t finConvertion = clock();

  //cout << "Temps converstion :" <<  (double) (finConvertion - debutConvertion) << endl;

  Mat imgThresholded;
	
 clock_t debutBinarisation = clock();
  inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
 clock_t finBinarisation = clock();
 //cout << "Temps binarisation :  " << (double) (finBinarisation - debutBinarisation) << endl;
 
 //cout << "Type de la matrice : " << imgThresholded.type()<<endl; 
  clock_t debutTraitement = clock();
  //morphological opening (remove small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 

  //morphological closing (fill small holes in the foreground)

  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    imgThresholded.type();

  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
 clock_t finTraitement = clock();
  //cout << "Temps Traitement" << (double) (finTraitement-debutTraitement)<< endl;
  //imshow("Thresholded Image", imgThresholded); //show the thresholded image
  //imshow("Original", imgOriginal); //show the original image

    int sommeX = 0, sommeY = 0;
    int nbPixels = 0;
    IplImage *mask = new IplImage(imgThresholded);
    IplImage *image = new IplImage(imgOriginal);
    
    //cvShowImage("Masque", mask);
    clock_t debutBary = clock();
    for(int x = 0; x < mask->width; x++) {
        for(int y = 0; y < mask->height; y++) { 
 
            // If its a tracked pixel, count it to the center of gravity's calcul
            if(((uchar *)(mask->imageData + y*mask->widthStep))[x] == 255) {
                sommeX += x;
                sommeY += y;
                (nbPixels)++;
            }
        }
    }
    clock_t finBary = clock();
    //cout << "Temps calcul barycentre : " << (double) (finBary-debutBary) << endl;
   
     CvPoint barycentre;
    
        // If there is no pixel, we return a center outside the image, else we return the center of gravity
	if(nbPixels > 0)
	{
         barycentre = cvPoint((int)(sommeX / (nbPixels)), (int)(sommeY / (nbPixels)));
	 }
        
    int objectNextStepX, objectNextStepY;
    CvPoint objectNextPos;
    
        // Calculate circle next position (if there is enough pixels)
    if (nbPixels > 10) {
 
        // Reset position if no pixel were found
       /* if (barycentre.x == -1 || barycentre.y == -1) {
            barycentre.x = objectNextPos.x;
            barycentre.y = objectNextPos.y;
        }
 
        // Move step by step the object position to the desired position
        if (abs(barycentre.x - objectNextPos.x) > STEP_MIN) {
            objectNextStepX = max(STEP_MIN, min(STEP_MAX, abs(barycentre.x - objectNextPos.x) / 2));
            //barycentre.x +=(( (-1) * sign(barycentre.x - objectNextPos.x) * objectNextStepX)+(sign(barycentre.x - objectNextPos.x) * objectNextStepX))/2;
        }
        if (abs(barycentre.y - objectNextPos.y) > STEP_MIN) {
            objectNextStepY = max(STEP_MIN, min(STEP_MAX, abs(barycentre.y - objectNextPos.y) / 2));
            //barycentre.y += (-1) * sign(barycentre.y - objectNextPos.y) * objectNextStepY;
        }*/
 
    // -1 = object isn't within the camera range
    } else {
 
        barycentre.x = -1;
        barycentre.y = -1;
 
    }
    /*
    if(nbPixels >10)
		cvDrawCircle(image,barycentre,15,CV_RGB(255,0,0),-1);*/
    // We show the image on the window
    //cvShowImage("GeckoGeek Color Tracking", image);
    

    /*
    if(waitKey(30) == 27)
    {
		break;
	}*/
 
    // We show the image on the window
    //cvShowImage("GeckoGeek Color Tracking", image);
    if(clock() >= arrivee)   
       if(!checkYellow(imgHSV))
       {
		barycentre.x = -1;
		barycentre.y = -1;
	   }
       return barycentre;
    }
    
    

   
}


int main(int argc, char *argv[])
{
    //demoRobot();
    
    bool isArrived = false;
    VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH,480 );
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 320);
    if (!cap.isOpened()) {
        throw string("Unable to open the device");
    } 
    Robot robot;
    int positionXBarycentre;
    
	if (argc == 5)
	{
		float P = atof(argv[1]) * 100;
		float I = atof(argv[2]) * 100;
		float D = atof(argv[3]) * 100;
		float speed = atof(argv[4]);
		//cout << P << " " << I << " " << D << " " << speed << endl;
		robot.sendPIDS(P, I, D, speed);
	}
	
    while(!isArrived)
    {
		positionXBarycentre = (demoCV(cap).x*100)/480;
		cout << positionXBarycentre << endl;
		robot.sendBarycenter(positionXBarycentre);
		if(color == "FINISH")
		{
			isArrived = true;
		}
	}
	
}

