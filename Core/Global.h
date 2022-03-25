#pragma once
#include <string>
#include "GlobalExceptionUtils.h"
#include "StringUtils.h"


#define SIZEOF_ARRAY(x)				(sizeof(x) / sizeof(x[0]))

#define CLEAR_MEMORY(x)				memset(x, 0, sizeof(x))

#define SECONDS(x)					(x * 1000)
#define MINUTES(x)					SECONDS(x * 60)
#define HOURS(x)					MINUTES(x * 60)

#define THREAD_DELAY_MS 3
#define THREAD_SLEEP() (std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_DELAY_MS)))

#define CastShared(type, shared)	std::static_pointer_cast<type>(shared)

#define CatUniqueVar_(x,y)		x##y
#define CatUniqueVar(x,y)		CatUniqueVar_(x,y)
#define RecursiveLockGuard(x)	CLockGuard CatUniqueVar(locker, __COUNTER__)(x);