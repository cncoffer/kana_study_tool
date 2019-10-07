#include <string>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <sstream>

#include "Examiner.h"
#include "Lexicon.h"
#include "MyLog.h"

using namespace std;

const string s_title_select = "请选择 %s 对应的%s:";
const string s_title_input = "请输入 %s 对应的%s:";
const string s_kana = "假名";
const string s_roman = "罗马音";
const string s_hiragana = "平假名";
const string s_katakana = "片假名";

CExaminer::CExaminer()
  : right_count_(0)
  , total_count_(0)
{
}

CExaminer::~CExaminer()
{
}

void CExaminer::SetType(unsigned int exam_type)
{
  pool_.SetType(exam_type);
}

unsigned int CExaminer::GetType()
{
  return pool_.GetType();
}

bool CExaminer::GetNextQuestion(FullQuestion & full_question)
{
  Question quest;
  bool ret = pool_.GetQuestion(quest);
  if (!ret) return false;

  char buff[MAX_STRING_LENGTH];
  vector<string> vt_option;
  int answer_pos;
  FullQuestion q;
  switch (quest.question_type_)
  {
  case select_kana2roman:
    sprintf_s(buff, s_title_select.c_str(), quest.kana_letter_.c_str(), s_roman.c_str());
    q.title_ = buff;
    q.question_type_ = quest.question_type_;
    ret = GetOption(quest.kana_letter_, false, vt_option, answer_pos);
    if (ret && vt_option.size() >= 4) {
      q.option1_ = "1. " + vt_option[0];
      q.option2_ = "2. " + vt_option[1];
      q.option3_ = "3. " + vt_option[2];
      q.option4_ = "4. " + vt_option[3];
      q.answer_pos_ = answer_pos;
    }
    break;
  case select_roman2kana:
    sprintf_s(buff, s_title_select.c_str(), CLexicon::GetInstance()->GetRoman(quest.kana_letter_).c_str(), s_kana.c_str());
    q.title_ = buff;
    q.question_type_ = quest.question_type_;
    ret = GetOption(quest.kana_letter_, true, vt_option, answer_pos);
    if (ret && vt_option.size() >= 4) {
      q.option1_ = "1. " + vt_option[0];
      q.option2_ = "2. " + vt_option[1];
      q.option3_ = "3. " + vt_option[2];
      q.option4_ = "4. " + vt_option[3];
      q.answer_pos_ = answer_pos;
    }
    break;
  case input_kana2roman:
    sprintf_s(buff, s_title_input.c_str(), quest.kana_letter_.c_str(), s_roman.c_str());
    q.title_ = buff;
    q.question_type_ = quest.question_type_;
    q.answer_str_ = CLexicon::GetInstance()->GetRoman(quest.kana_letter_);
    break;
  case input_roman2hiragana:
    sprintf_s(buff, s_title_input.c_str(), CLexicon::GetInstance()->GetRoman(quest.kana_letter_).c_str(), s_hiragana.c_str());
    q.title_ = buff;
    q.question_type_ = quest.question_type_;
    q.answer_str_ = quest.kana_letter_;
    break;
  case input_roman2katakana:
    sprintf_s(buff, s_title_input.c_str(), CLexicon::GetInstance()->GetRoman(quest.kana_letter_).c_str(), s_katakana.c_str());
    q.title_ = buff;
    q.question_type_ = quest.question_type_;
    q.answer_str_ = quest.kana_letter_;
    break;
  default:
    break;
  }

  full_question = q;
  total_count_++;
  return true;
}

std::string CExaminer::GetRateOfCorrect()
{
  ostringstream os;
  os << right_count_ << '/' << total_count_ << '(' << right_count_ * 100 / total_count_ << "%)";
  return os.str();
}

std::string CExaminer::GetProcess()
{
  return pool_.GetProcess();
}

bool CExaminer::ReloadPool()
{
  LOG_INFO("reload pool");
  total_count_ = 0;
  return pool_.ReloadPool();
}

void CExaminer::AddRightCount()
{
  right_count_++;
}

bool CExaminer::GetOption(string kana, bool is_kana, std::vector<std::string>& vt, int &answer_pos)
{
  vector<string> list;
  string answer = kana;
  // 首先随机选择另外三个假名/罗马音(随机选择也可以用shuffle做, 随机排序后选择前三个, 如果有重复的就再选择第四个), 然后将四个答案随机分配到四个位置上. 随机分配位置也可以使用shuffle函数
  if (is_kana) {
    if (CLexicon::GetInstance()->isHiraganaNoAoyin(kana)) {
      CLexicon::GetInstance()->GetHiraganaNoAoyinList(list);
    }
    else if (CLexicon::GetInstance()->isHiraganaAoyin(kana)) {
      CLexicon::GetInstance()->GetHiraganaAoyinList(list);
    }
    else if (CLexicon::GetInstance()->isKatakanaNoAoyin(kana)) {
      CLexicon::GetInstance()->GetKatakanaNoAoyinList(list);
    }
    else {
      CLexicon::GetInstance()->GetKatakanaAoyinList(list);
    }
  }
  else {
    if (CLexicon::GetInstance()->isRomanNoAoyin(CLexicon::GetInstance()->GetRoman(kana))) {
      CLexicon::GetInstance()->GetRomanNoAoyinList(list);
    }
    else {
      CLexicon::GetInstance()->GetRomanAoyinList(list);
    }
    answer = CLexicon::GetInstance()->GetRoman(kana);
  }

  if (list.empty()) return false;

  // select the answer
  vt.clear();
  vt.push_back(answer);
  unsigned int seed = unsigned int(std::chrono::system_clock::now().time_since_epoch().count());
  shuffle(list.begin(), list.end(), std::default_random_engine(seed));
  int count = 0;
  for (size_t i = 0; count < 3 && i < list.size(); ++i) {
    if (list[i] == answer) continue;
    vt.push_back(list[i]);
    count++;
  }
  if (count < 3) return false;

  // shuffle the answer
  shuffle(vt.begin(), vt.end(), std::default_random_engine(seed));

  auto it = find(vt.begin(), vt.end(), answer);
  answer_pos = it - vt.begin();

  return true;
}
