#pragma once
#include "ITask.h"



class Task10 final :
	public ITask
{
public:
	Task10() = default;
	~Task10() = default;
	void run() const override
	{
		cv::Mat image = cv::imread("../chinese.jpg", cv::IMREAD_COLOR);
		cv::Mat drawable;
		image.copyTo(drawable);
		cv::imshow("image", image);
		cv::waitKey(0);
		cv::Rect  face_area{ 685, 250, 55, 70 };
		//cv::rectangle(drawable, face_area, cv::Scalar{ 255, 0, 0 }, 1);
		//cv::imshow("draw", drawable);
		//cv::waitKey(0);

		cv::Mat face = image(face_area);
		cv::imshow("template", face);
		cv::waitKey(0);

		int match_method = cv::TM_SQDIFF_NORMED;
		
		cv::Mat result;

		cv::Mat noise(image.size(), image.type());
		cv::randu(noise, 100, 255);
		
		drawable += noise;
		cv::Mat image_saved;
		image.copyTo(image_saved);
	/*	cv::warpAffine(image, drawable, 
				cv::getRotationMatrix2D({ static_cast<float>(image.cols) / 2, static_cast<float>(image.rows) / 2 },
				180, 1), image.size());*/
		cv::imshow("image", drawable);
		cv::matchTemplate(drawable, face, result, match_method);

		cv::imshow("result", result);
		
		cv::waitKey(0);
		double max, min;
		cv::Point minLoc, maxLoc;
		cv::minMaxLoc(result, &min, &max, &minLoc, &maxLoc);
		//image.copyTo(drawable);
		cv::Point matchLoc;
		cv::imshow("draw", drawable);
		cv::waitKey(0);

		if (match_method == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED)
		{
			matchLoc = minLoc;
		}
		else
		{
			matchLoc = maxLoc;
		}
		rectangle(drawable, matchLoc, cv::Point(matchLoc.x + face.cols, matchLoc.y + face.rows), cv::Scalar{0, 0, 255}, 2, 8, 0);
		rectangle(result, matchLoc, cv::Point(matchLoc.x + face.cols, matchLoc.y + face.rows), cv::Scalar::all(0), 2, 8, 0);
		rectangle(image_saved, matchLoc, cv::Point(matchLoc.x + face.cols, matchLoc.y + face.rows), cv::Scalar{ 0, 0, 255 }, 2, 8, 0);

		cv::imshow("draw", drawable);
		cv::imshow("result", result);
		cv::imshow("image", image_saved);
		cv::waitKey(0);
	}
};

