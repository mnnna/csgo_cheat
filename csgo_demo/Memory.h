#pragma once
#include<Windows.h>
#include"Offsets.h"; 
using namespace std;
class Memory
{
public: 
	HWND hWnd;
	void Setup();
	template <typename T> 
	T readmemory(DWORD64 add){
		T buffer;
		ReadProcessMemory(offsets.hprocess, (LPCVOID)add, &buffer, sizeof(buffer), NULL);
		return buffer;
	};
	template <typename T>
	T writememory(DWORD64 add, T val ) {
		WriteProcessMemory(offsets.hprocess, (LPCVOID)add, &val, sizeof(val), NULL);
	};
};
extern Memory mem;
