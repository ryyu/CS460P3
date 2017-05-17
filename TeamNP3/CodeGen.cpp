#include <string>
#include "CodeGen.h"
using namespace std;

CodeGen::CodeGen(string filename)
{
	int length = filename.length();
	filename[length-2] = 'c';
  	filename[length-1] = 'p';
  	filename += 'p';
	cpp.open(filename);
	ret = "retValue$";
}


CodeGen::~CodeGen()
{
	cpp.close();
}


void CodeGen::writeCode(string code)
{
	cpp << code;
}


string CodeGen::getReturn()
{
	return ret;
}
