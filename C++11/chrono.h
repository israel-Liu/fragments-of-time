#pragma once

#include <chrono>
#include <string>

void SegmentsDurationIntoDifferentUnits();

std::string ConvertTimepointToString(const std::chrono::system_clock::time_point&);

std::chrono::system_clock::time_point ConvertCalendarTimeToTimepoint(int year, int mon, int day,
                                                                     int hour, int min, int sec = 0);

