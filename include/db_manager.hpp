#ifndef DB_MANAGER_HPP
#define DB_MANAGER_HPP

#include <string>
#include <sqlite3.h>
#include <stdexcept>

class DBManager {
public:
    DBManager(const std::string &dbPath);
    ~DBManager();

    // 创建作品和章节的表
    void initializeDatabase();

    // 插入作品记录（例如作品标题）
    void insertWork(const std::string &title);

    // 插入章节记录，关联作品 ID、章节序号与内容
    void insertChapter(int workId, int chapterNumber, const std::string &content);

private:
    sqlite3 *db;
};

#endif // DB_MANAGER_HPP
