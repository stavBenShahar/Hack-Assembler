#ifndef _CODE_H_
#define _CODE_H_

#include <unordered_map>

using std::string;
using std::pair;

enum mnemonic_type
{ dest, comp, jump };

class Code
{
  typedef std::unordered_map<string, string> Table;

 public:
  Code();
  ~Code();

 private:
  Table dest_table;
  Table comp_table;
  Table jump_table;

  inline static void insert(Table&, const string&, const string&);

  public:
  string get_bi_code(const string&, mnemonic_type) const;
};

#endif //_CODE_H_
