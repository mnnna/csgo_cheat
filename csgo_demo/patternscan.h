# pragma once
# include<Windows.h>
# include<TlHelp32.h>

DWORD64 findAddress(HANDLE hprocess, const wchar_t moduleName, const char* pattern /*������*/, const char* mask /*����*/);
DWORD64 findpattern(char* base, size_t size, const char* pattern, const char* mask );