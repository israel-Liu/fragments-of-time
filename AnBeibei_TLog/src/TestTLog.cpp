// TestTLog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "logging.h"

#include "tlog_file.h"

void TestLogMessageHeaderConstruction()
{
	tlog::LogMessage message(__FILE__, __LINE__, tlog::LogSeverity::TLOG_INFO);
	std::cout << static_cast<tlog::LogMessage::LogStream&>(message.stream()).str() << std::endl;
}

void TestLogIsOnMacro()
{
	std::cout << LOG_IS_ON(INFO) << std::endl
			  << LOG_IS_ON(ERROR) << std::endl;

	std::cout << LOG_IS_ON(INFO) << std::endl
			  << LOG_IS_ON(WARNING) << std::endl
			  << LOG_IS_ON(ERROR) << std::endl;
}

void TestLogMacro()
{
	LOG(INFO) << "logging on INFO level";
	//LOG(WARNING) << "logging on WARNING level";
	//LOG(ERROR) << "logging on ERROR level";
	//LOG(FATAL) << "logging on FATAL level";

	// Simulate that <windows.h> was included.
//#ifndef ERROR
//#define ERROR 0
//#endif
	tlog::SetMinLogLevel(tlog::LogSeverity::TLOG_ERROR);
	std::cout << "changed min level to LOG_ERROR\n";

	LOG(INFO) << "logging on INFO level";
	//LOG(WARNING) << "logging on WARNING level";
	//LOG(ERROR) << "logging on ERROR level";
	//LOG(FATAL) << "logging on FATAL level";
//#undef ERROR
	//LOG_IF(ERROR, 1 == 1) << "conditional logging";
	//LOG_IF(ERROR, 2 == 1) << "conditional logging";
}

void TestLogFileObject()
{
	tlog::LogFileObject log_file("Test");
	log_file.Write(false, "TestLogFileObject", 17);
}

int main()
{

	TestLogMessageHeaderConstruction();
	TestLogIsOnMacro();
	TestLogMacro();
	TestLogFileObject();

    return 0;
}

