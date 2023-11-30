#include "Draw.h"
#include "Offsets.h"
Draw draw;
void Draw::drawrect(HDC hdc, RECT rect)
{	
	float witdth = rect.right - rect.left;
	int length = witdth / 3;

	MoveToEx(hdc, rect.left, rect.top + length, NULL);
	LineTo(hdc, rect.left, rect.top);
	LineTo(hdc, rect.left + length , rect.top);

	MoveToEx(hdc, rect.right, rect.top + length, NULL);
	LineTo(hdc, rect.right, rect.top);
	LineTo(hdc, rect.right - length, rect.top);

	MoveToEx(hdc, rect.left, rect.bottom - length, NULL);
	LineTo(hdc, rect.left, rect.bottom);
	LineTo(hdc, rect.left + length, rect.bottom);

	MoveToEx(hdc, rect.right, rect.bottom - length, NULL);
	LineTo(hdc, rect.right, rect.bottom);
	LineTo(hdc, rect.right - length, rect.bottom);
}
void Draw::drawhp(HDC hdc, HBRUSH hb, RECT rect, float hp)
{
	int width = 5;
	RECT backgroundrect = {
		rect.left - width ,
		rect.top ,
		rect.left - width / 2 ,
		rect.bottom
	};

	FillRect(hdc, &backgroundrect, hb);

	HBRUSH hb2 = CreateSolidBrush(RGB(153,196,36));

	float autotop = (rect.bottom - rect.top) * ((100 - hp) / 100)+rect.top;
	 
	RECT hprect = {
		backgroundrect.left ,
		autotop,
		backgroundrect.right,
		backgroundrect.bottom
	};

	FillRect(hdc, &hprect, hb2); 
	DeleteObject(hb2);

}
void Draw::GetWindowInfo()
{
	GetClientRect(offsets.hwnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	GetWindowRect(offsets.hwnd, &rectex);
	widthex = rectex.right - rectex.left;
	heightex = rectex.bottom - rectex.top;
}
void Draw::drawbone(HDC hdc, DWORD64 entity)
{
	vec3 tmpbone3;
	vec2 tmpbone2, neckbone, crossbone;

	mem.readbone(entity, BONE_HEAD, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	MoveToEx(hdc, tmpbone2.x , tmpbone2.y, NULL);

	mem.readbone(entity, BONE_NECK, tmpbone3);
	WorldToScreen(tmpbone3, neckbone);
	LineTo(hdc, neckbone.x, neckbone.y);

	mem.readbone(entity, BONE_LEFT_SHOULDER, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);

	mem.readbone(entity, BONE_LEFT_SHOULDER, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);

	mem.readbone(entity, BONE_LEFT_ELBOW, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);

	mem.readbone(entity, BONE_LEFT_HAND, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);

	MoveToEx(hdc, neckbone.x, neckbone.y, NULL);

	mem.readbone(entity, BONE_RIGHT_SHOULDER, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);

	mem.readbone(entity, BONE_RIGHT_ELBOW, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);

	mem.readbone(entity, BONE_RIGHT_HAND, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);

	MoveToEx(hdc, neckbone.x, neckbone.y, NULL);

	mem.readbone(entity, BONE_CROSS, tmpbone3);
	WorldToScreen(tmpbone3, crossbone);
	LineTo(hdc, crossbone.x, crossbone.y);

	mem.readbone(entity, BONE_LEFT_KNEE, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);

	mem.readbone(entity, BONE_LEFT_FOOT, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);

	MoveToEx(hdc, neckbone.x, neckbone.y, NULL);

	mem.readbone(entity, BONE_RIGHT_KNEE, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);

	mem.readbone(entity, BONE_RIGHT_FOOT, tmpbone3);
	WorldToScreen(tmpbone3, tmpbone2);
	LineTo(hdc, tmpbone2.x, tmpbone2.y);


}
HFONT hfont = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY
	, DEFAULT_PITCH | FF_SWISS, NULL); 
void Draw::drawstr(HDC hdc, int x, int y, COLORREF color, const char* text)
{
	SetBkColor(hdc, TRANSPARENT);
	SetTextColor(hdc, color);
	SelectObject(hdc, hfont);
	TextOutA(hdc, x, y, text, strlen(text));
}
BOOL Draw::WorldToScreen(vec3& worldpos, vec2& screenpos)
{	
	GetWindowInfo();
	float matrix[4][4];
	ReadProcessMemory(offsets.hprocess, (LPCVOID)(offsets.clientbase + offsets.deViewMatrix), matrix, 64, NULL);
	vec4 clipos;

	clipos.x = matrix[0][0] * worldpos.x + matrix[0][1] * worldpos.y + matrix[0][2] * worldpos.z + matrix[0][3];
	clipos.y = matrix[1][0] * worldpos.x + matrix[1][1] * worldpos.y + matrix[1][2] * worldpos.z + matrix[1][3];
	clipos.z = matrix[2][0] * worldpos.x + matrix[2][1] * worldpos.y + matrix[2][2] * worldpos.z + matrix[2][3];
	clipos.w = matrix[3][0] * worldpos.x + matrix[3][1] * worldpos.y + matrix[3][2] * worldpos.z + matrix[3][3];

	if (clipos.w < 0.01) { return false; }

	vec3 ndc; 
	ndc.x = clipos.x / clipos.w; 
	ndc.y = clipos.y / clipos.w;
	ndc.z = clipos.z / clipos.w;

	screenpos.x = width / 2 + (width / 2) * ndc.x;
	screenpos.y = height / 2 - (height / 2) * ndc.y + 30;

	return true; 
}


