#pragma once
//C Libaray
#include <stdio.h>
#include <cstring>
//Cpp Library
#include <deque>
#include <string>
#include <math.h>
#include <io.h>
#include <fstream>
#include <time.h>
#include <vector>
#include <iostream>
//Windows API
#include <direct.h>
#include <time.h>
//Third_parts Library
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
//Headers
#include <stringProcessing.h>


namespace requests {
	struct vedioInfo {
		std::string bvid;
		std::string title;
		int cid;
		std::string part;
		int page;
	};

	nlohmann::json getData(const std::string url) {
		cpr::Response res = cpr::Get(cpr::Url{ url });
		if (res.status_code >= 300) {
			printf("HTTP ERROR: %s\n", std::to_string(res.status_code).c_str());
		}
		else {
			nlohmann::json jsonData = nlohmann::json::parse(res.text);
			if (jsonData["data"].is_null()) {
				printf("ERROR: Data Not Fount!\n");
			}
			else {
				return jsonData["data"];
			}
		}
	}
	
	std::deque<requests::vedioInfo> getVedioInfo(std::string bvid) {
		std::deque<requests::vedioInfo> infoList;
		std::string url = "https://api.bilibili.com/x/web-interface/view?bvid=" + bvid;
		nlohmann::json data = requests::getData(url);

		if (!data.is_null()) {
			unsigned int count = data["pages"].size();
			if (count == 1) {
				requests::vedioInfo info = { bvid, data["title"], data["pages"][0]["cid"], data["pages"][0]["part"], 1 };
				infoList.push_back(info);
				return infoList;
			}
			else {
				if (data["pages"][count - 1]["page"] > 1) {
					for (unsigned int i = 1; i <= count; i++) {
						if (data["pages"][i]["page"] > 1) {
							requests::vedioInfo info = { bvid, data["title"], data["pages"][i - 1]["cid"], data["pages"][i - 1]["part"], data["pages"][i - 1]["page"] };
							infoList.push_back(info);
						}
					}
					return infoList;
				}
				else {
					printf("ERROR: The value of the start page is greater than the maximum value pulled!\n");
					return infoList;
				}
			}
		}
		else {
			printf("ERROR: Can't get Info of vedio %s!\n", bvid.c_str());
		}
	}

	std::deque<requests::vedioInfo> getVedioInfo(std::string bvid, unsigned int startPage, unsigned int endPage = 0) {
		std::deque<requests::vedioInfo> infoList;
		std::string url = "https://api.bilibili.com/x/web-interface/view?bvid=" + bvid;
		nlohmann::json data = requests::getData(url);

		if (!data.is_null()) {
			unsigned int count = data["pages"].size();
			if (endPage > count) {
				printf("WARN: The value of the end page exceeds the maximum value pulled!\n");
				printf("WARN: The value of the end page has been automatically replaced with the maximum value pulled!\n");
				endPage = count;
			}
			if (endPage == 0) {
				endPage = count;
			}
			if (endPage < startPage) {
				printf("WARN: The value of startPage exceeds the endPage!\n");
				return infoList;
			}
			if (count == 1) {
				requests::vedioInfo info = { bvid, data["title"], data["pages"][0]["cid"], data["pages"][0]["part"], 1 };
				infoList.push_back(info);
				return infoList;
			}
			else {
				if (startPage <= data["pages"][count - 1]["page"]) {
					for (unsigned int i = startPage; i <= endPage; i++) {
						if (data["pages"][i - 1]["page"] >= startPage) {
							requests::vedioInfo info = { bvid, data["title"], data["pages"][i - 1]["cid"], data["pages"][i - 1]["part"], data["pages"][i - 1]["page"] };
							infoList.push_back(info);
						}
					}
					return infoList;
				}
				else {
					printf("ERROR: The value of the start page is greater than the maximum value pulled!\n");
					return infoList;
				}
			}
		}
		else {
			printf("ERROR: Can't get Info of vedio %s!\n", bvid.c_str());
		}
	}

	nlohmann::json getPages(std::string bvid) {
		nlohmann::json data = requests::getData("https://api.bilibili.com/x/web-interface/view?bvid=" + bvid);
		if (!data.is_null()) {
			return data["pages"];
		}
		else {
			printf("ERROR: Empty data!\n");
		}
	}
	void getAudio(std::deque<requests::vedioInfo> infoList) {
		for (requests::vedioInfo& vedioInfo : infoList) {
			clock_t startTime;
			startTime = clock();
			std::string baseURL = "http://api.bilibili.com/x/player/playurl?fnval=16&";
			std::string URL = baseURL + "bvid=" + vedioInfo.bvid + "&cid=" + std::to_string(vedioInfo.cid);
			nlohmann::json data = requests::getData(URL);
			std::string audioURL = data["dash"]["audio"][0]["baseUrl"];

			std::string title = stringProcessing::strRepair(vedioInfo.title);
			std::string part = stringProcessing::strRepair(vedioInfo.part);

			std::ofstream of;
			if (part == title) {
				printf("Downloading: %s.%s.mp3\n", std::to_string(vedioInfo.page).c_str(), title.c_str());
				std::string fileName = "./download/" + std::to_string(vedioInfo.page) + '.' + title + ".mp3";
				of.open(stringProcessing::UTF8ToUnicode(fileName), std::ios::binary);
			}
			else {
				printf("Downloading: %s %s.%s.mp3\n", title.c_str(), std::to_string(vedioInfo.page).c_str(), part.c_str());
				std::string prefix = "./download/" + title + '/';
				if (_access(stringProcessing::UTF8ToGB(prefix.c_str()).c_str(), 0) == -1) {
					_mkdir(stringProcessing::UTF8ToGB(prefix.c_str()).c_str());
				}
				std::string fileName = "./download/" + title + '/' + std::to_string(vedioInfo.page) + '.' + part + ".mp3";
				of.open(stringProcessing::UTF8ToUnicode(fileName), std::ios::binary);
			}
			cpr::Response res = cpr::Download(of,
				cpr::Url{ audioURL },
				cpr::Header{
					{"User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.13; rv:56.0) Gecko/20100101 Firefox/56.0"},
					{"Accept", "*/*"},
					{"Accept-Language", "en-US,en;q=0.5"},
					{"Accept-Encoding", "gzip, deflate, br"},
					{"Range", "bytes=0-"},
					{"Referer", "https://api.bilibili.com/x/web-interface/view?bvid=" + vedioInfo.bvid},
					{"Origin", "https://www.bilibili.com"},
					{"Connection", "keep-alive"}
				});
			clock_t endTime;
			endTime = clock();
			std::string Duration = stringProcessing::round(std::to_string(endTime - startTime));
			if (part == title) {
				printf("%s seconds download finish: %s.%s.mp3\n", Duration.c_str(), std::to_string(vedioInfo.page).c_str(), title.c_str());
			}
			else {
				printf("%s seconds download finish: %s %s.%s.mp3\n", Duration.c_str(), title.c_str(), std::to_string(vedioInfo.page).c_str(), part.c_str());
			}

			Sleep(1);
		}
	}
}