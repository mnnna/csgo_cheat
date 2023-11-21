#include "exWindow.h"



LRESULT CALLBACK WindowPRoc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg)
    {
    case WM_PAINT:
        loop();
        break; 
    case WM_CREATE:
        break;
    case WM_DESTROY:
        DestroyWindow(hwnd);
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam,  lParam);

    }

}


void CreatexExternalWindow()
{   
      
    GetWindowRect(offsets.hwnd, &draw.rectGame );
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WindowPRoc;
    wc.hInstance = GetModuleHandleA(NULL);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)RGB(0, 0, 0);
    wc.lpszClassName = L"Mnnna";

    RegisterClassEx(&wc);
    draw.hExwnd =  CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, wc.lpszClassName, L"Mnnna", WS_POPUP, draw.rectGame.left, draw.rectGame.top, draw.rectGame.right - draw.rectGame.left, draw.rectGame.bottom - draw.rectGame.top,
        NULL, NULL, wc.hInstance, NULL);

    if (draw.hExwnd == NULL) return; 
    SetLayeredWindowAttributes(draw.hExwnd, RGB(0,0,0), 0,LWA_ALPHA);
    ShowWindow(draw.hExwnd, SW_SHOW);
    UpdateWindow(draw.hExwnd);

    MSG msg; 
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT ){
        SetWindowPos(draw.hExwnd, HWND_TOPMOST, draw.rectGame.left, draw.rectGame.top, draw.rectGame.right - draw.rectGame.left, draw.rectGame.bottom - draw.rectGame.top, SWP_SHOWWINDOW);
        GetWindowRect(offsets.hwnd, &draw.rectGame);

        if (PeekMessageW(&msg, draw.hExwnd, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }
  
}

void loop()
{
   DWORD64 localplayer =  mem.readmemory<DWORD64>(offsets.clientbase+offsets.deLocalPlayer );
   DWORD64 localteam = mem.readmemory<DWORD64>(localplayer + offsets.m_iTeamNum);
   if (localplayer) {
       for (int i = 0; i < 32; ++i) {
           DWORD64 entity = mem.readmemory<DWORD64>(offsets.clientbase + offsets.dwEntityList + 0x8 * i); 
           if ((entity == 0)||(entity == localplayer)) continue;
           vec3 entitypos3; vec2 entitypos2;

           entitypos3.x = mem.readmemory<float>(entity + offsets.m_fPOS + 0x0);
           entitypos3.y = mem.readmemory<float>(entity + offsets.m_fPOS + 0x4);
           entitypos3.z = mem.readmemory<float>(entity + offsets.m_fPOS + 0x8);
           DWORD teamid = mem.readmemory<BYTE>(entity + offsets.m_iTeamNum);
           if (teamid != 2 && teamid != 3) continue;
           if (teamid != localteam) {
               DWORD entityHealth = mem.readmemory<DWORD>(entity + offsets.mHealth);
               if (0 < entityHealth && entityHealth  < 100 && draw.WorldToScreen(entitypos3,entitypos2))
           }
       }
   }
}



/*
typedef struct tagWNDCLASSEX {
    UINT      cbSize;
    UINT      style;
    WNDPROC   lpfnWndProc;
    int       cbClsExtra;
    int       cbWndExtra;
    HINSTANCE hInstance;
    HICON     hIcon;
    HCURSOR   hCursor;
    HBRUSH    hbrBackground;
    LPCTSTR   lpszMenuName;
    LPCTSTR   lpszClassName;
    HICON     hIconSm;
} WNDCLASSEX;

*/