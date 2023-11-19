#include "Memory.h"
Memory mem;


DWORD Memory::getprocessid()
{
	DWORD PID;
	do {
		offsets.hwnd = FindWindowA(NULL, "Counter-Strike 2");
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
}
