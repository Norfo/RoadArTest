#pragma once
#include <opencv2/core.hpp>
#include "TSQueue.h"
#include <opencv2/highgui.hpp>
#include <atomic>
#include <opencv2/imgproc.hpp>

class FrameProcessor
{
private:
	TSQueue<cv::Mat> * preprocessQueue;
	TSQueue<cv::Mat> * postprocessQueue;
	std::thread process;
	void processLoop();
	std::atomic<bool> needProcess = true;
public:
	FrameProcessor(TSQueue<cv::Mat> * preq, TSQueue<cv::Mat> * postq);
	~FrameProcessor();

	void StartProcess();
	void FinishProcess();
};

