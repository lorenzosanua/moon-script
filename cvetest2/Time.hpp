#ifndef _TIME_HPP
#define _TIME_HPP

#include <Windows.h>
#include <chrono>
#include <thread>
#include <time.h>

/* The undocumented NtDelayExecution function */
static LONG(__stdcall* NtDelayExecution)(BOOL Alertable, PLARGE_INTEGER DelayInterval) = (LONG(__stdcall*)(BOOL, PLARGE_INTEGER)) GetProcAddress(GetModuleHandle("ntdll.dll"), "NtDelayExecution");


namespace Time
{
    /*
    * Hot looping sleep function that uses timepoints to remain 'accurate'
    */
    void Sleep(int64_t sleep_ms, std::chrono::time_point<std::chrono::steady_clock> start);

}

#endif // !_TIME_HPP