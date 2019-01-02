#include "tlog_file.h"

#include <cstdio>
#include <thread>
#include <sstream>

#include "basic_types.h"

using std::ostringstream;

namespace tlog {

	Logger::~Logger() 
	{
	}

	LogFileObject::LogFileObject(const char* base_filename)
		: base_filename_selected_(base_filename != NULL),
		  base_filename_((base_filename != NULL) ? base_filename : ""),
		  filename_extension_(),
		  file_(NULL),
		  handle_file_(NULL),
		  bytes_since_flush_(0),
		  dropped_mem_length_(0),
		  file_length_(0),
		  next_flush_time_(0) 
	{
	}

	LogFileObject::~LogFileObject() 
	{
		if (handle_file_) {
			::CloseHandle(handle_file_);
			handle_file_ = NULL;
		}
	}

	void LogFileObject::SetBasename(const char* basename) 
	{
		base_filename_selected_ = true;
		if (base_filename_ != basename) {
			// Get rid of old log file since we are changing names
			if (file_ != NULL) {
				fclose(file_);
				file_ = NULL;
			}
			base_filename_ = basename;
		}
	}

	void LogFileObject::SetExtension(const char* ext) 
	{
		if (filename_extension_ != ext) {
			// Get rid of old log file since we are changing names
			if (file_ != NULL) {
				fclose(file_);
				file_ = NULL;
			}
			filename_extension_ = ext;
		}
	}

	void LogFileObject::Flush() 
	{
	}

	bool LogFileObject::CreateLogfile(const string& time_pid_string) 
	{
		string string_filename = base_filename_ + filename_extension_ + time_pid_string;
		wchar_t module_name[MAX_PATH];
		::GetModuleFileName(NULL, module_name, MAX_PATH);

		PathString log_file_name = module_name;
		PathString::size_type last_backslash = log_file_name.rfind('\\', log_file_name.size());

		if (last_backslash != PathString::npos) {
			log_file_name.erase(last_backslash + 1);
		}

		log_file_name += L"zoom_share_application_window_list.log";

		const wchar_t* filename = log_file_name.c_str();
		handle_file_ = ::CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 
									CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		SetFilePointer(handle_file_, 0, 0, FILE_END);		
		
		return true;  // Everything worked
	}

	void LogFileObject::Write(bool force_flush, const wchar_t* message, int message_len)
	{
		// We don't log if the base_name_ is "" (which means "don't write")
		if (base_filename_selected_ && base_filename_.empty()) {
			return;
		}

		// If there's no destination file, make one before outputting
		if (handle_file_ == NULL) {
			// The logfile's filename will have the date/time & pid in it
			ostringstream time_pid_stream;
			time_pid_stream.fill('0');
			time_pid_stream << std::this_thread::get_id();

			const string& time_pid_string = time_pid_stream.str();

			if (base_filename_selected_ && !CreateLogfile(time_pid_string)) {
				perror("Could not create log file");
				fprintf(stderr, "COULD NOT CREATE LOGFILE '%s'!\n", time_pid_string.c_str());
				return;
			}
		}

		// Write to LOG file
		DWORD written = 0;
		WriteFile(handle_file_, message, sizeof message[0] * message_len, &written, NULL);
	}
}