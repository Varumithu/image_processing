#pragma once
#include "ITask.h"

#include <opencv2/video/tracking.hpp>


cv::Point2f point;
bool addRemovePt = false;
static void onMouse(int event, int x, int y, int /*flags*/, void* /*param*/)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		point = cv::Point2f((float)x, (float)y);
		addRemovePt = true;
	}
}

class Task16 :
	public ITask
{
public:
	Task16() = default;
	~Task16() = default;

	void run() const override
	{
		cv::VideoCapture cap("../vtest.avi");
		cv::TermCriteria termcrit(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20, 0.03);
		cv::Size subPixWinSize(10, 10), winSize(31, 31);
		const int MAX_COUNT = 500;
		bool needToInit = false;
		bool nightMode = false;
		


		cv::namedWindow("LK Demo", 1);
		cv::setMouseCallback("LK Demo", onMouse, 0);
		cv::Mat gray, prevGray, image, frame;
		std::vector<cv::Point2f> points[2];
		std::vector<std::vector<cv::Point2f>> lines;
		for (;;)
		{
			cap >> frame;
			if (frame.empty())
				break;
			frame.copyTo(image);
			cvtColor(image, gray, cv::COLOR_BGR2GRAY);
			if (nightMode)
				image = cv::Scalar::all(0);
			if (needToInit)
			{
				// automatic initialization
				goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, cv::Mat(), 3, 3, 0, 0.04);
				cornerSubPix(gray, points[1], subPixWinSize, cv::Size(-1, -1), termcrit);
				addRemovePt = false;
			}
			else if (!points[0].empty())
			{
				std::vector<uchar> status;
				std::vector<float> err;
				if (prevGray.empty())
					gray.copyTo(prevGray);
				calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize,
					3, termcrit, 0, 0.001);
				size_t i, k;
				for (i = k = 0; i < points[1].size(); i++)
				{
					if (addRemovePt)
					{
						if (norm(point - points[1][i]) <= 5)
						{
							addRemovePt = false;
							continue;
						}
					}
					if (!status[i])
						continue;
					points[1][k++] = points[1][i];
					circle(image, points[1][i], 3, cv::Scalar(0, 255, 0), -1, 8);
					lines[i].push_back(points[1][i]);
					for (size_t j = 0; j < lines.size(); ++j)
					{
						for (size_t l = 0; l < lines[j].size(); ++l)
						{
							circle(image, lines[j][l] , 1, cv::Scalar(0, 255, 0), -1, 8);
						}
					}
				}
				points[1].resize(k);
			}
			if (addRemovePt && points[1].size() < (size_t)MAX_COUNT)
			{
				std::vector<cv::Point2f> tmp;
				tmp.push_back(point);
				cornerSubPix(gray, tmp, winSize, cv::Size(-1, -1), termcrit);
				points[1].push_back(tmp[0]);
				lines.emplace_back();
				lines.back().push_back(tmp[0]);
				addRemovePt = false;
			}
			needToInit = false;
			imshow("LK Demo", image);
			char c = (char)cv::waitKey(10);
			if (c == 27)
				break;
			switch (c)
			{
			case 'r':
				needToInit = true;
				break;
			case 'c':
				points[0].clear();
				points[1].clear();
				break;
			case 'n':
				nightMode = !nightMode;
				break;
			}
			std::swap(points[1], points[0]);
			cv::swap(prevGray, gray);
		}
	}
};

