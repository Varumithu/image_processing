#pragma once

#include "ITask.h"
#include <iostream>


class GCApplication
{
public:
	enum { NOT_SET = 0, IN_PROCESS = 1, SET = 2 };
	static const int radius = 2;
	static const int thickness = -1;
	void reset();
	void setImageAndWinName(const cv::Mat& _image, const std::string& _winName);
	void showImage() const;
	void mouseClick(int event, int x, int y, int flags, void* param);
	int nextIter();
	int getIterCount() const { return iterCount; }
private:
	void setRectInMask();
	void setLblsInMask(int flags, cv::Point p, bool isPr);
	const std::string* winName;
	const cv::Mat* image;
	cv::Mat mask;
	cv::Mat bgdModel, fgdModel;
	uchar rectState, lblsState, prLblsState;
	bool isInitialized;
	cv::Rect rect;
	std::vector<cv::Point> fgdPxls, bgdPxls, prFgdPxls, prBgdPxls;
	int iterCount;
	const int BGD_KEY = cv::EVENT_FLAG_CTRLKEY;
	const int FGD_KEY = cv::EVENT_FLAG_SHIFTKEY;
	const cv::Scalar RED = cv::Scalar(0, 0, 255);
	const cv::Scalar PINK = cv::Scalar(230, 130, 255);
	const cv::Scalar BLUE = cv::Scalar(255, 0, 0);
	const cv::Scalar LIGHTBLUE = cv::Scalar(255, 255, 160);
	const cv::Scalar GREEN = cv::Scalar(0, 255, 0);

};

static GCApplication gcapp;

class Task12 final : public ITask
{
public:
	Task12() = default;
	~Task12() = default;

	void run() const override
	{
		
		help();
		std::string filename = "../building.jpg";
		if (filename.empty())
		{
			std::cout << "\nDurn, empty filename" << std::endl;
			throw 2;
		}
		//Mat image = imread(samples::findFile(filename), IMREAD_COLOR);
		cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);
		if (image.empty())
		{
			std::cout << "\n Durn, couldn't read image filename " << filename << std::endl;
			return;
		}
		const std::string winName = "image";
		cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
		cv::setMouseCallback(winName, on_mouse, 0);
		gcapp.setImageAndWinName(image, winName);
		gcapp.showImage();
		for (;;)
		{
			char c = (char)cv::waitKey(0);
			switch (c)
			{
			case '\x1b':
				std::cout << "Exiting ..." << std::endl;
				goto exit_main;
			case 'r':
				std::cout << std::endl;
				gcapp.reset();
				gcapp.showImage();
				break;
			case 'n':
				int iterCount = gcapp.getIterCount();
				std::cout << "<" << iterCount << "... ";
				int newIterCount = gcapp.nextIter();
				if (newIterCount > iterCount)
				{
					gcapp.showImage();
					std::cout << iterCount << ">" << std::endl;
				}
				else
					std::cout << "rect must be determined>" << std::endl;
				break;
			}
		}
	exit_main:
		cv::destroyWindow(winName);
	}

	static void getBinMask(const cv::Mat& comMask, cv::Mat& binMask)
	{
		if (comMask.empty() || comMask.type() != CV_8UC1)
			CV_Error(cv::Error::StsBadArg, "comMask is empty or has incorrect type (not CV_8UC1)");
		if (binMask.empty() || binMask.rows != comMask.rows || binMask.cols != comMask.cols)
			binMask.create(comMask.size(), CV_8UC1);
		binMask = comMask & 1;
	}
	
private:
	static void help()
	{
		std::cout << "\nThis program demonstrates GrabCut segmentation -- select an object in a region\n"
			"and then grabcut will attempt to segment it out.\n"
			"Call:\n"
			"./grabcut <image_name>\n"
			"\nSelect a rectangular area around the object you want to segment\n" <<
			"\nHot keys: \n"
			"\tESC - quit the program\n"
			"\tr - restore the original image\n"
			"\tn - next iteration\n"
			"\n"
			"\tleft mouse button - set rectangle\n"
			"\n"
			"\tCTRL+left mouse button - set GC_BGD pixels\n"
			"\tSHIFT+left mouse button - set GC_FGD pixels\n"
			"\n"
			"\tCTRL+right mouse button - set GC_PR_BGD pixels\n"
			"\tSHIFT+right mouse button - set GC_PR_FGD pixels\n" << std::endl;
	}




	
	static void on_mouse(int event, int x, int y, int flags, void* param)
	{
		gcapp.mouseClick(event, x, y, flags, param);
	}
};

