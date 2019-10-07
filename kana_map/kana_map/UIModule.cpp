#include "UIModule.h"
#include <iostream>
#include <string>

#include "Global.h"
#include "MyLog.h"

using namespace std;

#define STR_ANSWER_TIP    "%s, ��ȷ����: %s."
#define STR_ANSWER_IS_RIGHT "��"
#define STR_ANSWER_IS_WRONG "��"

CUIModule::CUIModule()
{
}

CUIModule::~CUIModule()
{
}

int CUIModule::Init()
{
	int sel = 0;
  unsigned int question_type = 0;
	// select letter test area. ѡ��ƽ���� or Ƭ���� or ����
	do {
		cout << "��ѡ����Է�Χ(���԰�����������):\n\t1.ƽ����\t2.Ƭ����\t3.ȫ��\t4.�˳�\n";
		cin >> sel;
		switch (sel)
		{
		case 1:
      question_type |= LETTER_TYPE_HIRAGANA;
			break;
		case 2:
      question_type |= LETTER_TYPE_KATAKANA;
			break;
		case 3:
      question_type |= LETTER_TYPE_ALL;
			break;
		case 4:
      LOG_INFO(STR_USER_QUIT);
			return USER_QUIT;
		default:
      cout << "����1-4��Χ��ѡ��" << endl;
      sel = 0;
			break;
		}
  } while (!sel);

	// select question type area. ѡ������, ѡ���� or ������ or ������(��ʵ��) or ��д��(��ʵ��) or ����
  do {
    cout << "��ѡ�����ͷ�Χ:\n\t1.�Ķ�ѡ����\t2.�Ķ�������\t3.������(����)\t4.��д��(����)\t5.����\t6.�˳�\n" << endl;
    cin >> sel;
    switch (sel)
    {
    case 1:
      question_type |= QUESTION_TYPE_READ_SELECT;
      break;
    case 2:
      question_type |= QUESTION_TYPE_READ_INPUT;
      break;
    case 3:
      question_type |= QUESTION_TYPE_LISTEN_INPUT | QUESTION_TYPE_LISTEN_SELECT;
      break;
    case 4:
      question_type |= QUESTION_TYPE_LISTEN_WRITE;
      break;
    case 5:
      question_type |= QUESTION_TYPE_ALL;
      break;
    case 6:
      LOG_INFO(STR_USER_QUIT);
      return USER_QUIT;
      break;
    default:
      cout << "����1-6��Χ��ѡ��" << endl;
      sel = 0;
      break;
    }
  } while (!sel);

  examiner_.SetType(question_type);

  return SUCCESS;
}

void CUIModule::DoExam()
{
  FullQuestion  quest;
  char buff[MAX_STRING_LENGTH];
  string input;
  auto HandleAnswer = [](CExaminer &examiner, bool is_right, const FullQuestion &quest, const string &input) {
    if (is_right) {
      examiner.AddRightCount();
    }
    else {
      string str_wrong = ConvertQuestion2String(quest);
      str_wrong = "�������, ѡ����" + input + "\n" + str_wrong;
      LOG_INFO(str_wrong);
    }
  };
  while (true)
  {
    if (!examiner_.GetNextQuestion(quest)) {
      Init();
      if (!examiner_.ReloadPool()) {
        LOG_ERROR(STR_RELOAD_FAILED);
        cout << "�������ʧ��, ���˳������³���." << endl;
        break;
      }
      cout << "��ʼ����, һ�ֽ�����, ������ѡ������." << endl;
      cout << "������������, ��ֱ�ӹرճ���." << endl;
      continue;
    }
    cout << endl << examiner_.GetProcess();
    switch (quest.question_type_)
    {
    case select_kana2roman:
    case select_roman2kana:
    {
      cout << "\t" << quest.title_ << endl;
      cout << "\t" << quest.option1_ << "\t\t\t" << quest.option2_ << endl;
      cout << "\t" << quest.option3_ << "\t\t\t" << quest.option4_ << endl;
      cin >> input;

      int sel = atoi(input.c_str()) - 1;
      bool is_right = (sel == quest.answer_pos_);
      HandleAnswer(examiner_, is_right, quest, input);
      sprintf_s(buff, MAX_STRING_LENGTH, STR_ANSWER_TIP, is_right ? STR_ANSWER_IS_RIGHT : STR_ANSWER_IS_WRONG, to_string(quest.answer_pos_ + 1).c_str());
      cout << buff << endl;
      break;
    }
    case input_kana2roman:
    case input_roman2hiragana:
    case input_roman2katakana:
    {
      cout << "\t" << quest.title_ << endl;
      cin >> input;
      bool is_right = (quest.answer_str_.compare(input) == 0);
      HandleAnswer(examiner_, is_right, quest, input);
      sprintf_s(buff, MAX_STRING_LENGTH, STR_ANSWER_TIP, is_right ? STR_ANSWER_IS_RIGHT : STR_ANSWER_IS_WRONG, quest.answer_str_.c_str());
      cout << buff << endl;
      break;
    }
    default:
      cout << "unknown error" << endl;
      break;
    }
    cout << "��ǰ��ȷ��Ϊ: " << examiner_.GetRateOfCorrect() << endl;
  }
}

