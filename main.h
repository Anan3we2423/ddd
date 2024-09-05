#pragma once
#include "imgui\imgui.h"
#include "imgui\imgui_internal.h"
#include "imgui\imgui_impl_dx9.h"
#include "imgui\imgui_impl_win32.h"
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#include "detours.X86\detours.h"
#include <fstream>
#include <functional>
#include <string>
#include <ShlObj.h>
#if defined _M_X64
#pragma comment(lib, "detours.X64/detours.lib")
#elif defined _M_IX86
#pragma comment(lib, "detours.X86/detours.lib")
#endif
#pragma warning (disable: 4244) 
#include "include.h"
#include "xor.h"
#include "Cheats.h"
#include "actv.h"
bool Deneme = 0;
bool ShowMenu = false;
bool imguiStarted = false;
/* DETOURS <3 */
D3DVIEWPORT9 viewport;
LPDIRECT3DTEXTURE9 ZulaChamsColor, GladyoChamsColor;
HWND game_hwnd = NULL;
HMODULE Hand;
WNDPROC game_wndproc = NULL;
D3DVIEWPORT9 viewPort;

bool setup = true;


int Tab;
int selectedItem = 0;

static const char* aimkey[]{ "Ctrl","Capslock","Shift","Alt","LMB","RMB" };

int selectedBody = 0;
static const char* aimbody[]{ "Head","Pelvis","Body" };

static const char* Hexteams[] = { "All", "Zula", "Gladyo" };
int currentHexesT = 0;

// Özellikler
static bool FovChanger = false;
static bool FastReload = false;
static bool NoReload = false;
static bool AntiAFK = false;
static bool Spammmm = false;
static bool Wallhack = false;
static bool Chams = false;
static bool RainbowChams = false;
static bool EspBox3D = false;
static bool RainbowEspBox = false;
static bool EspLine = false;
static bool circlefov = false;
static bool RainbowEspLine = false;
static bool NameEspAktif = false;
static bool Watermark = false;
static bool Aimbot = false;
static bool Zula = true;
static bool Gladyo = true;
static bool norec1 = false;
static bool norec2 = false;
static bool nospr1 = false;
static bool norel1 = false;
static bool rapid1 = false;
static bool fwp1 = false;
static bool NoRecoil = false;
static bool NoSpread = false;
static bool laserdot = false;
static bool FastWeaponSwitch = false;
// Özellik bitiþ

float AimHhead = 28.0f;
float AimCtrlhead = 14.0f;
float AimHbody = 0.0f;
float AimHlegs = -28.0f;
struct ModelPlayer2
{
	D3DXVECTOR3 Player;
	float CrossDist;
};
std::vector<ModelPlayer2*>cPlayerA;

float GetDistance(float Xx, float Yy, float xX, float yY)
{
	return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
}
float aimsmooth = 0.300;
float aimfov = 30;


