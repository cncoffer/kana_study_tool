#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <deque>
#include "Global.h"

class CCandidatePool
{
public:
	CCandidatePool();
	~CCandidatePool();
  void SetType(unsigned int exam_type);
  unsigned int GetType();
  bool InitPool();
  bool GetQuestion(Question &quest);
  std::string GetProcess();
  void OptimizePool();

private:
  unsigned int exam_type_;
  std::deque<Question> candidate_pool_;
  int total_count_;
  int cur_count_;
};

