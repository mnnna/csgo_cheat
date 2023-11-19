#pragma once
#include<Windows.h>
#include<iostream>
# include<TlHelp32.h>
#include"Offsets.h"; 
using namespace std;
class Memory
{
public: 
	HWND hWnd;
	HANDLE hss;
	MODULEENTRY32 mEntry;
	void Setup();
	MODULEENTRY32 getmodule(DWORD pid, const wchar_t* windowname );
	void getmodules();
	DWORD getprocessid(); 
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
