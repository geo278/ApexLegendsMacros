// ApexLegendsMacros.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "iostream"
#include "Windows.h"
#include "magnification.h"

using namespace std;

bool enabled = true;
//bool g7ScoutMode = false;
int xSize = GetSystemMetrics(SM_CXSCREEN);
int ySize = GetSystemMetrics(SM_CYSCREEN);

float zoom = (float)1.25;

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
			if ((GetKeyState(VK_RBUTTON) & 0x100) != 0 &&enabled) { 
				SetZoomB(zoom);
				//MagSetFullscreenColorEffect(&g_MagEffectSaturation);
				//cout << "Zoom In" << endl;
				while ((GetKeyState(VK_RBUTTON) & 0x100) != 0) { Sleep(150); } 
			}
			else {
				SetZoomB(1);
				//MagSetFullscreenColorEffect(&g_MagEffectIdentity);
				//cout << "Restore" << endl;
				while ((GetKeyState(VK_RBUTTON) & 0x100) == 0) { Sleep(10); }
			}
			Sleep(5);
		}
	}
}

void reticule() {
	RGBQUAD centerColour;
	centerColour.rgbRed = 0;
	centerColour.rgbGreen = 255;
	centerColour.rgbBlue = 15;
	
	const int verticalWidth = 1;
	const int verticalHeight = 14;
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
	
	const int horizontalWidth = 14;
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

	const int dotWidth = 2;
	const int dotHeight = 2;
	HDC dcD = GetDC(HWND_DESKTOP);
	BITMAPINFOHEADER bmiD = { 0 };
	bmiD.biSize = sizeof(BITMAPINFOHEADER);
	bmiD.biPlanes = 1;
	bmiD.biBitCount = 32;
	bmiD.biWidth = dotWidth;
	bmiD.biHeight = -dotHeight;
	bmiD.biCompression = BI_RGB;
	bmiD.biSizeImage = 0; // 3 * ScreenX * ScreenY
	RGBQUAD dotPixels[dotWidth * dotHeight];
	for (int i = 0; i < dotWidth * dotHeight; i++) {
		dotPixels[i] = centerColour;
	}

	while (true) {
		if (enabled) {
			// Area:
			SetDIBitsToDevice(dcV, xSize / 2 - 2 - horizontalWidth, ySize / 2 - 1 - verticalHeight * 2, verticalWidth, verticalHeight, 0, 0, 0, verticalHeight, &verticalPixels, (BITMAPINFO*)&bmiV, DIB_RGB_COLORS);
			SetDIBitsToDevice(dcV, xSize / 2 + horizontalWidth,		ySize / 2 - 1 - verticalHeight * 2, verticalWidth, verticalHeight, 0, 0, 0, verticalHeight, &verticalPixels, (BITMAPINFO*)&bmiV, DIB_RGB_COLORS);
			SetDIBitsToDevice(dcV, xSize / 2 - 2 - horizontalWidth, ySize / 2 + verticalHeight, verticalWidth, verticalHeight, 0, 0, 0, verticalHeight, &verticalPixels, (BITMAPINFO*)&bmiV, DIB_RGB_COLORS);
			SetDIBitsToDevice(dcV, xSize / 2 + horizontalWidth,		ySize / 2 + verticalHeight, verticalWidth, verticalHeight, 0, 0, 0, verticalHeight, &verticalPixels, (BITMAPINFO*)&bmiV, DIB_RGB_COLORS);

			SetDIBitsToDevice(dcH, xSize / 2 - 1 - horizontalWidth * 2, ySize / 2 - 2 - verticalHeight, horizontalWidth, horizontalHeight, 0, 0, 0, horizontalHeight, &horizontalPixels, (BITMAPINFO*)&bmiH, DIB_RGB_COLORS);
			SetDIBitsToDevice(dcH, xSize / 2 + horizontalWidth,			ySize / 2 - 2 - verticalHeight, horizontalWidth, horizontalHeight, 0, 0, 0, horizontalHeight, &horizontalPixels, (BITMAPINFO*)&bmiH, DIB_RGB_COLORS);
			SetDIBitsToDevice(dcH, xSize / 2 - 1 - horizontalWidth * 2, ySize / 2 + verticalHeight, horizontalWidth, horizontalHeight, 0, 0, 0, horizontalHeight, &horizontalPixels, (BITMAPINFO*)&bmiH, DIB_RGB_COLORS);
			SetDIBitsToDevice(dcH, xSize / 2 + horizontalWidth,			ySize / 2 + verticalHeight, horizontalWidth, horizontalHeight, 0, 0, 0, horizontalHeight, &horizontalPixels, (BITMAPINFO*)&bmiH, DIB_RGB_COLORS);
			// Vertical:
			//SetDIBitsToDevice(dcV, xSize / 2 - 1, ySize / 2 - verticalHeight, verticalWidth, verticalHeight, 0, 0, 0, verticalHeight, &verticalPixels, (BITMAPINFO*)&bmiV, DIB_RGB_COLORS)

			// Dot:
			//SetDIBitsToDevice(dcD, xSize / 2 - dotWidth / 2, (ySize / 2 - dotHeight / 2), dotWidth, dotHeight, 0, 0, 0, dotHeight, &dotPixels, (BITMAPINFO*)&bmiD, DIB_RGB_COLORS);


		}
		Sleep(3);
	}
}

