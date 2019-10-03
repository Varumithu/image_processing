#include "Task05.h"


void Task05::run()
{
	cv::Mat image = cv::imread("../coins.bmp", cv::IMREAD_COLOR);
	cv::namedWindow("w1", cv::WINDOW_KEEPRATIO); // Create a window for display.
	cv::imshow("w1", image); // Show our image inside it.
	cv::waitKey(0); // Wait for a keystroke in the window

	cv::Mat edges;

	cv::Canny(image, edges, 50, 150, 3, false);

	cv::imshow("w1", edges); // Show our image inside it.
	cv::waitKey(0);

	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(edges, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
	cv::drawContours(image, contours, -1, cv::Scalar(255, 0, 0), 1);
	cv::imshow("w1", image); // Show our image inside it.
	cv::waitKey(0); // Wait for a keystroke in the window
}
