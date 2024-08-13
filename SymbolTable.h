#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <unordered_map>

using std::string;
using std::pair;

class SymbolTable
{
  typedef std::unordered_map<string,size_t> Table;

 private:
  unsigned int symbol_counter;
  Table table;

  inline void insert(const string& symbol,size_t num);
  bool contains(const string&) const;

 public:
  SymbolTable();
 ~SymbolTable();

 size_t get_address(const string&) const;
 void add_symbol(const string&);
 void add_label(const string&, size_t);
};

#endif //_SYMBOLTABLE_H_
