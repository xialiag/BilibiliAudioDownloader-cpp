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
	std::deque<requests::vedioInfo> cli(int argc, char* argv[]) {
		std::deque<requests::vedioInfo> infoList;
		switch (argc) {
		case 0: {
			printf("ERROR: Parameter error!\n");
			break;
		}
		case 1: {
			printf("ERROR: Parameter error!\n");
			break;
		}
		case 2: {
			printf("ERROR: Parameter error!\n");
			break;
		}
		default: {
			std::string mode = argv[1];
			if (mode == "-c") {
				//bad.exe -c bv bv bv
				return infoList::getInfoList(infoList::getBvList(argc, argv));
			}
			else if (mode == "-f") {
				std::ifstream infile(argv[2]);
				std::string line;
				std::deque<std::string> bvList;
				printf("Opening file: %s\n", argv[2]);
				if (infile) {
					while (std::getline(infile, line)) {
						bvList.push_back(line);
					}
					std::string bvs = "";
					for (std::string bv : bvList) {
						bvs += bv;
						bvs += "\n";
					}
					bvs.pop_back();
					printf("Download start!\n");
					printf("%s\n", bvs.c_str());
					return infoList::getInfoList(bvList);
				}
				else {
					printf("ERROR: Failed to open file \"%s\"\n", argv[2]);
				}
			}
			else {
				printf("ERROR: Parameter error!\n");
			}
		}
			   break;
		}
	}
}