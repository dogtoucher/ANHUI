#include "db_manager.hpp"
#include <iostream>

DBManager::DBManager(const std::string &dbPath) : db(nullptr) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        throw std::runtime_error("无法打开数据库: " + std::string(sqlite3_errmsg(db)));
    }
}

DBManager::~DBManager() {
    if (db) {
        sqlite3_close(db);
    }
}

void DBManager::initializeDatabase() {
    // 创建作品表
    const char *sqlWorks = "CREATE TABLE IF NOT EXISTS works ("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "title TEXT NOT NULL);";

    // 创建章节表
    const char *sqlChapters = "CREATE TABLE IF NOT EXISTS chapters ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "work_id INTEGER NOT NULL, "
                              "chapter_number INTEGER NOT NULL, "
                              "content TEXT NOT NULL, "
                              "FOREIGN KEY(work_id) REFERENCES works(id));";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlWorks, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "未知错误";
        sqlite3_free(errMsg);
        throw std::runtime_error("创建作品表失败: " + error);
    }

    rc = sqlite3_exec(db, sqlChapters, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "未知错误";
        sqlite3_free(errMsg);
        throw std::runtime_error("创建章节表失败: " + error);
    }
}

void DBManager::insertWork(const std::string &title) {
    std::string sql = "INSERT INTO works (title) VALUES (?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("预处理插入作品语句失败");
    }
    if (sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("绑定作品标题失败");
    }
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("执行插入作品失败");
    }
    sqlite3_finalize(stmt);
}

void DBManager::insertChapter(int workId, int chapterNumber, const std::string &content) {
    std::string sql = "INSERT INTO chapters (work_id, chapter_number, content) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("预处理插入章节语句失败");
    }
    if (sqlite3_bind_int(stmt, 1, workId) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 2, chapterNumber) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 3, content.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("绑定章节数据失败");
    }
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("执行插入章节失败");
    }
    sqlite3_finalize(stmt);
}
