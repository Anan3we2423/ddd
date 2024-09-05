#define ZulaTeamMin (NumVertices == 3190 )||(NumVertices == 2749 )||(NumVertices == 2498 )||(NumVertices == 2724 )||(NumVertices == 2555 )||(NumVertices == 3493 )||(NumVertices == 2170 )||(NumVertices == 2987 )||(NumVertices == 2149 )||(NumVertices == 2586 )||(NumVertices == 2178 )
#define ZulaTeamMAX (NumVertices == 4937 )||(NumVertices == 5216 )||(NumVertices == 4680 )||(NumVertices == 6127 )||(NumVertices == 4848 )||(NumVertices == 5295 )||(NumVertices == 4848 )||(NumVertices == 4856 )||(NumVertices == 6051 )||(NumVertices == 5909 )||(NumVertices == 5908 )||(NumVertices == 5586 )||(NumVertices == 5572 )||(NumVertices == 5909 )||(NumVertices == 6898 )
#define GladyoTeamMin (NumVertices == 3243 )||(NumVertices == 2941 )||(NumVertices == 2227 )||(NumVertices == 3046 )||(NumVertices == 2935 )||(NumVertices == 3091 )||(NumVertices == 2688 )||(NumVertices == 2924 )||(NumVertices == 3388 )||(NumVertices == 3315 )
#define GladyoTeamMAX (NumVertices == 5803 )||(NumVertices == 6695 )||(NumVertices == 5416 )||(NumVertices == 5812 )||(NumVertices == 6564 )||(NumVertices == 6914 )||(NumVertices == 5637 )||(NumVertices == 5359 )||(NumVertices == 6123 )||(NumVertices == 5493 )||(NumVertices == 7769 )
#define ZulaTeamHead primCount == 1093  primCount == 1930  primCount == 1726  primCount == 1232  primCount == 1798  primCount == 2042 primCount == 1432  primCount == 1432  primCount == 2028
#define GladyoTeamHead primCount == 845  primCount == 1166  primCount == 1292  primCount == 588  primCount == 2134  primCount == 1432  primCount == 1342 || primCount == 686


BYTE AfkOFF[6];
char* CAfk = 0;
int afkptr = 0;

BYTE FakeOFF[6];
char* CFake = 0;
int fakeptr = 0;

BYTE Spam1[6];
char* CSpam1 = 0;
int spamptr = 0;
BYTE Spam2[6];
DWORD CSpam2;

BYTE NorecoilOFF[6];
char* CNoRecoil = 0;
int norecoilptr = 0;

BYTE NospreadOFF[6];
char* CNoSpread = 0;
int nospreadptr = 0;

BYTE FastWeaponOFF[6];
char* CFastWeapon = 0;
int fastswptr = 0;
BYTE FovOFF[35];
char* CFov = 0;
int fovptr = 0;
BYTE LaserOFF[6];
char* CLaser = 0;
int laserptr = 0;

BYTE NoreloadOFF[6];
char* CNoReload = 0;
int noreloadptr = 0;

BYTE FastRelOFF[6];
char* CFastRel = 0;
int fastrelptr = 0;

BYTE FastRelON[] = { 0xF7,0xEA,0x0F,0xAC,0xD0,0x09 };
BYTE RapidSnip[] = { 0x90 , 0x90 };
BYTE ONSpeed[] = { 0x00 ,0x00 ,0x20 ,0x41 };
BYTE ONAray[] = { 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 };
BYTE ONFake[] = { 0x90 , 0x90 };
BYTE jeneye[] = { 0x74 };
BYTE jeye[] = { 0x75 };
BYTE FovON[] = { 0xF7,0xEA,0x0F,0xAC,0xD0,0x09,0x83,0xD0,0x00,0x89,0x85,0x14,0x01,0x00,0x00,0x8B,0x85,0x14,0x01,0x00,0x00,0x8B,0x95,0x08,0x00,0x00,0x00,0xF7,0xEA,0x0F,0xAC,0xD0,0x09,0x83,0xD0 };
BYTE ONAra2y[] = { 0x74 };
BYTE spamon[] = { 0x40, 0x9C, 0x00, 0x00, 0x40, 0x9C, 0x00, 0x00 };
namespace Signature
{
	/*---------# No Recoil #--------- update*/
	char NoRecoil[] = "\xDC\x8D\x5C\x00\x00\x00\xDD\x9D\x6C\x00\x00\x00\xE8\x08\x00\x00\x00";
	char NoRecoilMask[] = "xxxxxxxxxxxxxxxxxx";

	/*---------# No Spread #--------- update*/ // +
	char NoSpread[] = "\xDD\x85\x80\x03\x00\x00\xDC\x08\xDB\x9D\x88\x03\x00\x00\x8B\x85\x88\x03\x00\x00\x89";
	char NoSpreadMask[] = "xxxxxxxxxxxxxxxxxxxxx";

	/*---------# No Reload #---------*/
	char NoReload[] = "\xF7\xEA\x0F\xAC\xD0\x0A\x83\xD0\x00\x89\x85\x34\x02\x00\x00\x8B\x85\x34\x02\x00\x00\x89\x85\x20\x00";
	char NoReloadMask[] = "xxxxxxxxxxxxxxxxxxxxxxxxx";
	//8B 85 38 00 00 00 8B 8D 74 11
		/*---------# Fast Weapon Switch #---------*/
	char FastWeaponSwitch[] = "\x8B\x85\x40\x00\x00\x00\x8B\x8D\xF4\x11\x00\x00\x03\xC1\x89\x85";
	char FastWeaponSwitchMask[] = "xxxxxxxxxxxxxxxx";

	/*---------# Spammer #---------*/
	char Spammerqwe[] = "\x28\x00\x00\x00\x78\x00\x00\x33";
	char SpammerqweMask[] = "xxxxxxxx";
	/*---------# Anti Afk #---------*/
	char AntiAFK[] = "\xDB\x83\xB8\x90\x01\x00\xDC\x30\xDD\x9D\x54\x00\x00\x00\xDD\x85\x54\x00\x00\x00\xDC\x9B";
	char AntiAFKMask[] = "xx????xxxxxxxxxxxxxxxx";

	/*---------# Fast Reload #---------*/
	char FastReload[] = "\xF7\xEA\x0F\xAC\xD0\x0A\x83\xD0\x00\x89\x85\xC0\x05\x00\x00\x8B\x85\x0C\x00\x00\x00";
	char FastReloadMask[] = "xxxxxxxxxxxxxxxxxxxxx";

	/*---------# Fov #---------*/
	char Fov[] = "\xF7\xEA\x0F\xAC\xD0\x0A\x83\xD0\x00\x89\x85\x14\x01\x00\x00\x8B\x85\x14\x01\x00\x00\x8B\x95\x08\x00\x00\x00\xF7\xEA\x0F\xAC\xD0\x0A\x83\xD0";
	char FovMask[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

	/*---------# Laser #---------update*/
	char Laser[] = "\x75\x05\xE9\x25\x02\x00\x00\xB9";
	char LaserMask[] = "xxxxxxxx";
}