#pragma once

#include <string>
#include "Global.h"

#define DEBUG_OUTPUT 1
#if DEBUG_OUTPUT
#define LOG_INFO(msg) CMyLog::GetInstance()->Log(msg, CMyLog::info)
#define LOG_WARNING(msg) CMyLog::GetInstance()->Log(msg, CMyLog::warning)
#define LOG_ERROR(msg) CMyLog::GetInstance()->Log(msg, CMyLog::error)
#define LOG_OTHER(msg) CMyLog::GetInstance()->Log(msg, CMyLog::other)
#else
#define LOG_INFO(msg) 
#define LOG_WARNING(msg) 
#define LOG_ERROR(msg) 
#define LOG_OTHER(msg) 
#endif

#define STR_RELOAD_FAILED   "reload failed"
#define STR_USER_QUIT       "user select quit"

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

