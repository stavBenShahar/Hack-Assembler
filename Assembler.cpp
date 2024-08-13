#include <iostream>
#include <queue>
#include <bitset>

#include "Parser.h"
#include "SymbolTable.h"
#include "Code.h"

using std::string;
using std::queue;
using std::endl;

#define PREFIX_A "0"
#define PREFIX_C "111"

inline string dec_to_bi(const string& cmd)
{ return std::bitset<15>(stoi(cmd)).to_string(); }

string a_cmd_to_bi(const string& cmd, SymbolTable& symbols)
{
  //Raw number case
  if (std::isdigit(cmd[0]))
    return PREFIX_A + dec_to_bi(cmd);

  //Symbol case
  symbols.add_symbol(cmd);
  string address = std::to_string(symbols.get_address(cmd));
  return PREFIX_A + dec_to_bi(address);
}

/**
 * Parses given command to 3 parts (dest, comp, jump)
 * @param command C command as string
 * @param c_commands mnemonics binary code
 * @return given command as binary code as string
 */
string c_cmd_to_bi(const string& command, Code& c_cmds)
{
  size_t i = command.find('=');
  size_t j = command.find(';');

  // Split command to 3 parts:
  string raw_dest = (i == string::npos) ? "null" : command.substr(0, i);
  string raw_comp = command.substr(i + 1, j - i - 1);
  string raw_jump = (j == string::npos) ? "null" : command.substr(j + 1, command.size() - 1);

  // Translate parts to binary:
  string binary_comp = c_cmds.get_bi_code(raw_comp, comp);
  string binary_dest = c_cmds.get_bi_code(raw_dest, dest);
  string binary_jump = c_cmds.get_bi_code(raw_jump, jump);

  // Concat parts to final code:
  string res = PREFIX_C + binary_comp + binary_dest + binary_jump;

  //Left-Shift and Right-Shift operators:
//  if (binary_comp.find("<<") != std::string::npos)
//  {
//    long cmd_as_dec_num = 0;
//    cmd_as_dec_num = stol(res, nullptr, 2);
//    cmd_as_dec_num <<= 2;
//    res = dec_to_bi(res, 16);
//  }
//  else if (binary_comp.find(">>") != std::string::npos)
//  {
//    long cmd_as_dec_num = 0;
//    cmd_as_dec_num = stol(res, nullptr, 2);
//    cmd_as_dec_num >>= 2;
//    res = dec_to_bi(res, 16);
//  }

  return res;
}

string hack_cmd_to_bi(const string& cmd, SymbolTable& symbols,
                              Code& c_cmds)
{
  if (cmd[0] == '@')
  {
    string temp = cmd.substr(1, cmd.size() - 1); // Removes '@'
    return a_cmd_to_bi(temp, symbols);
  }
  return c_cmd_to_bi(cmd, c_cmds);
}

/**
 *
 * @param source_code a queue that contains all strings from given hack code
 * @param bi_code a queue to fill with equivalent binary code strings
 * @param symbols table of symbols and labels in code
 */
void hack_code_to_bi(queue<string>& source_code, queue<string>& bi_code,
                         SymbolTable& symbols)
{
  string cmd;
  Code c_cmd;
  while (!source_code.empty())
  {
    cmd = source_code.front();
    source_code.pop();

    string bi_cmd = hack_cmd_to_bi(cmd, symbols, c_cmd);
    bi_code.push(bi_cmd);
  }
}

std::string get_input_file_name(const std::string& file_path)
{
  std::string base_name = file_path.substr(file_path.find_last_of("/\\") + 1);
  auto type_extension_start(base_name.find_last_of('.'));
  return base_name.substr(0, type_extension_start);
}

/**
 * Creates a hack file filled with given source code in binary
 * @param input_file_path file path to source code
 * @param binary_code a queue of codes from given source code in binary
 */
void create_binary_code_file(const string& input_fp, queue<string>& bi_code)
{
  string outfile_name = get_input_file_name(input_fp) + ".hack";
  std::ofstream output_file(outfile_name);
  string cmd;
  while (!bi_code.empty())
  {
    cmd = bi_code.front();
    bi_code.pop();
    output_file << cmd << endl;
  }
  output_file.close();
}

int main(int argc, char** argv)
{
  SymbolTable symbols;
  queue<string> source_code;
  Parser parser(argv[1], source_code, symbols);
  queue<string> bi_code; // strings of source code in binary
  hack_code_to_bi(source_code, bi_code, symbols);
  create_binary_code_file(argv[1], bi_code);
  return 0;
}

