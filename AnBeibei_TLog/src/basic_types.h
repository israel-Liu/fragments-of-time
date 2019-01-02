#pragma once

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef TLOG_BASIC_TYPES_H
#define TLOG_BASIC_TYPES_H

#include <functional>
#include <string>

#include "basic_macros.h"

namespace tlog {

#if defined(OS_WIN)
	using PathChar = wchar_t;
	using PathString = std::wstring;
#define PATH_LITERAL(str) L##str
#else
	using PathChar = char;
	using PathString = std::string;
#define PATH_LITERAL(str) str
#endif

	using FileNameGenerator = std::function<PathString()>;

}   // namespace tlog

#endif  // TLOG_BASIC_TYPES_H