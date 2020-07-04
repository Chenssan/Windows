#include<windows.h>
#include<iostream>
using namespace std;
const string ProgramTile = "Hello Windows";
//the winsow event callback function
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT drawRect;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		for (int n = 0; n < 20; n++)
		{
			int x = n * 20;
			int y = n * 20;
			drawRect = { x,y,x + 100,y + 20 };
			DrawText(hdc, ProgramTile.c_str(), ProgramTile.length(), &drawRect, DT_CENTER);
		}
		EndPaint(hWnd, &ps);//stop drawing
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
//Helper hunction to set up the window properties
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ProgramTile.c_str();
	wc.hIconSm = NULL;
	return RegisterClassEx(&wc);
}
//Helper function to create the window and refresh it
bool InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	//create a new window
	HWND hWnd = CreateWindow(
		ProgramTile.c_str(), ProgramTile.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640, 480,
		NULL, NULL,
		hInstance, 
		NULL);
	//was there an error creating the window?
	if (hWnd == 0)return 0;

	//dispaly the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return 1;	
}
//Entry point for a windows program

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//create the window
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))return 0;

	//mian message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}