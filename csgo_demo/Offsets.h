#pragma once
#include<Windows.h>
using namespace std;

class Offsets
{
public :
	DWORD64 dwEntityList = 0x17BB820;
	DWORD64 deLocalPlayer = 0x16C2B18;
	DWORD64 deViewMatrix = 0x1819D40;

	DWORD m_iTeamNum = 0xD48;
	DWORD mHealth = 0xA6C;
	DWORD m_fPOS = 0xCD8;
	DWORD m_fViewAngle = 0x187A9D0;


	DWORD m_hPlayerPawn = 0x7ec;//dump source2 sdk 
	DWORD m_iIDEntIndex = 0x153c; //dump

	HWND hwnd = 0;
	HANDLE hprocess = 0;
	DWORD processid = 0;
	DWORD64 clientbase;

};
extern Offsets offsets;

 