#pragma once
//C Libaray
#include <stdio.h>
#include <cstring>
//Cpp Library
#include <deque>
#include <string>
#include <io.h>
#include <vector>
//Windows API
#include <direct.h>
#include <windows.h>
#include <time.h>
//Headers
#include <requests.h>

namespace stringProcessing {
	int findStr(std::string mainStr, std::string str) {
		int posFound = 0;
		posFound = mainStr.find(str, 0);
		return posFound;
	}
	std::string round(std::string rawData) {
		rawData.insert(rawData.end() - 3, 1, '.');
		if (rawData[0] == '.') {
			rawData.insert(rawData.begin(), 1, '0');
		}
		rawData.erase(stringProcessing::findStr(rawData, ".") + 3, rawData.length() - stringProcessing::findStr(rawData, ".") - 2);
		return rawData;
	}
	std::string UTF8ToGB(const char* str) {
		std::string result;
		WCHAR* strSrc;
		LPSTR szRes;
		int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
		strSrc = new WCHAR[i + 1];
		MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);
		i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
		szRes = new CHAR[i + 1];
		WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
		result = szRes;
		delete[]strSrc;
		delete[]szRes;
		return result;
	}
	std::vector<std::string> split(const std::string &s, const std::string &c) {
		std::vector<std::string> v;
		std::string::size_type pos1, pos2;
		size_t len = s.length();
		pos2 = s.find(c);
		pos1 = 0;
		while (std::string::npos != pos2)
		{
			v.emplace_back(s.substr(pos1, pos2 - pos1));

			pos1 = pos2 + c.size();
			pos2 = s.find(c, pos1);
		}
		if (pos1 != len) {
			v.emplace_back(s.substr(pos1));
		}
		return v;
	}
	std::string deleteStr(std::string &str, const std::string dltStr, const std::string rplStr) {
		if (stringProcessing::findStr(str, dltStr) != std::string::npos) {
			std::vector<std::string> temp = stringProcessing::split(str, dltStr);
			str = "";
			for (std::string eachStr : temp) {
				str += eachStr;
				if (eachStr != temp[temp.size() - 1]) {
					str += rplStr;
				}
			}
			return str;
		}
		else {
			return str;
		}
	}
	std::string strRepair(std::string &str) {
		stringProcessing::deleteStr(str, "/", "-");
		stringProcessing::deleteStr(str, "\\", " ");
		stringProcessing::deleteStr(str, "?", "£¿");
		stringProcessing::deleteStr(str, ":", "£º");
		stringProcessing::deleteStr(str, "*", " ");
		stringProcessing::deleteStr(str, "\"", "¡°");
		stringProcessing::deleteStr(str, "<", " ");
		stringProcessing::deleteStr(str, ">", " ");
		stringProcessing::deleteStr(str, "|", " ");
		return str;
	}

}