#pragma once
#include "ITask.h"

int thresh = 200;

cv::RNG rng(12345);


inline void run_subroutine(int, void*)
{
	cv::Mat image = cv::imread("../building.jpg", cv::IMREAD_GRAYSCALE);

	cv::Mat corners;
	cv::cornerHarris(image, corners, 3, 3, 0.04);

	//cv::imshow("corners", corners);
	//cv::waitKey(0);

	cv::Mat dst_norm, dst_norm_scaled;
	normalize(corners, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
	//corners.copyTo(dst_norm);
	convertScaleAbs(dst_norm, dst_norm_scaled);

	cv::imshow("corners", dst_norm_scaled);

	for (int i = 0; i < dst_norm.rows; i++)
	{
		for (int j = 0; j < dst_norm.cols; j++)
		{
			if ((int)dst_norm.at<float>(i, j) > thresh)
			{
				cv::circle(image, cv::Point(j, i), 5, cv::Scalar(0, 0, 255), 2, 8, 0);
			}
		}
	}

	cv::imshow("image corners", image);
}

inline void shi_tomasi_subroutine(int, void*)
{
	cv::Mat image = cv::imread("../building.jpg", cv::IMREAD_GRAYSCALE);

	cv::imshow("image", image);
	cv::Mat drawable = image.clone();
	cv::imshow("image", drawable);
	cv::warpAffine(image, drawable, cv::getRotationMatrix2D({ static_cast<float>(image.cols) / 2, static_cast<float>(image.rows) / 2 },
		40, 1), image.size());

	cv::Mat warp = cv::Mat::eye(3, 3, CV_32F);
	cv::Point2f persp_src[] { {0, 0}, {1, 1}, {2, 2}, {10, 100}};
	cv::Point2f persp_dst[] { {4, 0}, {2, 1}, {11, 2}, {100, 10} };
	warp = cv::getPerspectiveTransform(persp_src, persp_dst);
	
	cv::warpPerspective(drawable, drawable, warp, image.size(), cv::INTER_LINEAR);
	cv::imshow("drawable", drawable);

	
	int maxCorners = thresh;
	std::vector<cv::Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3, gradientSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	cv::Mat copy = drawable.clone();
	goodFeaturesToTrack(drawable,
		corners,
		maxCorners,
		qualityLevel,
		minDistance,
		cv::Mat(),
		blockSize,
		gradientSize,
		useHarrisDetector,
		k);
	std::cout << "** Number of corners detected: " << corners.size() << std::endl;
	int radius = 4;
	for (size_t i = 0; i < corners.size(); i++)
	{
		circle(copy, corners[i], radius, cv::Scalar(0, 0, 255), cv::FILLED);
	}
	imshow("image", copy);
}

class Task13 :
	public ITask
{
public:
	Task13() = default;
	~Task13() = default;
	void run() const override
	{

		cv::namedWindow("image");
		cv::createTrackbar("Threshold: ", "image", &thresh, 1000, shi_tomasi_subroutine);

		shi_tomasi_subroutine(0, 0);

		cv::waitKey(0);
	}


	
};

