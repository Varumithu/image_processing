#pragma once
#include "ITask.h"
class Task07 :
	public ITask
{
public:
	Task07() = default;
	virtual ~Task07() = default;

	inline void run() override
	{
		cv::Mat image = cv::imread("../cat.bmp", cv::IMREAD_GRAYSCALE);
		cv::Mat noise = cv::Mat::zeros(image.size(), CV_8U);

		std::vector<cv::Mat> images(10, cv::Mat::zeros(image.size(), image.type()));
		for (size_t i = 0; i < 10; ++i)
		{
			image.copyTo(images[i]);
			noise = cv::Mat::zeros(image.size(), CV_8U);
			cv::randu(noise, 0, 100);
			images[i] += noise;
		}
		cv::Mat average_noise = cv::Mat::zeros(image.size(), image.type());

		for (size_t i = 0; i < images.size(); ++i)
		{
			for (size_t j = 0; j < i; ++j)
			{
				average_noise += (images[i] - images[j]) / (images.size() * (images.size() - 1));
			}
			for (size_t j = i + 1; j < images.size(); ++j)
			{
				average_noise += (images[i] - images[j]) / (images.size() * (images.size() - 1));
			}
		}

		images[0] -= average_noise;
		cv::imshow("w1", images[0]);
		cv::waitKey(0);
	}

};

