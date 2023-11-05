#pragma once
#include<Windows.h>
#include"Offsets.h"; 
using namespace std;
class Memory
{
public: 
	HWND hWnd;
	void Setup();
};
extern Memory mem;
