#define _CRT_SECURE_NO_WARNINGS 1

#include"Head.h"

bool IfReturn()
{
	static bool L = false;
	//bool R = GetAsyncKeyState(VK_RETURN);
	MOUSEMSG msg = { 0 };

	if (MouseHit())
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			L = true;
			return false;
		}
		if (L)
		{
			if (msg.uMsg == WM_LBUTTONUP)
			{
				L = false;
				return true;
			}
		}
	}
	
	//if (R)
	//{
	//	L = true;
	//	return false;
	//}
	//if (L)
	//{
	//	if (!R)
	//	{
	//		L = false;
	//		return true;
	//	}
	//}
	return false;
}