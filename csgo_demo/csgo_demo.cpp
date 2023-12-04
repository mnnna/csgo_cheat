
#include <iostream>
#include <Windows.h>
#include"Memory.h"
#include"exWindow.h"
#include <thread>
#include"aimbot.h"

Config config;
using namespace std;
void init()
{
    mem.Setup();
}

void StartExternalWindows() {
    CreatexExternalWindow();
}


void printmeum() {
    cout << "---> 显示血条" << "                                  F2" << endl;
    cout << "---> 显示骨骼" << "                                  F3" << endl;
    cout << "---> 自瞄" << "                                      F4" << endl;
    cout << "---> 显示距离" << "                                  F5" << endl;
    cout << "---> 忽略阵营" << "                                  F6" << endl;
    cout << "---> 自动开枪" << "                                  F7" << endl;
}
void toggleFeatures() {
    if (GetAsyncKeyState(VK_F2) & 1) {
        config.health = !config.health;
        cout << "---> 显示血条 " << (config.health ? "true" : "false") << endl;
    }
    if (GetAsyncKeyState(VK_F3) & 1) {
        config.bone = !config.bone;
        cout << "---> 显示骨骼 " << (config.bone ? "true" : "false") << endl;
    }
    if (GetAsyncKeyState(VK_F4) & 1) {
        config.autoaim = !config.autoaim;
        cout << "---> 自瞄 " << (config.autoaim ? "true" : "false") << endl;
    }
    if (GetAsyncKeyState(VK_F5) & 1) {
        config.distance = !config.distance;
       cout << "---> 显示距离 " << (config.distance ? "true" : "false") << endl;
    }
    if (GetAsyncKeyState(VK_F6) & 1) {
        config.team = !config.team;
        cout << "---> 忽略阵营 " << (config.team ? "true" : "false") << endl;
    }
    if (GetAsyncKeyState(VK_F7) & 1) {
        config.triggerbot = !config.triggerbot;
       cout << "---> 自动开枪 " << (config.triggerbot ? "true" : "false") << endl;
    }
    
}

void features() {
    while(true) 
        if (config.autoaim) {
            AimBot();
    }
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
    thread aimbotThread (features);
    thread StartExternalWindow(StartExternalWindows);
    printmeum();
    while (true) {
        toggleFeatures();
    }
}

