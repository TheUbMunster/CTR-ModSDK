#pragma once

#include <nlohmann/json.hpp>
#include <unordered_map>
#include <tuple>
#include <string>

extern const std::string g_dataFolder;
extern const std::string g_openBiosPath;
extern const std::string g_duckDlFolder;
extern const std::string g_duckFolder;
extern const std::string g_duckExecutable;
extern const std::string g_patchString;
extern const std::string g_configString;

std::string GetPathWithoutExtension(const std::string& path);
const std::string GetPatchedGamePath(const std::string& version);
const std::string GetIniPath_Version(const std::string& version);
const std::string GetIniPath_Duck();

using json = nlohmann::json;

enum class IconType
{
	NONE,
	FAIL,
	WARNING,
	SUCCESS,
	RUNNING,
};

enum class DataType
{
	STRING, BOOL, FLOAT, SIZE_T
};

class DataManager
{
public:
	DataManager();
	void BindData(void* data, DataType dataType, const std::string& id);
	void SaveData();

private:
	const std::string m_path = g_dataFolder + "config.json";
	std::unordered_map<std::string, std::tuple<void*, DataType>> m_dataMap;
	json m_json;
};

extern DataManager g_dataManager;

struct GameData
{
	GameData();

	float m_fx = 1.0f;
	float m_music = 1.0f;
	float m_voice = 1.0f;
	bool m_stereo = true;
	bool m_vibration = false;
	bool m_reset = false;
	std::string m_username;
	std::string m_duckCommand;
};

extern GameData g_gameData;