#pragma once

#include <Windows.h>
#include <string>

#include "basic_macros.h"

using std::string;

namespace tlog {

	class ANBEIBEI_TLOG_DLL_DECL Logger {
	public:
		virtual ~Logger();

		virtual void Write(bool force_flush,
						   const wchar_t* message,
						   int message_len) = 0;

		// Flush any buffered messages
		virtual void Flush() = 0;
	};

	class ANBEIBEI_TLOG_DLL_DECL LogFileObject : public Logger
	{
	public:
		LogFileObject(const char* base_filename);
		~LogFileObject();

		void Write(bool force_flush, const wchar_t* message, int message_len) override;

		// Configuration options
		void SetBasename(const char* basename);
		void SetExtension(const char* ext);

		// Normal flushing routine
		virtual void Flush();

	private:

		bool base_filename_selected_;
		string base_filename_;
		string symlink_basename_;
		string filename_extension_;     
		FILE* file_;
		HANDLE handle_file_;

		int bytes_since_flush_;
		int dropped_mem_length_;
		int file_length_;
		unsigned int rollover_attempt_;
		long long next_flush_time_;         

		bool CreateLogfile(const string& time_pid_string);
	};

}

