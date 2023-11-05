#include "Memory.h"
Memory mem;

void Memory::Setup()
{
	offsets.hwnd = FindWindowA(NULL, "Counter-Strike 2");
}
