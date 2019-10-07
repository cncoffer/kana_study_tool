#pragma once

#include "Examiner.h"

class CUIModule
{
public:
	CUIModule();
	~CUIModule();

  void DoExam();

private:
  int Init();

private:
  CExaminer examiner_;
};

