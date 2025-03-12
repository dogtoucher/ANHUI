#include <iostream>
#include "curl_wrapper.hpp"
#include "config.hpp"
#include "deepseek_client.hpp"
#include "db_manager.hpp"
#include "json.hpp"

using json = nlohmann::json;

int main() {
    try {
        // init libcurl
        curl_global_init(CURL_GLOBAL_DEFAULT);

      
        auto apiKeys = loadApiKeys("keys/keys.json");
        std::string writerKey = apiKeys["writer"];
        std::string editorKey = apiKeys["editor"];
        std::string proofreaderKey = apiKeys["proofreader"];

        std::string writerPrompt = "你是一个专业作家，请写一篇chiikawa世界中乌萨奇(Usagi)为主角的硬汉派侦探小说。主要角色均来自于chiikawa原著，先研究chiikawa的剧情梗概与人物能力，后写出尽量长的第一章";
        std::string writerResponse = sendChatMessage(writerPrompt, writerKey, "deepseek-reasoner", 1.0);
        json writerJson = json::parse(writerResponse);
        std::string writerOutput = writerJson["choices"][0]["message"]["content"];
        std::cout << "作家生成的初稿：" << std::endl << writerOutput << std::endl << std::endl;

        std::string editorPrompt = "你是一个专业编辑，请对正文进行编辑，并提取出文章的正文，忽略其他的输出（如剧情梗概)：\n" + writerOutput;
        std::string editorResponse = sendChatMessage(editorPrompt, editorKey, "deepseek-chat", 0.0);
        json editorJson = json::parse(editorResponse);
        std::string editorOutput = editorJson["choices"][0]["message"]["content"];
        std::cout << "编辑后的版本：" << std::endl << editorOutput << std::endl << std::endl;

        std::string proofreaderPrompt = "你是一个专业校对员，请对下面的文本进行校对排版，修正语法错误并优化表达，从而适合最终出版,并只包含正文内容：\n" + editorOutput;
        std::string proofreaderResponse = sendChatMessage(proofreaderPrompt, proofreaderKey, "deepseek-chat", 0.0);
        json proofreaderJson = json::parse(proofreaderResponse);
        std::string finalOutput = proofreaderJson["choices"][0]["message"]["content"];
        std::cout << "最终文章正文：" << std::endl << finalOutput << std::endl << std::endl;

        DBManager dbManager("literature.db");
        dbManager.initializeDatabase();
        dbManager.insertWork("chiikawa");
        dbManager.insertChapter(1, 1, finalOutput);

        std::cout << "文章已成功保存到数据库。" << std::endl;

        // 全局清理 libcurl
        curl_global_cleanup();
    } catch (const std::exception &ex) {
        std::cerr << "错误: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
