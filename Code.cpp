#include "Code.h"

inline void Code::insert(Table& table, const std::string& mnemonic,
                                                 const std::string& binary)
{ table.insert(pair<string, string>(mnemonic, binary)); }

Code::Code()
{
  //Create comp_table - A
  insert(comp_table,  "0",    "0101010");
  insert(comp_table,  "1",    "0111111");
  insert(comp_table,  "-1",   "0111010");
  insert(comp_table,  "D",    "0001100");
  insert(comp_table,  "D>>",  "0001100");
  insert(comp_table,  "D<<",  "0001100");
  insert(comp_table,  "A",    "0110000");
  insert(comp_table,  "A>>",  "0110000");
  insert(comp_table,  "A<<",  "0110000");
  insert(comp_table,  "!D",   "0001111");
  insert(comp_table,  "!A",   "0110001");
  insert(comp_table,  "-D",   "0001111");
  insert(comp_table,  "-A",   "0110011");
  insert(comp_table,  "D+1",  "0011111");
  insert(comp_table,  "A+1",  "0110111");
  insert(comp_table,  "D-1",  "0001110");
  insert(comp_table,  "A-1",  "0110010");
  insert(comp_table,  "D+A",  "0000010");
  insert(comp_table,  "D-A",  "0010011");
  insert(comp_table,  "A-D",  "0000111");
  insert(comp_table,  "D&A",  "0000000");
  insert(comp_table,  "D|A",  "0010101");

  //Create comp_table - M
  insert(comp_table,  "M",    "1110000");
  insert(comp_table,  "M>>",  "1110000");
  insert(comp_table,  "M<<",  "1110000");
  insert(comp_table,  "!M",   "1110001");
  insert(comp_table,  "-M",   "1110011");
  insert(comp_table,  "M+1",  "1110111");
  insert(comp_table,  "M-1",  "1110010");
  insert(comp_table,  "D+M",  "1000010");
  insert(comp_table,  "D-M",  "1010011");
  insert(comp_table,  "M-D",  "1000111");
  insert(comp_table,  "D&M",  "1000000");
  insert(comp_table,  "D|M",  "1010101");

  //Create dest_table
  insert(dest_table,  "null",   "000");
  insert(dest_table,  "M",      "001");
  insert(dest_table,  "D",      "010");
  insert(dest_table,  "MD",     "011");
  insert(dest_table,  "A",      "100");
  insert(dest_table,  "AM",     "101");
  insert(dest_table,  "AD",     "110");
  insert(dest_table,  "AMD",    "111");

  //Crete jump_table
  insert(jump_table,  "null", "000");
  insert(jump_table,  "JGT",  "001");
  insert(jump_table,  "JEQ",  "010");
  insert(jump_table,  "JGE",  "011");
  insert(jump_table,  "JLT",  "100");
  insert(jump_table,  "JNE",  "101");
  insert(jump_table,  "JLE",  "110");
  insert(jump_table,  "JMP",  "111");
}

Code::~Code()
{
  dest_table.clear();
  comp_table.clear();
  jump_table.clear();
}

string Code::get_bi_code(const string& mnemonic, mnemonic_type type) const
{
  switch (type)
  {
    case dest: return dest_table.find(mnemonic)->second;
    case comp: return comp_table.find(mnemonic)->second;
    case jump: return jump_table.find(mnemonic)->second;
  }
}