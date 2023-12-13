#include "Offsets.h"
#include "PatternScan.h"
#include "Memory.h"
Offsets offsets;

void Offsets::OffsetUpdate()
{
	DWORD64  address = 0, offset = 0, len = 0;
	//48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1 EB
	len = 7; offset = 3;
	address = findAddress(hprocess, L"client.dll", "\x48\x8B\x0D\x00\x00\x00\x00\x48\x89\x7C\x24\x00\x8B\xFA\xC1\xEB", "xxx????xxxx?xxxx");
	offset = mem.ReadGlobalVarOffset(address + 3);
	offsets.dwEntityList = (address + len + offset) - offsets.clientbase;
}
