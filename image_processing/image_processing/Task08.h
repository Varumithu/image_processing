#pragma once
#include "ITask.h"


class Task08 :
	public ITask
{
public:
	Task08() = default;
	~Task08() = default;
	void run() const override
	{
		cv::Mat image = cv::imread("../building.jpg", cv::IMREAD_GRAYSCALE);
		cv::imshow("image", image);
		cv::waitKey(0);
		std::vector<cv::Vec2f> lines;
		cv::Mat cannied;
		cv::Canny(image, cannied, 50, 200, 3);
		cv::Mat lines_image = cv::Mat::zeros(image.size(), CV_8UC3);
		cv::HoughLines(cannied, lines, 1, CV_PI / 180, 200, 0, 0);
		cv::cvtColor(image, lines_image, cv::COLOR_GRAY2BGR);
		for (size_t i = 0; i < lines.size(); i++)
		{
			float rho = lines[i][0], theta = lines[i][1];
			cv::Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a * rho, y0 = b * rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(lines_image, pt1, pt2, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
		}
		cv::imshow("lines", lines_image);
		cv::waitKey(0);

		std::vector<cv::Vec4i> lines_p;
		cv::HoughLinesP(cannied, lines_p, 1, CV_PI / 180, 50, 10, 5);
		cv::Mat lines_p_image;
		cv::cvtColor(image, lines_p_image, cv::COLOR_GRAY2BGR);

		for (size_t i = 0; i < lines_p.size(); ++i)
		{
			cv::line(lines_p_image, cv::Point(lines_p[i][0], lines_p[i][1]), 
									cv::Point(lines_p[i][2], lines_p[i][3]), 
				cv::Scalar(0, 0, 255), 1);
			
		}
		cv::imshow("lines", lines_p_image);
		cv::waitKey(0);
	}
};

