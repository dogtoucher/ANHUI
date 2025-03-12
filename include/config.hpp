#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <stdexcept>
#include <fstream>

// 从指定文件中读取 API 密钥（读取文件的第一行）
std::string getApiKey(const std::string& filePath);

#endif // CONFIG_HPP
