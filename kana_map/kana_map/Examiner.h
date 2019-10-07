#pragma once

#include <vector>
#include <string>
#include "CandidatePool.h"
#include "Global.h"

class CExaminer
{
public:
	CExaminer();
	~CExaminer();
  void SetType(unsigned int exam_type);
  unsigned int GetType();
  bool GetNextQuestion(FullQuestion &full_question);
  std::string GetRateOfCorrect();
  std::string GetProcess();
  bool ReloadPool();
  void AddRightCount();

private:
  bool GetOption(std::string kana, bool is_kana, std::vector<std::string>& vt, int &answer_pos);

private:
  CCandidatePool pool_;
  int right_count_;
  int total_count_;
};

