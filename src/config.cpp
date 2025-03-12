#include "config.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "json.hpp"

using json = nlohmann::json;

std::map<std::string, std::string> loadApiKeys(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("无法打开 API 密钥文件: " + filePath);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    json j = json::parse(buffer.str());
    std::map<std::string, std::string> apiKeys;
    for (auto& [role, key] : j.items()) {
        apiKeys[role] = key.get<std::string>();
    }
    return apiKeys;
}
