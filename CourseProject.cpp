// CourseProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "Error.h"
#include "In.h"
#include "Parm.h"
#include "Log.h"
#include "LT.h"
#include "IT.h"
#include "Automats.h"
#include "ITform.h"
#include "GRB.h"
#include "MFST.h" 
#include "Semantica.h"
#include "Out.h"
#include "Generation.h"

void fillLibrary(IT::IdTable &IT)
{
	IT::IDDATATYPE *params = new IT::IDDATATYPE[2];
	params[0] = IT::IDDATATYPE::STR;
	params[1] = IT::IDDATATYPE::STR;
	IT.library[0] = IT::Func(0, (unsigned char*)"cat", 2, IT::IDDATATYPE::INT, params);
	IT.library[1] = IT::Func(0, (unsigned char*)"cpy", 2, IT::IDDATATYPE::INT, params);
	IT.libcur = 2;
	//-----------------------
}
int main(int argc, char* argv[])
{
	FST::FST_lexems auto_array[] = {FST::FST_lexems(LEX_ENTER, FST::FST("", 6, FST::FST::LEXEM, GRAPH_ENTER)),
									FST::FST_lexems(LEX_NEW, FST::FST("", 4, FST::FST::LEXEM, GRAPH_NEW)),
									FST::FST_lexems(LEX_FUNCTION, FST::FST("", 9, FST::FST::LEXEM, GRAPH_FUNCTION)),
									FST::FST_lexems(LEX_IF, FST::FST("", 3, FST::FST::LEXEM, GRAPH_IF)),
									FST::FST_lexems(LEX_ELSE, FST::FST("", 5, FST::FST::LEXEM, GRAPH_ELSE)),
									FST::FST_lexems(LEX_OUTPUT, FST::FST("", 7, FST::FST::LIB_NAME, GRAPH_OUTPUT)),
									FST::FST_lexems(LEX_STRCAT, FST::FST("", 4, FST::FST::LIB_NAME, GRAPH_STRCAT)),
									FST::FST_lexems(LEX_STRCPY, FST::FST("", 4, FST::FST::LIB_NAME, GRAPH_STRCPY)),
									FST::FST_lexems(LEX_INTEGER, FST::FST("", 8, FST::FST::LEXEM, GRAPH_INTEGER)),
									FST::FST_lexems(LEX_STRING, FST::FST("", 7, FST::FST::LEXEM, GRAPH_STRINGTYPE)),
									FST::FST_lexems(LEX_SYMBOL, FST::FST("", 7, FST::FST::LEXEM, GRAPH_SYMBOLTYPE)),
									FST::FST_lexems(LEX_LITERAL, FST::FST("", 4, FST::FST::NUM8_LITERAL, GRAPH_NUMBER8)),
									FST::FST_lexems(LEX_LITERAL, FST::FST("", 3, FST::FST::NUM2_LITERAL, GRAPH_NUMBER2)),
									FST::FST_lexems(LEX_LITERAL, FST::FST("", 4, FST::FST::SYM_LITERAL, GRAPH_SYMBOL)),
									FST::FST_lexems(LEX_LITERAL, FST::FST("", 5, FST::FST::STR_LITERAL, GRAPH_STRING)),
									FST::FST_lexems(LEX_RETURN, FST::FST("", 7, FST::FST::LEXEM, GRAPH_RETURN)),
									FST::FST_lexems(LEX_ID, FST::FST("", 3, FST::FST::IDENTIFICATOR, GRAPH_IDENTIFICATOR))};
	setlocale(LC_ALL, "rus");
	Log::LOG lg = Log::INITLOG;
	Out::OUT ot = Out::INITOUT;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		lg = Log::getlog(parm.log);
		ot = Out::getout(parm.out);
		Log::WriteLog(lg);
		Log::WriteParm(lg, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(lg, in);
		in.text = in.del_useless_blanks();
		int auto_amount = sizeof(auto_array) / sizeof(FST::FST_lexems);
		Parse::Words all_units = Parse::find_lexems(in);
		LT::LexTable LT = Parse::auto_check(all_units, auto_array, auto_amount, in, lg);
		IT::IdTable iTab = Form::getIDTable(LT, all_units);
		fillLibrary(iTab);
		LT.print_coded(lg);
		iTab.print(lg);
		//------------
		LT.table[LT.current] = LT::Entry('$', LT.table[LT.current - 1].sn);
		LT.current++;
		GRB::Greibach greibach = GRB::getGreibach();
		MFST_TRACE_START
		MFST::Mfst mfst(LT, greibach);
		mfst.start();
		mfst.savededucation();
		mfst.printrules();
		Sem::CompleteIDTab(LT, iTab, all_units);
		Sem::to_polish(LT, iTab, all_units);
		LT.print_coded(lg);
		Gen::Generate(ot, LT, iTab);
	}
	catch (Error::ERROR er)
	{
		Log::WriteError(lg, er);
		std::cout << er.id << " " << er.message << " " << er.inext.line << std::endl;
		Log::Close(lg);
		Out::Close(ot);
	}
	system("pause");
	return 0;
}


