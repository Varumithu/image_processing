// image_processing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>

#include "LocalThresholdFilter.h"

#include "ITask.h"
#include "Task01.h"
#include "Task02.h"
#include "Task04.h"
#include "Task05.h"








int main(int argc, char** argv)
{
	//ITask* task = new Task01;
	//ITask* task = new Task02;
	//ITask* task = new Task04;
	ITask* task = new Task05;


	task->run();
}




















