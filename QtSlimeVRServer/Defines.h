#pragma once
#include "Global.h"

// Global
#define CONSOLE_TITLE "SlimeVR Server"

// Threads
#define SIDE_TASK_THREAD_DELAY_MS 500

// Network
#define UDP_PORT 6969
#define KEEP_ALIVE_TIMEOUT SECONDS(5)
#define HEART_BEAT_TIMEOUT SECONDS(10)
#define UDP_SERVER_WORKER_COUNT 2