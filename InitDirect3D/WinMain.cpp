#include "WinMain.h"
#include "D3DApp.h"
#include <algorithm>
#include <numbers>
#include <cmath>
#include <windowsx.h>

namespace
{
	UINT_PTR timer;
	D3D12Sample *direct3DController;
}

INT WINAPI wWinMain(_In_ [[maybe_unused]] HINSTANCE instance,
	_In_opt_ [[maybe_unused]] HINSTANCE prev_instance,
	_In_ [[maybe_unused]] PWSTR cmd_line,
	_In_ [[maybe_unused]] INT cmd_show) {

	const wchar_t CLASS_NAME[] = TEXT("Sample Window Class");

	WNDCLASSEXW wind;
	wind.cbSize = sizeof(WNDCLASSEX);
	wind.style = 0;
	wind.lpfnWndProc = WindowProc;
	wind.cbClsExtra = 0;
	wind.cbWndExtra = 0;
	wind.hInstance = instance;
	wind.hIcon = NULL;
	wind.hCursor = NULL;
	wind.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wind.lpszMenuName = NULL;
	wind.lpszClassName = CLASS_NAME;
	wind.hIconSm = 0;

	RegisterClassEx(&wind);

	HWND hwnd = CreateWindowEx(
		0,
		wind.lpszClassName,
		TEXT("Learn to Program Windows"),
		WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,
		NULL,
		wind.hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		return 1;
	}

	ShowWindow(hwnd, cmd_show);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		timer = SetTimer(hwnd, 1000, 20, NULL);
		return TRUE;
	}
	case WM_CREATE:
	{
		direct3DController = new D3D12Sample(0, 0, TEXT("Direct3D"), hwnd);
		return 0;
	}
	case WM_DESTROY:
	{
		direct3DController->OnDestroy();
		KillTimer(hwnd, timer);
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		direct3DController->OnRender();
		// ValidateRect(hwnd, NULL);
		return 0;
	}
	case WM_TIMER:
	{
		// OnTimer(hwnd);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		// OnMouseMove(hwnd, { (float)GET_X_LPARAM(lParam),  (float)GET_Y_LPARAM(lParam) });
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		// OnMouseClick(hwnd);
		return 0;
	}
	case WM_SIZE:
	{
		// OnResize(hwnd);
		return 0;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


