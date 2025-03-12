#include "deepseek_client.hpp"
#include "curl_wrapper.hpp"

std::string sendChatMessage(const std::string& message, const std::string& apiKey) {
    // API 端点
    const std::string url = "https://api.deepseek.com/chat/completions";

    // 构造请求 JSON
    json requestBody = {
        {"model", "deepseek-chat"},
        {"messages", {
            {{"role", "user"}, {"content", message}}
        }},
        {"temperature", 0.7}
    };

    std::string requestBodyStr = requestBody.dump();

    // 通过 CurlWrapper 发送 POST 请求
    CurlWrapper curlWrapper;
    return curlWrapper.post(url, requestBodyStr, apiKey);
}
