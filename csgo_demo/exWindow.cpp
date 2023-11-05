#include "exWindow.h"


LRESULT CALLBACK WindowPRoc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg)
    {
    case WM_PAINT:
        break; 
    case WM_CREATE:
        break;
    case WM_DESTROY:
        break;
    case WM_CLOSE:
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