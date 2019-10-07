#include <string>
#include <fstream>
#include <chrono>
#include <time.h>
#include <memory>
#include <iostream>
#include <direct.h>

#include "MyLog.h"

using namespace std;

CMyLog * CMyLog::GetInstance()
{
  static CMyLog *inst = new CMyLog();
  return inst;
}

void CMyLog::Log(std::string msg, LogType type)
{
  time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
  tm local_time;
  localtime_s(&local_time, &t);
  string str_type;
  switch (type)
  {
  case CMyLog::info:
    str_type = "info";
    break;
  case CMyLog::warning:
    str_type = "warning";
    break;
  case CMyLog::error:
    str_type = "erro";
    break;
  case CMyLog::other:
    str_type = "other";
    break;
  default:
    str_type = "unknown";
    break;
  }

  char tmp[_MAX_PATH];
  sprintf_s(tmp, _MAX_PATH, "[%d:%d:%d][%s]%s\n", local_time.tm_hour, local_time.tm_min, local_time.tm_sec, str_type.c_str(), msg.c_str());
  string output(tmp);
  ofstream ofile(log_file_name_, ios::out | ios::app);
  ofile << output;
  ofile.close();
}

std::string CMyLog::GetLogFileName()
{
  return log_file_name_;
}

std::string CMyLog::GetLogFilePath()
{
  return log_file_path_;
}

CMyLog::CMyLog()
{
  Init();
}


CMyLog::~CMyLog()
{
}

void CMyLog::Init()
{
  time_t t = chrono::system_clock::to_time_t(chrono::system_clock::now());
  tm local_time;
  localtime_s(&local_time, &t);
  char tmp[_MAX_PATH];
  sprintf_s(tmp, _MAX_PATH, "log_%d_%d.log", local_time.tm_mon+1, local_time.tm_mday);
  log_file_name_ = tmp;
  
  _getcwd(tmp, _MAX_PATH);
  log_file_path_ = tmp;
}
