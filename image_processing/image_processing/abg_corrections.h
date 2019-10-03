#pragma once


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


cv::Mat alphabeta_correction(cv::Mat& image, double alpha, double beta);

cv::Mat gamma_correction(cv::Mat& image, double gamma);

