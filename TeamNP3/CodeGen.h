#ifndef CODE_GEN
#define CODE_GEN

#include <iostream>
#include <fstream>
using namespace std;

class CodeGen
{
  public:
  	CodeGen(string);
  	~CodeGen();
  	void writeCode(string);
  	string getReturn();

  private:
  	ofstream cpp;
  	string ret;
};

#endif
