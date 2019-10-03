#include "Task02.h"

void Task02::run()
{
	const cv::Mat sonnet = cv::imread("../sonnet.png", cv::IMREAD_GRAYSCALE);
	cv::Mat filtered;
	cv::adaptiveThreshold(sonnet, filtered, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 4);

	cv::namedWindow("w1", cv::WINDOW_AUTOSIZE); // Create a window for display.
	cv::imshow("w1", sonnet); // Show our image inside it.
	cv::waitKey(0); // Wait for a keystroke in the window

	cv::imshow("w1", filtered);
	cv::waitKey(0); // Wait for a keystroke in the window
}
