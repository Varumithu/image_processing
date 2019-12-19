#pragma once
#include "ITask.h"

#include "opencv2/xfeatures2d.hpp"
#include <opencv2/features2d.hpp>

class Task13_b :
	public ITask
{
public:
	void run() const override
	{
		auto orb = cv::ORB::create();
		cv::Mat img1 = imread("../building.jpg", cv::IMREAD_GRAYSCALE);
		cv::Mat img2 = cv::Mat::zeros(img1.size(), img1.type());

		cv::Mat output();
		
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

		//# find the keypointsand descriptors with ORB
		//	kp1, des1 = orb.detectAndCompute(img1, None)
		//	kp2, des2 = orb.detectAndCompute(img2, None)
		std::vector<cv::KeyPoint> kp1, kp2;
		cv::Mat des1, des2;
		orb->detectAndCompute(img1, cv::Mat(), kp1, des1);
		orb->detectAndCompute(img2, cv::Mat(), kp2, des2);

		auto bf = cv::BFMatcher(cv::NORM_HAMMING, true);

		std::vector<cv::DMatch> matches;
		
		bf.match(des1, des2, matches);
		
	/*	# Sort them in the order of their distance.
		matches = sorted(matches, key = lambda x : x.distance)
		# Draw first 10 matches.
		img3 = cv.drawMatches(img1, kp1, img2, kp2, matches[:10], None, flags = cv.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
		plt.imshow(img3), plt.show()*/

		std::sort(matches.begin(), matches.end(), [](cv::DMatch a, cv::DMatch b) { return a.distance < b.distance; });
		auto N = 50;
		std::vector<cv::DMatch> matches_first_N;
		for (size_t i = 0; i < N; ++i)
		{
			matches_first_N.push_back(matches[i]);
			if (i == matches.size() - 1){
				break;
			}
		}
		cv::Mat res;
		cv::drawMatches(img1, kp1, img2, kp2, matches_first_N, res);

		cv::imshow("image 1", img1);
		cv::imshow("image 2", img2);
		cv::imshow("result", res);
		cv::waitKey(0);
	}
	
};









//cv::Mat img1 = imread("../building.jpg", cv::IMREAD_GRAYSCALE);
//cv::Mat img2 = cv::Mat::zeros(img1.size(), img1.type());
//cv::Mat warp = cv::Mat::eye(3, 3, CV_32F);
//cv::Point2f persp_src[]{ {0, 0},
//						{static_cast<float>(img1.cols - 1), 0},
//						{0, static_cast<float>(img1.rows - 1)},
//						{static_cast<float>(img1.cols - 1), static_cast<float>(img1.rows - 1)} };
//cv::Point2f persp_dst[]{ {100, 100},
//						{static_cast<float>(img1.cols - 1), 0},
//						{0, static_cast<float>(img1.rows - 1)},
//						{static_cast<float>(img1.cols - 1), static_cast<float>(img1.rows - 1)} };
//warp = cv::getPerspectiveTransform(persp_src, persp_dst);

//cv::warpPerspective(img1, img2, warp, img1.size(), cv::INTER_LINEAR);
////-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
//int minHessian = 400;
//cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create(minHessian);
//std::vector <cv::KeyPoint > keypoints1, keypoints2;
//cv::Mat descriptors1, descriptors2;
//detector->detectAndCompute(img1, cv::noArray(), keypoints1, descriptors1);
//detector->detectAndCompute(img2, cv::noArray(), keypoints2, descriptors2);
////-- Step 2: Matching descriptor vectors with a FLANN based matcher
//// Since SURF is a floating-point descriptor NORM_L2 is used
//cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
//std::vector< std::vector<cv::DMatch> > knn_matches;
//matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);
////-- Filter matches using the Lowe's ratio test
//const float ratio_thresh = 0.7f;
//std::vector<cv::DMatch> good_matches;
//for (size_t i = 0; i < knn_matches.size(); i++)
//{
//	if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
//	{
//		good_matches.push_back(knn_matches[i][0]);
//	}
//}
////-- Draw matches
//cv::Mat img_matches;
//drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_matches, cv::Scalar::all(-1),
//	cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
////-- Show detected matches
//imshow("Good Matches", img_matches);
//cv::waitKey();