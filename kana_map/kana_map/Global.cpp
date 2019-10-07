#include <iostream>
#include <sstream>

#include "Global.h"

using namespace std;

std::string ConvertQuestion2String(const FullQuestion& quest)
{
  ostringstream os;
  os << "title = " << quest.title_ << endl;
  os << "type = " << quest.question_type_ << endl;
  //os << "audio path = " << quest.audio_path_ << endl;
  if (quest.question_type_ == select_kana2roman || quest.question_type_ == select_roman2kana) {
    os << "option1 = " << quest.option1_ << endl;
    os << "option2 = " << quest.option2_ << endl;
    os << "option3 = " << quest.option3_ << endl;
    os << "option4 = " << quest.option4_ << endl;
    os << "answer = " << quest.answer_pos_+1 << endl;
  }
  else {
    os << "answer = " << quest.answer_str_ << endl;
  }
  return os.str();
}