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
      return USER_QUIT;
      break;
    default:
      cout << "����1-6��Χ��ѡ��" << endl;
      sel = 0;
      break;
    }
  } while (!sel);

  // init candidate pool


  return SUCCESS;
}

