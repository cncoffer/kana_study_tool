#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

#include "CandidatePool.h"
#include "Global.h"
#include "Lexicon.h"
#include "MyLog.h"

using namespace std;

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
  if (candidate_pool_.empty()) return;
  // 检查是否有连续出现相同的, 尽量把他们消掉.
  for (PoolIter item = candidate_pool_.begin()+1; item < candidate_pool_.end() - 1; ++item) {
    if (item->kana_letter_.compare((item - 1)->kana_letter_) == 0) {
      PoolIter swap_item = candidate_pool_.end() - 1;
      while (swap_item >= candidate_pool_.begin()) {
        if (swap_item->kana_letter_.compare(item->kana_letter_) != 0) break;
        --swap_item;
      }
      if (item < swap_item) {
        Question temp = *item;
        *item = *swap_item;
        *swap_item = temp;
      };
    }
  }
}

void CCandidatePool::SetType(unsigned int exam_type)
{
  exam_type_ = exam_type;
}

unsigned int CCandidatePool::GetType()
{
  return exam_type_;
}

bool CCandidatePool::ReloadPool()
{
  CLexicon *lexicon = CLexicon::GetInstance();
  if (!lexicon) return false;
  total_count_ = 0;
  cur_count_ = 0;

  bool is_read_select = !!(exam_type_ & QUESTION_TYPE_READ_SELECT);
  bool is_read_input = !!(exam_type_ & QUESTION_TYPE_READ_INPUT);
  bool is_hiragana = !!(exam_type_ & LETTER_TYPE_HIRAGANA);
  bool is_katakana = !!(exam_type_ & LETTER_TYPE_KATAKANA);

  // add to the deque
  vector<string> list;
  if (is_hiragana && lexicon->GetHiraganaList(list)) {
    AddQuestion(list, candidate_pool_, is_read_select, is_read_input);
  }
  if (is_katakana && lexicon->GetKatakanaList(list)) {
    AddQuestion(list, candidate_pool_, is_read_select, is_read_input);
  }

  // shuffle the deque
  unsigned int seed = unsigned int(std::chrono::system_clock::now().time_since_epoch().count());
  shuffle(candidate_pool_.begin(), candidate_pool_.end(), std::default_random_engine(seed));

  // optimize the deque
  OptimizePool();

  total_count_ = candidate_pool_.size();
  return true;
}

void CCandidatePool::AddQuestion(vector<string> &list, Pool &candidate_pool, bool is_read_select, bool is_read_input)
{
  if (list.empty()) return;
  Question quest;
  auto add_question = [&candidate_pool, &quest](QuestionType type) {
    quest.question_type_ = type;
    candidate_pool.push_back(quest);
  };

  bool is_hiragana = CLexicon::GetInstance()->isHiragana(list[0]);
  for (vector<string>::const_iterator it = list.begin(); it < list.end(); ++it) {
    quest.kana_letter_ = *it;

    if (is_read_select) {
      add_question(select_kana2roman);
      add_question(select_roman2kana);
    }
    if (is_read_input) {
      add_question(input_kana2roman);
      add_question(is_hiragana ? input_roman2hiragana : input_roman2katakana);
    }
    // todo: add other type
  }
  return;
}