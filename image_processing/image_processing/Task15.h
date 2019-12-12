#pragma once
#include "ITask.h"

#include <opencv2/video/background_segm.hpp>



class Task15 :
	public ITask
{
public:
	Task15() = default;
	~Task15() = default;

	void run() const override;
};

inline void Task15::run() const
{

	cv::Ptr<cv::BackgroundSubtractor> pBackSub;
	
	pBackSub = cv::createBackgroundSubtractorKNN();

	cv::VideoCapture capture("../vtest.avi");
	cv::Mat test;
	capture.read(test);
	cv::imshow("test", test);
	cv::waitKey(0);

	cv::Mat frame, fgMask;
	while (true) {
		capture >> frame;
		if (frame.empty())
			break;
		//update the background model
		pBackSub->apply(frame, fgMask);
		//get the frame number and write it on the current frame
		rectangle(frame, cv::Point(10, 2), cv::Point(100, 20),
			cv::Scalar(255, 255, 255), -1);
		std::stringstream ss;
		ss << capture.get(cv::CAP_PROP_POS_FRAMES);
		std::string frameNumberString = ss.str();
		putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
			cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
		//show the current frame and the fg masks
		imshow("Frame", frame);
		imshow("FG Mask", fgMask);
		//get the input from the keyboard
		int keyboard = cv::waitKey(30);
		if (keyboard == 'q' || keyboard == 27)
			break;
	}
	
	
}

