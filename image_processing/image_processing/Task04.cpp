#include "Task04.h"


#include "abg_corrections.h"





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



void Task04::run()
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

	cv::Mat histImg = get_hist_img(hist_size, 2, hist, 1);
	cv::imshow("w1", histImg); // Show our image inside it.
	cv::waitKey(0); // Wait for a keystroke in the window

	cv::Mat graycat_equalized;
	cv::equalizeHist(graycat, graycat_equalized);
	cv::imshow("w1", graycat_equalized); // Show our image inside it.
	cv::waitKey(0); // Wait for a keystroke in the window
	cv::imshow("w1",
		alphabeta_correction(graycat, 1, 50)
	);
	cv::waitKey(0);

	cv::imshow("w1",
		gamma_correction(graycat, 0.8)
	);
	cv::waitKey(0);
}
