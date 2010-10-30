
#include "time_util.h"
#include "log.h"

namespace eventrpc {
static const int64_t NS_PER_S = 1000000000LL;
static const int64_t US_PER_S = 1000000LL;
static const int64_t MS_PER_S = 1000LL;

static const int64_t NS_PER_MS = NS_PER_S / MS_PER_S;
static const int64_t US_PER_MS = US_PER_S / MS_PER_S;

void TimeUtil::MakeTimespec(timespec *result, uint64_t value) {
  ASSERT_NE(static_cast<timespec*>(NULL), result);
  result->tv_sec = value / MS_PER_S; // ms to s
  result->tv_nsec = (value % MS_PER_S) * NS_PER_MS; // ms to ns
}

void TimeUtil::MakeTimeval(timeval *result, uint64_t value) {
  ASSERT_NE(static_cast<timeval*>(NULL), result);
  result->tv_sec = value / MS_PER_S; // ms to s
  result->tv_usec = (value % MS_PER_S) * US_PER_MS; // ms to us
}

void TimeUtil::MakeTimeSpecToMs(int64_t *result,
                                const struct timespec& value) {
  ASSERT_NE(static_cast<int64_t*>(NULL), result);
  *result = (value.tv_sec * MS_PER_S) + (value.tv_nsec / NS_PER_MS);

  if (int64_t(value.tv_nsec) % NS_PER_MS >= (NS_PER_MS / 2)) {
    ++(*result);
  }
}

void TimeUtil::MakeTimeValToMs(int64_t *result,
                               const struct timeval& value) {
  ASSERT_NE(static_cast<int64_t*>(NULL), result);
  *result = (value.tv_sec * MS_PER_S) + (value.tv_usec / US_PER_MS);
  if (int64_t(value.tv_usec) % US_PER_MS >= (US_PER_MS / 2)) {
    ++(*result);
  }
}

const int64_t TimeUtil::GetCurrentTime() {
  int64_t result;
  struct timeval now;
  int ret = gettimeofday(&now, NULL);
  ASSERT_EQ(0, ret);
  MakeTimeValToMs(&result, now);
  return result;
}
};
