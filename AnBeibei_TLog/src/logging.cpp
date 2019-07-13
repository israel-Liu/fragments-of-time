#include "logging.h"

#include <algorithm>
#include <thread>

#include <iostream>

using std::ostream;

namespace {

// https://stackoverflow.com/questions/14589417/can-an-enum-class-be-converted-to-the-underlying-type

template<typename E>
constexpr auto EnumToUnderlying(E e)
{
    return static_cast<std::underlying_type_t<E>>(e);
}

}

namespace tlog {

const char* const TLogSeverityNames[EnumToUnderlying(LogSeverity::NUM_SEVERITIES)] = {
	"INFO", "WARNING", "ERROR", "FATAL"
};

LogSeverity g_min_log_level = LogSeverity::TLOG_INFO;

void SetMinLogLevel(LogSeverity level) {
	g_min_log_level = std::min(LogSeverity::NUM_SEVERITIES, level);
}

LogSeverity GetMinLogLevel() {
	return g_min_log_level;
}

// An arbitrary limit on the length of a single log message.  This
// is so that streaming can be done more efficiently.
const size_t LogMessage::kMaxLogMessageLen = 30000;

struct LogMessage::LogMessageData
{
    LogMessageData();

    DISALLOW_COPY_AND_ASSIGN(LogMessageData);
    DISALLOW_MOVE_AND_ASSIGN(LogMessageData);

    const char* base_filename_ = nullptr;
    const char* full_filename_ = nullptr;
    int line_ = -1;
	// Buffer space; contains complete message text.
	char message_text_[LogMessage::kMaxLogMessageLen + 1] = {};
	LogStream stream_;
    LogSeverity severity_;
};

LogMessage::LogMessageData::LogMessageData()
    : stream_(message_text_, LogMessage::kMaxLogMessageLen, 0),
	  severity_(LogSeverity::TLOG_INFO)
{

}

LogMessage::LogMessage(const char* file, int line, LogSeverity severity)
{
    Init(file, line, severity);
}

void LogMessage::Init(const char* file, int line, LogSeverity severity)
{
    allocated_ = new LogMessageData();
    data_ = allocated_;

    stream().fill('0');

    stream() << "["
			 << " " << std::this_thread::get_id() << " "
             << " " << TLogSeverityNames[EnumToUnderlying(severity)] << " "
		     << " " << "(" << line << ")" << " "
             << "]";
}

LogMessage::~LogMessage()
{
  std::cout << data_->stream_.self()->str() << std::endl;
}

ostream& LogMessage::stream()
{
    return data_->stream_;
}

} // namespace tlog