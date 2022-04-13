#pragma once
#include <iostream>
#include <chrono>
#include <stdio.h>
#include <Windows.h>
#include "Vector2.hpp"
#include "mouse.h"
#include "WeaponHelpers.h"
#include <thread>
#include <math.h>
#include <stdlib.h>

namespace MouseHelpers {

    double timeDelta(std::chrono::high_resolution_clock::time_point t1, std::chrono::high_resolution_clock::time_point t2) {
        double delta = 0.0f;

        std::chrono::duration<double, std::milli> fp_ms = t1 - t2;
        return fp_ms.count();
    }

    void Sleep(double seconds) //very very very very accurate sleep clock
    {
        using namespace std;
        using namespace std::chrono;

        static double estimate = 5e-3;
        static double mean = 5e-3;
        static double m2 = 0;
        static int64_t count = 1;

        while (seconds > estimate) {
            auto start = high_resolution_clock::now();
            this_thread::sleep_for(milliseconds(1));
            auto end = high_resolution_clock::now();

            double observed = (end - start).count() / 1e9;
            seconds -= observed;

            ++count;
            double delta = observed - mean;
            mean += delta / count;
            m2 += delta * (observed - mean);
            double stddev = sqrt(m2 / (count - 1));                                                                                          
            estimate = mean + stddev;
        }

        // spin lock
        auto start = high_resolution_clock::now();
        while ((high_resolution_clock::now() - start).count() / 1e9 < seconds);
    }


    double randomAnimTime(double anim_time, double repeatDelay, double percent) {
        if (percent > 0.05) {
            double range = (repeatDelay - anim_time) * 100;
            range *= percent;
            float random = (rand() % (int)range) / 100;
            return anim_time += random;
        }
        else return anim_time;
    
    }

    double animationTime(Math::Vector2 v, int scope, int muzzle) {
        double anim_time = sqrt(pow(v.x, 2) + pow(v.y, 2)) / 0.02f;
        if (scope == 1 || scope == 2) {
            anim_time *= 0.8f;
        }
        else {
            if (muzzle == 1) anim_time *= 0.8f;
        }
        return anim_time;
    }

    void SmoothMove(Math::Vector2 val, double repeatDelay, std::chrono::time_point<std::chrono::steady_clock> f_excess, double &extraX, double &extraY) //smoothing func
    {
        int previous_x = 0, previous_y = 0; double previous_a = 0.0;
        auto xd = std::chrono::high_resolution_clock::now();
        std::chrono::time_point<std::chrono::steady_clock> excess = f_excess;
        for (int index = 1; index < (int)(val.anim_time); index++)
        {
            int x = index * (int)(val.x) / (int)(val.anim_time);
            int y = index * (int)(val.y) / (int)(val.anim_time);

            int a = index * 1;
            mouse_move(0, x-previous_x, y-previous_y, 0);

            Sleep((a - previous_a)/1000);
            excess = std::chrono::high_resolution_clock::now();

            previous_x = x; previous_y = y; previous_a = a;
        }
        double elapsed = timeDelta(std::chrono::high_resolution_clock::now(), xd);
        
        if (repeatDelay-elapsed > 0) Sleep((repeatDelay-elapsed) / 1000);
    }

    Math::Vector2 readyValue(Math::Vector2 value, double sensitivity, double fov, double muzzleMultiplier, double scopeMultiplier, int magsize, int muzzle, int scope, float repeatDelay, float random) {
        Math::Vector2 r;
        
        
        r.x = ((value.x * muzzleMultiplier * scopeMultiplier) / (-0.03f * (sensitivity * 3.0f) * (fov / 100.0f)));
        r.y =  ((value.y * muzzleMultiplier * scopeMultiplier) / (-0.03f * (sensitivity * 3.0f) * (fov / 100.0f)));
        r.anim_time = randomAnimTime(animationTime(value, scope, muzzle), repeatDelay,random);
        return r;
    }

    void fillArray(Math::Vector2 array[], double sens, double fov, int muzzle, int scope, int weapon, float random) {
        double scopeMulti = WeaponHelpers::getScopeMulti(scope);
        
        double muzzleMulti = WeaponHelpers::getAttachmentValues(muzzle).multiplier;
        if (muzzle == 1) muzzleMulti = 0.8f;
        if (scope == 1 || scope == 2) muzzleMulti = 1;
        for (int i = 0; i < WeaponHelpers::magSize(weapon); i++) {
            array[i] = readyValue(WeaponHelpers::recoilTable(weapon)[i], sens, fov, muzzleMulti, scopeMulti, sizeof(array), scope, muzzle, WeaponHelpers::weaponRepeatDelay(weapon), random);
            
        }
    }
}


