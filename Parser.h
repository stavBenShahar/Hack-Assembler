#ifndef _PARSER_H_
#define _PARSER_H_

#include <fstream>
#include <queue>

#include "SymbolTable.h"

using std::queue;
using std::string;

class Parser
{
  typedef queue<string> HackCode;

 public:
  /*
   * The parser removes all the comments and white spaces of the hack code.
   * In addition to that it does the "first pass" section of the assembly, it
   * adds the required labels into the symbol table and adds all the
   * "regular" commands into the given hack_code queue one by one.
   */
  Parser(const string&, HackCode&, SymbolTable&);
  ~Parser() = default;

 private:
  static void crop_comment(string&);
  static bool is_line_whitespace(const std::string&);
  static void remove_whitespace(string&);
};

#endif //_PARSER_H_
