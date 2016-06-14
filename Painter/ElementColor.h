#pragma once
#include <Windows.h>

//标准的颜色类型
enum class ElementColor : COLORREF
{
	BLACK = RGB(0, 0, 0),
	RED = RGB(255, 0, 0),
	GREEN = RGB(0, 255, 0),
	BLUE = RGB(0, 0, 255)
};