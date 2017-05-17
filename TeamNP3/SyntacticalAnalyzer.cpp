/********************************************************************************/
/* Project: Project 02: Syntactical Analyzer					*/
/* Author: Team B: Brooke Borges, Austin Lehrer, Ryan Yu			*/
/* Date: 16 April 2017								*/
/* Description:	This program is meant to work in conjunction with the class     */
/*              contained in the file LexicalAnalyzer.h. These classes will     */
/*              read in scheme code from a .ss file and tokenize the lexemes    */
/*              using the LexicalAnalyzer. It will then check for the correct   */
/*              syntax using the rules defined by the contained table. The      */
/*              Syntactic Analyzer works by calling functions in a recursive    */
/*              manner to walk through the token stream coming in from the      */
/*              source code.                                                    */
/********************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <map>
#include "SyntacticalAnalyzer.h"

using namespace std;

// This enumerated type is used to index the table at the correct non-terminal token.
// Its purpose is to make reading the code easier. 
enum nonTerminals {PROGRAM=0, DEFINE, MORE_DEFINES, STMT_LIST, STMT, LITERAL, QUOTED_LIT, MORE_TOKENS,
 PARAM_LIST, ELSE_PART, ACTION, ANY_OTHER_TOKEN};

 static int table[12][32] = {
  // EOF_T,LPAREN_T,DEFINE_T,IDENT_T,RPAREN_T,NUMLIT_T,QUOTE_T,IF_T,LISTOP_T,CONS_T,AND_T,OR_T,NOT_T,NUMBERP_T,SYMBOLP_T,LISTP_T,ZEROP_T,NULLP_T,CHARP_T,STRINGP_T,PLUS_T,MINUS_T,DIV_T,MULT_T,EQUALTO_T,GT_T,LT_T,GTE_T,LTE_T,DISPLAY_T,NEWLINE_T,$
  {74,1,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74}, // <program>
  {74,2,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74}, // <define>
  {4,3,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74}, // <more_defines>
  {74,5,74,5,6,5,5,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74}, // <stmt_list>
  {74,9,74,8,74,7,7,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74}, // <stmt>
  {74,74,74,74,74,10,11,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74}, // <literal>
  {74,12,12,12,74,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,74}, // <quoted_lit>
  {74,13,13,13,14,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,74}, // <more_tokens>
  {74,74,74,15,16,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74}, // <param_list>
  {74,17,74,17,18,17,17,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74}, // <else_part>
  {74,74,74,41,74,74,74,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,42,43,74}, // <action>
  {74,44,55,45,74,46,72,48,51,47,52,53,54,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,49,50,74} // <any_other_token>
};

// This map is used to index the table at the correct terminal character.
static map<token_type, int> tokenmap = {
  {EOF_T, 0},
  {LPAREN_T, 1},
  {DEFINE_T, 2},
  {IDENT_T, 3},
  {RPAREN_T, 4},
  {NUMLIT_T, 5},
  {QUOTE_T, 6},
  {IF_T, 7},
  {LISTOP_T, 8},
  {CONS_T, 9},
  {AND_T, 10},
  {OR_T, 11},
  {NOT_T, 12},
  {NUMBERP_T, 13},
  {SYMBOLP_T, 14},
  {LISTP_T, 15},
  {ZEROP_T, 16},
  {NULLP_T, 17},
  {CHARP_T, 18},
  {STRINGP_T, 19},
  {PLUS_T, 20},
  {MINUS_T, 21},
  {DIV_T, 22},
  {MULT_T, 23},
  {EQUALTO_T, 24},
  {GT_T, 25},
  {LT_T, 26},
  {GTE_T, 27},
  {LTE_T, 28},
  {DISPLAY_T, 29},
  {NEWLINE_T, 30}
};


SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
  /********************************************************************************/
  /* This function will create an instance of a SyntacticalAnalyzer using the     */
  /* passed in filename. It will get the first token from the stream.		*/
  /* An instance of the LexicalAnalyzer will also get created.                    */
  /********************************************************************************/
  lex = new LexicalAnalyzer (filename);
  int fnlength = strlen (filename);
  string file = string(filename);
  first = true;
  ifstmt = false;
  generator = new CodeGen(file);
  
  filename[fnlength-2] = 'p';
  filename[fnlength-1] = '2';
  p2file.open (filename);
  token = lex->GetToken();
  int errors = program ();
  
}


SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
  /********************************************************************************/
  /* This function will delete the instance of the Lexical Analyzer created       */
  /* and close the debug file opened.                                             */
  /********************************************************************************/
  delete lex;
  delete generator;
  p2file.close();
}


