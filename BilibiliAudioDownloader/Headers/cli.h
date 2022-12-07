#pragma once
//Cpp Library
#include <deque>
#include <string>
#include <fstream>
//Headers
#include <requests.h>
#include <stringProcessing.h>
#include <infoList.h>


namespace cli {
	std::deque<requests::vedioInfo> cli(int argc, char* argv[], bool& transcodingOpinion) {
		switch (argc) {
		case 0: {
			break;
		}
		case 1: {
			break;
		}
		case 2: {
			break;
		}
		default: {
			std::string mode = argv[1];
			if (mode == "-c") {
				//bad.exe -c bv bv bv
				return infoList::getInfoList(infoList::getBvList(argc, argv));
			}
			else if (mode == "-f") {
				return infoList::getInfoList(infoList::getBvList(argv[2]));
			}
			else if (mode == "-ct") {
				transcodingOpinion = true;
				return infoList::getInfoList(infoList::getBvList(argc, argv));
			}
			else if (mode == "-ft") {
				transcodingOpinion = true;
				return infoList::getInfoList(infoList::getBvList(argv[2]));
			}
			else {
				printf("ERROR: Parameter error!\n");
			}
			break;
		}
		}
	}
}
