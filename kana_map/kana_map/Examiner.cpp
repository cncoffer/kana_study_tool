#include "Examiner.h"
#include <string>
#include <iostream>
#include "Lexicon.h"
using namespace std;

const string s_title_select = "请选择%s对应的%s:";
const string s_title_input = "请输入%s对应的%s:";
const string s_kana = "假名";
const string s_roman = "罗马音";

CExaminer::CExaminer()
  : right_count_(0),
  total_count_(0)
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

  char temp[_MAX_PATH];
  vector<string> vt_option;
  switch (quest.question_type_)
  {
  case select_kana2roman:
    sprintf_s(temp, s_title_select.c_str(), quest.kana_letter_.c_str(), s_kana.c_str());
    full_question.title_ = temp;
    full_question.question_type_ = quest.question_type_;
    ret = GetOption(quest.kana_letter_, true, vt_option);
    if (ret) {
      full_question.option1_ = vt_option[0];
      full_question.option2_ = vt_option[1];
      full_question.option3_ = vt_option[2];
      full_question.option4_ = vt_option[3];
    }
    full_question.answer_ = CLexicon::GetInstance()->GetRoman(quest.kana_letter_);
    full_question.audio_path_ = "";
    break;
  case select_roman2kana:
    break;
  case input_kana2roman:
    break;
  case input_roman2kana:
    break;
  default:
    break;
  }

  return true;
}

bool CExaminer::GetOption(string kana, bool is_kana, std::vector<std::string>& vt)
{
  // 首先随机选择另外三个假名/罗马音(随机选择也可以用shuffle做, 随机排序后选择前三个, 如果有重复的就再选择第四个), 然后将四个答案随机分配到四个位置上. 随机分配位置也可以使用shuffle函数
  if (is_kana) {
    if (CLexicon::GetInstance()->isHiragana(kana)) {
      // 先随机选出3个平假名, 和当前平假名放在一起, 然后打乱顺序, 并输出.
    }
    else { // 片假名

    }
  }
  else { // 罗马音

  }

  return false;
}
