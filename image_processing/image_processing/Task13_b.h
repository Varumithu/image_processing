#pragma once
#include "ITask.h"

#include "opencv2/xfeatures2d.hpp"

class Task13_b :
	public ITask
{
public:
	void run() const override
	{
		cv::Mat img1 = imread("../building.jpg", cv::IMREAD_GRAYSCALE);
		cv::Mat img2 = cv::Mat::zeros(img1.size(), img1.type());
		cv::Mat warp = cv::Mat::eye(3, 3, CV_32F);
		cv::Point2f persp_src[]{ {0, 0},
								{static_cast<float>(img1.cols - 1), 0},
								{0, static_cast<float>(img1.rows - 1)},
								{static_cast<float>(img1.cols - 1), static_cast<float>(img1.rows - 1)} };
		cv::Point2f persp_dst[]{ {100, 100},
								{static_cast<float>(img1.cols - 1), 0},
								{0, static_cast<float>(img1.rows - 1)},
								{static_cast<float>(img1.cols - 1), static_cast<float>(img1.rows - 1)} };
		warp = cv::getPerspectiveTransform(persp_src, persp_dst);

		cv::warpPerspective(img1, img2, warp, img1.size(), cv::INTER_LINEAR);
		//-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
		int minHessian = 400;
		cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create(minHessian);
		std::vector <cv::KeyPoint > keypoints1, keypoints2;
		cv::Mat descriptors1, descriptors2;
		detector->detectAndCompute(img1, cv::noArray(), keypoints1, descriptors1);
		detector->detectAndCompute(img2, cv::noArray(), keypoints2, descriptors2);
		//-- Step 2: Matching descriptor vectors with a FLANN based matcher
		// Since SURF is a floating-point descriptor NORM_L2 is used
		cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
		std::vector< std::vector<cv::DMatch> > knn_matches;
		matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);
		//-- Filter matches using the Lowe's ratio test
		const float ratio_thresh = 0.7f;
		std::vector<cv::DMatch> good_matches;
		for (size_t i = 0; i < knn_matches.size(); i++)
		{
			if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
			{
				good_matches.push_back(knn_matches[i][0]);
			}
		}
		//-- Draw matches
		cv::Mat img_matches;
		drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_matches, cv::Scalar::all(-1),
			cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		//-- Show detected matches
		imshow("Good Matches", img_matches);
		cv::waitKey();
	}
	
};

