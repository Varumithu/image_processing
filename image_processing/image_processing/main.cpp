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
#include "Task06.h"
#include "Task07.h"
#include "Task08.h"
#include "Task09.h"
#include "Task10.h"
#include "Task11.h"
#include "Task12.h"
#include "Task13.h"
#include "Task13_b.h"
#include "Task15.h"
#include "Task16.h"


int main()
{
	
	const auto task = std::make_unique<Task16>();

	task->run();
	
	return 0;
}



















