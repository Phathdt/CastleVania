#include "Windows.h"


Windows* Windows::_windows = 0;
Windows * Windows::getCurrentWindows()
{
	if (_windows == 0)
		_windows = new Windows();
	return _windows;
}

bool Windows::initWindows()
{
	WNDCLASSEX WndcEx;
	ZeroMemory(&WndcEx, sizeof(WndcEx));
	WndcEx.cbSize = sizeof(WNDCLASSEX);
	WndcEx.hInstance = this->_hInstance;
	WndcEx.lpfnWndProc = (WNDPROC)WndProc;
	WndcEx.lpszClassName = GAME_NAME;
	WndcEx.cbClsExtra = 0;
	WndcEx.cbWndExtra = 0;
	WndcEx.hbrBackground = CreateSolidBrush(RGB(10, 255, 255));
	WndcEx.hCursor = LoadCursor(0, IDC_ARROW);
	WndcEx.style = CS_HREDRAW | CS_VREDRAW; // cho thay doi kich thuoc
	if (!RegisterClassEx(&WndcEx))
	{
		return false;
	}

	this->_hWindows = CreateWindow(
		GAME_NAME,
		GAME_NAME, // TITLE của cửa sổ
		WS_OVERLAPPEDWINDOW, // style của cửa sổ
		CW_USEDEFAULT, // tọa độ x khi cửa sổ xuất hiện
		CW_USEDEFAULT, // tọa độ y khi cửa sổ xuất hiện
		_width, // chiều dài cửa sổ
		_height, // chiều cao cửa sổ
		0, // handle window parent của của sổ hiện tại. Để là 0
		0, // handle đến Menu. Để là 0
		this->_hInstance, // Handle Instance của ứng dụng
		0);
	if (!this->_hWindows) // Kiểm tra tạo thành công.
	{
		return false;
	}
	ShowWindow(this->_hWindows, SW_SHOWNORMAL); // show cửa sổ lên màn hình
	UpdateWindow(this->_hWindows); // Update cửa sổ theo thời gian
	return true;
}

LRESULT Windows::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

Windows::Windows()
{
}


Windows::~Windows()
{

}
