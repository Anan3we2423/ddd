#include "main.h"
#include "arama.h"
#include "icons.h"
#include "Fonts.h"
#include "Enc.h"
#include "Theme.h"
#include "vector.h"
#include <ctime>
#include <chrono>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <iostream>
#include "Cursor.h"

LPDIRECT3DTEXTURE9 DrawCursor;

const char* entity_handle;
uint32_t LocalPlayer = NULL;
#define isLocalPlayer strstr(entity_handle.c_str(), "FPS_" && strstr(entity_handle.c_str(), "_MESH.M")
#define isPlayer strstr(entity_handle.c_str(), "CHAR_" && strstr(entity_handle.c_str(), XorString("MESH.MD"))
#define ZulaTeam strstr(entity_handle.c_str(), "CHAR_HALIL") || strstr(entity_handle.c_str(), "CHAR_CEMAL") || strstr(entity_handle.c_str(), "CHAR_AZAD") || strstr(entity_handle.c_str(), "CHAR_DAYI") || strstr(entity_handle.c_str(), "CHAR_TAHIR") || strstr(entity_handle.c_str(), "CHAR_CETIN") || strstr(entity_handle.c_str(), "CHAR_OSMAN") || strstr(entity_handle.c_str(), "CHAR_SAMIL") || strstr(entity_handle.c_str(), "CHAR_CUMALI") || strstr(entity_handle.c_str(), "KADIN") || strstr(entity_handle.c_str(), "CHAR_BAHRAM")
#define GladioTeam strstr(entity_handle.c_str(), "CHAR_AZER") || strstr(entity_handle.c_str(), "CHAR_PIERRE") || strstr(entity_handle.c_str(), "CHAR_BOB") || strstr(entity_handle.c_str(), "CHAR_AVI") || strstr(entity_handle.c_str(), "CHAR_EDWARD") || strstr(entity_handle.c_str(), "CHAR_GEORGE") || strstr(entity_handle.c_str(), "CHAR_IVAN") || strstr(entity_handle.c_str(), "CHAR_JACK") || strstr(entity_handle.c_str(), "CHAR_ROSA") || strstr(entity_handle.c_str(), "CHAR_PABLO") || strstr(entity_handle.c_str(), "CHAR_MILLA")


#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

#define M_PI                       3.14159265358979323846f

#define URotationToRadians(URotation)		((URotation)* (M_PI / 32768.0f))
#define URotationToDegree( URotation )		( ( URotation ) * ( 360.0f / 65536.0f ) ) 

#define DegreeToURotation( Degree )			( ( Degree ) * ( 65536.0f / 360.0f ) )
#define DegreeToRadian( Degree )			( ( Degree ) * ( M_PI / 180.0f ) )

#define RadianToURotation( URotation )		( ( URotation ) * ( 32768.0f / M_PI ) ) 
#define RadianToDegree( Radian )			( ( Radian ) * ( 180.0f / M_PI ) )


struct ModelPlayer {
	Vector Player;
	float CrossDist;
};
std::vector<ModelPlayer*>cPlayerA2;
std::vector<ModelPlayer*>cPlayerManual;


using _RtlCreateUserThread = NTSTATUS(NTAPI*)(
	HANDLE ProcessHandle,
	PSECURITY_DESCRIPTOR SecurityDescriptor,
	BOOLEAN CreateSuspend,
	ULONG StackZeroBits,
	PULONG StackReserved,
	PULONG StackCommit,
	void* StartAddress,
	void* StartParameter,
	PHANDLE ThreadHandle,
	void* ClientID
	);

void SpoofThread(void* Thread, HMODULE& hModule)
{
	HMODULE NT_DLL = LoadLibrary("ntdll");
	uintptr_t SpoofedAddress = NULL;
	int DefaultThreadSize = 1000;
	srand(time(NULL));

	for (int i = 1; i < 4; i++) {
		SpoofedAddress |= (rand() & 0xFF) << i * 8;
		SpoofedAddress |= (rand() & 0xFF) << i * 8;
		SpoofedAddress |= (rand() & 0xFF) << i * 8;
	}
	while (SpoofedAddress > 0x7FFFFFFF) {
		SpoofedAddress -= 0x1000;
	}
	VirtualProtect((void*)SpoofedAddress, DefaultThreadSize, PAGE_EXECUTE_READWRITE, NULL);

	CONTEXT tContext;
	HANDLE  pHandle = nullptr;

	_RtlCreateUserThread KeThread = (_RtlCreateUserThread)(GetProcAddress(GetModuleHandle("ntdll"), "RtlCreateUserThread"));
	KeThread(GetCurrentProcess(), nullptr, TRUE, NULL, NULL, NULL, (PTHREAD_START_ROUTINE)SpoofedAddress, hModule, &pHandle, NULL); //create a thread & stop init everything

	tContext.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;
	GetThreadContext(pHandle, &tContext);

#ifdef _WIN32
	tContext.Eax = (ULONG32)Thread;
#else
	tContext.Rcx = (ULONG64)Thread;
#endif

	tContext.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;

	SetThreadContext(pHandle, &tContext);

	ResumeThread(pHandle);
}


HANDLE MEMORY = OpenProcess(PROCESS_ALL_ACCESS, 0, GetCurrentProcessId());
DWORD AckBase = NULL;
DWORD NetBase = NULL;

LPDIRECT3DTEXTURE9 zulachamscolor;
LPDIRECT3DTEXTURE9 gladyochamscolor;
LPDIRECT3DTEXTURE9 zulachamscolor1;
LPDIRECT3DTEXTURE9 gladyochamscolor1;
LPD3DXLINE      g_pLine = NULL; //D3D Line
D3DVIEWPORT9    g_ViewPort; //ViewPort
LPD3DXLINE	 Line1;
HWND hewnwem;
IDirect3D9Ex* p_Object = NULL;
typedef long var;

typedef struct {
	var x, y, z;
} VECTOR;

typedef DWORD(*numelel)(const char* name);
numelel engine_getscript = (numelel)GetProcAddress(GetModuleHandleA("acknex.dll"), "engine_getscript");

typedef var(*avec_to_angle)(Vector*, Vector*);
avec_to_angle vec_to_angle = (avec_to_angle)GetProcAddress(GetModuleHandleA("acknex.dll"), "vec_to_angle");

typedef DWORD(*ent_next_0)(DWORD ent);
ent_next_0 ent_next = (ent_next_0)GetProcAddress(GetModuleHandleA("acknex.dll"), "ent_next");

typedef var(*trace_0)(VECTOR*, VECTOR*, var mode);
trace_0 c_trace = (trace_0)GetProcAddress(GetModuleHandleA("acknex.dll"), "c_trace");

typedef VECTOR* (*vec_for_ent_0)(VECTOR*, DWORD);
vec_for_ent_0 vec_for_ent = (vec_for_ent_0)GetProcAddress(GetModuleHandleA("acknex.dll"), "vec_for_ent");

typedef VECTOR* (*vec_to_ent_0)(VECTOR*, DWORD);
vec_to_ent_0 vec_to_ent = (vec_to_ent_0)GetProcAddress(GetModuleHandleA("acknex.dll"), "vec_to_ent");

typedef DWORD(*ent_file_0)(char* s);
ent_file_0 ent_for_file = (ent_file_0)GetProcAddress(GetModuleHandleA("acknex.dll"), "ent_for_file");

static ImVec2 pRadar;

VECTOR* vec_for_bone(VECTOR* temp, DWORD ent, const char* bonename) {

	FARPROC v30 = GetProcAddress(GetModuleHandleA("acknex.dll"), (LPCSTR)"vec_for_bone");
	((void(__cdecl*)(VECTOR*, DWORD, const char*))v30)(temp, ent, (char*)bonename);
	return temp;
}

struct HEXXModelPlayer2
{
	D3DXVECTOR3 Player;
	float CrossDist;
};
std::vector<HEXXModelPlayer2*>HEXXcPlayerA;


static void DrawLine(int x1, int y1, int x2, int y2, Vector color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 255)), thickness);
}

D3DMATRIX TempMatrix;


static bool WorldToScreen(const Vector& pos, Vector& screen, const D3DXMATRIX& matrix)
{
	D3DXVECTOR4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;
	D3DXVECTOR3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (ScreenCenterX * NDC.x) + (NDC.x + ScreenCenterX);
	screen.y = -(ScreenCenterY * NDC.y) + (NDC.y + ScreenCenterY);
	return true;
}

Vector CreateScreen(Vector Rootpoz)
{
	Vector screen;
	WorldToScreen(Vector(Rootpoz.x, Rootpoz.z, Rootpoz.y), screen, TempMatrix);
	return screen;
}

