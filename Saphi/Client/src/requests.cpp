#include "requests.h"
#include "languages.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <fstream>

bool Requests::DownloadFile(const std::string& domain, const std::string& sitePath, const std::string& filePath)
{
  httplib::SSLClient request(domain);
  httplib::Result response = request.Get(sitePath);
  if (!response) { return false; }
  if (response->status == 200)
  {
    std::ofstream file(filePath.c_str(), std::ios::binary);
    file.write(response->body.c_str(), response->body.size());
    file.close();
    return true;
  }
  if (response->status == 302)
  {
    const std::string hostStart = "://";
    const std::string pathStart = "/";
    std::string location = response->get_header_value("Location");
    if (location == domain + sitePath) { return false; }

    size_t hostStartIndex = location.find(hostStart) + hostStart.length();
    size_t pathStartIndex = location.find(pathStart, hostStartIndex);
    std::string host = location.substr(hostStartIndex, pathStartIndex - hostStartIndex);
    std::string path = location.substr(pathStartIndex);
    return DownloadFile(host, path, filePath);
  }
  return false;
}

bool Requests::CheckUpdates(std::string& version)
{
	httplib::SSLClient request("projectsaphi.com");
	httplib::Result response = request.Get("/wp-content/uploads/onlinectr_patches/build.txt");
  if (response && response->status == 200) {
    version = response->body;
    return true;
  }
  return false;
}

bool Requests::DownloadUpdates(const std::string& path, std::string& status, IconType& statusIcon)
{
  const std::string octrDomain = "projectsaphi.com";
  const std::string octrPath = "/wp-content/uploads/onlinectr_patches/";
  const std::vector<std::string> files = { g_patchString, g_configString };
  const std::filesystem::path u8path = std::u8string(path.begin(), path.end());
  if (!std::filesystem::is_directory(u8path)) { std::filesystem::create_directory(u8path); }
  for (const std::string& file : files)
  {
    status = g_lang["Downloading"] + " " + file + "...";
    statusIcon = IconType::RUNNING;
    if (!DownloadFile(octrDomain, octrPath + file, path + file))
    {
      status = g_lang["Error downloading"] + " " + file;
      statusIcon = IconType::FAIL;
      return false;
    }
  }
  return true;
}