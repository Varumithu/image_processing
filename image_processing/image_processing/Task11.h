#pragma once
#include "ITask.h"


class Task11 final :
	public ITask
{
public:
	Task11() = default;
	~Task11() = default;
	void run() const override
	{
		//! [load_image]
		// Load the image
		cv::Mat src = cv::imread("../coins.bmp");


		// Show source image
		imshow("Source Image", src);
		//! [load_image]

		//! [black_bg]
		// Change the background from white to black, since that will help later to extract
		// better results during the use of Distance Transform
		//for (int i = 0; i < src.rows; i++) {
		//	for (int j = 0; j < src.cols; j++) {
		//		if (src.at<cv::Vec3b>(i, j) == cv::Vec3b(255, 255, 255))
		//		{
		//			src.at<cv::Vec3b>(i, j)[0] = 0;
		//			src.at<cv::Vec3b>(i, j)[1] = 0;
		//			src.at<cv::Vec3b>(i, j)[2] = 0;
		//		}
		//	}
		//}

		// Show output image
		imshow("Black Background Image", src);
		//! [black_bg]

		//! [sharp]
		// Create a kernel that we will use to sharpen our image
		cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
			1, 1, 1,
			1, -8, 1,
			1, 1, 1); // an approximation of second derivative, a quite strong kernel

// do the laplacian filtering as it is
// well, we need to convert everything in something more deeper then CV_8U
// because the kernel has some negative values,
// and we can expect in general to have a Laplacian image with negative values
// BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
// so the possible negative number will be truncated
		cv::Mat imgLaplacian;
		filter2D(src, imgLaplacian, CV_32F, kernel);
		cv::Mat sharp;
		src.convertTo(sharp, CV_32F);
		cv::Mat imgResult = sharp - imgLaplacian;

		// convert back to 8bits gray scale
		imgResult.convertTo(imgResult, CV_8UC3);
		imgLaplacian.convertTo(imgLaplacian, CV_8UC3);

		// imshow( "Laplace Filtered Image", imgLaplacian );
		imshow("New Sharped Image", imgResult);
		//! [sharp]

		//! [bin]
		// Create binary image from source image
		cv::Mat bw;
		cvtColor(imgResult, bw, cv::COLOR_BGR2GRAY);
		threshold(bw, bw, 40, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
		imshow("Binary Image", bw);
		//! [bin]

		//! [dist]
		// Perform the distance transform algorithm
		cv::Mat dist;
		distanceTransform(bw, dist, cv::DIST_L2, 3);

		// Normalize the distance image for range = {0.0, 1.0}
		// so we can visualize and threshold it
		normalize(dist, dist, 0, 1.0, cv::NORM_MINMAX);
		imshow("Distance Transform Image", dist);
		//! [dist]

		//! [peaks]
		// Threshold to obtain the peaks
		// This will be the markers for the foreground objects
		threshold(dist, dist, 0.2, 1, cv::THRESH_BINARY);

		// Dilate a bit the dist image
		cv::Mat kernel1 = cv::Mat::ones(3, 3, CV_8U);
		dilate(dist, dist, kernel1);
		imshow("Peaks", dist);
		//! [peaks]

		//! [seeds]
		// Create the CV_8U version of the distance image
		// It is needed for findContours()
		cv::Mat dist_8u;
		dist.convertTo(dist_8u, CV_8U);

		// Find total markers
		std::vector<std::vector<cv::Point> > contours;
		findContours(dist_8u, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		// Create the marker image for the watershed algorithm
		cv::Mat markers = cv::Mat::zeros(dist.size(), CV_32S);

		// Draw the foreground markers
		for (size_t i = 0; i < contours.size(); i++)
		{
			drawContours(markers, contours, static_cast<int>(i), cv::Scalar(static_cast<int>(i) + 1), -1);
		}

		// Draw the background marker
		circle(markers, cv::Point(5, 5), 3, cv::Scalar(255), -1);
		//imshow("Markers", markers * 10000);
		//! [seeds]

		//! [watershed]
		// Perform the watershed algorithm
		watershed(imgResult, markers);

		cv::Mat mark;
		markers.convertTo(mark, CV_8U);
		bitwise_not(mark, mark);
		//    imshow("Markers_v2", mark); // uncomment this if you want to see how the mark
		// image looks like at that point

		// Generate random colors
		std::vector<cv::Vec3b> colors;
		for (size_t i = 0; i < contours.size(); i++)
		{
			int b = cv::theRNG().uniform(0, 256);
			int g = cv::theRNG().uniform(0, 256);
			int r = cv::theRNG().uniform(0, 256);

			colors.push_back(cv::Vec3b((uchar)b, (uchar)g, (uchar)r));
		}

		// Create the result image
		cv::Mat dst = cv::Mat::zeros(markers.size(), CV_8UC3);

		// Fill labeled objects with random colors
		for (int i = 0; i < markers.rows; i++)
		{
			for (int j = 0; j < markers.cols; j++)
			{
				int index = markers.at<int>(i, j);
				if (index > 0 && index <= static_cast<int>(contours.size()))
				{
					dst.at<cv::Vec3b>(i, j) = colors[index - 1];
				}
			}
		}

		// Visualize the final image
		imshow("Final Result", dst);
		//! [watershed]

		cv::waitKey();
	}
};

