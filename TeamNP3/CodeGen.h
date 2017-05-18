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
  	void increaseIndent();
  	void decreaseIndent();
  	void writeIndent();

  private:
  	ofstream cpp;
  	string ret;
  	int indent;
};

#endif
