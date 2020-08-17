#include <iostream>
#include "ImageReader.h"

void ImageReader::readingLoop()
{
	while (capture.isOpened() && needReading)
	{
		cv::Mat img;
		capture.read(img);
		if (img.empty())
			break;
		queue->push(img);
	}

	endFileCallback();
}

ImageReader::ImageReader(const char * filePath, TSQueue<cv::Mat> * q, void(*cb)())
	: srcPath(filePath), queue(q), endFileCallback(cb)
{
	std::ifstream f(filePath);
	fileExist = f.good();
}

ImageReader::~ImageReader()
{
}

bool ImageReader::IsFileExist()
{
	return fileExist;
}

void ImageReader::StartReading()
{
	if (fileExist)
	{
		needReading = true;
		capture.open(srcPath);
		readThread = std::thread(&ImageReader::readingLoop, this);
		readThread.detach();
	}
}

void ImageReader::FinishReading()
{
	needReading = true;
}
