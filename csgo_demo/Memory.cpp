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
	OpenProcess(PROCESS_ALL_ACCESS, FALSE, offsets.processid);
	offsets.hwnd = FindWindowA(NULL, "Counter-Strike 2");

	if (offsets.processid) {
		cout << "csgo2 hporcess:" << offsets.processid << endl;
	}
	else {
		cout << " get process error" << endl;
	}
}
