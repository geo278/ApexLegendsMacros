// ApexLegendsMacros.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "iostream"
#include "Windows.h"
#include "magnification.h"

using namespace std;

bool enabled = true;
int xSize = GetSystemMetrics(SM_CXSCREEN);
int ySize = GetSystemMetrics(SM_CYSCREEN);

float zoom = (float) 2;

BOOL SetZoomB(float magFactor) {
	if (magFactor < 1.0) {
		return FALSE;
	}
	xSize = GetSystemMetrics(SM_CXSCREEN);
	ySize = GetSystemMetrics(SM_CYSCREEN);
	//cout << xSize << "  " << ySize << endl;
	if (xSize == 2048 && ySize == 1152) {
		xSize = 2560;
		ySize = 1440;
	}
	if (xSize == 2133 && ySize == 1200) {
		xSize = 3200;
		ySize = 1800;
	}
	int xOffset = (int)((float)xSize * (1.0 - (1.0 / magFactor)) / 2.0);
	int yOffset = (int)((float)ySize * (1.0 - (1.0 / magFactor)) / 2.0);
	//cout << (int)(float)GetSystemMetrics(SM_CXSCREEN) << "  " << (int)(float)GetSystemMetrics(SM_CYSCREEN) << endl;
	return MagSetFullscreenTransform(magFactor, xOffset, yOffset);
}

void trackZoom() {
	if (MagInitialize()) {
		cout << "Initialized" << endl << endl;
		while (true) {
			if ((GetKeyState(VK_RBUTTON) & 0x100) != 0 && enabled) {
				SetZoomB(zoom);
				//MagSetFullscreenColorEffect(&g_MagEffectSaturation);
				cout << "Zoom In" << endl;
				while ((GetKeyState(VK_RBUTTON) & 0x100) != 0) { Sleep(10); }
			} else {
				SetZoomB(1);
				//MagSetFullscreenColorEffect(&g_MagEffectIdentity);
				cout << "Restore" << endl;
				while ((GetKeyState(VK_RBUTTON) & 0x100) == 0) { Sleep(150); }
			}
			Sleep(5);
		}
	}
}

void reticule() {
	RGBQUAD centerColour;
	centerColour.rgbRed = 0;
	centerColour.rgbBlue = 0;
	centerColour.rgbGreen = 255;

	const int verticalWidth = 1;
	const int verticalHeight = 20;
	HDC dcV = GetDC(HWND_DESKTOP);
	BITMAPINFOHEADER bmiV = { 0 };
	bmiV.biSize = sizeof(BITMAPINFOHEADER);
	bmiV.biPlanes = 1;
	bmiV.biBitCount = 32;
	bmiV.biWidth = verticalWidth;
	bmiV.biHeight = -verticalHeight;
	bmiV.biCompression = BI_RGB;
	bmiV.biSizeImage = 0; // 3 * ScreenX * ScreenY
	RGBQUAD verticalPixels[verticalWidth * verticalHeight];
	for (int i = 0; i < verticalWidth * verticalHeight; i++) {
		verticalPixels[i] = centerColour;
	}

	const int horizontalWidth = 20;
	const int horizontalHeight = 1;
	HDC dcH = GetDC(HWND_DESKTOP);
	BITMAPINFOHEADER bmiH = { 0 };
	bmiH.biSize = sizeof(BITMAPINFOHEADER);
	bmiH.biPlanes = 1;
	bmiH.biBitCount = 32;
	bmiH.biWidth = horizontalWidth;
	bmiH.biHeight = -horizontalHeight;
	bmiH.biCompression = BI_RGB;
	bmiH.biSizeImage = 0; // 3 * ScreenX * ScreenY
	RGBQUAD horizontalPixels[horizontalWidth * horizontalHeight];
	for (int i = 0; i < horizontalWidth * horizontalHeight; i++) {
		horizontalPixels[i] = centerColour;
	}

	while (true) {
		if (enabled) {
			SetDIBitsToDevice(dcV, xSize / 2 - 10, ySize / 2 - 10, verticalWidth, verticalHeight, 0, 0, 0, verticalHeight, &verticalPixels, (BITMAPINFO*)&bmiV, DIB_RGB_COLORS);
			SetDIBitsToDevice(dcH, xSize / 2 - 10, ySize / 2 - 10, horizontalWidth, horizontalHeight, 0, 0, 0, horizontalHeight, &horizontalPixels, (BITMAPINFO*)&bmiH, DIB_RGB_COLORS);
			SetDIBitsToDevice(dcV, xSize / 2 + 9, ySize / 2 - 10, verticalWidth, verticalHeight, 0, 0, 0, verticalHeight, &verticalPixels, (BITMAPINFO*)&bmiV, DIB_RGB_COLORS);
			SetDIBitsToDevice(dcH, xSize / 2 - 10, ySize / 2 + 9, horizontalWidth, horizontalHeight, 0, 0, 0, horizontalHeight, &horizontalPixels, (BITMAPINFO*)&bmiH, DIB_RGB_COLORS);
		}
		Sleep(3);
	}
}

