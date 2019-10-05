#pragma once

#include "CandidatePool.h"
#include "Global.h"
#include <vector>
#include <string>

class CExaminer
{
public:
	CExaminer();
	~CExaminer();
  void SetType(unsigned int exam_type);
  unsigned int GetType();
  bool GetNextQuestion(FullQuestion &full_question);
  bool GetOption(std::string kana, bool is_kana, std::vector<std::string>& vt);

private:
  CCandidatePool pool_;
  int right_count_;
  int total_count_;
};

