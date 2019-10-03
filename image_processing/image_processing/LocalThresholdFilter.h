#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>



class LocalThresholdFilter
{
public:

	cv::Mat image;
	size_t range;
	LocalThresholdFilter(cv::Mat& image, size_t range) : image(image), range(range) {}
	
	void filter();

	~LocalThresholdFilter() = default;
};

