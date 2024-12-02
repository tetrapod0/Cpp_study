
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>


#include "opencv2/videoio.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

int main()
{
	cv::VideoCapture cap(0);
	//cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
	cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
	//std::cout << "MJPG: " << cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
	//cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
	//cap.set(cv::CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G')););


	//if (!cap.isOpened()) {	// isOpened() : 카메라 정보가 있는지 없는지 (1: 있다, 0: 없다)
	//	printf("Can't open the camera");
	//	return -1;
	//}
	//printf("asdf");

	cv::Mat img;


	while (true) {

		//cap.open(0);
		//cap >> img;

		cap >> img;

		//cap.retrieve(img);
		//cap.grab();




		if (!img.data) {
			std::cout << "Image not loaded";
			return -1;
		}
		//cap.release();

		printf("%d, %d\n", img.cols, img.rows);

		cv::imshow("camera img", img);
		cv::waitKey(0);

		//if (cv::waitKey(1) == 'q') break;
	}

	return 0;
}