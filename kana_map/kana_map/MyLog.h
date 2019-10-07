#pragma once

#include <string>
#include "Global.h"

#define LOG_INFO(msg) CMyLog::GetInstance()->Log(msg, CMyLog::info)
#define LOG_WARNING(msg) CMyLog::GetInstance()->Log(msg, CMyLog::warning)
#define LOG_ERROR(msg) CMyLog::GetInstance()->Log(msg, CMyLog::error)
#define LOG_OTHER(msg) CMyLog::GetInstance()->Log(msg, CMyLog::other)

class CMyLog
{
public:
  enum LogType
  {
    info = 0,
    warning,
    error,
    other
  };

public:
  static CMyLog* GetInstance();
  void Log(std::string msg, LogType type);
  std::string GetLogFileName();
  std::string GetLogFilePath();

private:
  CMyLog();
  ~CMyLog();
  void Init();
  std::string log_file_name_;
  std::string log_file_path_;
};

