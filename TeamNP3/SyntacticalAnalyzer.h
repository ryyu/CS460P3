/********************************************************************************/
/* Project: 									*/
/* Author: 									*/
/* Date: 									*/
/* Description:									*/
/********************************************************************************/

#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (char * filename);
	~SyntacticalAnalyzer ();
    private:
	LexicalAnalyzer * lex;
	ofstream p2file;
	ofstream cpp;
	token_type token;
	int program ();
	//int errors;
	bool first;
	int define ();
	int more_defines ();
	int param_list ();
	int stmt ();
	int literal ();
	int action ();
	int stmt_list (string);
	int quoted_lit ();
	int any_other_token ();
	int more_tokens ();
	int else_part ();
};
	
#endif
