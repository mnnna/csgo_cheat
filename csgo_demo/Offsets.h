#pragma once
#include<Windows.h>
using namespace std;

class Offsets
{
public :
	HWND hwnd = 0; 
	HANDLE hprocess = 0;
	DWORD processid = 0;
	DWORD64 clientbase;
};
extern Offsets offsets;

 