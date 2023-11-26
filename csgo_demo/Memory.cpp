#include "Memory.h"
Memory mem;

MODULEENTRY32 Memory::getmodule(DWORD pid, const wchar_t* windowname)
{
	hss =  CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid );
	mEntry.dwSize = sizeof(MODULEENTRY32);
	if (hss != INVALID_HANDLE_VALUE) {
		if (Module32First(hss, &mEntry)) {
			do {
				if (! wcscmp((const wchar_t*)mEntry.szModule, windowname)) {
					break;
				}
			} while (Module32Next(hss, &mEntry));
		};
		CloseHandle(hss);
	}
	return mEntry;
}


DWORD Memory::getprocessid()
{
	DWORD PID;
	do {
		offsets.hwnd = FindWindow(NULL, L"Counter-Strike 2");
		Sleep(50);
	} while (!offsets.hwnd);

	GetWindowThreadProcessId(offsets.hwnd, &PID);
	cout<< "csgo2 PID: " << PID << endl;
	return PID;
}

void Memory::Setup()
{
	offsets.processid = getprocessid();
 	offsets.hprocess =  OpenProcess(PROCESS_ALL_ACCESS, FALSE, offsets.processid);
	offsets.hwnd = FindWindowA(NULL, "Counter-Strike 2");

	if (offsets.hprocess) {
		cout << "csgo2 hporcess:" << offsets.hprocess << endl;
	}
	else {
		cout << " get process error" << endl;
	}
	cout << "" << endl;
	getmodules();
	cout << "csgo2 hporcess:" << offsets.clientbase << endl;
}


void Memory::getmodules()
{
	do {
		offsets.clientbase = (DWORD64)getmodule(offsets.processid, L"client.dll").modBaseAddr;
		Sleep(50);
	} while (!offsets.clientbase);
	
}
