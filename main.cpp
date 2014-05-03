#include <iostream>
#include <fstream>
#include <string>
#include <libethcore/CommonIO.h>
#include "Instruction.h"

using namespace std;

using eth::compileLisp;
using eth::disassemble;
using eth::toString;

int main (int argc, char** argv) {
  string assemblyOrBytes;
  string codeFragment;
  string codeToCompile;
  ifstream in;
  eth::bytes byteCode;
  eth::bytes initCode;
  string assemblyCode;

  for (int i = 1; i < argc; ++i)
  {
    string arg = argv[i];
    if ((arg == "-a" || arg == "--asm") && i + 1 < argc)
    {
      assemblyOrBytes = 'a';
    }
    else
    {
      in.open(argv[i]);
    }
  }

  while (getline(in, codeFragment))
  {
    codeToCompile += codeFragment;
    codeToCompile.push_back('\n');
  }

  if (assemblyOrBytes == "a")
  {
    assemblyCode = disassemble(compileLisp(codeToCompile, false));
    cout << assemblyCode;
  }
  else
  {
    byteCode = compileLisp(codeToCompile, false);
    cout << toString(byteCode);
  }

  return 0;
}