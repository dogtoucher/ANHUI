#include <iostream>
#include "config.hpp"
#include "deepseek_client.hpp"
#include "json.hpp"  // nlohmann/json 头文件

using json = nlohmann::json;

int main() {
    try {
        // 从 keys/api_key.txt 中读取 API 密钥
        std::string apiKey = getApiKey("keys/api_key.txt");

        // 发送聊天请求
        std::string response = sendChatMessage("你好，请介绍一下你自己", apiKey);

        // 解析 JSON 响应
        json responseJson = json::parse(response);
        std::string output = responseJson["choices"][0]["message"]["content"];

        std::cout << "DeepSeek respond: " << output << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
