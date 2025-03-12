#ifndef DEEPSEEK_CLIENT_HPP
#define DEEPSEEK_CLIENT_HPP

#include <string>
#include "json.hpp"  // nlohmann/json 头文件

using json = nlohmann::json;

// 发送聊天消息，返回 API 的 JSON 响应字符串
std::string sendChatMessage(const std::string& message, const std::string& apiKey, const std::string& model, const float& temp);

#endif // DEEPSEEK_CLIENT_HPP
