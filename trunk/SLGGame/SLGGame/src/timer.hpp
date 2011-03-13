#include <windows.h>
#include <time.h>
#include <string>

class Timer
{
    private:
    clock_t mZeroClock;

    DWORD mStartTick;
	LONGLONG mLastTime;
    LARGE_INTEGER mStartTime;
    LARGE_INTEGER mFrequency;

	DWORD mTimerMask;
    public:
        Timer();
        ~Timer();

        bool setOption(const std::string& strKey, const void* pValue);
        void reset();
        unsigned long getMilliseconds();
        unsigned long getMicroseconds();
        unsigned long getMillisecondsCPU();
        unsigned long getMicrosecondsCPU();
};


