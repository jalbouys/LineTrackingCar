#include <iostream>
#include <stdio.h>
#include "Robot.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/**
 * Fonction de démonstration
 */
void demoRobot()
{
    Robot robot;
    while (true) {
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
    }
}

void demoCV()
{
    VideoCapture cap(1);

    if (!cap.isOpened()) {
        cout << "Unable to open the device" << endl;
        return;
    }   

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

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }

   
}

int main(int argc, char *argv[])
{
    // demoRobot();
    demoCV();
}
