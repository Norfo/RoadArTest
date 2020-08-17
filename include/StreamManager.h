#pragma once
#include <thread>
#include <iostream>
#include <vector>
#include "TSQueue.h"
#include <opencv2/core.hpp>
#include <atomic>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

class StreamManager
{
private:
	TSQueue<cv::Mat> * queue;
	std::thread streamingThread;
	void streamLoop();
	const char * streamingServer;
	void initializeStream();
	void initialize_avformat_context(AVFormatContext *&fctx, const char *format_name);
	void initialize_io_context(AVFormatContext *&fctx, const char *output);
	void set_codec_params(AVFormatContext *&fctx, AVCodecContext *&codec_ctx, double width, double height, int fps, int bitrate);
	void initialize_codec_stream(AVStream *&stream, AVCodecContext *&codec_ctx, AVCodec *&codec, std::string codec_profile);
	void write_frame(AVCodecContext *codec_ctx, AVFormatContext *fmt_ctx, AVFrame *frame);
	SwsContext *initialize_sample_scaler(AVCodecContext *codec_ctx, double width, double height);
	AVFrame *allocate_frame_buffer(AVCodecContext *codec_ctx, double width, double height);
	std::atomic<bool> needStreaming = false;
	SwsContext * swsctx = nullptr;
	AVFrame * frame = nullptr;
	AVFormatContext *ofmt_ctx = nullptr;
	AVCodec *out_codec = nullptr;
	AVStream *out_stream = nullptr;
	AVCodecContext *out_codec_ctx = nullptr;
	int fps = 30, width = 1280, height = 720, bitrate = 300000;
	std::string codec_profile = "high444";
public:
	StreamManager(const char * server, TSQueue<cv::Mat> * q);
	~StreamManager();	
	void StartStreaming();
	void FinishStreaming();
};

