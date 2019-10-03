#include "abg_corrections.h"


cv::Mat alphabeta_correction(cv::Mat& image, double alpha, double beta)
{
	cv::Mat res = cv::Mat::zeros(image.size(), CV_8U);
	for (size_t i = 0; i < image.size().height; ++i) {
		for (size_t j = 0; j < image.size().width; ++j) {
			res.at<uint8_t>(j, i) = alpha * image.at<uint8_t>(j, i) + beta;
		}
	}
	return res;
}

cv::Mat gamma_correction(cv::Mat& image, double gamma)
{
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
