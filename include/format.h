#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
// determine string HH:MM:SS from given seconds
std::string ElapsedTime(long times);

std::string TimeValueToString(long time);
};  // namespace Format

#endif