#include "main.h"
#include "enc.h"
#include "icons.h"

ImVec4 esprenk = ImVec4(0.7f, 0.0f, 0.0f, 1.0f);
ImVec4 esprenkg = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);

ImVec4 skeletonrenk = ImVec4(0.7f, 0.0f, 0.0f, 1.0f);
ImVec4 skeletonrenkg = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);

ImVec4 esplinerenk = ImVec4(1.0f, 0.7137f, 0.7569f, 1.0f);
ImVec4 esplinerenkg = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);

int esptypee = 0;
int aimbone = 0;
static bool nosmoke = false;
static bool fakelag = false;
static bool EspBox2D = false;
static bool skeleton = false;
static bool bombesp = false;
static bool radar = false;
static bool noflash = false;

const char* box[3] = { "2D", "3D", "Corner" };
const char* bones[3] = { "Head", "Body", "Foot" };
const char* radars[2] = { "Square", "Circle" };
int radartype = 0;

const char* radarcol[3] = { "Red", "Green", "Blue" };
int radarcolint = 0;
int radarcolint2 = 0;

static bool espskeleton = false;
static bool espline = false;
static bool espdistance = false;

RGBA selectedColor = { 255, 0, 0, 255 };
RGBA selectedColor2 = { 255, 0, 0, 255 };

ImU32 cornerColor = IM_COL32(255, 0, 0, 255);
ImU32 cornerColor2 = IM_COL32(255, 0, 0, 255);

static bool lookdirection = false;

static bool radarpos = false;

namespace HexSet
{
	static int HexTab = 0;
}


void Tema()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowBorderSize = 0;
	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->WindowMinSize = ImVec2(460, 300);

	style->FramePadding = ImVec2(8, 6);
	style->Colors[ImGuiCol_TitleBg] = ImColor(10, 10, 10, 255);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(10, 10, 10, 255);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(10, 10, 10, 255);

	style->Colors[ImGuiCol_WindowBg] = ImColor(34, 34, 34, 255);//background


	style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);// button color
	style->Colors[ImGuiCol_ButtonActive] = ImColor(31, 30, 31, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

	style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

	style->Colors[ImGuiCol_FrameBg] = ImColor(37, 36, 37, 255);//checkbox background
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(37, 36, 37, 255);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);

	style->Colors[ImGuiCol_CheckMark] = ImColor(0.0f, 1.0f, 1.0f, 1.0f);

	style->Colors[ImGuiCol_Header] = ImColor(46, 46, 46, 255);// colapsing header
	style->Colors[ImGuiCol_HeaderActive] = ImColor(46, 46, 46, 255);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);

	style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(144, 143, 143, 255);; // Aþaðý kaydýrma çubuðu rengi
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(144, 143, 143, 255); // Aþaðý kaydýrma çubuðu arka plan rengi
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(144, 143, 143, 255);; // Aþaðý kaydýrma çubuðu rengi
}





void HmenuRender()
{

	if (ImGui::CollapsingHeader(std::string(std::string(XorString(ICON_FA_EYE)) + XorString(" V!sual")).c_str()))
	{
		ImGui::Checkbox("Box ESP", &EspBox2D);
		ImGui::Checkbox("Skeleton ESP", &espskeleton);
		ImGui::Checkbox("Look Direction", &lookdirection);
		ImGui::Checkbox("Line ESP", &espline);
		ImGui::Checkbox("Distance ESP", &espdistance);
		ImGui::Checkbox("Radar ESP", &radar);
		ImGui::Checkbox("Name ESP", &NameEspAktif);
		ImGui::Checkbox("Wallhack", &Wallhack);
		ImGui::Checkbox("Chams", &Chams);
		ImGui::Checkbox("Chams Rainbow", &RainbowChams);
		ImGui::Checkbox("Bomb Warning", &bombesp);
		ImGui::Checkbox("No Smoke", &nosmoke);
		if (ImGui::Combo("Select Team", &currentHexesT, Hexteams, IM_ARRAYSIZE(Hexteams))) {
			Zula = (currentHexesT == 0 || currentHexesT == 1);
			Gladyo = (currentHexesT == 0 || currentHexesT == 2);
		}
	}
	if (ImGui::CollapsingHeader(std::string(std::string(XorString(ICON_FA_CROSSHAIRS)) + XorString(" Aimbot")).c_str()))
	{
		ImGui::Checkbox("Enable Aimbot", &Aimbot);
		ImGui::Combo("Aim Key", &selectedItem, aimkey, IM_ARRAYSIZE(aimkey));
		ImGui::Combo("Aim Bone", &selectedBody, aimbody, IM_ARRAYSIZE(aimbody));
		ImGui::Checkbox("Circle Fov", &circlefov);
		ImGui::SliderFloat("Aim FOV", &aimfov, 30, 360);
		ImGui::SliderFloat("Smooth", &aimsmooth, 0.300, 5);
	}
	if (ImGui::CollapsingHeader(std::string(std::string(XorString(ICON_FA_REDDIT_ALIEN)) + XorString(" Memory")).c_str()))
	{
		ImGui::Checkbox("No Recoil", &NoRecoil);
		ImGui::Checkbox(("No Spread"), &NoSpread);
		//ImGui::Checkbox(("Fake Lag [E]"), &fakelag);
		ImGui::Checkbox(("No Weapon Swap"), &FastWeaponSwitch);
		ImGui::Checkbox(("Laser Dot"), &laserdot);
		ImGui::Checkbox(("Spam Limit Unlocker"), &Spammmm);
		//ImGui::Checkbox(("Anti AFK"), &AntiAFK);
		//ImGui::Checkbox(("Fov Changer"), &FovChanger);
		//ImGui::Checkbox(("No Reload[B22 Risky]"), &NoReload);
		//ImGui::Checkbox(("Fast Reload[B22 Risky]"), &FastReload);
	}
	if (ImGui::CollapsingHeader(std::string(std::string(XorString(ICON_FA_PENCIL)) + XorString(" Settings")).c_str()))
	{
		ImGui::Combo("Radar Type", &radartype, radars, IM_ARRAYSIZE(radars));
		ImGui::Combo("Box Type", &esptypee, box, IM_ARRAYSIZE(box));

		ImGui::ColorEdit4("Esp Color (Zula Team)", (float*)&esprenk, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4("Esp Color (Gladio Team)", (float*)&esprenkg, ImGuiColorEditFlags_NoInputs);

		ImGui::ColorEdit4("Esp Line Color (Zula Team)", (float*)&esplinerenk, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4("Esp Line Color (Gladio Team)", (float*)&esplinerenkg, ImGuiColorEditFlags_NoInputs);

		ImGui::ColorEdit4("Zula Skeleton Color", (float*)&skeletonrenk, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4("Gladio Skeleton Color", (float*)&skeletonrenkg, ImGuiColorEditFlags_NoInputs);
		if (Zula)
		{
			ImGui::Combo("Radar Zula Color", &radarcolint, radarcol, IM_ARRAYSIZE(radarcol));
		}

		if (Gladyo)
		{
			ImGui::Combo("Radar Gladyo Color", &radarcolint2, radarcol, IM_ARRAYSIZE(radarcol));
		}

		ImGui::ColorEdit3("Chams Zula Visible", zulachams, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit3("Chams Zula Invisible", zulachams1, ImGuiColorEditFlags_NoInputs);
		ImGui::NewLine();
		ImGui::ColorEdit3("Chams Gladyo Visible", gladyochams, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit3("Chams Gladyo Invisible", gladyochams1, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4("Circle Fov", (float*)&circlecolor, ImGuiColorEditFlags_NoInputs);
	}
}