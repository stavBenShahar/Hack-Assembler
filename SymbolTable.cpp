#include "SymbolTable.h"

inline void SymbolTable::insert(const std::string& symbol, size_t num)
{ table.insert(pair<string, size_t>(symbol, num)); }

SymbolTable::SymbolTable()
{
  table.clear();

  /* Initialize predefined symbols */
  insert("SP", 0);
  insert("LCL", 1);
  insert("ARG", 2);
  insert("THIS", 3);
  insert("THAT", 4);

  for (int i = 0; i < 16; i++)
    insert("R" + std::to_string(i), i);

  insert("SCREEN", 16384);
  insert("KBD", 24576);

  this->symbol_counter = 15;
}

SymbolTable::~SymbolTable()
{ this->table.clear(); }

bool SymbolTable::contains (const string &symbol) const
{ return table.find(symbol) != table.end(); }

size_t SymbolTable::get_address (const string &symbol) const
{ return table.find(symbol)->second; }

void SymbolTable::add_symbol (const string &symbol)
{
  if (!contains (symbol))
    insert(symbol, ++symbol_counter);
}

void SymbolTable::add_label (const string &label, size_t line_index)
{
  //A label without its ()
  string clean_label = label.substr (1, label.size() - 2);
  insert(clean_label, line_index);
}