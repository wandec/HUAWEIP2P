#include"Timestamp.h"
#include<iostream>
#include<sys/time.h>
#include<stdio.h>
#define __STDC_FORMAT_MACROS
#include<inttypes.h>
#undef __STDC_FORMAT_MACROS
#include<boost/static_assert.hpp>
using namespace huaweip2p;

BOOST_STATIC_ASSERT(sizeof(Timestamp) == sizeof(int64_t));

Timestamp::Timestamp(int64_t microseconds)
  : microSecondsSinceEpoch_(microseconds)
{
}
std::string Timestamp::toString() const
{
  char buf[32] = {0};
  int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
  int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
  snprintf(buf, sizeof(buf)-1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
  return buf;
}

std::string Timestamp::toFormattedString() const
{

  char buf[32] = {0};
  time_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
  int microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
  struct tm tm_time;

  //gmtime_r() return UTC
  //localtime_r() return local time(+8:00 in china)
  localtime_r(&seconds, &tm_time);
  
  snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d", 
      tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
      tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
      microseconds);
  return buf;
}

Timestamp Timestamp::now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  int64_t seconds = tv.tv_sec;
  return Timestamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
}
Timestamp Timestamp::invalid()
{
  return Timestamp();
}
