#include <iostream>
#include "ImageReader.h"
#include "TSQueue.h"
#include "FrameProcessor.h"
#include "StreamManager.h"

const char * path = "D:/VID_20200621_043054.3gp";
const char * server = "rtmp://localhost:8090/live/stream";
bool isFileEnds = false;

void endVideoHandler()
{
	std::cout << "File reading was finished" << std::endl;
	isFileEnds = true;
}

int main(int argc, char* argv[])
{
	TSQueue<cv::Mat> preprocessQ;
	TSQueue<cv::Mat> postprocessQ;

	ImageReader reader(path, &preprocessQ, &endVideoHandler);
	FrameProcessor processor(&preprocessQ, &postprocessQ);
	StreamManager streamer(server, &postprocessQ);
	streamer.StartStreaming();
	if (reader.IsFileExist())
	{
		std::cout << "File " << path << " exist. Start processing!" << std::endl;
		reader.StartReading();
		processor.StartProcess();		
	}
	else
		std::cout << "File " << path << " not exist! Please, check input file name" << std::endl;

	char c;
	std::cin >> c;
	if (c == 'q')
	{
		reader.FinishReading();
		processor.FinishProcess();
		return 1;
	}
		
}