#include <iostream>
#include <stdio.h>
#include "Robot.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define sign(x) ((x) > 0 ? 1 : -1)
 
// Step mooving for object min & max
#define STEP_MIN 5
#define STEP_MAX 100 

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

CvPoint demoCV(VideoCapture cap)
{
    

 

//namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

 int iLowH = 102;
 int iHighH = 120;

 int iLowS = 60; 
 int iHighS = 255;

 int iLowV = 0;
 int iHighV = 255;



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

  cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
 
  Mat imgThresholded;

  inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
  //morphological opening (remove small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

  //morphological closing (fill small holes in the foreground)
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

  imshow("Thresholded Image", imgThresholded); //show the thresholded image
  imshow("Original", imgOriginal); //show the original image

    int sommeX = 0, sommeY = 0;
    int nbPixels = 0;
    IplImage *mask = new IplImage(imgThresholded);
    IplImage *image = new IplImage(imgOriginal);
    
    cvShowImage("Masque", mask);
    
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
    
     CvPoint barycentre;
    
        // If there is no pixel, we return a center outside the image, else we return the center of gravity
	if(nbPixels > 0)
	{
         barycentre = cvPoint((int)(sommeX / (nbPixels)), (int)(sommeY / (nbPixels)));
	 }
    else
        cout << "out of picture" << endl;
    
    int objectNextStepX, objectNextStepY;
    CvPoint objectNextPos;
    
        // Calculate circle next position (if there is enough pixels)
    if (nbPixels > 10) {
 
        // Reset position if no pixel were found
        if (barycentre.x == -1 || barycentre.y == -1) {
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
        }
 
    // -1 = object isn't within the camera range
    } else {
 
        barycentre.x = -1;
        barycentre.y = -1;
 
    }
 
    // Draw an object (circle) centered on the calculated center of gravity
    if (nbPixels > 10)
        cvDrawCircle(image, barycentre, 15, CV_RGB(255, 0, 0), -1);
 
    // We show the image on the window
    cvShowImage("GeckoGeek Color Tracking", image);

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
       
       return barycentre;
    }

   
}


int main(int argc, char *argv[])
{
    demoRobot();
    /*
    VideoCapture cap(1);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    if (!cap.isOpened()) {
        throw string("Unable to open the device");
    } 
    Robot robot;
    int positionXBarycentre;
    
    while(true)
    {
		positionXBarycentre = (demoCV(cap).x*100)/640;
		cout << positionXBarycentre << endl;
		robot.sendBarycenter(demoCV(cap));
	}*/
}

