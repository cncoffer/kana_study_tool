#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

#include "CandidatePool.h"
#include "Global.h"
#include "Lexicon.h"

using namespace std;


void AddQuestion(vector<string> &list, std::deque<Question> &candidate_pool, bool is_read_select, bool is_read_input) {
  Question quest;
  auto add_question = [&candidate_pool, &quest](QuestionType type) {
    quest.question_type_ = type;
    candidate_pool.push_back(quest);
  };
  if (is_read_select) {
    for (vector<string>::const_iterator it = list.begin(); it < list.end(); ++it) {
      quest.kana_letter_ = *it;

      if (is_read_select) {
        add_question(select_kana2roman);
        add_question(select_roman2kana);
      }
      if (is_read_input) {
        add_question(input_kana2roman);
        add_question(input_roman2kana);
      }
      // todo: add other type
    }
  }
  return;
}

CCandidatePool::CCandidatePool()
  : total_count_(0),
  cur_count_(0),
  exam_type_(0)
{
}

CCandidatePool::~CCandidatePool()
{
}

bool CCandidatePool::GetQuestion(Question &quest)
{
  if (candidate_pool_.empty()) {
    // reload pool
    InitPool();

    // output reload success
    cout << "reload." << endl;

    // if reload failed, return false
    return false;
  }

  quest = candidate_pool_.front();
  candidate_pool_.pop_front();
  cur_count_++;
  return true;
}

string CCandidatePool::GetProcess()
{
  return to_string(cur_count_) + "/" + to_string(total_count_);
}

void CCandidatePool::OptimizePool()
{
  // 检查是否有连续出现相同的, 尽量把他们消掉.
}

void CCandidatePool::SetType(unsigned int exam_type)
{
  exam_type_ = exam_type;
}

unsigned int CCandidatePool::GetType()
{
  return exam_type_;
}

bool CCandidatePool::InitPool()
{
  CLexicon *lexicon = CLexicon::GetInstance();
  if (!lexicon) return ERROR_OUT;
  total_count_ = 0;

  bool is_read_select = bool(exam_type_ & QUESTION_TYPE_READ_SELECT);
  bool is_read_input = bool(exam_type_ & QUESTION_TYPE_READ_INPUT);
  bool is_hiragana = bool(exam_type_ & LETTER_TYPE_HIRAGANA);
  bool is_katakana = bool(exam_type_ & LETTER_TYPE_KATAKANA);

  // add to the deque
  vector<string> list;
  if (is_hiragana && lexicon->GetHiraganaList(list)) {
    AddQuestion(list, candidate_pool_, is_read_select, is_read_input);
  }
  if (is_katakana && lexicon->GetKatakanaList(list)) {
    AddQuestion(list, candidate_pool_, is_read_select, is_read_input);
  }

  // shuffle the deque
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(candidate_pool_.begin(), candidate_pool_.end(), std::default_random_engine(seed));

  // optimize the deque
  OptimizePool();

  total_count_ = candidate_pool_.size();
}
