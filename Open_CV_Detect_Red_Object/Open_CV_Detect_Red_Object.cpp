#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main()
{
	VideoCapture cap(0);
	if (cap.isOpened() == false)
	{
		cout << "Could Not Open Video File";
		return -1;
	}
	string w = "original";
	namedWindow(w, WINDOW_NORMAL);
	string w1 = "Control";
	namedWindow(w1, WINDOW_NORMAL);

	int low_hue = 0;
	int high_hue = 179;

	int low_satur = 0;
	int high_satur = 255;

	int low_value = 0;
	int high_value = 255;

	createTrackbar("MinH", w1, &low_hue, 179);
	createTrackbar("MaxH", w1, &high_hue, 179);

	createTrackbar("MinS", w1, &low_satur, 255);
	createTrackbar("MaxS", w1, &high_satur, 255);

	createTrackbar("MinV", w1, &low_value, 255);
	createTrackbar("MaxV", w1, &high_value, 255);



	while (true)
	{
		Mat frame;
		bool b =cap.read(frame);
		if (b == false)
		{
			cout << "Could Not Play Video";
			break;
		}
		
		Mat imgHSV;

		cvtColor(frame, imgHSV, COLOR_BGR2HSV);

		Mat imgthresold;

		inRange(imgHSV, Scalar(low_hue, low_satur, low_value), Scalar(high_hue, high_satur, high_satur), imgthresold);

		//Opening on the image
		erode(imgthresold, imgthresold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgthresold, imgthresold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//Closing on the image
		dilate(imgthresold, imgthresold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgthresold, imgthresold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		imshow("Thresold", imgthresold);
		imshow(w, frame);

		if (waitKey(30) == 27)
		{
			break;
		}
		
	}

	return 0;
}