D3DXVECTOR3 GetMidPoint(D3DXVECTOR3 V1, D3DXVECTOR3 V2)
{
	D3DXVECTOR3 Mid;
	Mid.x = (V1.x + V2.x) / 2;
	Mid.y = (V1.y + V2.y) / 2;
	Mid.z = (V1.z + V2.z) / 2;
	return Mid;
}
bool Trans3DTo2D(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3* InOut)
{
	D3DXVECTOR3 vScreen;
	D3DXVECTOR3 PlayerPos(InOut->x, InOut->y, InOut->z);
	D3DVIEWPORT9 viewPort = { 0 };
	D3DXMATRIX projection, view, world;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	pDevice->GetTransform(D3DTS_WORLD, &world);
	pDevice->GetViewport(&viewPort);
	D3DXVec3Project(&vScreen, &PlayerPos, &viewPort, &projection, &view, &world);
	if (vScreen.z < 1)
	{
		*InOut = vScreen;
		return true;
	}
	return false;
}
void FillRGB(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawBorder(int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice)
{
	FillRGB(x, (y + h - px), w, px, BorderColor, pDevice);
	FillRGB(x, y, px, h, BorderColor, pDevice);
	FillRGB(x, y, w, px, BorderColor, pDevice);
	FillRGB((x + w - px), y, px, h, BorderColor, pDevice);
}
LPD3DXLINE Line2;
void DrawLine2(float StartX, float StartY, float EndX, float EndY, D3DCOLOR dColor,int width)
{
	Line2[0].SetWidth(width);
	Line2[0].SetGLLines(0);
	Line2[0].SetAntialias(0);

	D3DXVECTOR2 v2Line[2];
	v2Line[0].x = StartX;
	v2Line[0].y = StartY;
	v2Line[1].x = EndX;
	v2Line[1].y = EndY;

	Line2[0].Begin();
	Line2[0].Draw(v2Line, 2, dColor);
	Line2[0].End();
}

bool desp = true;
int width = 1;
void Draw3DBox(D3DXVECTOR3 Head, D3DXVECTOR3 Feet, DWORD Color, LPDIRECT3DDEVICE9 Device)
{
	int xz = 16;
	int uzunluk = xz * 2;
	D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
	Pos0 = GetMidPoint(Head, Feet);
	Pos1 = Pos0 + D3DXVECTOR3(-xz, uzunluk, -xz);
	Pos2 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, -xz);
	Pos3 = Pos0 + D3DXVECTOR3(xz, -uzunluk, -xz);
	Pos4 = Pos0 + D3DXVECTOR3(xz, uzunluk, -xz);
	Pos5 = Pos0 + D3DXVECTOR3(-xz, uzunluk, xz);
	Pos6 = Pos0 + D3DXVECTOR3(-xz, -uzunluk, xz);
	Pos7 = Pos0 + D3DXVECTOR3(xz, -uzunluk, xz);
	Pos8 = Pos0 + D3DXVECTOR3(xz, uzunluk, xz);

	if (Trans3DTo2D(Device, &Pos1) && Trans3DTo2D(Device, &Pos2) &&
		Trans3DTo2D(Device, &Pos3) && Trans3DTo2D(Device, &Pos4) &&
		Trans3DTo2D(Device, &Pos5) && Trans3DTo2D(Device, &Pos6) &&
		Trans3DTo2D(Device, &Pos7) && Trans3DTo2D(Device, &Pos8))
	{
		if (desp)
		{
			DrawLine2(Pos1.x, Pos1.y, Pos2.x, Pos2.y, Color, width);
			DrawLine2(Pos2.x, Pos2.y, Pos3.x, Pos3.y, Color, width);
			DrawLine2(Pos3.x, Pos3.y, Pos4.x, Pos4.y, Color, width);
			DrawLine2(Pos4.x, Pos4.y, Pos1.x, Pos1.y, Color, width);
			DrawLine2(Pos5.x, Pos5.y, Pos6.x, Pos6.y, Color, width);
			DrawLine2(Pos6.x, Pos6.y, Pos7.x, Pos7.y, Color, width);
			DrawLine2(Pos7.x, Pos7.y, Pos8.x, Pos8.y, Color, width);
			DrawLine2(Pos8.x, Pos8.y, Pos5.x, Pos5.y, Color, width);
			DrawLine2(Pos1.x, Pos1.y, Pos5.x, Pos5.y, Color, width);
			DrawLine2(Pos2.x, Pos2.y, Pos6.x, Pos6.y, Color, width);
			DrawLine2(Pos3.x, Pos3.y, Pos7.x, Pos7.y, Color, width);
			DrawLine2(Pos4.x, Pos4.y, Pos8.x, Pos8.y, Color, width);

		}
	}
}
int width1 = 1;
void EspLineFunc(D3DXVECTOR3 VectorHead, D3DXVECTOR3 VectorFeet, LPDIRECT3DDEVICE9 Device,DWORD Color)
{
	D3DXVECTOR3 Pos0,Cizgi,ayak;
	Pos0 = GetMidPoint(VectorHead, VectorFeet);
	Cizgi = Pos0;
	ayak = Cizgi - D3DXVECTOR3(0, 20.f, 0);

	if (Trans3DTo2D(Device, &Cizgi) && Trans3DTo2D(Device, &ayak))
	{
		if (desp)
		{
			DrawLine2(viewPort.Width / 2.0f, viewPort.Height, Cizgi.x, Cizgi.y, Color, width1);
		}
	}
}
void EspFree(D3DXVECTOR3 VectorHead, D3DXVECTOR3 VectorFeet, LPDIRECT3DDEVICE9 Device, DWORD Color)
{
	D3DXVECTOR3 Pos0, Cizgi, ayak;
	Pos0 = GetMidPoint(VectorHead, VectorFeet);
	Cizgi = Pos0;
	ayak = Cizgi - D3DXVECTOR3(0, 28.f, 0);

	if (Trans3DTo2D(Device, &Cizgi) && Trans3DTo2D(Device, &ayak))
	{
		if (desp)
		{
			char xxd2[64];
			sprintf(xxd2, "[Medusa]");
			Draw_TextACTV(ayak.x, ayak.y, Color, xxd2, C_Text); //kontrol
		}
	}
}
void DrawRect(IDirect3DDevice9* pDevice, int x, int y, int h, int w, DWORD Color)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 0, 0);
}

