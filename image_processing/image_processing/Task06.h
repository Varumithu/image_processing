#pragma once
#include "ITask.h"
class Task06 :
	public ITask
{
public:
	Task06() = default;
	virtual ~Task06() = default;

	inline void run() override
	{
		cv::Mat image = cv::imread("../cat.bmp", cv::IMREAD_GRAYSCALE);
		cv::namedWindow("w1", cv::WINDOW_GUI_NORMAL);
		cv::imshow("w1", image);
		cv::waitKey(0);

		cv::Mat noise = cv::Mat::zeros(image.size(), CV_8U);

		/*cv::randn(noise, 0, 100);*/
		cv::randu(noise, 0, 100);

		cv::Mat noisy;
		image.copyTo(noisy);
		noisy += noise;
		
		cv::imshow("w1", noisy);
		cv::waitKey(0);

		cv::Mat image_gauss_filtered;
		image.copyTo(image_gauss_filtered);
		cv::Mat image_median_filtered;
		image.copyTo(image_median_filtered);
		cv::Mat image_sobel_filtered = cv::Mat::zeros(image.size(), CV_8U);
		cv::Mat image_custom_filtered = cv::Mat::zeros(image.size(), CV_8U);;
		cv::blur(noisy, image_gauss_filtered, cv::Size(10, 10));
		cv::imshow("w1", image_gauss_filtered);
		cv::waitKey(0);

		cv::imshow("w1", noisy);
		cv::waitKey(0);

		cv::medianBlur(noisy, image_median_filtered, 5);
		cv::imshow("w1", image_median_filtered);
		cv::waitKey(0);

		cv::Mat mask = cv::Mat::ones(3, 3, CV_8U);
		
		
		cv::filter2D(noisy, image_custom_filtered, CV_8U, mask);
		cv::imshow("w1", noisy);
		cv::waitKey(0);
		
		
		cv::Sobel(image, image_sobel_filtered, CV_8U, 1, 1, 3);

		cv::imshow("w1", image_sobel_filtered);
		cv::waitKey(0);

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

