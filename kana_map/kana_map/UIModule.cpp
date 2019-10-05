#include "UIModule.h"
#include <iostream>
#include <string>
#include "Global.h"
using namespace std;


CUIModule::CUIModule()
{
}

CUIModule::~CUIModule()
{
}

int CUIModule::Init()
{
	int sel = 0;
  int question_type = 0;
	// select letter test area. 选择平假名 or 片假名 or 所有
	do {
		cout << "请选择测试范围(均以包含浊音拗音):\n\t1.平假名\t2.片假名\t3.全部\t4.退出\n";
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
			return USER_QUIT;
		default:
      cout << "请在1-4范围内选择" << endl;
      sel = 0;
			break;
		}
  } while (!sel);

	// select question type area. 选择题型, 选择题 or 输入题 or 听力题(待实现) or 听写题(待实现) or 所有
  do {
    cout << "请选择题型范围:\n\t1.阅读选择题\t2.阅读输入题\t3.听力题(暂无)\t4.听写题(暂无)\t5.所有\t6.退出\n" << endl;
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
      return USER_QUIT;
      break;
    default:
      cout << "请在1-6范围内选择" << endl;
      sel = 0;
      break;
    }
  } while (!sel);

  // init candidate pool


  return SUCCESS;
}

