#include "PlayerData.h"
#include "Utils.h"
#include <iostream>
PlayerData::PlayerData(string Jwt)
{
    auto data = jwt::decode(Jwt);
    auto json = data.get_payload_claims();
	CapeImageWidth = json["CapeImageWidth"].as_int();
	GameVersion = json["GameVersion"].as_string();
	AnimatedImageData = json["AnimatedImageData"].to_json();
	ArmSize = json["ArmSize"].as_string();
	ClientRandomId = json["ClientRandomId"].as_int();
	CapeData = json["CapeData"].as_string();
	CapeId = json["CapeId"].as_string();
	CapeOnClassicSkin = json["CapeOnClassicSkin"].as_bool();
	CapeImageHeight = json["CapeImageHeight"].as_int();
	PlayFabId = json["PlayFabId"].as_string();
	CurrentInputMode = json["CurrentInputMode"].as_int();
	DefaultInputMode = json["DefaultInputMode"].as_int();
	DeviceId = json["DeviceId"].as_string();
	DeviceModel = json["DeviceModel"].as_string();
	SkinId = json["SkinId"].as_string();
	DeviceOS = json["DeviceOS"].as_int();
	GuiScale = json["GuiScale"].as_int();
	SkinImageHeight = json["SkinImageHeight"].as_int();
	LanguageCode = json["LanguageCode"].as_string();
	SkinData = json["SkinData"].as_string();
	PersonaPieces = json["PersonaPieces"].to_json(); //json
	PersonaSkin = json["PersonaSkin"].as_bool();	  //is minecraft persona skin
	SkinGeometryData = Utils::get()->decode_base64String(json["SkinGeometryData"].as_string()); //base64 encoded json geometry
	PieceTintColors = json["PieceTintColors"].to_json();
	PlatformOfflineId = json["PlatformOfflineId"].as_string();
	PlatformOnlineId = json["PlatformOnlineId"].as_string();
	PremiumSkin = json["PremiumSkin"].as_bool();
	SelfSignedId = json["SelfSignedId"].as_string();
	SkinResourcePatch = json["SkinResourcePatch"].as_string();
	ServerAddress = json["ServerAddress"].as_string();
	SkinAnimationData = json["SkinAnimationData"].as_string();
	SkinColor = json["SkinColor"].as_string();
	SkinImageWidth = json["SkinImageWidth"].as_int();
	ThirdPartyName = json["ThirdPartyName"].as_string();
	ThirdPartyNameOnly = json["ThirdPartyNameOnly"].as_bool();
	UIProfile = json["UIProfile"].as_int();
}

PlayerData::~PlayerData()
{
}