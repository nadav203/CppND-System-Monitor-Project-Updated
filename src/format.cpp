#include <string>

#include "format.h"

using std::string;

// helper 
// Input: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  string time = "00:00:00";
  long cal = 0;
  if (seconds > 0) {
    // calculate hours
    cal = seconds / 3600;
    time = TimeValueToString(cal) + ":";
    // calculate minutes
    cal = (seconds / 60) % 60;
    time += TimeValueToString(cal) + ":";
    // calculate seconds
    cal = seconds % 60;
    time += TimeValueToString(cal);
  }

  return time;
}

std::string Format::TimeValueToString(long time) {
  if (time < 10)
    return "0" + std::to_string(time);
  else
    return std::to_string(time);
}