// CourseProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Error.h"
#include "In.h"
#include "Parm.h"
#include "Log.h"
#include "LT.h"
#include "IT.h"
#include "Automats.h"
#include "Semantica.h"

int main(int argc, char* argv[])
{
	FST::FST_lexems auto_array[] = {FST::FST_lexems(LEX_ENTER, FST::FST("", 6, FST::FST::LEXEM, GRAPH_ENTER)),
									FST::FST_lexems(LEX_NEW, FST::FST("", 4, FST::FST::LEXEM, GRAPH_NEW)),
									FST::FST_lexems(LEX_FUNCTION, FST::FST("", 9, FST::FST::LEXEM, GRAPH_FUNCTION)),
									FST::FST_lexems(LEX_OUTPUT, FST::FST("", 7, FST::FST::LIB_NAME, GRAPH_OUTPUT)),
									FST::FST_lexems(LEX_INTEGER, FST::FST("", 8, FST::FST::LEXEM, GRAPH_INTEGER)),
									FST::FST_lexems(LEX_STRING, FST::FST("", 7, FST::FST::LEXEM, GRAPH_STRINGTYPE)),
									FST::FST_lexems(LEX_SYMBOL, FST::FST("", 7, FST::FST::LEXEM, GRAPH_SYMBOLTYPE)),
									FST::FST_lexems(LEX_LITERAL, FST::FST("", 3, FST::FST::NUM_LITERAL, GRAPH_NUMBER)),
									FST::FST_lexems(LEX_RETURN, FST::FST("", 7, FST::FST::LEXEM, GRAPH_RETURN)),
									FST::FST_lexems(LEX_ID, FST::FST("", 3, FST::FST::IDENTIFICATOR, GRAPH_IDENTIFICATOR))};
	setlocale(LC_ALL, "rus");
	Log::LOG lg = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		lg = Log::getlog(parm.log);
		Log::WriteLog(lg);
		Log::WriteParm(lg, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(lg, in);
		in.text = in.del_useless_blanks();
		int auto_amount = sizeof(auto_array) / sizeof(FST::FST_lexems);
		Parse::Words all_units = Parse::find_lexems(in);
		LT::LexTable LT = Parse::auto_check(all_units, auto_array, auto_amount, in, lg);
		int k = 0;
	}
	catch (Error::ERROR er)
	{
		Log::WriteError(lg, er);
		std::cout << er.id << " " << er.message << " " << er.inext.line << std::endl;
		Log::Close(lg);
	}
	system("pause");
	return 0;
}


