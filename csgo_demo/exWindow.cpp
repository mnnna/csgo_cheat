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
    SetLayeredWindowAttributes(draw.hExwnd, RGB(0,0,0), 0, LWA_COLORKEY);
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

   DWORD localteam = mem.readmemory<DWORD64>(localplayer + offsets.m_iTeamNum);
   HDC hdc = GetDC(draw.hExwnd);

   HDC dcmemory = CreateCompatibleDC(hdc);
   HBITMAP bmpmem = CreateCompatibleBitmap(hdc, draw.rectGame.right - draw.rectGame.left, draw.rectGame.bottom - draw.rectGame.top);
   HPEN hp = CreatePen(PS_SOLID, 2, RGB(123, 241, 123));
   SelectObject(dcmemory, bmpmem);
   SelectObject(dcmemory, hp);
   //HBRUSH hbrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
  HBRUSH hbrush = CreateSolidBrush(RGB(128, 0, 0));
  // SetBkMode(hdc, TRANSPARENT);
   //FillRect(hdc, &draw.rect, hbrush);
  // DeleteObject(hbrush);
  DWORD64  entityList = mem.readmemory<uintptr_t>(offsets.clientbase + offsets.dwEntityList); // client.dll+17BB820
   if (localplayer) {
       for (int i = 0; i < 32; i++) {
           // DWORD64 entity = mem.readmemory<DWORD64>(offsets.clientbase + offsets.dwEntityList + i * 0x8);
           DWORD64 listEntry = mem.readmemory<DWORD64>(entityList + (8 * (i & 0x7FFF) >> 9) + 16);
           if (!listEntry) continue;
           DWORD64 CBasePlayerController = mem.readmemory<DWORD64>(listEntry + 120 * (i & 0x1FF));
           DWORD64 m_hPlayerPawn = mem.readmemory<DWORD64>(CBasePlayerController + offsets.m_hPlayerPawn);
           //C_BaseEntity
           DWORD64 listEntry2 = mem.readmemory<DWORD64>(entityList + 0x8 * ((m_hPlayerPawn & 0x7FFF) >> 9) + 16);
           if (!listEntry2) continue;
           //pCSPlayerPawn 
           DWORD64 entity = mem.readmemory<DWORD64>(listEntry2 + 120 * (m_hPlayerPawn & 0x1FF));
          
           if (localplayer == entity) { continue; }
           if (entity == 0) { continue; }
           vec3 entitypos3,entityheadpos3, localpos3; 
           vec2 entitypos2, entityheadpos2;

           entitypos3.x = mem.readmemory<float>(entity + offsets.m_fPOS + 0x0);
           entitypos3.y = mem.readmemory<float>(entity + offsets.m_fPOS + 0x4);
           entitypos3.z = mem.readmemory<float>(entity + offsets.m_fPOS + 0x8);

           localpos3.x = mem.readmemory<float>(localplayer + offsets.m_fPOS + 0x0);
           localpos3.y = mem.readmemory<float>(localplayer + offsets.m_fPOS + 0x4);
           localpos3.z = mem.readmemory<float>(localplayer + offsets.m_fPOS + 0x8);
           DWORD teamid = mem.readmemory<BYTE>(entity + offsets.m_iTeamNum);
           if (config.team || (teamid != 2 && teamid != 3)) { continue; };
           if (teamid != localteam) {

               DWORD entityHealth = mem.readmemory<DWORD>(entity + offsets.mHealth);
               if (0 <  entityHealth && entityHealth <= 100 && draw.WorldToScreen(entitypos3, entitypos2)) {
                   mem.readbone(entity, BONE_HEAD, entityheadpos3);
                   if (draw.WorldToScreen(entityheadpos3, entityheadpos2)) {
                       float height = entitypos2.y - entityheadpos2.y;
                       float width = height / 2;
                       if ((height <= 0) || (width <= 0)) continue;
                       RECT _rect;
                       _rect.left = entitypos2.x - (width / 2);
                       _rect.top = entityheadpos2.y;
                       _rect.right = entitypos2.x + (width / 2);
                       _rect.bottom = entitypos2.y;
                       
                      // FrameRect(dcmemory, &_rect, hbrush);
                       draw.drawrect(dcmemory, _rect);
                       if (config.health) {
                           draw.drawhp(dcmemory, hbrush, _rect, entityHealth);
                       }
                       if (config.bone) {
                           draw.drawbone(dcmemory, entity);
                       }
                       if (config.distance) {
                           unsigned int distance = sqrt((entitypos3.x - localpos3.x) * (entitypos3.x - localpos3.x) + (entitypos3.y - localpos3.y) * (entitypos3.y - localpos3.y) 
                               + (entitypos3.z - localpos3.z))/100;
                           char tmpstr[255];
                           char prefix[] = "[";
                           char suffix[] = "m]";
                           _itoa_s(distance, tmpstr, 10);
                           string endstr = prefix + (string)tmpstr + suffix;
                           draw.drawstr(dcmemory, entitypos2.x - 5, entitypos2.y + 2, distance < 5 ? RGB(255, 0, 0) : RGB(143, 143, 143), endstr.c_str());
                       }
                   }
#if 0               
                   vec3 tmpbone3;
                   vec2 tmpbone2;
                   for (int i = 0; i <= 50; i++) {
                       mem.readbone(entity, i, tmpbone3);
                       wchar_t buffer[255];
                       wsprintf(buffer, L"%d", i);
                       if (draw.WorldToScreen(tmpbone3, tmpbone2)) {
                           TextOut(hdc, tmpbone2.x, tmpbone2.y, buffer, 2);
                       }
                   }
#endif 
               }
           }
       }
       if (config.autoaim) {
           int circleredius = (draw.rectGame.right - draw.rectGame.left) * CONFIG_FOV / 2 / 130;
           int centerx = (draw.rectGame.right - draw.rectGame.left) / 2;
           int centery = (draw.rectGame.bottom - draw.rectGame.top) / 2 + 15;
           Arc(dcmemory,
               centerx - circleredius, centery - circleredius,
               centerx + circleredius, centery + circleredius,
               centerx - centery, centery,
               centerx - centery, centery
           );
       }

       BitBlt(hdc, 0, 0, draw.rectGame.right - draw.rectGame.left, draw.rectGame.bottom - draw.rectGame.top, dcmemory, 0, 0, SRCCOPY);

   }
   DeleteObject(hbrush);
   DeleteObject(hp);
   ReleaseDC(draw.hExwnd, hdc);
   DeleteDC(dcmemory);
   DeleteObject(bmpmem);
}



