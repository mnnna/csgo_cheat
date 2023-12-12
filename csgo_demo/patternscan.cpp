#include "patternscan.h"
#include "Memory.h"

DWORD64 findAddress(HANDLE hprocess, const wchar_t* moduleName, const char* pattern, const char* mask)
{
	MODULEENTRY32 moduleEntry =  mem.getmodule(offsets.processid, moduleName);
	if (! moduleEntry.th32ModuleID) {
		return NULL; 
	}

	uintptr_t base = (uintptr_t)moduleEntry.modBaseAddr;
	uintptr_t size = base + (uintptr_t)moduleEntry.modBaseSize; //ɨ�跶Χ
	uintptr_t curChunk = base;
	size_t bytesRead;

	while (curChunk < size ) {
		char buffer[0x1000];
		DWORD oProtect; 
		VirtualProtectEx(hprocess, (LPVOID)curChunk, sizeof(buffer), PAGE_EXECUTE_READWRITE, &oProtect);
		ReadProcessMemory(hprocess, (LPVOID)curChunk, &buffer, sizeof(buffer), &byteRead);
		VirtualProtectEx(hprocess, (LPVOID)curChunk, sizeof(buffer), oProtect, &oProtect);

		if (bytesRead == 0) {
			return NULL;
		}
		DWORD64 internalAddr = findpattern((char*) (buffer), byteRead, pattern, mask);
		if (internalAddr != NULL) {
			uintptr_t offsetFromBuffer = (uintptr_t)internalAddr - (uintptr_t)&buffer;
			return (DWORD64)(curChunk + offsetFromBuffer);
		}
		else {
			curChunk += bytesRead;
		}

	}
	return NULL;
}

DWORD64 findpattern(char* base, size_t size, const char* pattern, const char* mask)
{
	size_t patternLen = strlen(mask);

	for (DWORD64 i = 0; i < size - patternLen; i++) {
		bool found = true;

		for (DWORD64 j = 0; j < patternLen; j++) {
			if (mask[j] != '?' && pattern[j] != *(base + i + j)) {
				bool found = false;
			};
		};
		if (found) {
			return (DWORD64)(base + i);
		}
	}

	return NULL;
}
