#pragma once
#include <string>
#include <vector>
#include "Player.h"

using namespace std;
using namespace nlohmann;

class PlayerData
{
public:
	PlayerData(std::string data);
	~PlayerData();

	int CapeImageWidth = 0;
	string GameVersion = "";
	nlohmann::json AnimatedImageData;
	string ArmSize = "";
	long long ClientRandomId = 0;
	string CapeData = "";
	string CapeId = "";
	bool CapeOnClassicSkin = false;
	int CapeImageHeight = 0;
	string PlayFabId = "";
	int CurrentInputMode = 0;
	int DefaultInputMode = 0;
	string DeviceId = "";
	string DeviceModel = "";
	string SkinId = "";
	int DeviceOS = 0;
	int GuiScale = 0;
	int SkinImageHeight = 0;
	string LanguageCode = "";
	string SkinData = "";
	nlohmann::json PersonaPieces; //json
	bool PersonaSkin = false;	  //is minecraft persona skin
	string SkinGeometryData = ""; //base64 encoded json geometry
	nlohmann::json PieceTintColors;
	string PlatformOfflineId = "";
	string PlatformOnlineId = "";
	bool PremiumSkin = true;
	string SelfSignedId = "";
	string SkinResourcePatch = "";
	string ServerAddress = "";
	string SkinAnimationData = "";
	string SkinColor = "";
	int SkinImageWidth = 0;
	string ThirdPartyName = "";
	bool ThirdPartyNameOnly = false;
	int UIProfile = 0;
private:

};