#pragma once
#include<Windows.h>
using namespace std;

class Offsets
{
public :
	DWORD64 dwEntityList = NULL;
	DWORD64 deLocalPlayer = 123; 
	DWORD64 deViewMatrix = NULL; 

	DWORD m_iTeamNum = NULL;
	DWORD mHealth = NULL;
	DWORD m_fPOS = NULL; 


	HWND hwnd = 0; 
	HANDLE hprocess = 0;
	DWORD processid = 0;
	DWORD64 clientbase;

};
extern Offsets offsets;

 