void slideBack() {
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

	while (true) {
		while ((GetKeyState(0x53) & 0x100) != 0 && (GetKeyState(VK_RBUTTON) & 0x100) == 0 && enabled) {
			Sleep(150);
			if ((GetKeyState(0x53) & 0x100) == 0) { break; }

			SendInput(1, &VK_SPACE_keyDown, sizeof(INPUT));
			Sleep(68);
			SendInput(1, &VK_SPACE_keyUp, sizeof(INPUT));
			Sleep(68);

			SendInput(1, &VK_SPACE_keyDown, sizeof(INPUT));
			Sleep(68);
			SendInput(1, &VK_SPACE_keyUp, sizeof(INPUT));
			Sleep(68);

			SendInput(1, &VK_SPACE_keyDown, sizeof(INPUT));
			Sleep(68);
			SendInput(1, &VK_SPACE_keyUp, sizeof(INPUT));
			Sleep(68);

			if ((GetKeyState(0x53) & 0x100) == 0) { break; }
			SendInput(1, &C_keyDown, sizeof(INPUT));
			Sleep(200);
			SendInput(1, &C_keyUp, sizeof(INPUT));

			for (int i = 0; i < 6; i++) {
				Sleep(200);
				if ((GetKeyState(0x53) & 0x100) == 0) {
					SendInput(1, &C_keyUp, sizeof(INPUT));
					break;
				}
			}
			SendInput(1, &C_keyDown, sizeof(INPUT));
			Sleep(50);
			SendInput(1, &C_keyUp, sizeof(INPUT));
			Sleep(50);
		}
		Sleep(5);
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

	while (true) {
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
		Sleep(5);
	}
}

void passiveBHop() {
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

	while (true) {
		while ((GetKeyState(VK_CONTROL) & 0x100) != 00) {
			SendInput(1, &VK_SPACE_keyDown, sizeof(INPUT));
			Sleep(196);
			SendInput(1, &VK_SPACE_keyUp, sizeof(INPUT));
			Sleep(196);
		}
		Sleep(1);
	}
}

void passiveRecoilCompensation() {
	while (true) {
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && (GetKeyState(VK_RBUTTON) & 0x100) != 0 && enabled) {
			mouse_event(MOUSEEVENTF_MOVE, 0, 1, 0, 0);
			Sleep(25);
		}
		Sleep(5);
	}
}
void passiveStrafeCompensation() {
	while (true) {
		if ((GetKeyState(0x44) & 0x100) != 0 && enabled) { // D causes leftward mouse movement
			mouse_event(MOUSEEVENTF_MOVE, -1, 0, 0, 0);
		}
		if ((GetKeyState(0x41) & 0x100) != 0 && enabled) { // A causes rightward mouse movement
			mouse_event(MOUSEEVENTF_MOVE, 1, 0, 0, 0);
		}
		Sleep(15);
	}
}

void autoSwapWeapon() {
	INPUT VK_NUMPAD0_keyDown;
	VK_NUMPAD0_keyDown.type = INPUT_KEYBOARD;
	VK_NUMPAD0_keyDown.ki.wScan = MapVirtualKey(VK_NUMPAD0, MAPVK_VK_TO_VSC); // hardware scan code
	VK_NUMPAD0_keyDown.ki.time = 0;
	VK_NUMPAD0_keyDown.ki.wVk = VK_NUMPAD0; // virtual-key code
	VK_NUMPAD0_keyDown.ki.dwExtraInfo = 0;
	VK_NUMPAD0_keyDown.ki.dwFlags = 0; // 0 for key down
	INPUT VK_NUMPAD0_keyUp = VK_NUMPAD0_keyDown;
	VK_NUMPAD0_keyUp.ki.dwFlags = KEYEVENTF_KEYUP;

	while (true) {
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && enabled) {
			while ((GetKeyState(VK_LBUTTON) & 0x100) != 0 || (GetKeyState(VK_RBUTTON) & 0x100) != 0) {
				Sleep(10);
			}
			SendInput(1, &VK_NUMPAD0_keyDown, sizeof(INPUT));
			Sleep(10);
			SendInput(1, &VK_NUMPAD0_keyUp, sizeof(INPUT));
			Sleep(4000);
		}
		Sleep(5);
	}
}

void autoClick() {
	INPUT VK_NUMPAD1_keyDown;
	VK_NUMPAD1_keyDown.type = INPUT_KEYBOARD;
	VK_NUMPAD1_keyDown.ki.wScan = MapVirtualKey(VK_NUMPAD1, MAPVK_VK_TO_VSC); // hardware scan code
	VK_NUMPAD1_keyDown.ki.time = 0;
	VK_NUMPAD1_keyDown.ki.wVk = VK_NUMPAD1; // virtual-key code
	VK_NUMPAD1_keyDown.ki.dwExtraInfo = 0;
	VK_NUMPAD1_keyDown.ki.dwFlags = 0; // 0 for key down
	INPUT  VK_NUMPAD1_keyUp = VK_NUMPAD1_keyDown;
	VK_NUMPAD1_keyUp.ki.dwFlags = KEYEVENTF_KEYUP;

	while (true) {
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && enabled) {
			// mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			SendInput(1, &VK_NUMPAD1_keyDown, sizeof(INPUT));
			Sleep(5);
			// mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); // Left click
			SendInput(1, &VK_NUMPAD1_keyUp, sizeof(INPUT));
		}
		Sleep(5);
	}
}

void trackEnabled() {
	while (1) {
		if ((GetKeyState(VK_F2) & 0x100) != 0) {
			enabled = !enabled;
			enabled ? cout << "enabled" << endl : cout << "disabled" << endl;
			Sleep(500);
		}
		Sleep(5);
	}
}

void zoomInput() {
	while (1) {
		cout << "Enter number to change zoom value ( current value: " << zoom << " )" << endl;
		cin >> zoom;
		Sleep(500);
	}
}

int main() {
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)trackEnabled, 0, 0, 0);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)slideBack, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)slideForward, 0, 0, 0);
	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)passiveBHop, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)passiveRecoilCompensation, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)passiveStrafeCompensation, 0, 0, 0);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)autoClick, 0, 0, 0);
	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)autoSwapWeapon, 0, 0, 0);


	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)reticule, 0, 0, 0); 
	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)zoomInput, 0, 0, 0);
	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)trackZoom, 0, 0, 0);

	while (1) {
		Sleep(1000);
	}
	return 0;
}
