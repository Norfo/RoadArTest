#pragma once
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include "TSQueue.h"
#include <atomic>

class ImageReader
{
private:
	bool fileExist = false;
	cv::VideoCapture capture;
	const char * srcPath;
	std::thread readThread;
	void readingLoop();
	TSQueue<cv::Mat> * queue;
	void(*endFileCallback)();
	std::atomic<bool> needReading = false;
public:
	ImageReader(const char * filePath, TSQueue<cv::Mat> * q, void(*cb)());
	~ImageReader();
	bool IsFileExist();
	void StartReading();
	void FinishReading();
};

