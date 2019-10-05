#pragma once

#include <unordered_map>
#include <vector>
#include <string>

class CLexicon
{
public:
  static CLexicon* GetInstance();
  std::string GetKana(const std::string& roman);
  std::string GetRoman(const std::string&kana);
  bool isHiragana(const std::string&kana);
  bool isKatakana(const std::string&kana);
  bool isRoman(const std::string&roman);
  bool GetHiraganaList(std::vector<std::string> &list);
  bool GetKatakanaList(std::vector<std::string> &list);
  bool GetRomanList(std::vector<std::string> &list);

private:
  CLexicon();
  ~CLexicon();
  void Init();
  std::unordered_map<std::string, std::string> kana_roman_map_;
  std::vector<std::string> hiragana_list_; 
  std::vector<std::string> katakana_list_;
  std::vector<std::string> roman_list_;
};

