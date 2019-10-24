#pragma once
#include "ITask.h"
class Task09 final :
	public ITask
{
public:
	Task09() = default;
	~Task09() = default;
	void run() const override
	{
		cv::Mat image = cv::imread("../coins.bmp", cv::IMREAD_GRAYSCALE);
		cv::imshow("image", image);
		cv::waitKey(0);
		
		std::vector<cv::Vec3f> circles;
		cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT,
			1, 50, 300, 50);
		cv::Mat img;
		cv::cvtColor(image, img, cv::COLOR_GRAY2BGR);
		for (size_t i = 0; i < circles.size(); i++)
		{
			cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			// draw the circle center
			cv::circle(img, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
			// draw the circle outline
			circle(img, center, radius, cv::Scalar(0, 0, 255), 1, 8, 0);
		}

		cv::imshow("circles", img);
		cv:: waitKey(0);
	}
};

