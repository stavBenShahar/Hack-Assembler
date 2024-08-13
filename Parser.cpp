#include <algorithm>
#include "Parser.h"

#define LABEL_PREFIX '('

Parser::Parser(const string& input_fp,
               HackCode& hack_code,
               SymbolTable& symbols)
{
  std::ifstream input_file;
  input_file.open(input_fp);

  string line;
  size_t i = 0;
  while (std::getline(input_file, line))
  {
    if (is_line_whitespace(line))
      continue;

    crop_comment(line);
    remove_whitespace(line);
    if (line[0] == LABEL_PREFIX)
    {
      symbols.add_label(line, i);
      continue;
    }
    hack_code.push(line);
    i++;
  }
}

void Parser::remove_whitespace(string& line)
{
  line.erase(std::remove_if(
    line.begin(), line.end(),
    [](char c) { return std::isspace(c); }), line.end());
}

void Parser::crop_comment(string& curr_line)
{
  std::string delimiter = "//";
  std::string token = curr_line.substr(0, curr_line.find(delimiter));
  curr_line = token;
}

bool Parser::is_line_whitespace(const std::string& line)
{
  for (char c : line)
  {
    if (c == '/')
      return true;
    if (!std::isspace(c))
      return false;
  }
  return true;
}
