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
	indent = 0;
}


CodeGen::~CodeGen()
{
	cpp.close();
}


void CodeGen::writeCode(string code)
{	
	cpp << code;
}

void CodeGen::writeIndent()
{
	for(int i = 0; i < indent; i++)
	{
		cpp << "    ";
	}
}

string CodeGen::getReturn()
{
	return ret;
}

void CodeGen::increaseIndent()
{
	indent++;
}

void CodeGen::decreaseIndent()
{
	indent--;
}