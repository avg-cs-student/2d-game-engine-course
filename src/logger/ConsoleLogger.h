#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "Logger.h"

const std::string RED = "\033[0;31m";
const std::string GREEN = "\e[0;32m";
const std::string RESET = "\e[0m";

#define MAKE_RED(msg) RED + msg + RESET
#define MAKE_GREEN(msg) GREEN + msg + RESET

enum struct LogType {
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
};

struct LogEntry {
	LogType type;
	std::string msg;
};

class ConsoleLogger : public Logger {
public:
	void Log(const std::string& msg) override {
		LogEntry entry({ LogType::LOG_INFO, msg });
		history.push_back(entry);
		std::cout << GREEN << CurrentDateTimeToStr() << " " + entry.msg + RESET << std::endl;
	}

	void Err(const std::string& msg) override {
		LogEntry entry({ LogType::LOG_ERROR, msg });
		history.push_back(entry);
		std::cerr << RED << CurrentDateTimeToStr() << " " + entry.msg + RESET << std::endl;
	}

	static std::string CurrentDateTimeToStr() {
		auto const now = std::chrono::system_clock::now();
		auto const now_t = std::chrono::system_clock::to_time_t(now);
		std::string output(30, '\0');
		std::strftime(&output[0], output.size(), "%d-%b-%Y %T", std::localtime(&now_t));
		return output;
	}
private:
	std::vector<LogEntry> history;
};
