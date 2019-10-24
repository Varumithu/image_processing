#include "Task01.h"

#include <iostream>


void Task01::run() const
{
	const cv::Mat image = cv::imread("../cat.bmp", cv::IMREAD_COLOR); // Read the file
	if (image.empty()) // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		throw -1;
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
}
