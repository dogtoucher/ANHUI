#include "deepseek_client.hpp"
#include "curl_wrapper.hpp"

std::string sendChatMessage(const std::string& message, const std::string& apiKey, const std::string& model, const float& temp) {
    // API 端点
    const std::string url = "https://api.deepseek.com/chat/completions";

    // 构造请求 JSON
    json requestBody = {
        {"model", model},
        {"messages", {
            {{"role", "system"}, {"content", "你是专业的作家有丰富的写作和出版经验，擅长思考模仿知名作家的行文风格，产出适合互联网连载的长篇小说"}},
            {{"role", "user"}, {"content", message}}
        }},
        {"temperature", temp}
    };

    std::string requestBodyStr = requestBody.dump();

    // 通过 CurlWrapper 发送 POST 请求
    CurlWrapper curlWrapper;
    return curlWrapper.post(url, requestBodyStr, apiKey);
}