int SyntacticalAnalyzer::program ()
{
  /********************************************************************************/
  /* This function will check the rule at PROGRAM and also the current token.     */
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/
  lex->debug << "program function called\n";
  p2file << "Starting <program>. Current token = " << token_names[token] << endl;
  int errors = 0;
  int rule = table[(int)PROGRAM][tokenmap[token]]; // PROGRAM is enum type corresponding to program row in table.
  p2file << "Using rule " << rule << endl;

  generator->writeCode("#include<iostream>\n#include \"Object.h\"\nusing namespace std;\n\n");//includes
  if (token != LPAREN_T)
  {
    lex->ReportError("Unexpected token or character: " + token_names[token]);
    errors++; 
  }

  // token should be in the firsts of program
  // if true... keep going
  // if false...
  // Error message -
  // then keep going or keep getting token until token is
  // in the firsts of program

  errors += define ();

  errors += more_defines ();

  if (token != EOF_T)
  {
    lex->ReportError ("Expected end of file; " + lex->GetLexeme ());
    errors++;
  }

  // token should be in the follows of program
  // if true... keep going
  // if false...
  // Error message -
  // then keep going or keep getting token until token is
  // in the follows of program

  p2file << "Ending <program>. Current token = " << token_names[token] << ". Errors = " << errors << endl;
  return errors;
}


int SyntacticalAnalyzer::define ()
{
  /********************************************************************************/
  /* This function will check the rule at DEFINE and also the current token.      */
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/

  p2file << "Starting <define>. Current token = " << token_names[token]  << endl;
  int errors = 0;
  int rule = table[(int)DEFINE][tokenmap[token]];
  p2file << "Using rule " << rule << endl;
  
  if (token != LPAREN_T)
  {     
    lex->ReportError("Unexpected token or character: " + token_names[token] + ". Expected token: DEFINE_T");
    errors++;
  }
  token = lex->GetToken();
  
  if (token != DEFINE_T)
  {     
    lex->ReportError("Unexpected token or character: " + token_names[token] + ". Expected token: DEFINE_T");
    errors++;
  }
  
  token = lex->GetToken();
  
  if (token != LPAREN_T)
  {
    lex->ReportError("Unexpected token or character: " + token_names[token] + ". Expected token: LPAREN_T");
    errors++;
  }
  
  token = lex->GetToken();
  
  if (token != IDENT_T)
  {
    lex->ReportError("Unexpected token or character: " + token_names[token] + ". Expected token: IDENT_T");
    errors++;     
  }
  if(lex -> GetLexeme() == "main")
    generator->writeCode("int main");
  else
    generator->writeCode("Object " + lex -> GetLexeme());
  
  token = lex->GetToken();
  generator->writeCode("(");
  errors += param_list();
  generator->writeCode(")\n");
  first = true;
  token = lex->GetToken();
  generator->writeCode("{\n\n\t");
  generator->writeCode("Object " + generator->getReturn() + ";\n\t");
  errors += stmt();

  errors += stmt_list(";");

  token = lex->GetToken();
  generator->writeCode("return " + generator->getReturn() + ";\n");
  generator->writeCode("\n}\n\n");
  p2file << "Ending <define>. Current token = " << token_names[token] << ". Errors = " << errors << endl;
  return errors;
  
}

int SyntacticalAnalyzer::more_defines()
{
  /********************************************************************************/
  /* This function will check the rule at MORE_DEFINES and also the current token.*/
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/

  p2file << "Starting <more_defines>. Current token = " << token_names[token]   << endl;
  int errors = 0;
  int rule = table[(int)MORE_DEFINES][tokenmap[token]];
  p2file << "Using rule " << rule << endl;
  
  if ((token == RPAREN_T) || (token == EOF_T))
  {

  }
  else
  {
    errors += define();
    errors += more_defines();
  }
  
  p2file << "Ending <more_defines>. Current token = " << token_names[token] << ". Errors = " << errors << endl;
  return errors;
  
}


int SyntacticalAnalyzer::param_list ()
{
  /********************************************************************************/
  /* This function will check the rule at PARAM_LIST and also the current token.  */
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/

  p2file << "Starting <param_list>. Current token = " << token_names[token]  << endl;
  int errors = 0;
  int rule = table[(int)PARAM_LIST][tokenmap[token]];
  p2file << "Using rule " << rule << endl;
  if (token == IDENT_T)
  {
    if(first)
    {
     generator->writeCode("Object " + lex -> GetLexeme());
     first = false;
   }
   else
     generator->writeCode(", Object " + lex ->GetLexeme());
   token = lex->GetToken();
   errors += param_list();
 }
 else if(token != RPAREN_T)
 {
  lex->ReportError("Unexpected token or character: " + token_names[token] + ". Expected token: RPAREN_T");
  errors++;
}

p2file << "Ending <param_list>. Current token = " << token_names[token] << ". Errors = " << errors << endl;

return errors; 
}


