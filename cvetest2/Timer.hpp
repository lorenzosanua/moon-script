#include <profileapi.h>
#include <winnt.h>

class Timer
{
   

    /**
     * Used to get the time elapsed (in milliseconds) since the timer was instantiated.
     */
public:

    Timer()
    {
        // Store the time at which this timer was instantiated.
        QueryPerformanceCounter(&starting_time);
    }

    float Elapsed()
    {
        // Will contain the current performance counter value
        LARGE_INTEGER current_time;

        // Used for b1g matematic
        LARGE_INTEGER elapsed_pc;

        // Used to store the performance frequency for math
        LARGE_INTEGER frequency;

        // Update performance frequency
        QueryPerformanceFrequency(&frequency);

        // Get the current performance counter value
        QueryPerformanceCounter(&current_time);

        // Get elapsed time in seconds
        elapsed_pc.QuadPart = current_time.QuadPart - starting_time.QuadPart;

        // Calculate the elapsed time (in ms)
        float elapsed = (
            (static_cast<float>(elapsed_pc.QuadPart) * 1000.0f) /
            (static_cast<float>(frequency.QuadPart))
            );

        // Return elapsed time
        return elapsed;
    }

    // Used to determine when the function was instantiated
    LARGE_INTEGER starting_time;
};