static bool W2SForSkeleton(const VECTOR& pos, VECTOR& screen, const D3DXMATRIX& matrix)
{
	VECTOR v20;

	v20.x = pos.x * 0.0009765625;
	v20.y = pos.y * 0.0009765625;
	v20.z = pos.z * 0.0009765625;

	D3DXVECTOR4 clipCoords;
	clipCoords.x = v20.x * matrix[0] + v20.y * matrix[4] + v20.z * matrix[8] + matrix[12];
	clipCoords.y = v20.x * matrix[1] + v20.y * matrix[5] + v20.z * matrix[9] + matrix[13];
	clipCoords.z = v20.x * matrix[2] + v20.y * matrix[6] + v20.z * matrix[10] + matrix[14];
	clipCoords.w = v20.x * matrix[3] + v20.y * matrix[7] + v20.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;
	D3DXVECTOR3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (ScreenCenterX * NDC.x) + (NDC.x + ScreenCenterX);
	screen.y = -(ScreenCenterY * NDC.y) + (NDC.y + ScreenCenterY);
	return true;
}

VECTOR SkeletonScreen(VECTOR Rootpoz)
{
	VECTOR screen;
	VECTOR screen2;
	screen2.x = Rootpoz.x;
	screen2.y = Rootpoz.z;
	screen2.z = Rootpoz.y;
	W2SForSkeleton(screen2, screen, TempMatrix);
	return screen;
}

void Box3D(Vector RootPos, Vector Color, int Thickness)
{
	auto a1 = RootPos.x;
	auto a2 = RootPos.z; //height
	auto a3 = RootPos.y;
	auto v7 = a1 - 31.5f; //width
	auto v8 = a2 - 50.f;
	auto v9 = a3 - 29.5f;
	auto v10 = a1 + 27.5f; //width
	auto v12 = a3 + 26.0f;
	Vector line1, line2, line3, line4, line5, line6, line7, line8;
	if (WorldToScreen(Vector(v7, v8, v9), line1, TempMatrix))
	{
		auto v4 = a2 + 40.5f;
		auto v11 = a2 + 40.5f;
		auto v13 = v4;
		auto v14 = v4;
		if (WorldToScreen(Vector(v10, v4, v12), line2, TempMatrix))
		{
			if (WorldToScreen(Vector(v10, v8, v9), line3, TempMatrix))
			{
				if (WorldToScreen(Vector(v7, v11, v9), line4, TempMatrix))
				{
					if (WorldToScreen(Vector(v7, v8, v12), line5, TempMatrix))
					{
						if (WorldToScreen(Vector(v7, v13, v12), line6, TempMatrix))
						{
							if (WorldToScreen(Vector(v10, v8, v12), line7, TempMatrix))
							{
								if (WorldToScreen(Vector(v10, v14, v9), line8, TempMatrix))
								{
									DrawLine(line1.x, line1.y, line4.x, line4.y, Color, Thickness);
									DrawLine(line3.x, line3.y, line8.x, line8.y, Color, Thickness);
									DrawLine(line7.x, line7.y, line2.x, line2.y, Color, Thickness);
									DrawLine(line5.x, line5.y, line6.x, line6.y, Color, Thickness);

									//Chan
									DrawLine(line1.x, line1.y, line3.x, line3.y, Color, Thickness);
									DrawLine(line3.x, line3.y, line7.x, line7.y, Color, Thickness);
									DrawLine(line7.x, line7.y, line5.x, line5.y, Color, Thickness);
									DrawLine(line5.x, line5.y, line1.x, line1.y, Color, Thickness);

									//Dau
									DrawLine(line4.x, line4.y, line8.x, line8.y, Color, Thickness);
									DrawLine(line8.x, line8.y, line2.x, line2.y, Color, Thickness);
									DrawLine(line2.x, line2.y, line6.x, line6.y, Color, Thickness);
									DrawLine(line6.x, line6.y, line4.x, line4.y, Color, Thickness);
								}
							}
						}
					}
				}
			}
		}
	}
}

void LAPDRWCRNbx(int X, int Y, int W, int H, Vector color, int thickness)
{
	float lineW = (W / 3);
	float lineH = (H / 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 255)), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 255)), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 255)), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 255)), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 255)), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 255)), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 255)), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 255)), thickness);
}

void RenderZ()
{

	ImVec4 color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 screenSize = io.DisplaySize;
	ImVec2 position = ImVec2(13, 4);
	ImGui::SetNextWindowPos(position);
	ImGui::Begin("", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);
	ImGui::PushStyleColor(ImGuiCol_Text, color); // Metin rengini değiştir
	ImGui::SetWindowFontScale(1.0f);// Yazı boyutunu küçültün
	ImGui::Text(""); // Metni çiz
	ImGui::PopStyleColor(); // Metin rengini geri yükle
	ImGui::End();

}

void InputHandler()
{
	for (int i = 0; i < 5; i++) ImGui::GetIO().MouseDown[i] = false;

	int button = -1;
	if (GetAsyncKeyState(VK_LBUTTON)) button = 0;

	if (button != -1) ImGui::GetIO().MouseDown[button] = true;
}

HRESULT GenerateTexture32(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
		return E_FAIL;

	WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
		| (WORD)(((colour32 >> 20) & 0xF) << 8)
		| (WORD)(((colour32 >> 12) & 0xF) << 4)
		| (WORD)(((colour32 >> 4) & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;

	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}
void mousee(float x, float y)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dx = (LONG)x;
	Input.mi.dy = (LONG)y;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &Input, sizeof(INPUT));
}

Vector localposs;

static int local_size = 4;
static int enemy_size = 4;

Vector RootPos;
Vector ScreenF;

Vector local;
Vector enemy;

float LAPTDGRTRDN(float degree)
{
	return degree * (M_PI / 180);
}


void LApangrtn(const Vector& angles, Vector* forward)
{
	float	sp, sy, cp, cy;

	sy = sin(LAPTDGRTRDN(angles.y));
	cy = cos(LAPTDGRTRDN(angles.y));

	sp = sin(LAPTDGRTRDN(angles.x));
	cp = cos(LAPTDGRTRDN(angles.x));

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}

Vector ViewAngles(uint32_t Entity)
{
	return readmem<Vector>(Entity + 0x3E8);// X: Yaw | Y: Pitch
}

static void DrawCircleFilled(int x, int y, int radius, RGBA* color, int segments)
{
	ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}

void DrawColoredRect(int x, int y, int w, int h, Vector color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, 255)), 3.f, 0, thickness);
}

D3DXVECTOR2 WorldRadar(Vector srcPos, Vector distPos, float yaw, float radarX, float radarY, float size)
{
	auto cosYaw = cos(DegreeToRadian(-yaw));
	auto sinYaw = sin(DegreeToRadian(-yaw));

	auto deltaX = srcPos.x - distPos.x;
	auto deltaY = srcPos.y - distPos.y;

	auto locationX = (float)(deltaY * cosYaw + deltaX * sinYaw) / 75.f;
	auto locationY = (float)(deltaX * cosYaw - deltaY * sinYaw) / 75.f;

	if (locationX > (size - 2.f))
		locationX = (size - 2.f);
	else if (locationX < -(size - 2.f))
		locationX = -(size - 2.f);

	if (locationY > (size - 6.f))
		locationY = (size - 6.f);
	else if (locationY < -(size - 6.f))
		locationY = -(size - 6.f);

	return D3DXVECTOR2((int)(locationX + radarX), (int)(locationY + radarY));
}


void DrawRadar(Vector LocalPos, Vector EntityPos, RGBA* EntityColor)
{
	auto radar_posX = pRadar.x + 135;
	auto radar_posY = pRadar.y + 135;

	auto Radar2D = WorldRadar(LocalPos, EntityPos, ViewAngles(LocalPlayer).x, radar_posX, radar_posY, 135.f);// radar pos
	DrawCircleFilled(Radar2D.x, Radar2D.y, enemy_size, EntityColor, 10);
}

void DrawESPBox(Vector Head, Vector Foot, Vector dwColor)
{
	Vector Box = Head - Foot;

	if (Box.y < 0)
		Box.y *= -1;

	int BoxWidth = (int)Box.y / 2;

	int DrawX = (int)Head.x - (BoxWidth / 2);
	int DrawY = (int)Head.y;

	DrawColoredRect(DrawX, DrawY, BoxWidth, (int)Box.y, dwColor, 1);
}

void LoopMatrix()
{
	uint32_t matrix_ptr = *(uint32_t*)(AckBase + 0x243F8C); //0x5916C0 //0x246FF4

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		D3DXMATRIX Draw = *(D3DXMATRIX*)(matrix_ptr);
		if (Draw._44 != 0.0f)
			TempMatrix = Draw;
		else
			Draw = TempMatrix;
	}
}

