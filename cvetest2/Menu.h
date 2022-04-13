#pragma once
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include "LicenseHelpers.h"
#include <string>
#define _WIN32_WINNT 0x0500
using namespace std;

namespace Menu {

	bool loginPage() {
		system("CLS");
		cout << "INSERT KEY: ";
		std::string key;
		cin >> key;
		std::string hwid = LicenseHelpers::getHWID();
		if (LicenseHelpers::connectToServer(key,hwid)) {
			cout << "logged in!";
				return true;
		}
		else {
			cout << "\nlogin error, check your key or message an admin!\n";
				return false;
		}
	}

	void mainMenu(int &currentWeapon, int &currentMuzzle, int &currentScope, bool &menuUpdate, bool recoilStatus) {
		
		if (menuUpdate) {
			system("CLS");
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			cout << "=================MOON RCS=================";
			cout << "\n[INS]       RECOIL: ";
			if (recoilStatus) {
				SetConsoleTextAttribute(hConsole, 2);
				cout << "ON";
			}
			else {
				SetConsoleTextAttribute(hConsole, 4);
				cout << "OFF";
			}
			SetConsoleTextAttribute(hConsole, 15);
			cout << "\n[LEFT][RIGHT] CURRENT WEAPON: ";
			switch (currentWeapon) {
			case 0:
				cout << "AssaultRifle";
				break;
			case 1:
				cout << "LR300";
				break;
			case 2:
				cout << "MP5A4";
				break;
			case 3:
				cout << "Thompson";
				break;
			case 4:
				cout << "Custom SMG";
				break;
			case 5:
				cout << "M249";
				break;
			}
			cout << "\n[DOWN][UP]    CURRENT SCOPE: ";
			switch (currentScope) {
			case 0:
				cout << "No Scope";
				break;
			case 1:
				cout << "8X Scope";
				break;
			case 2:
				cout << "16X Scope";
				break;
			case 3:
				cout << "Handmade";
				break;
			case 4:
				cout << "Holo";
				break;
			}
			cout << "\n[F5]          SUPRRESSOR:";
			SetConsoleTextAttribute(hConsole, 2);
			if (currentMuzzle == 1) cout << "ON";
			SetConsoleTextAttribute(hConsole, 4);
			if (currentMuzzle == 0) cout << "OFF";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "\n==========================================";
			
			menuUpdate = false;

		}

	}

	void KeyboardInput(int& currentWeapon, int& currentMuzzle, int& currentScope, bool &menuUpdate, bool &recoilStatus) {
		if (GetAsyncKeyState(0x25)) {//left arrow
			currentWeapon--;
			menuUpdate = true;
			Sleep(50);
		}
		if (GetAsyncKeyState(0x27)) { //right arrow
			currentWeapon++;
			menuUpdate = true;
			Sleep(50);
		}
		if (GetAsyncKeyState(0x28)) {//down arrow
			currentScope--;
			menuUpdate = true;
			Sleep(50);
		}
		if (GetAsyncKeyState(0x26)) {//up arrow
			currentScope++;
			menuUpdate = true;
			Sleep(50);
		}
		if (GetAsyncKeyState(0x74)) {
			if (currentMuzzle == 0) {
				currentMuzzle++;
				Sleep(50);
			}
			else {
				if (currentMuzzle >= 1) currentMuzzle--;
			}
			menuUpdate = true;
		}
		if (GetAsyncKeyState(0x2D)) { //0X90 = NUMLOCK 0X2D insert
			recoilStatus = !recoilStatus;
			menuUpdate = true;
			Sleep(50);
		}
		if (currentWeapon < 0) currentWeapon = 0;
		if (currentWeapon > 5) currentWeapon = 5;
		if (currentScope < 0) currentScope = 0;
		if (currentScope > 4) currentScope = 4;
		
	}

	string printstring(int n)
	{
		char letters[33] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
		'r','s','t','u','v','w','x',
		'y','z', '1','2','3','4','0','*','/' };
		string ran = "";
		for (int i = 0; i < n; i++)
			ran = ran + letters[rand() % 33];
		return ran;
	}

	void setConsole(int Width, int Height)
	{
		HWND consoleWindow = GetConsoleWindow();
		SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
		_COORD coord;
		coord.X = Width;
		coord.Y = Height;

		_SMALL_RECT Rect;
		Rect.Top = 0;
		Rect.Left = 0;
		Rect.Bottom = Height - 1;
		Rect.Right = Width - 1;

		HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);// Get Handle 
		SetWindowTextA(consoleWindow,printstring(24).c_str());
		SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
		SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
	}


	

}