void recoilCompensation() { // // // // MOUSEEVENTF_LEFTDOWN
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
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && (GetKeyState(VK_RBUTTON) & 0x100) != 0&& enabled) {
			//SendInput(1, &VK_NUMPAD0_keyDown, sizeof(INPUT));
			for (int i = 65; i > 0; i--) {
				mouse_event(MOUSEEVENTF_MOVE, 0, 2, 0, 0);
				Sleep(14);
				if ((GetKeyState(VK_LBUTTON) & 0x100) == 0) {
					break;
				}
			}
			while ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
				mouse_event(MOUSEEVENTF_MOVE, 0, 1, 0, 0);
				Sleep(14);
			}
			//SendInput(1, &VK_NUMPAD0_keyUp, sizeof(INPUT));
		}
		Sleep(1);
	}
}

void crouchCompensation() {
	while (true) {
		if ((GetKeyState(VK_CONTROL) & 0x100) != 0 && enabled) {
			for (int i = 0; i < 20; i++) {
				mouse_event(MOUSEEVENTF_MOVE, 0, -2, 0, 0);
				Sleep(12);
			}
			while ((GetKeyState(VK_CONTROL) & 0x100) != 0) {
				Sleep(10);
			}
			for (int i = 0; i < 20; i++) {
				mouse_event(MOUSEEVENTF_MOVE, 0, 2, 0, 0);
				Sleep(10);
			}
		}
		Sleep(10);
	}
}

void extraAimStrafe() {
	while (true) {
		if ((GetKeyState(0x41) & 0x100) != 0 && enabled) { // A				
			mouse_event(MOUSEEVENTF_MOVE, -2, 0, 0, 0);
		}
		if ((GetKeyState(0x44) & 0x100) != 0 && enabled) { // D
			mouse_event(MOUSEEVENTF_MOVE, 2, 0, 0, 0);
		}
		Sleep(5);
	}
}

void passiveBHop() {
	INPUT VK_SPACE_keyDown;
	VK_SPACE_keyDown.type = INPUT_KEYBOARD;
	VK_SPACE_keyDown.ki.wScan = MapVirtualKey(VK_SPACE, MAPVK_VK_TO_VSC); // hardware scan code
	VK_SPACE_keyDown.ki.time = 0;
	VK_SPACE_keyDown.ki.wVk = VK_SPACE; // virtual-key code
	VK_SPACE_keyDown.ki.dwExtraInfo = 0;
	VK_SPACE_keyDown.ki.dwFlags = 0; // 0 for key down
	INPUT VK_SPACE_keyUp = VK_SPACE_keyDown;
	VK_SPACE_keyUp.ki.dwFlags = KEYEVENTF_KEYUP;

	while (true) {
		while ((GetKeyState(VK_CONTROL) & 0x100) != 0 && (GetKeyState(0x53) & 0x100) != 0 && enabled) {
			SendInput(1, &VK_SPACE_keyDown, sizeof(INPUT));
			Sleep(10);
			SendInput(1, &VK_SPACE_keyUp, sizeof(INPUT));
			Sleep(10);
		}
		Sleep(1);
	}
}
void backwardBHop() {
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

	bool release = false;

	while (true) {
		while ((GetKeyState(0x53) & 0x100) != 0 && (GetKeyState(VK_RBUTTON) & 0x100) == 0 && enabled) {
			release = false;
			for (int i = 0; i < 15; i++) {
				Sleep(10);
				if ((GetKeyState(0x53) & 0x100) == 0) {
					release = true;
					break;
				}
			}
			if (!release) {
				SendInput(1, &VK_CONTROL_keyDown, sizeof(INPUT));
				while ((GetKeyState(0x53) & 0x100) != 0) {
					Sleep(10);
				}
				SendInput(1, &VK_CONTROL_keyUp, sizeof(INPUT));
			}
		}
		Sleep(5);
	}
}

