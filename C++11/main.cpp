
#include <iostream>

#include "chrono.h"
#include "iterator.h"

void UsingPowerMap();

int main()
{
  SegmentsDurationIntoDifferentUnits();

  auto tp1 = ConvertCalendarTimeToTimepoint(2010, 01, 01, 00, 00);
  std::cout << ConvertTimepointToString(tp1) << std::endl;

  auto tp2 = ConvertCalendarTimeToTimepoint(2011, 05, 23, 13, 44);
  std::cout << ConvertTimepointToString(tp2) << std::endl;

  UsingIteratorAdapter();

  UsingPowerMap();
}