#ifndef CURL_WRAPPER_HPP
#define CURL_WRAPPER_HPP

#include <string>
#include <curl/curl.h>

class CurlWrapper {
public:
    CurlWrapper();
    ~CurlWrapper();

    // 发送 HTTP POST 请求，返回响应字符串
    std::string post(const std::string& url, const std::string& postFields, const std::string& apiKey);

private:
    CURL* curl;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
};

#endif // CURL_WRAPPER_HPP