static void VectorAngles(const Vector& forward, Vector& angles)
{
	if (forward.y == 0.0f && forward.x == 0.0f)
	{
		angles.x = (forward.z > 0.0f) ? 75.0f : -75.0f; // Pitch (up/down)
		angles.y = 0.0f;  //yaw left/right
	}
	else
	{
		angles.x = atan2(forward.z, forward.Length2D()) * -180 / M_PI;
		angles.y = atan2(forward.y, forward.x) * 180 / M_PI;

		if (angles.y > 75)
			angles.y -= 180;
		else if (angles.y < 75)
			angles.y += 180;
		else if (angles.y == 75)
			angles.y = 0;

	}
	angles.z = 0.0f;
}

static Vector CalcAngle(Vector src, Vector dst)
{
	Vector angles;
	Vector delta = src - dst;
	VectorAngles(delta, angles);
	return Vector(angles.y, angles.x, angles.z);
}

void SetViewAngle(Vector angle)
{
	__try
	{
		writemem(LocalPlayer + 0x3E8, angle, sizeof(angle));
	}
	__except(1){}
}

#define IGNORE_ME 	(1<<0)
#define IGNORE_YOU	(1<<1)
#define IGNORE_PASSABLE (1<<2)
#define IGNORE_PASSENTS (1<<3)
#define IGNORE_MODELS	(1<<4)
#define IGNORE_SPRITES	(1<<5)
#define IGNORE_CONTENT  (1<<6)
#define IGNORE_MAPS	(1<<7)
#define IGNORE_WORLD	(1<<8)
#define ACTIVATE_SHOOT	(1<<10)

static bool visiblecheck;

inline var _VAR(double f) { return (var)(f * (1 << 10)); }

VECTOR bHead = { _VAR(0), _VAR(0), _VAR(0) };
VECTOR bSpine2 = { _VAR(0), _VAR(0), _VAR(0) }; // omurga başlangıcı
VECTOR bSpine = { _VAR(0), _VAR(0), _VAR(0) }; // omurga bitişi
VECTOR bPelvis = { _VAR(0), _VAR(0), _VAR(0) };

VECTOR bR_UpArm = { _VAR(0), _VAR(0), _VAR(0) };
VECTOR bR_ForeArm = { _VAR(0), _VAR(0), _VAR(0) };
VECTOR bR_Hand = { _VAR(0), _VAR(0), _VAR(0) };

VECTOR bR_Thigh = { _VAR(0), _VAR(0), _VAR(0) };
VECTOR bR_Calf = { _VAR(0), _VAR(0), _VAR(0) };
VECTOR bR_Foot = { _VAR(0), _VAR(0), _VAR(0) };

VECTOR bL_UpArm = { _VAR(0), _VAR(0), _VAR(0) };
VECTOR bL_ForeArm = { _VAR(0), _VAR(0), _VAR(0) };
VECTOR bL_Hand = { _VAR(0), _VAR(0), _VAR(0) };

VECTOR bL_Thigh = { _VAR(0), _VAR(0), _VAR(0) };
VECTOR bL_Calf = { _VAR(0), _VAR(0), _VAR(0) };
VECTOR bL_Foot = { _VAR(0), _VAR(0), _VAR(0) };

inline float _FLOAT(var x) { return ((float)x) / (1 << 10); }	// var -> float

