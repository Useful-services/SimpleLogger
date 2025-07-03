#pragma once

#include <sqlite3.h>
#include <print>
#include <stdexcept>
#include <string>

class SQLite {
public:
  SQLite(const std::string& db_path) {
    if (sqlite3_open(db_path.c_str(), &db_) != SQLITE_OK) {
      throw std::runtime_error("Не удалось открыть базу данных: " + std::string(sqlite3_errmsg(db_)));
    }
  }
private:
  sqlite3* db_ = nullptr;
};