void W2AIM(LPDIRECT3DDEVICE9 pDevice, float AimH)
{
	D3DXMATRIX projection, view, world;
	ModelPlayer2* pPlayer = new ModelPlayer2;
	D3DXVECTOR3 pOut(0, AimH, 0), pV(0, AimH, 0);
	pDevice->GetViewport(&viewport);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_WORLD, &world);
	D3DXVec3Project(&pOut, &pV, &viewport, &projection, &view, &world);
	if (pOut.z < 1)
	{
		pPlayer->Player.x = pOut.x;
		pPlayer->Player.y = pOut.y;
	}
	cPlayerA.push_back(pPlayer);
}


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ShowMenu && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}

	return CallWindowProc(game_wndproc, hWnd, msg, wParam, lParam);
}

#define IM_COL32(R,G,B,A)    (((ImU32)(A)<<24) | ((ImU32)(B)<<16) | ((ImU32)(G)<<8) | ((ImU32)(R)))



void DrawCross(IDirect3DDevice9* pDevice, D3DCOLOR Color)
{
	D3DVIEWPORT9 Viewport;
	pDevice->GetViewport(&Viewport);
	DWORD ScreenX = Viewport.Width / 2;
	DWORD ScreenY = Viewport.Height / 2;

	DrawRect(pDevice, ScreenX + 5, ScreenY - 1, 2, 20, Color);
	DrawRect(pDevice, ScreenX - 25, ScreenY - 1, 2, 20, Color);
	DrawRect(pDevice, ScreenX - 1, ScreenY + 5, 20, 2, Color);
	DrawRect(pDevice, ScreenX - 1, ScreenY - 25, 20, 2, Color);
}


D3DCOLOR FLOAT4TOD3DCOLOR(float Col[])
{
	ImU32 col32_no_alpha = ImGui::ColorConvertFloat4ToU32(ImVec4(Col[0], Col[1], Col[2], Col[3]));
	float a = (col32_no_alpha >> 24) & 255;
	float r = (col32_no_alpha >> 16) & 255;
	float g = (col32_no_alpha >> 8) & 255;
	float b = col32_no_alpha & 255;
	return D3DCOLOR_ARGB((int)a, (int)b, (int)g, (int)r);
}
float zulachams[] = { 1.00f, 0.00f, 0.00f, 0.50f };
float gladyochams[] = { 0.08f, 0.00f, 1.00f, 0.50f };

float zulabox[] = { 1.00f, 0.00f, 0.00f, 0.50f };
float gladyobox[] = { 0.08f, 0.00f, 1.00f, 0.50f };

float zulaline[] = { 1.00f, 0.00f, 0.00f, 0.50f };
float gladyoline[] = { 0.08f, 0.00f, 1.00f, 0.50f };

float zulachams1[] = { 1.00f, 0.00f, 0.00f, 0.50f };
float gladyochams1[] = { 0.08f, 0.00f, 1.00f, 0.50f };

ImVec4 circlecolor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

float zulabox1[] = { 1.00f, 0.00f, 0.00f, 0.50f };
float gladyobox1[] = { 0.08f, 0.00f, 1.00f, 0.50f };

float zulaline1[] = { 1.00f, 0.00f, 0.00f, 0.50f };
float gladyoline1[] = { 0.08f, 0.00f, 1.00f, 0.50f };

float zuladistance[] = { 1.00f, 0.00f, 0.00f, 0.50f };
float gladyodistance[] = { 0.08f, 0.00f, 1.00f, 0.50f };

float crosscolor[] = { 0.00f, 1.00f, 0.02f, 0.50f };

