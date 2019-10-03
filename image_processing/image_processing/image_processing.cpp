// image_processing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>

#include "LocalThresholdFilter.h"

int lesson_1() {
	cv::Mat image;
	image = cv::imread("../cat.bmp", cv::IMREAD_COLOR); // Read the file
	if (image.empty()) // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
	cv::imshow("Display window", image); // Show our image inside it.
	cv::waitKey(0); // Wait for a keystroke in the window

	cv::Mat greyscale;
	cv::cvtColor(image, greyscale, cv::COLOR_BGR2GRAY, 0);
	cv::imshow("Display window", greyscale);
	cv::waitKey(0); // Wait for a keystroke in the window

	cv::rectangle(greyscale, cv::Point(1000, 800), cv::Point(600, 600), 150, 10);
	cv::ellipse(greyscale, { 200, 200 }, cv::Size(100, 100), 5, 10, 20, 180);
	cv::imshow("Display window", greyscale);
	cv::waitKey(0); // Wait for a keystroke in the window



	size_t count = 0;
	size_t count_all = 0;
	for (size_t i = 0; i < greyscale.size().height; ++i) {
		for (size_t j = 0; j < greyscale.size().width; ++j) {
			if (greyscale.at<uint8_t>(j, i) > 150) {
				++count;
			}
			++count_all;
		}
	}
	std::cout << std::endl << count << std::endl;
	std::cout << std::endl << count_all << std::endl;
	return 0;
}


void adaptive_thteshold_task() {
	cv::Mat sonnet = cv::imread("../sonnet.png", cv::IMREAD_GRAYSCALE);
	cv::Mat filtered;
	cv::adaptiveThreshold(sonnet, filtered, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 4);

	cv::namedWindow("w1", cv::WINDOW_AUTOSIZE); // Create a window for display.
	cv::imshow("w1", sonnet); // Show our image inside it.
	cv::waitKey(0); // Wait for a keystroke in the window

	cv::imshow("w1", filtered);
	cv::waitKey(0); // Wait for a keystroke in the window

}


cv::Mat alphabeta_correction(cv::Mat& image, double alpha, double beta) {
	cv::Mat res = cv::Mat::zeros(image.size(), CV_8U);
	for (size_t i = 0; i < image.size().height; ++i) {
		for (size_t j = 0; j < image.size().width; ++j) {
			res.at<uint8_t>(j, i) = alpha * image.at<uint8_t>(j, i) + beta;
		}
	}
	return res;
}

cv::Mat get_hist_img(int hist_size, int scale, cv::Mat hist, size_t space_length) {
	double maxVal = 0;
	cv::Mat histImg = cv::Mat::zeros(hist_size * scale, 500, CV_8UC3);

	cv::minMaxLoc(hist, 0, &maxVal, 0, 0);

	for (size_t i = 0; i < hist_size; ++i) {
		float binVal = hist.at<float>(i);
		int intensity = cvRound(binVal * 255 / maxVal);
		rectangle(histImg, cv::Point(i * scale + space_length, 500),
			cv::Point((i + 1) * scale - 1, 500 - intensity),
			cv::Scalar(255, 255, 255),
			-1);
	}
	return histImg;
}

cv::Mat gamma_correction(cv::Mat& image, double gamma) {
	cv::Mat res = cv::Mat::zeros(image.size(), CV_8U);

	for (size_t i = 0; i < image.size().height; ++i) {
		for (size_t j = 0; j < image.size().width; ++j) {
			//uint8_t debug1 = image.at<uint8_t>(j, i);
			//auto debug2 = image.at<uint8_t>(j, i) / 255.0;
			//double debug3 = static_cast<double>(image.at<uint8_t>(j, i));

			res.at<uint8_t>(j, i) = static_cast<uint8_t>(std::pow(static_cast<double>(image.at<uint8_t>(j, i)) / 255.0, gamma) * 255);
		}
	}
	return res;
}

int main(int argc, char** argv)
{
	cv::Mat graycat = cv::imread("../cat.bmp", cv::IMREAD_GRAYSCALE);
	cv::namedWindow("w1", cv::WINDOW_AUTOSIZE); // Create a window for display.
	cv::imshow("w1", graycat); // Show our image inside it.
	cv::waitKey(0); // Wait for a keystroke in the window


	int scale = 2;

	cv::Mat hist;
	int hist_size = 256;
	int channels[] = { 0 };
	float range[] = { 0, 256 };
	const float* histRange = { range };
	cv::calcHist(&graycat, 1, channels, cv::Mat(), hist, 1, &hist_size, &histRange, true, false);


	//cv::Mat histImg = get_hist_img(hist_size, 2, hist, 1);

	//cv::imshow("w1", histImg); // Show our image inside it.
	//cv::waitKey(0); // Wait for a keystroke in the window
	
	//cv::Mat graycat_equalized;
	//cv::equalizeHist(graycat, graycat_equalized);
	//cv::imshow("w1", graycat_equalized); // Show our image inside it.
	//cv::waitKey(0); // Wait for a keystroke in the window

	//cv::imshow("w1",
	//	alphabeta_correction(graycat, 1, 50)
	//);
	//cv::waitKey(0);


	cv::imshow("w1",
		gamma_correction(graycat, 1.3)
	);
	cv::waitKey(0);

}