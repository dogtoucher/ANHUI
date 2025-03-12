#include "config.hpp"

std::string getApiKey(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("无法打开 API 密钥文件: " + filePath);
    }
    std::string apiKey;
    std::getline(file, apiKey);  // 读取第一行
    return apiKey;
}