template <typename T>
T readmem(uintptr_t address)
{
	T buffer{ };
	if (ReadProcessMemory(GetCurrentProcess(), (LPVOID)address, &buffer, sizeof(T), 0))
		return buffer;
}

template <typename T>
static T writemem(uintptr_t address, T val, SIZE_T size)
{
	T buffer{ };
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)address, &val, size, NULL);
	return buffer;
}


typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;


RGBA moi_blue = { 0, 143, 209,255 };
RGBA moi_red = { 241,34,34,255 };
RGBA moi_green = { 0,209,91,255 };

RGBA red = { 255,0,0,255 };
RGBA Magenta = { 255,0,255,255 };
RGBA yellow = { 255,255,0,255 };
RGBA grayblue = { 128,128,255,255 };
RGBA green = { 128,224,0,255 };
RGBA darkgreen2 = { 26, 128, 0, 255 };
RGBA darkgreen3 = { 6, 68, 0, 255 };
RGBA darkgreen = { 0,224,128,255 };
RGBA brown = { 192,96,0,255 };
RGBA pink = { 255,168,255,255 };
RGBA DarkYellow = { 216,216,0,255 };
RGBA SilverWhite = { 236,236,236,255 };
RGBA purple = { 144,0,255,255 };
RGBA Navy = { 88,48,224,255 };
RGBA skyblue = { 0,136,255,255 };
RGBA graygreen = { 128,160,128,255 };
RGBA blue = { 0,96,192,255 };

RGBA orange = { 255,128,0,255 };
RGBA peachred = { 255,80,128,255 };
RGBA reds = { 255,128,192,255 };
RGBA darkgray = { 96,96,96,255 };
RGBA Navys = { 0,0,128,255 };
RGBA darkgreens = { 0,128,0,255 };
RGBA darkblue = { 0,128,128,255 };
RGBA redbrown = { 128,0,0,255 };
RGBA red4 = { 255, 24, 101, 255 };
RGBA purplered = { 128,0,128,255 };
RGBA greens = { 0,255,0,255 };
RGBA envy = { 0,255,255,255 };
RGBA black = { 0,0,0,255 };
RGBA gray = { 128,128,128,255 };
RGBA white = { 255,255,255,255 };
RGBA blues = { 30,144,255,255 };
RGBA lightblue = { 135,206,250,160 };
RGBA Scarlet = { 220, 20, 60, 160 };
RGBA white_ = { 255,255,255,200 };
RGBA gray_ = { 128,128,128,200 };
RGBA black_ = { 0,0,0,200 };
RGBA red_ = { 255,0,0,200 };
RGBA Magenta_ = { 255, 95, 96, 255 };
RGBA yellow_ = { 255,255,0,200 };
RGBA grayblue_ = { 128,128,255,200 };
RGBA green_ = { 128,224,0,200 };
RGBA darkgreen_ = { 0,224,128,200 };
RGBA brown_ = { 192,96,0,200 };
RGBA pink_ = { 255,168,255,200 };
RGBA darkyellow_ = { 216,216,0,200 };
RGBA silverwhite_ = { 236,236,236,200 };
RGBA purple_ = { 144,0,255,200 };
RGBA Blue_ = { 88,48,224,200 };
RGBA skyblue_ = { 0,136,255,200 };
RGBA graygreen_ = { 128,160,128,200 };
RGBA blue_ = { 0,96,192,180 };
RGBA orange_ = { 255,128,0,200 };
RGBA orange2_ = { 255,100,0,180 };
RGBA pinks_ = { 255,80,128,200 };
RGBA Fuhong_ = { 255,128,192,200 };
RGBA darkgray_ = { 96,96,96,200 };
RGBA Navy_ = { 0,0,128,200 };
RGBA darkgreens_ = { 0,128,0,200 };
RGBA darkblue_ = { 0,128,128,200 };
RGBA redbrown_ = { 128,0,0,200 };
RGBA purplered_ = { 128,0,128,200 };
RGBA greens_ = { 0,255,0,200 };
RGBA envy_ = { 0,255,255,200 };

RGBA glassblack = { 0, 0, 0, 180 };
RGBA GlassBlue = { 65,105,225,80 };
RGBA glassyellow = { 255,255,0,160 };
RGBA glass = { 200,200,200,60 };


RGBA Plum = { 221,160,221,160 };