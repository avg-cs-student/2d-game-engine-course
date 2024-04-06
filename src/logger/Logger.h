#pragma once

#include <string>

class Logger {
public:
	virtual ~Logger() = default;
	virtual void Log(const std::string& message) = 0;
	virtual void Err(const std::string& message) = 0;
};
