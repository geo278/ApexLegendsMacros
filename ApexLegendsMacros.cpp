// ApexLegendsMacros.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "iostream"
#include "Windows.h"

using namespace std;

bool enabled = true;

void slideBack() {
	INPUT VK_CONTROL_keyDown;
	VK_CONTROL_keyDown.type = INPUT_KEYBOARD;
	VK_CONTROL_keyDown.ki.wScan = MapVirtualKey(VK_CONTROL, MAPVK_VK_TO_VSC); // hardware scan code
	VK_CONTROL_keyDown.ki.time = 0;
	VK_CONTROL_keyDown.ki.wVk = VK_CONTROL; // virtual-key code
	VK_CONTROL_keyDown.ki.dwExtraInfo = 0;
	VK_CONTROL_keyDown.ki.dwFlags = 0; // 0 for key down
	INPUT VK_CONTROL_keyUp = VK_CONTROL_keyDown;
	VK_CONTROL_keyUp.ki.dwFlags = KEYEVENTF_KEYUP;

	INPUT VK_SPACE_keyDown = VK_CONTROL_keyDown;
	VK_SPACE_keyDown.ki.wScan = MapVirtualKey(VK_SPACE, MAPVK_VK_TO_VSC); // hardware scan code
	VK_SPACE_keyDown.ki.wVk = VK_SPACE; // virtual-key code
	INPUT VK_SPACE_keyUp = VK_SPACE_keyDown;
	VK_SPACE_keyUp.ki.dwFlags = KEYEVENTF_KEYUP;

	while (1) {
		while ((GetKeyState(0x53) & 0x100) != 0 && (GetKeyState(VK_RBUTTON) & 0x100) != 0 && enabled) {
			Sleep(150);
			if ((GetKeyState(0x53) & 0x100) == 0) { break; }
			SendInput(1, &VK_SPACE_keyDown, sizeof(INPUT));
			Sleep(200);
			SendInput(1, &VK_SPACE_keyUp, sizeof(INPUT));
			if ((GetKeyState(0x53) & 0x100) == 0) { break; }
			Sleep(200);
			if ((GetKeyState(0x53) & 0x100) == 0) { break; }
			SendInput(1, &VK_CONTROL_keyDown, sizeof(INPUT));
			Sleep(200);
			if ((GetKeyState(0x53) & 0x100) == 0) {
				SendInput(1, &VK_CONTROL_keyUp, sizeof(INPUT));
				break; 
			}
			Sleep(200);
			if ((GetKeyState(0x53) & 0x100) == 0) {
				SendInput(1, &VK_CONTROL_keyUp, sizeof(INPUT));
				break;
			}
			Sleep(200);
			if ((GetKeyState(0x53) & 0x100) == 0) {
				SendInput(1, &VK_CONTROL_keyUp, sizeof(INPUT));
				break;
			}
			Sleep(200);
			if ((GetKeyState(0x53) & 0x100) == 0) {
				SendInput(1, &VK_CONTROL_keyUp, sizeof(INPUT));
				break;
			}
			Sleep(200);
			if ((GetKeyState(0x53) & 0x100) == 0) {
				SendInput(1, &VK_CONTROL_keyUp, sizeof(INPUT));
				break;
			}
			Sleep(100);
			SendInput(1, &VK_CONTROL_keyUp, sizeof(INPUT));
			Sleep(400);
		}
		Sleep(1);
	}
}

void slideForward() {
	INPUT C_keyDown;
	C_keyDown.type = INPUT_KEYBOARD;
	C_keyDown.ki.wScan = MapVirtualKey(0x43, MAPVK_VK_TO_VSC); // hardware scan code
	C_keyDown.ki.time = 0;
	C_keyDown.ki.wVk = 0x43; // virtual-key code
	C_keyDown.ki.dwExtraInfo = 0;
	C_keyDown.ki.dwFlags = 0; // 0 for key down
	INPUT C_keyUp = C_keyDown;
	C_keyUp.ki.dwFlags = KEYEVENTF_KEYUP;

	INPUT VK_SPACE_keyDown = C_keyDown;
	VK_SPACE_keyDown.ki.wScan = MapVirtualKey(VK_SPACE, MAPVK_VK_TO_VSC); // hardware scan code
	VK_SPACE_keyDown.ki.wVk = VK_SPACE; // virtual-key code
	INPUT VK_SPACE_keyUp = VK_SPACE_keyDown;
	VK_SPACE_keyUp.ki.dwFlags = KEYEVENTF_KEYUP;

	while (1) {
		while (((GetKeyState(0x57) & 0x100) != 0) && ((GetKeyState(VK_SHIFT) & 0x100) != 0) && enabled) {
			Sleep(200);
			if ((GetKeyState(0x57) & 0x100) == 0 || (GetKeyState(VK_SHIFT) & 0x100) == 0) { break; }
			Sleep(200);
			if ((GetKeyState(0x57) & 0x100) == 0 || (GetKeyState(VK_SHIFT) & 0x100) == 0) { break; }
			Sleep(200);
			if ((GetKeyState(0x57) & 0x100) == 0 || (GetKeyState(VK_SHIFT) & 0x100) == 0) { break; }
			Sleep(200);
			if ((GetKeyState(0x57) & 0x100) == 0 || (GetKeyState(VK_SHIFT) & 0x100) == 0) { break; }
			Sleep(200);
			if ((GetKeyState(0x57) & 0x100) == 0 || (GetKeyState(VK_SHIFT) & 0x100) == 0) { break; }
			SendInput(1, &C_keyDown, sizeof(INPUT));
			Sleep(350);
			SendInput(1, &C_keyUp, sizeof(INPUT));
			Sleep(50);
			if ((GetKeyState(0x57) & 0x100) == 0 || (GetKeyState(VK_SHIFT) & 0x100) == 0) { break; }
			SendInput(1, &VK_SPACE_keyDown, sizeof(INPUT));
			Sleep(200);
			SendInput(1, &VK_SPACE_keyUp, sizeof(INPUT));
			Sleep(200);
			if ((GetKeyState(0x57) & 0x100) == 0 || (GetKeyState(VK_SHIFT) & 0x100) == 0) { break; }
			Sleep(200);
			if ((GetKeyState(0x57) & 0x100) == 0 || (GetKeyState(VK_SHIFT) & 0x100) == 0) { break; }
			Sleep(50);
			if ((GetKeyState(0x57) & 0x100) == 0 || (GetKeyState(VK_SHIFT) & 0x100) == 0) { break; }
		}
		Sleep(1);
	}
}

void trackEnabled() {
	while (1) {
		if ((GetKeyState(VK_F1) & 0x100) != 0) {
			enabled = !enabled;
			cout << "F1" << endl;
			Sleep(500);
		}
		Sleep(5);
	}
}

void Input() {
	while (1) {
		cout << "Enter int to change value";
		cin >> enabled;
		Sleep(1000);
	}
}

int main() {
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)trackEnabled, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)slideBack, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)slideForward, 0, 0, 0);


	while (1) {
		Sleep(1000);
	}
	return 0;
}
