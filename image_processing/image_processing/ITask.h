#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>



class ITask
{
public:
	ITask() = default;
	virtual ~ITask() = default;
	virtual void run() = 0;
};
