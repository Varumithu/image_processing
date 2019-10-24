#pragma once
#include "ITask.h"

#include <stdlib.h>
#include <time.h>

class Task07 :
	public ITask
{
public:
	Task07() = default;
	virtual ~Task07() = default;

	inline void run() const override
	{
		cv::Mat image = cv::imread("../Lenna.png", cv::IMREAD_GRAYSCALE);
		cv::Mat noise = cv::Mat::zeros(image.size(), CV_8U);
		//cv::namedWindow("w1", cv::WINDOW_GUI_NORMAL);
		//cv::namedWindow("w2", cv::WINDOW_GUI_NORMAL);
		//
		cv::imshow("image", image);
		cv::waitKey(0);
	
		cv::Mat images[10];
		
		
		for (size_t i = 0; i < 10; ++i)
		{
			image.copyTo(images[i]);
			//noise = cv::Mat::zeros(image.size(), CV_8U);
			srand(time(nullptr));

			for (size_t j = 0; j < images[i].size().height; ++j)
			{
				for (size_t k = 0; k < images[i].size().width; ++k)
				{
					srand(time(nullptr));
					images[i].at<uint8_t>(j, k) += rand() % 50;
				}
			}
			//cv::imshow("noise" + static_cast<char>(i), images[i]);
			//cv::waitKey(0);
		}
		cv::Mat filtered = cv::Mat::zeros(image.size(), image.type());

		cv::imshow("noise", images[0]);
		cv::waitKey(0);
		
		for (size_t i = 0; i < image.size().height; ++i)
		{
			for (size_t j = 0; j < image.size().width; ++j)
			{
				double sum = 0;
				for (size_t k = 0; k < 10; ++k)
				{
					sum += static_cast<double>(images[k].at<uint8_t>(i, j));
				}
				image.at<uint8_t>(i, j) = static_cast<uint8_t>(sum / static_cast<double>(10));
			}
		}
		
		cv::imshow("filtered", image);
		cv::waitKey(0);

	}

};

