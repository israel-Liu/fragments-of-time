#pragma once

namespace himawari {

class Location
{
public:
	Location(const char* function_name, const char* file_name, int line_number);
	Location();

	bool operator<(const Location& other) const
	{
		if (line_number_ != other.line_number_) {
			return line_number_ < other.line_number_;
		}

		if (file_name_ != other.file_name_) {
			return file_name_ < other.file_name_;
		}

		return function_name_ < other.function_name_;
	}

	const char* function_name() const
	{
		return function_name_;
	}

	const char* file_name() const
	{
		return file_name_;
	}

	int line_number() const
	{
		return line_number_;
	}

private:
	const char* const function_name_;
	const char* const file_name_;
	const int line_number_;
};

//------------------------------------------------------------------------------
// Define a macro to record the current source location.

#define FROM_HERE himawari::Location(__FUNCTION__, __FILE__, __LINE__)

}
