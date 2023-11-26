#pragma once
#include<Windows.h>
#include"structurers.h"
#include"Offsets.h"
#include"Memory.h"
using namespace std; 
class Draw
{
public:
	RECT rectGame; 
	HWND hExwnd;
	BOOL WorldToScreen(vec3 &worldpos, vec2 &screenpos);			

	RECT rect;
	RECT rectex;

	int width;
	int height;
	int widthex;
	int heightex;

	void GetWindowInfo();
};
extern Draw draw; 
