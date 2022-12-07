﻿//Cpp Library
#include <deque>
#include <string>
#include <io.h>
//Windows API
#include <direct.h>
#include <windows.h>
#include <time.h>
//Headers
#include <requests.h>
#include <stringProcessing.h>
#include <cli.h>
#include <infoList.h>


int main(int argc, char* argv[]) {
	if (argc <= 2) {
	    return 0;
	}
	system("@echo off");
	system("chcp>nul 2>nul 65001");

	std::string prefix = "./download/";
	if (_access(prefix.c_str(), 0) == -1) {
		_mkdir(prefix.c_str());
	}

	clock_t startTime;
	startTime = clock();

	bool transcodingOpinion = false;
	std::deque<requests::vedioInfo> infoList = cli::cli(argc, argv, transcodingOpinion);

	if (transcodingOpinion) {
		std::string transcodingPath = "./transcoded/";
		if (_access(transcodingPath.c_str(), 0) == -1) {
			_mkdir(transcodingPath.c_str());
		}
	}
	for (requests::vedioInfo eachInfo : infoList) {
		printf("%s.%s\n", std::to_string(eachInfo.page).c_str(), eachInfo.part.c_str());
	}
	requests::getAudio(infoList, transcodingOpinion);

	clock_t endTime;
	endTime = clock();
	std::string Duration = stringProcessing::round(std::to_string(endTime - startTime));

	printf("Download Finish All! Time consuming: %s seconds", Duration.c_str());
}
