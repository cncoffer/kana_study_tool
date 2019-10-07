#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "Lexicon.h"
#include "MyLog.h"

using namespace std;

#define COUNT_HIRAGANA 104

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
  hiragana_list_.clear();
  katakana_list_.clear();
  roman_list_.clear();
  ifstream ifile("pair.txt");
  string str;
  int count = 0;
  while (getline(ifile, str)) {
    istringstream isstream(str);
    string kana, roman;
    isstream >> kana >> roman;
    kana_roman_map_[kana] = roman;
    count++;
    if (count <= COUNT_HIRAGANA) {
      hiragana_list_.push_back(kana);
      roman_list_.push_back(roman);
    }
    else {
      katakana_list_.push_back(kana);
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
  auto it = std::find(hiragana_list_.begin(), hiragana_list_.end(), kana);
  return it != hiragana_list_.end();
}

bool CLexicon::isKatakana(const std::string & kana)
{
  auto it = std::find(katakana_list_.begin(), katakana_list_.end(), kana);
  return it != katakana_list_.end();
}

bool CLexicon::isRoman(const std::string & roman)
{
  auto it = std::find(roman_list_.begin(), roman_list_.end(), roman);
  return it != roman_list_.end();
}

bool CLexicon::GetHiraganaList(std::vector<std::string>& list)
{
  list.clear();
  copy(hiragana_list_.begin(), hiragana_list_.end(), back_inserter(list));
  return true;
}

bool CLexicon::GetKatakanaList(std::vector<std::string>& list)
{
  list.clear();
  copy(katakana_list_.begin(), katakana_list_.end(), back_inserter(list));
  return true;
}

bool CLexicon::GetRomanList(std::vector<std::string>& list)
{
  list.clear();
  copy(roman_list_.begin(), roman_list_.end(), back_inserter(list));
  return true;
}