int SyntacticalAnalyzer::stmt ()
{
  /********************************************************************************/
  /* This function will check the rule at STMT and also the current token.        */
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/

  int errors = 0; 
  p2file << "Starting <stmt>. ";
  p2file << "Current token = " << token_names[token]  << endl;
  int rule = table[(int)STMT][tokenmap[token]];
  p2file << "Using rule " << rule << endl;

  //generator->writeCode("(");

  if (token == IDENT_T)
  {
    generator->writeCode(lex->GetLexeme());
    token = lex->GetToken();
  }
  else if (token == LPAREN_T)
  {
    token = lex->GetToken();
    errors += action();
    if (token != RPAREN_T)
    {
      lex->ReportError("Unexpected token or character: " + token_names[token] + ". Expected token: RPAREN_T");
      errors++; 
    }
      token = lex->GetToken(); // gets rparen
    }
    else if ((token == QUOTE_T) || (token == NUMLIT_T))
    {
      errors += literal();
    }
    else
    {
      token = lex->GetToken();
    }

    //generator->writeCode(")");
    p2file << "Ending <stmt>. Current token = " << token_names[token] << ". Errors = " << errors << endl;

    return errors;

  }


  int SyntacticalAnalyzer::stmt_list(string action)
  {
  /********************************************************************************/
  /* This function will check the rule at STMT_LIST and also the current token.   */
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/

    int errors = 0; 
    p2file << "Starting <stmt_list>. ";
    p2file << "Current token = " << token_names[token]  << endl;
    int rule = table[(int)STMT_LIST][tokenmap[token]];
    p2file << "Using rule " << rule << endl;

    if (action == ";")
    {
      if (!ifstmt)
      {
        generator->writeCode(";\n\t");
      }
      else
      {
        generator->writeCode("\n\t");
      }
      ifstmt = false;
    }

    if ((token != RPAREN_T) && (token != EOF_T))
    {
      errors += stmt();
      if (token != RPAREN_T)
      {
        generator->writeCode(action);
      }
      errors += stmt_list(action);
    }
  

    p2file << "Ending <stmt_list>. Current token = " << token_names[token] << ". Errors = " << errors << endl;
    return errors;
  }


  int SyntacticalAnalyzer::else_part()
  {
  /********************************************************************************/
  /* This function will check the rule at ELSE_PART and also the current token.   */
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/

    int errors = 0; 
    p2file << "Starting <else_part>. ";
    p2file << "Current token = " << token_names[token]  << endl;
    int rule = table[(int)ELSE_PART][tokenmap[token]];
    p2file << "Using rule " << rule << endl;

    if (token == RPAREN_T)
    {

    }
    else
    {
      generator->writeCode(";\n\t}\n\telse\n\t{\n\t\t");
      generator->writeCode(generator->getReturn() + " = ");
      errors += stmt();
    }

    p2file << "Ending <else_part>. Current token = " << token_names[token] << ". Errors = " << errors << endl;
    return errors;

  }


  int SyntacticalAnalyzer::literal()
  {
  /********************************************************************************/
  /* This function will check the rule at LITERAL and also the current token.     */
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/
    int errors = 0; 
    p2file << "Starting <literal>. ";
    p2file << "Current token = " << token_names[token]  << endl;
    int rule = table[(int)LITERAL][tokenmap[token]];
    p2file << "Using rule " << rule << endl;
    if (token == NUMLIT_T)
    {
      generator->writeCode("Object(" + lex->GetLexeme() + ")");
      token = lex->GetToken();    
      // do nothing. continue to return statement. 
    }
    else if (token == QUOTE_T)
    {
      token = lex->GetToken();
      errors += quoted_lit();
    }
    else
    {
      lex->ReportError("Unexpected token or character: " + token_names[token] + ". Expected token: NUMLIT_T or QUOTE_T");
      errors++; 
    }

    p2file << "Ending <literal>. Current token = " << token_names[token] << ". Errors = " << errors << endl;
    return errors;

  }


  int SyntacticalAnalyzer::quoted_lit()
  {
  /********************************************************************************/
  /* This function will check the rule at QUOTED_LIT and also the current token.  */
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/

    int errors = 0; 
    p2file << "Starting <quoted_lit>. ";
    p2file << "Current token = " << token_names[token]  << endl;
    int rule = table[(int)QUOTED_LIT][tokenmap[token]];
    p2file << "Using rule " << rule << endl;

  // next token already parsed from literal()
    errors += any_other_token();

    p2file << "Ending <quoted_lit>. Current token = " << token_names[token] << ". Errors = " << errors << endl;
    return errors;

  }


  int SyntacticalAnalyzer::action()
  {
  /********************************************************************************/
  /* This function will check the rule at ACTION and also the current token.      */
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/

    int errors = 0; 
    p2file << "Starting <action>. ";
    p2file << "Current token = " << token_names[token]  << endl;
    int rule = table[(int)ACTION][tokenmap[token]];
    p2file << "Using rule " << rule << endl;
    string operation = " " + lex->GetLexeme() + " ";

    if (token == NEWLINE_T)
    {
      token = lex->GetToken();
    }
    else if (token == IF_T)
    {
      ifstmt = true;
      generator->writeCode(lex->GetLexeme() + "(");
      token = lex->GetToken();
      errors += stmt();
      generator->writeCode(")\n\t{\n\t\t" );
      generator->writeCode(generator->getReturn() + " = ");
      errors += stmt();
      errors += else_part();
      generator->writeCode(";\n\t}\n");
    }
    else if(token == CONS_T)
    {
      token = lex->GetToken();
      errors += stmt();
      errors += stmt();
    }
    else if ((token == NOT_T) || (token == NUMBERP_T) || (token == SYMBOLP_T) || (token == LISTP_T) || (token == ZEROP_T) || 
      (token == NULLP_T) || (token == CHARP_T) || (token == STRINGP_T) || (token == DISPLAY_T) || (token == LISTOP_T))
    {
      token = lex->GetToken();
      errors += stmt(); 
    }
    else if ((token == PLUS_T) || (token == AND_T) || (token == OR_T) || (token == MULT_T) || (token == EQUALTO_T) || (token == GT_T) || 
     (token == LT_T) || (token == GTE_T) || (token == LTE_T) || (token == IDENT_T))
    {
      if (!ifstmt)
      {
        generator->writeCode(generator->getReturn() + " = ");
      }
      if (token == IDENT_T)
      {
        generator->writeCode(lex->GetLexeme());
        operation = ", ";
      }
      generator->writeCode("(");
      token = lex->GetToken();
      errors += stmt_list(operation);
      generator->writeCode(")");
    }
    else if((token == MINUS_T) || (token == DIV_T))
    {
      generator->writeCode("(");
      token = lex->GetToken();
      errors += stmt();
      errors += stmt_list(operation);
      generator->writeCode(")");
      if (token != RPAREN_T)
      {
       lex->ReportError("Unexpected token or character: " + token_names[token] + ". Expected token: RPAREN_T");
       errors++; 
     }
   }

   p2file << "Ending <action>. Current token = " << token_names[token] << ". Errors = " << errors << endl;

   return errors;

 }


 int SyntacticalAnalyzer::any_other_token ()
 {
  /********************************************************************************/
  /* This function will check the rule at ANY_OTHER_TOKEN and also the current    */
  /* token. It will check for the expected tokens in program, and then call       */
  /* the correct functions corresponding to the following non-terminals.          */
  /********************************************************************************/

  int errors = 0; 
  p2file << "Starting <any_other_token>. ";
  p2file << "Current token = " << token_names[token]  << endl;
  int rule = table[(int)ANY_OTHER_TOKEN][tokenmap[token]];
  p2file << "Using rule " << rule << endl;

  if (token == LPAREN_T)
  {
    token = lex->GetToken();
    errors += more_tokens();
    token = lex->GetToken();
  }
  else if (token == ERROR_T)
  {
    lex->ReportError("Unexpected token or character. Recieved: " + lex->GetLexeme());
  }
  else
  {
    token = lex->GetToken();
  }

  p2file << "Ending <any_other_token>. Current token = " << token_names[token] << ". Errors = " << errors << endl;
  return errors;

}

int SyntacticalAnalyzer::more_tokens ()
{
  /********************************************************************************/
  /* This function will check the rule at MORE_TOKENS and also the current token. */
  /* It will check for the expected tokens in program, and then call the correct  */
  /* functions corresponding to the following non-terminals.                      */
  /********************************************************************************/

  int errors = 0; 
  p2file << "Starting <more_tokens>. ";
  p2file << "Current token = " << token_names[token] << endl;
  int rule = table[(int)MORE_TOKENS][tokenmap[token]];
  p2file << "Using rule " << rule << endl;

  if ((token == RPAREN_T) || (token == EOF_T))
  {

  }
  else
  {
    errors += any_other_token();
    errors += more_tokens();
  }

  p2file << "Ending <more_tokens>. Current token = " << token_names[token] << ". Errors = " << errors << endl;
  return errors;

}





