void loop()
{
	DWORD pent = ent_next(NULL);
	while (pent)
	{
		pent = ent_next(pent);
		if (pent != NULL)
		{
			auto dwEntityHandle = readmem<uint32_t>(pent + 0xC);

			if (dwEntityHandle != NULL)
			{
				const char* entity_handle = (const char*)(dwEntityHandle);

#define isLocalPlayer strstr(entity_handle, "FPS_") && strstr(entity_handle, "_MESH.M")
#define ZulaTeam strstr(entity_handle, "CHAR_HALIL") || strstr(entity_handle, "CHAR_CEMAL") || strstr(entity_handle, "CHAR_AZAD") || strstr(entity_handle, "CHAR_DAYI") || strstr(entity_handle, "CHAR_TAHIR") || strstr(entity_handle, "CHAR_CETIN") || strstr(entity_handle, "CHAR_OSMAN") || strstr(entity_handle, "CHAR_SAMIL") || strstr(entity_handle, "CHAR_CUMALI") || strstr(entity_handle, "CHAR_POKADIN") || strstr(entity_handle, "CHAR_BAHRAM") || strstr(entity_handle, "CHAR_LEYLA")
#define GladioTeam strstr(entity_handle, "CHAR_AZER") || strstr(entity_handle, "CHAR_PIERRE") || strstr(entity_handle, "CHAR_BOB") || strstr(entity_handle, "CHAR_AVI") || strstr(entity_handle, "CHAR_EDWARD") || strstr(entity_handle, "CHAR_GEORGE") || strstr(entity_handle,"CHAR_IVAN") || strstr(entity_handle, "CHAR_JACK") || strstr(entity_handle, "CHAR_ROSA") || strstr(entity_handle, "CHAR_PABLO") || strstr(entity_handle, "CHAR_MILLA") || strstr(entity_handle, "CHAR_KIERA")
#define BombModels strstr(entity_handle, "SIL_BS_M18_MESH") || strstr(entity_handle, "SIL_BG_DUALK4_MESH") || strstr(entity_handle, "SIL_BS_TRP90_MESH") || strstr(entity_handle, "SIL_BF_M84_MESH") || strstr(entity_handle, "SIL_BG_M61_MESH") || strstr(entity_handle, "SIL_BG_C4KUMANDA_MESH") || strstr(entity_handle, "SIL_BG_MK3_MESH") || strstr(entity_handle, "SIL_BG_MK2_MESH")


				if (entity_handle)
				{
					RootPos = readmem<Vector>(pent + 0x3DC);
					ScreenF = CreateScreen(RootPos);

					if (bombesp)
					{
						if (BombModels)
						{
							if (ScreenF.x != 0 || ScreenF.y != 0)
							{
								ImGui::GetOverlayDrawList()->AddText(ImVec2(ScreenF.x, ScreenF.y), ImColor(255, 35, 35), "Bomb!!");//sol yazı
							}
						}
					}

					if (nosmoke)
					{
						if (strstr(entity_handle, "SMOKE") && strstr(entity_handle, "SPRITE") && strstr(entity_handle, ".DDS"))
						{
							*(Vector*)(pent + 0x3DC) = { 999.f, 999.f, 999.f };
						}
					}

					if (isLocalPlayer)
					{
						LocalPlayer = pent;
					}

					Vector LocalPos = readmem<Vector>(LocalPlayer + 0x3DC);
					Vector LocalScreen = CreateScreen(LocalPos);

					float distance = LocalPos.DistTo(RootPos) / 100.f;
					char xdist[64];
					sprintf(xdist, "%.fm", distance);

					if (strstr(entity_handle, "CHAR") && strstr(entity_handle, "ME"))
					{
						vec_for_bone(&bPelvis, pent, (char*)"Bip01 Pelvis");
						vec_for_bone(&bHead, pent, (char*)"Bip01 Head");
						vec_for_bone(&bSpine, pent, (char*)"Bip01 Spine");
						vec_for_bone(&bSpine2, pent, (char*)"Bip01 Spine2");
						vec_for_bone(&bL_Hand, pent, (char*)"Bip01 L Hand");
						vec_for_bone(&bL_Foot, pent, (char*)"Bip01 L Foot");
						vec_for_bone(&bL_Calf, pent, (char*)"Bip01 L Calf");
						vec_for_bone(&bL_Thigh, pent, (char*)"Bip01 L Thigh");
						vec_for_bone(&bL_UpArm, pent, (char*)"Bip01 L UpperArm");
						vec_for_bone(&bL_ForeArm, pent, (char*)"Bip01 L Forearm");
						vec_for_bone(&bR_UpArm, pent, (char*)"Bip01 R UpperArm");
						vec_for_bone(&bR_ForeArm, pent, (char*)"Bip01 R Forearm");
						vec_for_bone(&bR_Hand, pent, (char*)"Bip01 R Hand");
						vec_for_bone(&bR_Thigh, pent, (char*)"Bip01 R Thigh");
						vec_for_bone(&bR_Calf, pent, (char*)"Bip01 R Calf");
						vec_for_bone(&bR_Foot, pent, (char*)"Bip01 R Foot");

						int die = readmem<int>(readmem<DWORD>(readmem<DWORD>(pent + 0x4) + 0x4) + 0x34);
						if (die == 67109120)
						{

							Vector vRoot;
							WorldToScreen(Vector((float)RootPos.x, (float)RootPos.z, (float)RootPos.y), vRoot, TempMatrix);

							Vector aimpos = readmem<Vector>(pent + 0x3DC);

							Vector vHead, vFoot, vNeckk, rThigh;


							if (WorldToScreen(Vector((float)RootPos.x, (float)RootPos.z + 32.f, (float)RootPos.y), vHead, TempMatrix) &&
								WorldToScreen(Vector((float)RootPos.x, (float)RootPos.z - 30.f, (float)RootPos.y), vFoot, TempMatrix) &&
								WorldToScreen(Vector((float)RootPos.x, (float)RootPos.z + 23.f, (float)RootPos.y), vNeckk, TempMatrix) &&
								WorldToScreen(Vector((float)RootPos.x, (float)RootPos.z, (float)RootPos.y), vRoot, TempMatrix)) {
								float BoxHeight = vFoot.y - vHead.y;
								float BoxWidth = BoxHeight / 2.4f;

								float x1 = vHead.x - (BoxWidth / 2.f);
								float y1 = vHead.y;
								float x2 = x1 + BoxWidth;
								float y2 = y1 + BoxHeight;


								if (EspBox2D)
								{
									if (esptypee == 0)
									{
										if (Zula)
										{
											if (ZulaTeam)
											{
												DrawESPBox(vHead, vFoot, Vector(255 * esprenk.x, 255 * esprenk.y, 255 * esprenk.z));
											}
										}
										if (Gladyo)
										{
											if (GladioTeam)
											{
												DrawESPBox(vHead, vFoot, Vector(255 * esprenkg.x, 255 * esprenkg.y, 255 * esprenkg.z));
											}
										}
									}

									if (esptypee == 1) //megacheat esp xd
									{
										if (Zula)
										{
											if (ZulaTeam)
											{
												Box3D(RootPos, Vector(255 * esprenk.x, 255 * esprenk.y, 255 * esprenk.z), 0.6);
											}
										}

										if (Gladyo)
										{
											if (GladioTeam)
											{
												Box3D(RootPos, Vector(255 * esprenkg.x, 255 * esprenkg.y, 255 * esprenkg.z), 0.6);
											}
										}
									}

									if (esptypee == 2)
									{
										Vector head2 = RootPos;

										Vector zero_r = Vector(RootPos.x, RootPos.y, RootPos.z - 52);
										Vector head_r = Vector(head2.x, head2.y, head2.z + 40);

										Vector zero_w2s_r = CreateScreen(zero_r);
										Vector head_w2s_r = CreateScreen(head_r);

										float BoxHeight = zero_w2s_r.y - head_w2s_r.y;
										float BoxWidth = BoxHeight / 2.f;

										if (Zula)
										{
											if (ZulaTeam)
											{
												LAPDRWCRNbx(zero_w2s_r.x - (BoxWidth / 2), head_w2s_r.y, BoxWidth, BoxHeight, Vector(255 * esprenk.x, 255 * esprenk.y, 255 * esprenk.z), 0.6f);
											}
										}

										if (Gladyo)
										{
											if (GladioTeam)
											{
												LAPDRWCRNbx(zero_w2s_r.x - (BoxWidth / 2), head_w2s_r.y, BoxWidth, BoxHeight, Vector(255 * esprenkg.x, 255 * esprenkg.y, 255 * esprenkg.z), 0.6f);
											}
										}
									}
								}

								if (espline)
								{
									ImVec4 redColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // R=1, G=0, B=0, A=1
									ImVec4 greenColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);  // R=0, G=1, B=0, A=1

									Vector redcol = Vector(255 * redColor.x, 255 * redColor.y, 255 * redColor.z);
									Vector greencol = Vector(255 * greenColor.x, 255 * greenColor.y, 255 * greenColor.z);

									if (Zula)
									{
										if (ZulaTeam)
										{
											DrawLine(ScreenCenterX, ScreenCenterY + ScreenCenterY, vFoot.x, vFoot.y - 3.5f, Vector(255 * esplinerenk.x, 255 * esplinerenk.y, 255 * esplinerenk.z), 0.6);
										}
									}

									if (Gladyo)
									{
										if (GladioTeam)
										{
											DrawLine(ScreenCenterX, ScreenCenterY + ScreenCenterY, vFoot.x, vFoot.y - 3.5f, Vector(255 * esplinerenkg.x, 255 * esplinerenkg.y, 255 * esplinerenkg.z), 0.6);
										}
									}
								}

								if (espdistance)
								{
									if (Zula)
									{
										if (ZulaTeam)
										{
											ImGui::GetOverlayDrawList()->AddText(ImVec2((vFoot.x + 3.f) - (strlen(xdist) * 7 / 2), vFoot.y + 8.f), ImColor(255, 35, 35), xdist);
										}
									}

									if (Gladyo)
									{
										if (GladioTeam)
										{
											ImGui::GetOverlayDrawList()->AddText(ImVec2((vFoot.x + 3.f) - (strlen(xdist) * 7 / 2), vFoot.y + 8.f), ImColor(255, 35, 35), xdist);
										}
									}
								}

								if (radar)
								{

									ImVec4 silverwhitee = ImVec4(236 / 255.0f, 236 / 255.0f, 236 / 255.0f, 200 / 255.0f);

									Vector silverwhitee_ = Vector(255 * silverwhitee.x, 255 * silverwhitee.y, 255 * silverwhitee.z);

									static ImVec2 radarPosition = ImVec2(pRadar.x, pRadar.y);  // Radarın başlangıç konumu

									if (ImGui::IsMouseDragging(0))  // Fare sol tuşu ile sürükleniyor mu kontrolü
									{
										ImVec2 delta = ImGui::GetIO().MouseDelta;
										radarPosition.x += delta.x;
										radarPosition.y += delta.y;
									}

									pRadar.x = radarPosition.x;
									pRadar.y = radarPosition.y;

									if (radartype == 0)
									{
										ImGui::GetOverlayDrawList()->AddRect(ImVec2(pRadar.x, pRadar.y), ImVec2(pRadar.x + 270, pRadar.y + 270), ImGui::ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 255)), 2);
										auto radar_posX = pRadar.x + 135;
										auto radar_posY = pRadar.y + 135;
										DrawLine(radar_posX, radar_posY, radar_posX, radar_posY + 135, silverwhitee_, 1);
										DrawLine(radar_posX, radar_posY, radar_posX, radar_posY - 135, silverwhitee_, 1);
										DrawLine(radar_posX, radar_posY, radar_posX + 135, radar_posY, silverwhitee_, 1);
										DrawLine(radar_posX, radar_posY, radar_posX - 135, radar_posY, silverwhitee_, 1);
										DrawCircleFilled(radar_posX + 0.50f, radar_posY, local_size, &DarkYellow, 50);
									}

									if (radartype == 1)
									{
										float radius = 135.0f;
										float radar_posX = pRadar.x + radius;
										float radar_posY = pRadar.y + radius;

										ImVec2 center(radar_posX, radar_posY);
										ImGui::GetOverlayDrawList()->AddCircle(center, radius, ImGui::ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 255)), 32, 1.0f);

										DrawLine(radar_posX, radar_posY, radar_posX, radar_posY + radius, silverwhitee_, 1);
										DrawLine(radar_posX, radar_posY, radar_posX, radar_posY - radius, silverwhitee_, 1);
										DrawLine(radar_posX, radar_posY, radar_posX + radius, radar_posY, silverwhitee_, 1);
										DrawLine(radar_posX, radar_posY, radar_posX - radius, radar_posY, silverwhitee_, 1);
										DrawCircleFilled(radar_posX + 0.50f, radar_posY, local_size, &DarkYellow, 50);
									}

									if (Zula)
									{
										if (radarcolint == 0)
										{
											if (ZulaTeam)
											{
												DrawRadar(LocalPos, RootPos, &red);
											}
										}

										if (radarcolint == 1)
										{
											if (ZulaTeam)
											{
												DrawRadar(LocalPos, RootPos, &green);
											}
										}

										if (radarcolint == 2)
										{
											if (ZulaTeam)
											{
												DrawRadar(LocalPos, RootPos, &blue);
											}
										}
									}


									if (Gladyo)
									{
										if (radarcolint2 == 0)
										{
											if (GladioTeam)
											{
												DrawRadar(LocalPos, RootPos, &red);
											}
										}

										if (radarcolint2 == 1)
										{
											if (GladioTeam)
											{
												DrawRadar(LocalPos, RootPos, &green);
											}
										}

										if (radarcolint2 == 2)
										{
											if (GladioTeam)
											{
												DrawRadar(LocalPos, RootPos, &blue);
											}
										}
									}
								}

								if (espskeleton)
								{

									VECTOR vNeck = SkeletonScreen(bHead);
									VECTOR vSpine2 = SkeletonScreen(bSpine2);
									VECTOR vSpine = SkeletonScreen(bSpine);
									VECTOR vPelvis = SkeletonScreen(bPelvis);

									VECTOR vR_UpArm = SkeletonScreen(bR_UpArm);
									VECTOR vR_ForeArm = SkeletonScreen(bR_ForeArm);
									VECTOR vR_Hand = SkeletonScreen(bR_Hand);

									VECTOR vL_UpArm = SkeletonScreen(bL_UpArm);
									VECTOR vL_ForeArm = SkeletonScreen(bL_ForeArm);
									VECTOR vL_Hand = SkeletonScreen(bL_Hand);

									VECTOR vR_Thigh = SkeletonScreen(bR_Thigh);
									VECTOR vR_Calf = SkeletonScreen(bR_Calf);
									VECTOR vR_Foot = SkeletonScreen(bR_Foot);

									VECTOR vL_Thigh = SkeletonScreen(bL_Thigh);
									VECTOR vL_Calf = SkeletonScreen(bL_Calf);
									VECTOR vL_Foot = SkeletonScreen(bL_Foot);

									if (Zula)
									{
										if (ZulaTeam)
										{

											//bel üstü
											DrawLine(vNeck.x, vNeck.y, vSpine2.x, vSpine2.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
											DrawLine(vSpine2.x, vSpine2.y, vSpine.x, vSpine.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
											DrawLine(vSpine.x, vSpine.y, vPelvis.x, vPelvis.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);

											DrawLine(vNeck.x, vNeck.y, vR_UpArm.x, vR_UpArm.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
											DrawLine(vR_UpArm.x, vR_UpArm.y, vR_ForeArm.x, vR_ForeArm.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
											DrawLine(vR_ForeArm.x, vR_ForeArm.y, vR_Hand.x, vR_Hand.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);

											DrawLine(vNeck.x, vNeck.y, vL_UpArm.x, vL_UpArm.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
											DrawLine(vL_UpArm.x, vL_UpArm.y, vL_ForeArm.x, vL_ForeArm.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
											DrawLine(vL_ForeArm.x, vL_ForeArm.y, vL_Hand.x, vL_Hand.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);

											//bel altı
											DrawLine(vPelvis.x, vPelvis.y, vR_Thigh.x, vR_Thigh.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
											DrawLine(vR_Thigh.x, vR_Thigh.y, vR_Calf.x, vR_Calf.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
											DrawLine(vR_Calf.x, vR_Calf.y, vR_Foot.x, vR_Foot.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);

											DrawLine(vPelvis.x, vPelvis.y, vL_Thigh.x, vL_Thigh.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
											DrawLine(vL_Thigh.x, vL_Thigh.y, vL_Calf.x, vL_Calf.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
											DrawLine(vL_Calf.x, vL_Calf.y, vL_Foot.x, vL_Foot.y, Vector(255 * skeletonrenk.x, 255 * skeletonrenk.y, 255 * skeletonrenk.z), 1.4);
										}
									}

									if (Gladyo)
									{
										if (GladioTeam)
										{
											DrawLine(vNeck.x, vNeck.y, vSpine2.x, vSpine2.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
											DrawLine(vSpine2.x, vSpine2.y, vSpine.x, vSpine.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
											DrawLine(vSpine.x, vSpine.y, vPelvis.x, vPelvis.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);

											DrawLine(vNeck.x, vNeck.y, vR_UpArm.x, vR_UpArm.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
											DrawLine(vR_UpArm.x, vR_UpArm.y, vR_ForeArm.x, vR_ForeArm.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
											DrawLine(vR_ForeArm.x, vR_ForeArm.y, vR_Hand.x, vR_Hand.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);

											DrawLine(vNeck.x, vNeck.y, vL_UpArm.x, vL_UpArm.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
											DrawLine(vL_UpArm.x, vL_UpArm.y, vL_ForeArm.x, vL_ForeArm.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
											DrawLine(vL_ForeArm.x, vL_ForeArm.y, vL_Hand.x, vL_Hand.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);

											DrawLine(vPelvis.x, vPelvis.y, vR_Thigh.x, vR_Thigh.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
											DrawLine(vR_Thigh.x, vR_Thigh.y, vR_Calf.x, vR_Calf.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
											DrawLine(vR_Calf.x, vR_Calf.y, vR_Foot.x, vR_Foot.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);

											DrawLine(vPelvis.x, vPelvis.y, vL_Thigh.x, vL_Thigh.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
											DrawLine(vL_Thigh.x, vL_Thigh.y, vL_Calf.x, vL_Calf.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
											DrawLine(vL_Calf.x, vL_Calf.y, vL_Foot.x, vL_Foot.y, Vector(255 * skeletonrenkg.x, 255 * skeletonrenkg.y, 255 * skeletonrenkg.z), 1.4);
										}
									}
								}

								if (lookdirection)
								{
									Vector view_angle = ViewAngles(pent);
									VECTOR foot = SkeletonScreen(bL_Foot);
									VECTOR head = SkeletonScreen(bHead);
									float boxwheightorg = foot.y - head.y;
									float boxwidthtorg = boxwheightorg / 2.4f;

									if (Zula)
									{
										if (ZulaTeam)
										{
											Vector test2, headpos;

											headpos.x = bHead.x * 0.0009765625;
											headpos.y = bHead.y * 0.0009765625;
											headpos.z = bHead.z * 0.0009765625;

											LApangrtn(view_angle, &test2);
											test2.x *= 120;
											test2.y *= 120;
											test2.z *= 120;

											Vector end = headpos + test2;
											Vector test1, test3;
											test1 = CreateScreen(headpos);
											test3 = CreateScreen(end);

											ImGui::GetOverlayDrawList()->AddLine(ImVec2(test1.x, test1.y), ImVec2(test3.x, test3.y), ImGui::GetColorU32({ 0.0f, 1.0f, 0.0f, 1.0f }), 1.f);
											ImGui::GetOverlayDrawList()->AddCircle(ImVec2(test3.x, test3.y), boxwidthtorg / 6, ImGui::GetColorU32({ 0.33f, 0.33f, 0.33f, 1.f }), 32, 2.f);
										}
									}

									if (Gladyo)
									{
										if (GladioTeam)
										{
											Vector test2, headpos;

											headpos.x = bHead.x * 0.0009765625;
											headpos.y = bHead.y * 0.0009765625;
											headpos.z = bHead.z * 0.0009765625;

											LApangrtn(view_angle, &test2);
											test2.x *= 120;
											test2.y *= 120;
											test2.z *= 120;

											Vector end = headpos + test2;
											Vector test1, test3;
											test1 = CreateScreen(headpos);
											test3 = CreateScreen(end);

											ImGui::GetOverlayDrawList()->AddLine(ImVec2(test1.x, test1.y), ImVec2(test3.x, test3.y), ImGui::GetColorU32({ 0.0f, 1.0f, 0.0f, 1.0f }), 1.f);
											ImGui::GetOverlayDrawList()->AddCircle(ImVec2(test3.x, test3.y), boxwidthtorg / 6, ImGui::GetColorU32({ 0.33f, 0.33f, 0.33f, 1.f }), 32, 2.f);
										}
									}
								}

								if (Aimbot == true && ShowMenu == false)
								{
									//yess some math problems for aimbot !!

									VECTOR SrcPos = { LocalPos.x * 1024.0, _VAR(0), _VAR(0) }; //float -> var -> (only x for trace)
									VECTOR EnemyPos = { bHead.x, _VAR(0), _VAR(0) }; //float -> var -> (only x for trace)

									if (Zula)
									{
										if (ZulaTeam)
										{
											if (visiblecheck)
											{
												var hit = c_trace(&SrcPos, &EnemyPos, IGNORE_ME | IGNORE_SPRITES); //not work maybe
												if ((hit * 0.0009765625) > 0) //var -> float or int for visiblecheck (with 1/1024)
												{

												}
												else
												{
													float z_offset = 0.0f;

													if (aimbone == 0) {
														Vector headpos = Vector(bHead.x * 0.0009765625, bHead.y * 0.0009765625, bHead.z * 0.0009765625);
														Vector screen;

														if (WorldToScreen(Vector((float)headpos.x, (float)headpos.z + 5.0f, (float)headpos.y), screen, TempMatrix))
														{
															ModelPlayer* aiment = new ModelPlayer;

															aiment->Player = screen;

															cPlayerManual.push_back(aiment);
														}

													}
													else if (aimbone == 1) {
														z_offset = 13.0f;

														aimpos.z += z_offset;

														Vector screen;
														if (WorldToScreen(Vector((float)aimpos.x, (float)aimpos.z, (float)aimpos.y), screen, TempMatrix))
														{
															ModelPlayer* aiment = new ModelPlayer;

															aiment->Player = screen;

															cPlayerManual.push_back(aiment);
														}
													}
													else if (aimbone == 2) {
														z_offset = -21.0f;

														aimpos.z += z_offset;

														Vector screen;
														if (WorldToScreen(Vector((float)aimpos.x, (float)aimpos.z, (float)aimpos.y), screen, TempMatrix))
														{
															ModelPlayer* aiment = new ModelPlayer;

															aiment->Player = screen;

															cPlayerManual.push_back(aiment);
														}
													}

												}
											}
											else
											{
												float z_offset = 0.0f;

												if (aimbone == 0) {
													Vector headpos = Vector(bHead.x * 0.0009765625, bHead.y * 0.0009765625, bHead.z * 0.0009765625);
													Vector screen;

													//float distance = LocalPos.DistTo(headpos) / 100.f;
													//Vector LocPos = LocalPos;
													//LocPos.z -= distance;
													//Vector vector_pos = CalcAngle(LocPos, headpos);
													//SetViewAngle(vector_pos);

													if (WorldToScreen(Vector((float)headpos.x, (float)headpos.z + 5.0f, (float)headpos.y), screen, TempMatrix))
													{
														ModelPlayer* aiment = new ModelPlayer;

														aiment->Player = screen;

														cPlayerManual.push_back(aiment);
													}

												}
												else if (aimbone == 1) {
													z_offset = 13.0f;

													aimpos.z += z_offset;

													Vector screen;
													if (WorldToScreen(Vector((float)aimpos.x, (float)aimpos.z, (float)aimpos.y), screen, TempMatrix))
													{
														ModelPlayer* aiment = new ModelPlayer;

														aiment->Player = screen;

														cPlayerManual.push_back(aiment);
													}
												}
												else if (aimbone == 2) {
													z_offset = -21.0f;

													aimpos.z += z_offset;

													Vector screen;
													if (WorldToScreen(Vector((float)aimpos.x, (float)aimpos.z, (float)aimpos.y), screen, TempMatrix))
													{
														ModelPlayer* aiment = new ModelPlayer;

														aiment->Player = screen;

														cPlayerManual.push_back(aiment);
													}
												}
											}
										}
									}
									if (Gladyo)
									{
										if (GladioTeam)
										{
											if (visiblecheck)
											{
												var hit = c_trace(&SrcPos, &EnemyPos, IGNORE_ME | IGNORE_SPRITES); //not work maybe
												if ((hit * 0.0009765625) > 0) //var -> float or int for visiblecheck
												{

												}
												else
												{
													float z_offset = 0.0f;

													if (aimbone == 0) {
														Vector headpos = Vector(bHead.x * 0.0009765625, bHead.y * 0.0009765625, bHead.z * 0.0009765625);
														Vector screen;
														if (WorldToScreen(Vector((float)headpos.x, (float)headpos.z + 5.0f, (float)headpos.y), screen, TempMatrix))
														{
															ModelPlayer* aiment = new ModelPlayer;

															aiment->Player = screen;

															cPlayerManual.push_back(aiment);
														}

													}
													else if (aimbone == 1) {
														z_offset = 13.0f;

														aimpos.z += z_offset;

														Vector screen;
														if (WorldToScreen(Vector((float)aimpos.x, (float)aimpos.z, (float)aimpos.y), screen, TempMatrix))
														{
															ModelPlayer* aiment = new ModelPlayer;

															aiment->Player = screen;

															cPlayerManual.push_back(aiment);
														}
													}
													else if (aimbone == 2) {
														z_offset = -21.0f;

														aimpos.z += z_offset;

														Vector screen;
														if (WorldToScreen(Vector((float)aimpos.x, (float)aimpos.z, (float)aimpos.y), screen, TempMatrix))
														{
															ModelPlayer* aiment = new ModelPlayer;

															aiment->Player = screen;

															cPlayerManual.push_back(aiment);
														}
													}
												}
											}
											else
											{
												float z_offset = 0.0f;

												if (aimbone == 0) {
													Vector headpos = Vector(bHead.x * 0.0009765625, bHead.y * 0.0009765625, bHead.z * 0.0009765625);
													Vector screen;

													//float distance = LocalPos.DistTo(headpos) / 100.f;
													//Vector LocPos = LocalPos;
												///	LocPos.z -= distance;
												//	Vector vector_pos = CalcAngle(LocPos, headpos);
												//	SetViewAngle(vector_pos);

													if (WorldToScreen(Vector((float)headpos.x, (float)headpos.z + 5.0f, (float)headpos.y), screen, TempMatrix))
													{
														ModelPlayer* aiment = new ModelPlayer;

														aiment->Player = screen;

														cPlayerManual.push_back(aiment);
													}

												}
												else if (aimbone == 1) {
													z_offset = 13.0f;

													aimpos.z += z_offset;

													Vector screen;
													if (WorldToScreen(Vector((float)aimpos.x, (float)aimpos.z, (float)aimpos.y), screen, TempMatrix))
													{
														ModelPlayer* aiment = new ModelPlayer;

														aiment->Player = screen;

														cPlayerManual.push_back(aiment);
													}
												}
												else if (aimbone == 2) {
													z_offset = -21.0f;

													aimpos.z += z_offset;

													Vector screen;
													if (WorldToScreen(Vector((float)aimpos.x, (float)aimpos.z, (float)aimpos.y), screen, TempMatrix))
													{
														ModelPlayer* aiment = new ModelPlayer;

														aiment->Player = screen;

														cPlayerManual.push_back(aiment);
													}
												}
											}

										}
									}
								}

							}
						}
					}
				}
			}
		}
	}
}

HRESULT APIENTRY presentt(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	if (pDevice == nullptr) return presento(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	if (setup) {
		D3DXCreateLine(pDevice, &Line2);
		setup = false;
	}
	if (!imguiStarted)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		D3DDEVICE_CREATION_PARAMETERS d3dcp;
		pDevice->GetCreationParameters(&d3dcp);
		game_hwnd = d3dcp.hFocusWindow;
		if (game_hwnd != NULL)
		{
			game_wndproc = (WNDPROC)SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui_ImplWin32_Init(game_hwnd);
			ImGui_ImplDX9_Init(pDevice);
			ImGui::GetIO().ImeWindowHandle = game_hwnd;
			ImGuiIO& io = ImGui::GetIO();
			ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf ", 14);
			static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
			ImFontConfig icons_config;
			icons_config.MergeMode = true;
			io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome_data, FontAwesome_size, 14.0f, &icons_config, icons_ranges);
			io.Fonts->Build();
			imguiStarted = true;
		}
	}
	static bool create = false;
	if (!create) {
		pDevice->GetViewport(&viewport);
		ScreenCenterX = viewport.Width / 2.0f;
		ScreenCenterY = viewport.Height / 2.0f;
		D3DXCreateLine(pDevice, &Line1);
		create = true;
	}

	if (g_pFont == NULL) D3DXCreateFont(pDevice, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Verdana.ttf", &g_pFont); //Create fonts

	if (g_pLine == NULL) D3DXCreateLine(pDevice, &g_pLine); //Create lines

	D3DXCreateTextureFromFileInMemory(pDevice, &MJCursor, sizeof(MJCursor), &DrawCursor);
	ImGui::GetIO().MouseDrawCursor = 1;
	ImGui::GetOverlayDrawList()->AddImage(DrawCursor, ImVec2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), ImVec2(ImGui::GetIO().MousePos.x + 20, ImGui::GetIO().MousePos.y + 20));

	if (ShowMenu)
	{
		ImGui::GetIO().MouseDrawCursor = 1;
		create = false;
		if (Chams)
		{
			if (RainbowChams == 0)
			{
				GenerateTexture32(pDevice, &zulachamscolor, FLOAT4TOD3DCOLOR(zulachams));
				GenerateTexture32(pDevice, &zulachamscolor1, FLOAT4TOD3DCOLOR(zulachams1));
				GenerateTexture32(pDevice, &gladyochamscolor, FLOAT4TOD3DCOLOR(gladyochams));
				GenerateTexture32(pDevice, &gladyochamscolor1, FLOAT4TOD3DCOLOR(gladyochams1));
			}
		}
	}
	else
		ImGui::GetIO().MouseDrawCursor = 0;

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		ShowMenu = !ShowMenu;
	}
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (ShowMenu)
	{
	    RenderZ();
		pDevice->GetViewport(&viewPort);
		pDevice->GetViewport(&g_ViewPort);
		Tema();
		InputHandler();
		ImGui::SetNextWindowSize(ImVec2(535, 340));
		if (ImGui::Begin("Zula Cheat v3", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
		{
			HmenuRender();
		}ImGui::End();
	}

	pRadar.x = ScreenCenterX + 298;
	pRadar.y = ScreenCenterY - ScreenCenterY + 80;

	ImGui::Begin(XorString("##Background"), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);
	loop();
	auto draw = ImGui::GetOverlayDrawList();
	if (circlefov)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), aimfov * 2, ImGui::ColorConvertFloat4ToU32(circlecolor), 100, 1.0f);
	}ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	//name esp func
	typedef PVOID(*nameVoid)();
	nameVoid esseknameactive = (nameVoid)engine_getscript((char*)"PNL_DrawPlayerNameAll");
	if (NameEspAktif)
	{
		esseknameactive();
	}

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return presento(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT APIENTRY drawindexed(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	static float rainbow;
	rainbow += 0.0001f;
	if (rainbow > 1.f) rainbow = 0.f;
	DWORD rainbowcolor = Color2::ToImColor(Color2::FromHSB(rainbow, 1.f, 1.f));

	//No Recoil
	if (NoRecoil > 0)
	{
		if (norecoilptr == 0) {

			if (CNoRecoil)
			{
				norecoilptr = 1;
			}
			else {
				CNoRecoil = ScanProc(Signature::NoRecoil, Signature::NoRecoilMask);
				if (CNoRecoil)
				{
					ReadProcessMemory(GetCurrentProcess(), (LPVOID)(CNoRecoil), &NorecoilOFF, sizeof(NorecoilOFF), NULL);

					norecoilptr = 1;
				}
			}
		}
		if (norecoilptr == 1)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CNoRecoil), &ONAray, sizeof(ONAray), NULL);
			norecoilptr = 2;
		}

	}
	else {
		if (norecoilptr == 1 || norecoilptr == 2)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CNoRecoil), &NorecoilOFF, sizeof(NorecoilOFF), NULL);
			norecoilptr = 0;
		}
	}
	//No Spread
	if (NoSpread > 0)
	{
		if (nospreadptr == 0) {

			if (CNoSpread)
			{
				nospreadptr = 1;
			}
			else {
				CNoSpread = ScanProc(Signature::NoSpread, Signature::NoSpreadMask);
				if (CNoSpread)
				{
					ReadProcessMemory(GetCurrentProcess(), (LPVOID)(CNoSpread), &NospreadOFF, sizeof(NospreadOFF), NULL);

					nospreadptr = 1;
				}
			}
		}
		if (nospreadptr == 1)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CNoSpread), &ONAray, sizeof(ONAray), NULL);
			nospreadptr = 2;
		}

	}
	else {
		if (nospreadptr == 1 || nospreadptr == 2)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CNoSpread), &NospreadOFF, sizeof(NospreadOFF), NULL);
			nospreadptr = 0;
		}
	}
	//Fast Weapon Switch
	if (FastWeaponSwitch > 0)
	{
		if (fastswptr == 0) {

			if (CFastWeapon)
			{
				fastswptr = 1;
			}
			else {
				CFastWeapon = ScanProc(Signature::FastWeaponSwitch, Signature::FastWeaponSwitchMask);
				if (CFastWeapon)
				{
					ReadProcessMemory(GetCurrentProcess(), (LPVOID)(CFastWeapon), &FastWeaponOFF, sizeof(FastWeaponOFF), NULL);

					fastswptr = 1;
				}
			}
		}
		if (fastswptr == 1)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CFastWeapon), &ONAray, sizeof(ONAray), NULL);
			fastswptr = 2;
		}

	}
	else {
		if (fastswptr == 1 || fastswptr == 2)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CFastWeapon), &FastWeaponOFF, sizeof(FastWeaponOFF), NULL);
			fastswptr = 0;
		}
	}

	if (Spammmm > 0)
	{
		if (spamptr == 0) {

			if (CSpam1)
			{
				spamptr = 1;
			}
			else {
				CSpam1 = ScanProc(Signature::Spammerqwe, Signature::SpammerqweMask);
				if (CSpam1)
				{
					ReadProcessMemory(GetCurrentProcess(), (LPVOID)(CSpam1), &Spam1, sizeof(Spam1), NULL);
					spamptr = 1;
				}
			}
		}
		if (spamptr == 1)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CSpam1), &spamon, sizeof(spamon), NULL);
			spamptr = 2;
		}

	}
	else {
		if (spamptr == 1 || spamptr == 2)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CSpam1), &Spam1, sizeof(Spam1), NULL);
			spamptr = 0;
		}
	}

	//AntiAfk
	if (AntiAFK)
	{
		if (afkptr == 0) {

			if (CAfk)
			{
				afkptr = 1;
			}
			else {
				CAfk = ScanProc(Signature::AntiAFK, Signature::AntiAFKMask);
				if (CAfk)
				{
					ReadProcessMemory(GetCurrentProcess(), (LPVOID)(CAfk), &AfkOFF, sizeof(AfkOFF), NULL);

					afkptr = 1;
				}
			}
		}
		if (afkptr == 1)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CAfk), &ONAray, sizeof(ONAray), NULL);
			afkptr = 2;
		}

	}
	else {
		if (afkptr == 1 || afkptr == 2)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CAfk), &AfkOFF, sizeof(AfkOFF), NULL);
			afkptr = 0;
		}
	}

	if (fakelag)
	{
		if (GetAsyncKeyState('E') & 0x8000)
		{
			if (fakeptr == 0) {

				ReadProcessMemory(GetCurrentProcess(), (LPVOID)(NetBase + 0x5A00), &FakeOFF, sizeof(FakeOFF), NULL);

				fakeptr = 1;
			}
			if (fakeptr == 1)
			{
				writemem(NetBase + 0x5A00, &ONAray, sizeof(ONAray));
				fakeptr = 2;
			}
		}
		else {
			if (fakeptr == 1 || fakeptr == 2)
			{
				writemem(NetBase + 0x5A00, &FakeOFF, sizeof(FakeOFF));
				fakeptr = 0;
			}
		}
	}

	//No Reload
	if (NoReload)
	{
		if (noreloadptr == 0) {

			if (CNoReload)
			{
				noreloadptr = 1;
			}
			else {
				CNoReload = ScanProc(Signature::NoReload, Signature::NoReloadMask);
				if (CNoReload)
				{
					ReadProcessMemory(GetCurrentProcess(), (LPVOID)(CNoReload), &NoreloadOFF, sizeof(NoreloadOFF), NULL);

					noreloadptr = 1;
				}
			}
		}
		if (noreloadptr == 1)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CNoReload), &RapidSnip, sizeof(RapidSnip), NULL);
			noreloadptr = 2;
		}

	}
	else {
		if (noreloadptr == 1 || noreloadptr == 2)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CNoReload), &NoreloadOFF, sizeof(NoreloadOFF), NULL);
			noreloadptr = 0;
		}
	}
	//Fast Reload
	if (FastReload)
	{
		if (fastrelptr == 0) {

			if (CFastRel)
			{
				fastrelptr = 1;
			}
			else {
				CFastRel = ScanProc(Signature::FastReload, Signature::FastReloadMask);
				if (CFastRel)
				{
					ReadProcessMemory(GetCurrentProcess(), (LPVOID)(CFastRel), &FastRelOFF, sizeof(FastRelOFF), NULL);

					fastrelptr = 1;
				}
			}
		}
		if (fastrelptr == 1)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CFastRel), &FastRelON, sizeof(FastRelON), NULL);
			fastrelptr = 2;
		}

	}
	else {
		if (fastrelptr == 1 || fastrelptr == 2)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CFastRel), &FastRelOFF, sizeof(FastRelOFF), NULL);
			fastrelptr = 0;
		}
	}
	if (FovChanger)
	{
		if (fovptr == 0) {

			if (CFov)
			{
				fovptr = 1;
			}
			else {
				CFov = ScanProc(Signature::Fov, Signature::FovMask);
				if (CFov)
				{
					ReadProcessMemory(GetCurrentProcess(), (LPVOID)(CFov), &FovOFF, sizeof(FovOFF), NULL);

					fovptr = 1;
				}
			}
		}
		if (fovptr == 1)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CFov), &FovON, sizeof(FovON), NULL);
			fovptr = 2;
		}

	}
	else {
		if (fovptr == 1 || fovptr == 2)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CFov), &FovOFF, sizeof(FovOFF), NULL);
			fovptr = 0;
		}
	}

	if (laserdot > 0)
	{
		if (laserptr == 0) {

			if (CLaser)
			{
				laserptr = 1;
			}
			else {
				CLaser = ScanProc(Signature::Laser, Signature::LaserMask);
				if (CLaser)
				{
					ReadProcessMemory(GetCurrentProcess(), (LPVOID)(CLaser), &LaserOFF, sizeof(LaserOFF), NULL);

					laserptr = 1;
				}
			}
		}
		if (laserptr == 1)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CLaser), &ONAra2y, sizeof(ONAra2y), NULL);
			laserptr = 2;
		}

	}
	else {
		if (laserptr == 1 || laserptr == 2)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)(CLaser), &LaserOFF, sizeof(LaserOFF), NULL);
			laserptr = 0;
		}
	}


	if (Chams)
	{
		if (RainbowChams)
		{
			if (NumVertices > tolerance)
			{
				if (Zula)
				{
					if (ZulaTeamMAX | ZulaTeamMin)
					{
						GenerateTexture32(pDevice, &zulachamscolor, rainbowcolor);
						pDevice->SetRenderState(D3DRS_ZENABLE, 0);
						pDevice->SetTexture(0, zulachamscolor);
						draww(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
						pDevice->SetRenderState(D3DRS_ZENABLE, 1);
						pDevice->SetTexture(0, zulachamscolor);
					}
				}
				if (Gladyo)
				{
					if (GladyoTeamMAX | GladyoTeamMin)
					{
						GenerateTexture32(pDevice, &gladyochamscolor, rainbowcolor);
						pDevice->SetRenderState(D3DRS_ZENABLE, 0);
						pDevice->SetTexture(0, gladyochamscolor);
						draww(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
						pDevice->SetRenderState(D3DRS_ZENABLE, 1);
						pDevice->SetTexture(0, gladyochamscolor);
					}
				}
			}
		}
		if (RainbowChams == 0)
		{
			if (NumVertices > tolerance)
			{
				if (Zula)
				{
					if (ZulaTeamMAX | ZulaTeamMin)
					{
						pDevice->SetRenderState(D3DRS_ZENABLE, 0);
						pDevice->SetTexture(0, zulachamscolor1);
						draww(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
						pDevice->SetRenderState(D3DRS_ZENABLE, 1);
						pDevice->SetTexture(0, zulachamscolor);
					}
				}
				if (Gladyo)
				{
					if (GladyoTeamMAX | GladyoTeamMin)
					{
						pDevice->SetRenderState(D3DRS_ZENABLE, 0);
						pDevice->SetTexture(0, gladyochamscolor1);
						draww(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
						pDevice->SetRenderState(D3DRS_ZENABLE, 1);
						pDevice->SetTexture(0, gladyochamscolor);
					}
				}
			}
		}
	}
	if (Wallhack)
	{
		if (NumVertices > tolerance)
		{
			if (Zula)
			{
				if (ZulaTeamMAX | ZulaTeamMin)
				{
					float bias = 1000.0f;
					float bias_float = static_cast<float>(-bias);
					bias_float /= 2000;//10000.0f;
					pDevice->SetRenderState(D3DRS_DEPTHBIAS, *(DWORD*)&bias_float);
					draww(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
					pDevice->SetRenderState(D3DRS_DEPTHBIAS, 0);
				}
			}
			if (Gladyo)
			{
				if (GladyoTeamMAX | GladyoTeamMin)
				{
					float bias = 1000.0f;
					float bias_float = static_cast<float>(-bias);
					bias_float /= 2000;//10000.0f;
					pDevice->SetRenderState(D3DRS_DEPTHBIAS, *(DWORD*)&bias_float);
					draww(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
					pDevice->SetRenderState(D3DRS_DEPTHBIAS, 0);
				}
			}
		}
	}
    return draww(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

void CLeft(float dwx, float dwy) {

	INPUT Inputs[3] = { 0 };
	Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dx = (LONG)dwx; // desired X coordinate
	Inputs[0].mi.dy = (LONG)dwy; // desired Y coordinate
	Inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(3, Inputs, sizeof(INPUT));
}

HRESULT APIENTRY endscenee(IDirect3DDevice9* pDevice)
{
	if (cPlayerManual.size() != NULL && Aimbot == true && ShowMenu == false)
	{
		UINT BestTarget = -1;
		DOUBLE fClosestPos = 9999;
		float radiusx = aimfov * (ScreenCenterX / 190);
		float radiusy = aimfov * (ScreenCenterY / 190);
		for (size_t i = 0; i < cPlayerManual.size(); i += 1)
		{
			cPlayerManual[i]->CrossDist = GetDistance(cPlayerManual[i]->Player.x, cPlayerManual[i]->Player.y, ScreenCenterX, ScreenCenterY);
			if (cPlayerManual[i]->Player.x >= ScreenCenterX - radiusx &&
				cPlayerManual[i]->Player.x <= ScreenCenterX + radiusx &&
				cPlayerManual[i]->Player.y >= ScreenCenterY - radiusy &&
				cPlayerManual[i]->Player.y <= ScreenCenterY + radiusy)
				if (cPlayerManual[i]->CrossDist < fClosestPos)
				{
					fClosestPos = cPlayerManual[i]->CrossDist;
					BestTarget = i;
				}
		}
		//aimhhead mi arıoyrsun
		if (BestTarget != -1)
		{
			double DistX = (cPlayerManual[BestTarget]->Player.x - ScreenCenterX) / aimsmooth;
			double DistY = (cPlayerManual[BestTarget]->Player.y - ScreenCenterY) / aimsmooth;

			if (selectedItem == 0)
			{
				if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
					CLeft(DistX, DistY);
				}
			}

			if (selectedItem == 1)
			{
				if (GetAsyncKeyState(VK_CAPITAL) & 0x8000) {
					CLeft(DistX, DistY);
				}
			}

			if (selectedItem == 2)
			{
				if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
					CLeft(DistX, DistY);
				}
			}

			if (selectedItem == 3)
			{
				if (GetAsyncKeyState(VK_MENU) & 0x8000) {
					CLeft(DistX, DistY);
				}
			}

			if (selectedItem == 4)
			{
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
					CLeft(DistX, DistY);
				}
			}

			if (selectedItem == 5)
			{
				if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
					CLeft(DistX, DistY);
				}
			}
		}
		cPlayerManual.clear();
	}


	return endsceneo(pDevice);
}
DWORD WINAPI GUI(LPVOID lpParameter)
{
	AckBase = (DWORD)GetModuleHandleA("acknex.dll");
	NetBase = (DWORD)GetModuleHandleA("ANet.dll");

	std::thread(LoopMatrix).detach();

	while (!GetModuleHandleA("d3d9.dll")) {
		Sleep(200);
	}

	IDirect3D9* d3d = NULL;
	IDirect3DDevice9* d3ddev = NULL;
	HWND tmpWnd = CreateWindowA("BUTTON", "-*-*154*6", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, Hand, NULL);
	if (tmpWnd == NULL)
	{
		return 0;
	}
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		DestroyWindow(tmpWnd);
		return 0;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = tmpWnd;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	HRESULT result = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, tmpWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	if (result != D3D_OK)
	{
		d3d->Release();
		DestroyWindow(tmpWnd);
		
		return 0;
	}
#if defined _M_X64
	DWORD64* dVtable = (DWORD64*)d3ddev;
	dVtable = (DWORD64*)dVtable[0];
#elif defined _M_IX86
	DWORD* dVtable = (DWORD*)d3ddev;
	dVtable = (DWORD*)dVtable[0]; // == *d3ddev
#endif
		// Detour functions x86 & x64
	SetStreamSource_orig = (SetStreamSource)dVtable[100];
	SetVertexDeclaration_orig = (SetVertexDeclaration)dVtable[87];
	SetVertexShaderConstantF_orig = (SetVertexShaderConstantF)dVtable[94];
	SetVertexShader_orig = (SetVertexShader)dVtable[92];
	SetPixelShader_orig = (SetPixelShader)dVtable[107];

	draww = (DrawIndexedPrimitive)dVtable[82];
	DrawPrimitive_orig = (DrawPrimitive)dVtable[81];
	SetTexture_orig = (SetTexture)dVtable[65];
    presento = (Present)dVtable[17];
	endsceneo = (EndScene)dVtable[42];
	Reset_orig = (Reset)dVtable[16];

	Sleep(2000);//required in a few games

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)SetStreamSource_orig, (PBYTE)SetStreamSource_hook);
	DetourAttach(&(LPVOID&)SetVertexDeclaration_orig, (PBYTE)SetVertexDeclaration_hook);
	DetourAttach(&(LPVOID&)SetVertexShader_orig, (PBYTE)SetVertexShader_hook);
	DetourAttach(&(LPVOID&)draww, (PBYTE)drawindexed);
	DetourAttach(&(LPVOID&)presento, (PBYTE)presentt);
	DetourAttach(&(LPVOID&)Reset_orig, (PBYTE)Reset_hook);
	DetourAttach(&(LPVOID&)endsceneo, (PBYTE)endscenee);
	DetourTransactionCommit();


	d3ddev->Release();
	d3d->Release();
	DestroyWindow(tmpWnd);

	return 1;
}
bool threadqwe = false;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Hand = hModule;
		SpoofThread((void*)GUI, hModule);
		break;
	case DLL_PROCESS_DETACH:
		SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG>(WndProc));
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX9_Shutdown();
		ImGui::DestroyContext();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}
