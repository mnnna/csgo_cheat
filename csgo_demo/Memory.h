#pragma once
#include<Windows.h>
#include<iostream>
# include<TlHelp32.h>
#include"Offsets.h"; 
#include"structurers.h"
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
	void writememory(DWORD64 add, T val ) {
		WriteProcessMemory(offsets.hprocess, (LPVOID)add, &val, sizeof(val), NULL);
	};

	void  readbone(DWORD64 dwentity, int bindex, vec3& bonepos3) {
		DWORD64 tmp, tmp1, tmp2, tmp3, tmp4, tmp5, dwbonemartix;
		tmp1 = 0x318;
		tmp2 = 0x40;
		tmp3 = 0x00;
		tmp4 = 0x20;
		tmp5 = 0xC8;
		tmp = readmemory<DWORD64>(dwentity + tmp1);
		tmp = readmemory<DWORD64>(tmp + tmp2);
		tmp = readmemory<DWORD64>(tmp + tmp3);
		tmp = readmemory<DWORD64>(tmp + tmp4);
		dwbonemartix = readmemory<DWORD64>(tmp + tmp5);
		

		bonepos3.x = readmemory<float>(dwbonemartix + bindex * 0x30 + 0xc);
		bonepos3.y = readmemory<float>(dwbonemartix + bindex * 0x30 + 0x1c);
		bonepos3.z = readmemory<float>(dwbonemartix + bindex * 0x30 + 0x2c);

	}
};
extern Memory mem;
