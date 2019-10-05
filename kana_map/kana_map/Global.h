#pragma once

#include <string>

#define SUCCESS		0
#define USER_QUIT	1
#define ERROR_OUT	2

#define LETTER_TYPE_HIRAGANA        0x10000000  // Æ½¼ÙÃû
#define LETTER_TYPE_KATAKANA		    0x20000000  // Æ¬¼ÙÃû
#define LETTER_TYPE_ALL				      0xff000000

#define QUESTION_TYPE_READ_SELECT	  0x00000001
#define QUESTION_TYPE_READ_INPUT	  0x00000002
#define QUESTION_TYPE_LISTEN_SELECT	0x00000004  // todo
#define QUESTION_TYPE_LISTEN_INPUT	0x00000008  // todo
#define QUESTION_TYPE_LISTEN_WRITE	0x00000010  // todo
#define QUESTION_TYPE_ALL			      0x0fffffff

enum QuestionType
{
  select_kana2roman = 0,
  select_roman2kana,
  input_kana2roman,
  input_roman2kana,
};

struct FullQuestion
{
  QuestionType question_type_;
	std::string title_;
	std::string option1_;
	std::string option2_;
	std::string option3_;
	std::string option4_;
	std::string answer_;
	std::string audio_path_;
};

struct Question
{
  QuestionType question_type_;
	std::string kana_letter_;
};

