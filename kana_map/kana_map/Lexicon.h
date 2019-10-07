#pragma once

#include <unordered_map>
#include <vector>
#include <string>

typedef std::vector<std::string> StrList;

class CLexicon
{
public:
  static CLexicon* GetInstance();
  std::string GetKana(const std::string& roman);
  std::string GetRoman(const std::string&kana);
  bool isHiraganaNoAoyin(const std::string&kana);
  bool isKatakanaNoAoyin(const std::string&kana);
  bool isRomanNoAoyin(const std::string&roman);
  bool isHiraganaAoyin(const std::string&kana);
  bool isKatakanaAoyin(const std::string&kana);
  bool isRomanAoyin(const std::string&roman);
  bool isHiragana(const std::string&kana);
  bool isKatakana(const std::string&kana);
  bool isRoman(const std::string&roman);
  bool GetHiraganaList(StrList &list);
  bool GetKatakanaList(StrList &list);
  bool GetRomanList(StrList &list);
  bool GetHiraganaNoAoyinList(StrList &list);
  bool GetKatakanaNoAoyinList(StrList &list);
  bool GetRomanNoAoyinList(StrList &list);
  bool GetHiraganaAoyinList(StrList &list);
  bool GetKatakanaAoyinList(StrList &list);
  bool GetRomanAoyinList(StrList &list);

private:
  CLexicon();
  ~CLexicon();
  void Init();
  std::unordered_map<std::string, std::string> kana_roman_map_;
  StrList hiragana_no_aoyin_list_;
  StrList katakana_no_aoyin_list_;
  StrList roman_no_aoyin_list_;
  StrList hiragana_aoyin_list_;
  StrList katakana_aoyin_list_;
  StrList roman_aoyin_list_;
};

