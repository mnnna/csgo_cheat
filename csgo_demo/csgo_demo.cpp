
#include <iostream>
#include <Windows.h>
#include"Memory.h"
#include"exWindow.h"
using namespace std;
void init()
{
    mem.Setup();
}
int main()
{
    SetConsoleTitle ( L"csgo_meum" );
    HWND p = GetConsoleWindow();
    RECT r; 
    GetWindowRect(p, &r);
    MoveWindow(p, r.right, r.left, 500, 700 ,TRUE);

    cout << "\n ------------------------------------" << endl;
    init();
    CreatexExternalWindow();
}