void pathfinderJump() {
	INPUT VK_SPACE_keyDown;
	VK_SPACE_keyDown.type = INPUT_KEYBOARD;
	VK_SPACE_keyDown.ki.wScan = MapVirtualKey(VK_SPACE, MAPVK_VK_TO_VSC); // hardware scan code
	VK_SPACE_keyDown.ki.time = 0;
	VK_SPACE_keyDown.ki.wVk = VK_SPACE; // virtual-key code
	VK_SPACE_keyDown.ki.dwExtraInfo = 0;
	VK_SPACE_keyDown.ki.dwFlags = 0; // 0 for key down
	INPUT VK_SPACE_keyUp = VK_SPACE_keyDown;
	VK_SPACE_keyUp.ki.dwFlags = KEYEVENTF_KEYUP;
	while (true) {
		if ((GetKeyState(0x46) & 0x100) != 0 && enabled) { // if F key pressed
			Sleep(450);
			for (int i = 0; i < 10; i++) {
				SendInput(1, &VK_SPACE_keyDown, sizeof(INPUT));
				Sleep(20);
				SendInput(1, &VK_SPACE_keyUp, sizeof(INPUT));
				Sleep(10);
			}
		}
		Sleep(10);
	}
}


RGBQUAD* capture(POINT a, POINT b) { /////////////////
	int width = 2;
	int height = 2;
	int gridSize = width * height;
	// copy screen to bitmap
	HDC     hScreen = GetDC(NULL);
	HDC     hDC = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, abs(b.x - a.x), abs(b.y - a.y));
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL    bRet = BitBlt(hDC, 0, 0, abs(b.x - a.x), abs(b.y - a.y), hScreen, a.x, a.y, SRCCOPY); // BitBlt does the copying

	/*
	// save bitmap to clipboard
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hBitmap);
	CloseClipboard();
	*/

	// Array conversion:
	RGBQUAD* pixels = new RGBQUAD[gridSize];

	BITMAPINFOHEADER bmi = { 0 };
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biPlanes = 1;
	bmi.biBitCount = 32;
	bmi.biWidth = width;
	bmi.biHeight = -height;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 0;// 3 * ScreenX * ScreenY;

	GetDIBits(hDC, hBitmap, 0, height, pixels, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

	// clean up
	SelectObject(hDC, old_obj);
	DeleteDC(hDC);
	ReleaseDC(NULL, hScreen);
	DeleteObject(hBitmap);
	return pixels;
}
void trackEnabled() {
	POINT expectLightA, expectLightB, expectDarkA, expectDarkB;
	expectLightA.x = 3;
	expectLightA.y = 50;
	expectLightB.x = 4;
	expectLightB.y = 51;
	expectDarkA.x = 2;
	expectDarkA.y = 51;
	expectDarkB.x = 3;
	expectDarkB.y = 52;

	while (1) {
		RGBQUAD expectLight = capture(expectLightA, expectLightB)[0];
		RGBQUAD expectDark = capture(expectDarkA, expectDarkB)[0];
		//cout << (int)expectLight.rgbRed << "  " << (int)expectLight.rgbGreen << "  " << (int)expectLight.rgbBlue << "  " << endl;
		//cout << (int)expectDark.rgbRed << "  " << (int)expectDark.rgbGreen << "  " << (int)expectDark.rgbBlue << "  " << endl;
		if (((int)expectLight.rgbRed > 230 && (int)expectLight.rgbGreen > 230 && (int)expectLight.rgbBlue > 230 &&
			(int)expectDark.rgbRed < 200 && (int)expectDark.rgbGreen < 80 && (int)expectDark.rgbBlue < 80) || ((GetKeyState(VK_RBUTTON) & 0x100) != 0)) {
			enabled = true;
		} else {
			enabled = false;
		}
		Sleep(200);

		//if ((GetKeyState(VK_F2) & 0x100) != 0) {
		//	enabled = !enabled;
		//	enabled ? cout << "enabled" << endl : cout << "disabled" << endl;
		//	Sleep(500);
		//}

		//Sleep(5);
	}
}

int main() {
	SetZoomB(1);
	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)extraAimStrafe, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)recoilCompensation, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)reticule, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)passiveBHop, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)backwardBHop, 0, 0, 0);
	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)trackZoom, 0, 0, 0);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)trackEnabled, 0, 0, 0);

	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pathfinderJump, 0, 0, 0);


	while (1) {
		Sleep(1000);

		// for testing
		//Sleep(50);
		//if ((GetKeyState(VK_SHIFT) & 0x100) != 0) {
		//	mouse_event(MOUSEEVENTF_MOVE, 500, 0, 0, 0);
		//	Sleep(500);
		//}

		//HWND test = GetActiveWindow();
		//cout << test << endl;
	}
	return 0;
}
