#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <map>

// 从 JSON 文件中加载 API 密钥，返回角色与密钥的映射
std::map<std::string, std::string> loadApiKeys(const std::string &filePath);

#endif // CONFIG_HPP
