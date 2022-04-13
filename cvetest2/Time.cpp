/* Includes for this file */
#include "Time.hpp"

namespace Time
{
    /*
    * Hot looping sleep function that uses timepoints to remain 'accurate'
    */
    void Sleep(int64_t sleep_ms, std::chrono::time_point<std::chrono::steady_clock> start)
    {
        /* Convert the wanted ms sleep to us (Microseconds) */
        sleep_ms *= 1000;

        /* Truncate the wanted time by the elapsed time */
        auto truncated = (sleep_ms - std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()) / 1000;

        /* Loop whilst the actual time is less than the wanted sleep time */
        while (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() < sleep_ms)
        {
            /* Use sleep until close to target then hot loop */
            if (truncated)
            {
                /* Sleep.. */
                std::this_thread::sleep_for(std::chrono::milliseconds(truncated));
                truncated = 0;
            }
        }
    }
}