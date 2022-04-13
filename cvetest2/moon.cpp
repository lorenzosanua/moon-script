#pragma comment (lib, "winmm.lib")
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif


#include <windows.h>
#include "mouse.h"
#include "mouse.c"
#include <stdio.h>
#include "Timer.hpp"
#include "RecoilTables.h"
#include <iostream>
#include <chrono>
#include "WeaponHelpers.h"
#include "MouseHelpers.h"
#include "Menu.h"
#include "LicenseHelpers.h"
#include <thread>
#include <mmsystem.h>








float random = 0.0f;
int fov = 90;
int currentWeapon = 0;
int currentMuzzle = 0;
int currentScope = 0;
int shotCounter = 0;
double sens = 0.5f;
int smoothing = 6;
bool menuUpdate = true;
bool loggedIn = false;
double extraX = 0, extraY = 0;
bool arrayFilled[6];
bool recoilStatus = false;
Math::Vector2 ak_tables[30];
Math::Vector2 lr_tables[30];
Math::Vector2 mp5_tables[30];
Math::Vector2 thompson_tables[19];
Math::Vector2 csmg_tables[23];
Math::Vector2 m249_tables[99];

Math::Vector2* realRecoilTable(int weapon) {
    switch (weapon) {
    case 0:
        return ak_tables; //ak
        break;

    case 1:
        return lr_tables; //lr300
        break;
    case 2:
        return mp5_tables; //mp5
        break;
    case 3:
        return thompson_tables; //thompson
        break;
    case 4:
        return csmg_tables; //csmg
        break;
    case 5:
        return m249_tables; //m249
        break;
    }
}

auto t_now = std::chrono::high_resolution_clock::now();




int main()

{
    
    //Menu::setConsole(42,6);
    
    //timeBeginPeriod(1);
    if (!mouse_open()) {
        printf("[-] failed to open ghub macro driver\n");
        system("pause");
    }//driver error
    //loggedIn = Menu::loginPage();
    loggedIn = true;
    double elapsed = 0;
    auto timer = std::chrono::high_resolution_clock::now();
    while (loggedIn)
    {
        while (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(VK_RBUTTON) && recoilStatus)
        {
            double repeatdelay = WeaponHelpers::weaponRepeatDelay(currentWeapon);
            int magsize = WeaponHelpers::magSize(currentWeapon);
            timer = std::chrono::high_resolution_clock::now();
            double time_error = 0;
            for (int i = 1; i < magsize; i++)
            {
                if (!GetAsyncKeyState(VK_LBUTTON)) break;
            
                auto t_now = std::chrono::high_resolution_clock::now();
                Math::Vector2 shot = realRecoilTable(currentWeapon)[i];
                MouseHelpers::SmoothMove(shot, (double)repeatdelay - time_error, t_now, extraX, extraY);
                timer = std::chrono::high_resolution_clock::now();
                elapsed = MouseHelpers::timeDelta(timer, t_now);
                if (elapsed < 138 || currentWeapon != 0)time_error += elapsed - repeatdelay;              
            }
            extraX = 0;
            extraY = 0;
        }

        Menu::KeyboardInput(currentWeapon, currentMuzzle, currentScope, menuUpdate, recoilStatus);
        if (menuUpdate) {
            switch (currentWeapon) {
            case 0:
                if (menuUpdate)MouseHelpers::fillArray(ak_tables, sens, WeaponHelpers::getFov(currentWeapon,currentScope,fov), currentMuzzle, currentScope, currentWeapon, random);
                arrayFilled[0] = true;
                break;
            case 1:
                if (menuUpdate)MouseHelpers::fillArray(lr_tables, sens, WeaponHelpers::getFov(currentWeapon,currentScope,fov), currentMuzzle, currentScope, currentWeapon, random);
                arrayFilled[1] = true;
                break;
            case 2:
                if (menuUpdate)MouseHelpers::fillArray(mp5_tables, sens, WeaponHelpers::getFov(currentWeapon,currentScope,fov), currentMuzzle, currentScope, currentWeapon, random);
                arrayFilled[2] = true;
                break;
            case 3:
                if (menuUpdate)MouseHelpers::fillArray(thompson_tables, sens, WeaponHelpers::getFov(currentWeapon,currentScope,fov), currentMuzzle, currentScope, currentWeapon, random);
                arrayFilled[3] = true;
                break;
            case 4:
                if (menuUpdate)MouseHelpers::fillArray(csmg_tables, sens, WeaponHelpers::getFov(currentWeapon,currentScope,fov), currentMuzzle, currentScope, currentWeapon, random);
                arrayFilled[4] = true;
                break;
            case 5:
                if (menuUpdate)MouseHelpers::fillArray(m249_tables, sens, WeaponHelpers::getFov(currentWeapon,currentScope,fov), currentMuzzle, currentScope, currentWeapon, random);
                arrayFilled[5] = true;
                break;
            }
            Menu::mainMenu(currentWeapon, currentMuzzle, currentScope, menuUpdate, recoilStatus);  
        }   
    }
    std::getchar();
    system("pause");
    mouse_close();
}


