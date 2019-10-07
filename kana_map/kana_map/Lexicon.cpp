#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "Lexicon.h"
#include "MyLog.h"

using namespace std;

#define COUNT_FIFTY_SOUND   46
#define COUNT_VOICED_SOUND  25
#define COUNT_AOYIN         33
#define COUNT_HIRAGANA      104 // 46 + 25 + 33

#define CONF_INI            "kana_pair.ini"

bool IsInList(const StrList &list, const string &target)
{
  return find(list.begin(), list.end(), target) != list.end();
}

CLexicon::CLexicon()
{
  Init();
}


CLexicon::~CLexicon()
{
}

void CLexicon::Init()
{
  kana_roman_map_.clear();
  hiragana_aoyin_list_.clear();
  katakana_aoyin_list_.clear();
  roman_aoyin_list_.clear();
  hiragana_no_aoyin_list_.clear();
  katakana_no_aoyin_list_.clear();
  roman_no_aoyin_list_.clear();
  ifstream ifile(CONF_INI);
  string str;
  int count = 0;
  while (getline(ifile, str)) {
    istringstream isstream(str);
    string kana, roman;
    isstream >> kana >> roman;
    kana_roman_map_[kana] = roman;
    count++;
    if (count <= COUNT_FIFTY_SOUND + COUNT_VOICED_SOUND) {
      hiragana_no_aoyin_list_.push_back(kana);
      roman_no_aoyin_list_.push_back(roman);
    }
    else if (count > COUNT_FIFTY_SOUND + COUNT_VOICED_SOUND && count <= COUNT_HIRAGANA) {
      hiragana_aoyin_list_.push_back(kana);
      roman_aoyin_list_.push_back(roman);
    }
    else if (count > COUNT_HIRAGANA && count <= COUNT_HIRAGANA + COUNT_FIFTY_SOUND + COUNT_VOICED_SOUND) {
      katakana_no_aoyin_list_.push_back(kana);
    }
    else {
      katakana_aoyin_list_.push_back(kana);
    }
  }
}

CLexicon * CLexicon::GetInstance()
{
  static CLexicon* inst = new CLexicon();
  if (inst == nullptr) {
    LOG_ERROR("new Lexicon failed.");
    exit(0);
  }
  return inst;
}

std::string CLexicon::GetKana(const std::string&roman)
{
  auto find_func = [roman](const  std::unordered_map<std::string, std::string>::value_type item){return item.second == roman;};
  auto it = std::find_if(kana_roman_map_.begin(), kana_roman_map_.end(), find_func);
  return it == kana_roman_map_.end() ? string("") : it->first;
}

std::string CLexicon::GetRoman(const std::string&kana)
{
  auto it = kana_roman_map_.find(kana);
  return it == kana_roman_map_.end() ? string("") : it->second;
}

bool CLexicon::isHiragana(const std::string & kana)
{
  return isHiraganaAoyin(kana) || isHiraganaNoAoyin(kana);
}

bool CLexicon::isKatakana(const std::string & kana)
{
  return isKatakanaAoyin(kana) || isKatakanaNoAoyin(kana);
}

bool CLexicon::isRoman(const std::string & roman)
{
  return isRomanAoyin(roman) || isRomanNoAoyin(roman);
}

bool CLexicon::GetHiraganaList(StrList& list)
{
  list.clear();
  copy(hiragana_aoyin_list_.begin(), hiragana_aoyin_list_.end(), back_inserter(list));
  copy(hiragana_no_aoyin_list_.begin(), hiragana_no_aoyin_list_.end(), back_inserter(list));
  return true;
}

bool CLexicon::GetKatakanaList(StrList& list)
{
  list.clear();
  copy(katakana_aoyin_list_.begin(), katakana_aoyin_list_.end(), back_inserter(list));
  copy(katakana_no_aoyin_list_.begin(), katakana_no_aoyin_list_.end(), back_inserter(list));
  return true;
}

bool CLexicon::GetRomanList(StrList& list)
{
  list.clear();
  copy(roman_aoyin_list_.begin(), roman_aoyin_list_.end(), back_inserter(list));
  copy(roman_no_aoyin_list_.begin(), roman_no_aoyin_list_.end(), back_inserter(list));
  return true;
}


bool CLexicon::isHiraganaNoAoyin(const std::string&kana)
{
  return IsInList(hiragana_no_aoyin_list_, kana);
}

bool CLexicon::isKatakanaNoAoyin(const std::string&kana)
{
  return IsInList(katakana_no_aoyin_list_, kana);
}

bool CLexicon::isRomanNoAoyin(const std::string&roman)
{
  return IsInList(roman_no_aoyin_list_, roman);
}

bool CLexicon::isHiraganaAoyin(const std::string&kana)
{
  return IsInList(hiragana_aoyin_list_, kana);
}

bool CLexicon::isKatakanaAoyin(const std::string&kana)
{
  return IsInList(katakana_aoyin_list_, kana);
}

bool CLexicon::isRomanAoyin(const std::string&roman)
{
  return IsInList(roman_aoyin_list_, roman);
}

bool CLexicon::GetHiraganaNoAoyinList(StrList &list)
{
  list.clear();
  copy(hiragana_no_aoyin_list_.begin(), hiragana_no_aoyin_list_.end(), back_inserter(list));
  return true;
}

bool CLexicon::GetKatakanaNoAoyinList(StrList &list)
{
  list.clear();
  copy(katakana_no_aoyin_list_.begin(), katakana_no_aoyin_list_.end(), back_inserter(list));
  return true;
}

bool CLexicon::GetRomanNoAoyinList(StrList &list)
{
  list.clear();
  copy(roman_no_aoyin_list_.begin(), roman_no_aoyin_list_.end(), back_inserter(list));
  return true;
}

bool CLexicon::GetHiraganaAoyinList(StrList &list)
{
  list.clear();
  copy(hiragana_aoyin_list_.begin(), hiragana_aoyin_list_.end(), back_inserter(list));
  return true;
}

bool CLexicon::GetKatakanaAoyinList(StrList &list)
{
  list.clear();
  copy(katakana_aoyin_list_.begin(), katakana_aoyin_list_.end(), back_inserter(list));
  return true;
}

bool CLexicon::GetRomanAoyinList(StrList &list)
{
  list.clear();
  copy(roman_aoyin_list_.begin(), roman_aoyin_list_.end(), back_inserter(list));
  return true;
}
