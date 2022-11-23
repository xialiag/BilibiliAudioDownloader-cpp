#pragma once
//C Library
#include <stdio.h>
#include <cstring>
//Cpp Library
#include <deque>
#include <string>
#include <vector>
//Headers
#include <requests.h>
#include <stringProcessing.h>


namespace infoList {
	std::deque<requests::vedioInfo> getInfoList(std::deque<std::string> bvList) {
		std::deque<std::deque<requests::vedioInfo>> resultList;
		for (std::string& eachBv : bvList) {
			if (stringProcessing::findStr(eachBv, "@") == std::string::npos) {
				resultList.push_back(requests::getVedioInfo(eachBv));
			}
			else {
				if (eachBv.size() == 13) {
					eachBv.pop_back();
					resultList.push_back(requests::getVedioInfo(eachBv));
				}
				if (eachBv.size() > 13) {
					std::vector<std::string> option = stringProcessing::split(eachBv, "@");
					std::string bv = option[0];
					std::string pageOption = option[1];
					if (stringProcessing::findStr(pageOption, "-") == std::string::npos) {
						resultList.push_back(requests::getVedioInfo(bv, std::stoi(pageOption)));
					}
					else {
						if (pageOption[pageOption.size() - 1] == '-') {
							resultList.push_back(requests::getVedioInfo(bv, std::stoi(stringProcessing::deleteStr(pageOption, "-", ""))));
						}
						else {
							std::vector<std::string> pageOptions = stringProcessing::split(pageOption, "-");
							std::string startPage = pageOptions[0];
							std::string endPage = pageOptions[1];
							resultList.push_back(requests::getVedioInfo(bv, std::stoi(startPage), std::stoi(endPage)));
						}
					}
				}
			}
		}
		std::deque<requests::vedioInfo> result;
		for (std::deque<requests::vedioInfo> eachResult : resultList) {
			if (eachResult.size() == 1) {
				result.push_back(eachResult[0]);
			}
			else {
				for (requests::vedioInfo eachInfo : eachResult) {
					result.push_back(eachInfo);
				}
			}
		}
		return result;
	}

	std::deque<std::string> getBvList(int argc, char* argv[]) {
		std::deque<std::string> bvList;
		for (int i = 2; i < argc; i++) {
			bvList.push_back(argv[i]);
		}
		std::string bvs = "";
		for (std::string bv : bvList) {
			bvs += bv;
			bvs += "\n";
		}
		bvs.pop_back();
		printf("Download start!\n");
		printf("%s\n", bvs.c_str());
		return bvList;
	}
}