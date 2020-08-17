#include "FrameProcessor.h"

void FrameProcessor::processLoop()
{
	while (needProcess)
	{
		cv::Mat img;
		if (preprocessQueue->try_pop(img) && !img.empty())
		{
			//cv::addText(img, "Processed", cv::Point(img.cols / 2, img.rows / 2), "Arial", 1, cv::Scalar(0, 0, 255));
			cv::blur(img, img, cv::Size(15, 15));
			postprocessQueue->push(img);

			cv::imshow("Process", img);
			cv::waitKey(1);
		}
	}
}

FrameProcessor::FrameProcessor(TSQueue<cv::Mat> * preq, TSQueue<cv::Mat> * postq)
	:preprocessQueue(preq), postprocessQueue(postq)
{
}

FrameProcessor::~FrameProcessor()
{
}

void FrameProcessor::StartProcess()
{
	needProcess = true;
	process = std::thread(&FrameProcessor::processLoop, this);
	process.detach();
}

void FrameProcessor::FinishProcess()
{
	needProcess = false;
}
