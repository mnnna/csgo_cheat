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
void Draw::GetWindowInfo()
{
	GetClientRect(offsets.hwnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	GetWindowRect(offsets.hwnd, &rectex);
	widthex = rectex.right - rectex.left;
	heightex = rectex.bottom - rectex.top;
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


