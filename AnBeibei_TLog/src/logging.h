#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   pragma once
#endif

#ifndef TLOG_LOGGING_H
#define TLOG_LOGGING_H

#include <ostream>

#include "basic_macros.h"

namespace tlog {

enum class LogSeverity : int
{
    TLOG_INFO = 0,
    TLOG_WARNING = 1,
    TLOG_ERROR = 2,
    TLOG_FATAL = 3,
    NUM_SEVERITIES = 4
};

// LogMessage::LogStream is a std::ostream backed by this streambuf.
// This class ignores overflow and leaves two bytes at the end of the
// buffer to allow for a '\n' and '\0'.
class ANBEIBEI_TLOG_DLL_DECL LogStreamBuf : public std::streambuf {
public:
	// REQUIREMENTS: "len" must be >= 2 to account for the '\n' and '\n'.
	LogStreamBuf(char *buf, int len) {
		setp(buf, buf + len - 2);
	}

	// Resets the buffer. Useful if we reuse it by means of TLS.
	void reset() {
		setp(pbase(), epptr());
	}

	// This effectively ignores overflow.
	virtual int_type overflow(int_type ch) {
		return ch;
	}

	// Legacy public ostrstream method.
	size_t pcount() const { return pptr() - pbase(); }
	char* pbase() const { return std::streambuf::pbase(); }
};

LogSeverity ANBEIBEI_TLOG_DLL_DECL GetMinLogLevel();

void ANBEIBEI_TLOG_DLL_DECL SetMinLogLevel(LogSeverity min_severity);

#define COMPACT_TLOG_INFO \
    tlog::LogMessage(__FILE__, __LINE__, tlog::LogSeverity::TLOG_INFO)

#define LOG_IS_ON(severity) \
    ((tlog::LogSeverity::TLOG_##severity) >= tlog::GetMinLogLevel())

#define LOG_STREAM(severity) \
    COMPACT_TLOG_##severity.stream()

#define LAZY_STREAM(stream, condition) \
    !(condition) ? (void)0 : tlog::LogMessageVoidify() & (stream)

#define LOG(severity) \
    LAZY_STREAM(LOG_STREAM(severity), LOG_IS_ON(severity))

class ANBEIBEI_TLOG_DLL_DECL LogMessage
{
public:
	// LogStream inherit from non-DLL-exported class (std::ostrstream)
	// and VC++ produces a warning for this situation.
	// However, MSDN says "C4275 can be ignored in Microsoft Visual C++
	// 2005 if you are deriving from a type in the Standard C++ Library"
	// http://msdn.microsoft.com/en-us/library/3tdb471s(VS.80).aspx
	// Let's just ignore the warning.
#ifdef _MSC_VER
# pragma warning(disable: 4275)
#endif
	class ANBEIBEI_TLOG_DLL_DECL LogStream : public std::ostream 
	{
#ifdef _MSC_VER
# pragma warning(default: 4275)
#endif
	public:
		LogStream(char* buf, int len, int ctr)
			: std::ostream(NULL),
			  streambuf_(buf, len),
			  ctr_(ctr),
			  self_(this) {
			  rdbuf(&streambuf_);
		}

		int ctr() const { return ctr_; }
		void set_ctr(int ctr) { ctr_ = ctr; }
		LogStream* self() const { return self_; }

		// Legacy std::streambuf methods.
		size_t pcount() const { return streambuf_.pcount(); }
		char* pbase() const { return streambuf_.pbase(); }
		char* str() const { return pbase(); }
		void reset() { streambuf_.reset(); }

	private:
		LogStream(const LogStream&);
		LogStream& operator=(const LogStream&);
		tlog::LogStreamBuf streambuf_;
		int ctr_;  // Counter hack (for the LOG_EVERY_X() macro)
		LogStream *self_;  // Consistency check hack
	};

public:
    LogMessage(const char* file, int line, LogSeverity severity);
    ~LogMessage();

    DISALLOW_COPY_AND_ASSIGN(LogMessage);
    DISALLOW_MOVE_AND_ASSIGN(LogMessage);

    std::ostream& stream();
    struct LogMessageData;

private:
    void Init(const char* file, int line, LogSeverity severity);
	// An arbitrary limit on the length of a single log message.  This
	// is so that streaming can be done more efficiently.
	static const size_t kMaxLogMessageLen;
    LogMessageData* allocated_ = nullptr;
    LogMessageData* data_ = nullptr;
};

// This class is used to explicitly ignore values in the conditional
// logging macros.  This avoids compiler warnings like "value computed
// is not used" and "statement has no effect".
class LogMessageVoidify {
public:
	LogMessageVoidify() { }
	// This has to be an operator with a precedence lower than << but
	// higher than ?:
	void operator&(std::ostream&) { }
};

}

#endif // TLOG_LOGGING_H