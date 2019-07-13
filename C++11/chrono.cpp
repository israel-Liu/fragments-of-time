#include "chrono.h"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;
using namespace std::chrono;

//using std::ostream;

template <typename V, typename R>
ostream& operator << (ostream& s, const chrono::duration<V, R>& d)
{
  s << "[" << d.count() << " of " << R::num << "/" << R::den << "]";
  return s;
}

void SegmentsDurationIntoDifferentUnits()
{
  milliseconds ms(7255042);
  hours hh = duration_cast<hours>(ms);
  minutes mm = duration_cast<minutes>(ms % chrono::hours(1));
  seconds ss = duration_cast<seconds>(ms % chrono::minutes(1));
  milliseconds msec = duration_cast<milliseconds>(ms % chrono::seconds(1));

  cout << "raw: " << hh << "::" << mm << "::" << ss << "::" << msec << endl;

  cout << "  " << setfill('0') << setw(2) << hh.count() << "::"
       << setw(2) << mm.count() << "::"
       << setw(2) << ss.count() << "::"
       << setw(3) << msec.count() << endl;
}

std::string ConvertTimepointToString(const chrono::system_clock::time_point& tp)
{
  std::time_t t = chrono::system_clock::to_time_t(tp);
  char ts[100];
  ctime_s(ts, sizeof ts, &t);

  return ts;
}

chrono::system_clock::time_point ConvertCalendarTimeToTimepoint(int year, int mon, int day,
                                                                int hour, int min, int sec)
{
  struct std::tm t;
  t.tm_sec = sec;
  t.tm_min = min;
  t.tm_hour = hour;
  t.tm_mday = day;
  t.tm_mon = mon - 1;
  t.tm_year = year - 1900;
  t.tm_isdst = -1; // determine whether daylight saving time

  std::time_t tt = std::mktime(&t);
  if (tt == -1) {
    throw "no valid system time";
  }

  return chrono::system_clock::from_time_t(tt);
}