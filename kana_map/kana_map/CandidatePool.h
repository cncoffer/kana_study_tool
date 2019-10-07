#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <deque>
#include "Global.h"

typedef std::deque<Question> Pool;
typedef std::deque<Question>::iterator PoolIter;

class CCandidatePool
{
public:
	CCandidatePool();
	~CCandidatePool();
  void SetType(unsigned int exam_type);
  unsigned int GetType();
  bool ReloadPool();
  bool GetQuestion(Question &quest);
  std::string GetProcess();

private:
  void OptimizePool();
  void AddQuestion(std::vector<std::string> &list, Pool &candidate_pool, bool is_read_select, bool is_read_input);

private:
  unsigned int exam_type_;
  Pool candidate_pool_;
  int total_count_;
  int cur_count_;
};

