#include "pch.h"
#include "Generation.h"
namespace Gen
{
	void start(Out::OUT out)
	{
		Out::WriteLine(out, ".586", "");
		Out::WriteLine(out, ".MODEL flat, stdcall", "");
		Out::WriteLine(out, "includelib kernel32.lib", "");
		Out::WriteLine(out, "includelib msvcrt.lib", "");
		Out::WriteLine(out, "includelib library.lib", "");
	}
	void protos(Out::OUT out, IT::IdTable IT, LT::LexTable LT)
	{
		Out::WriteLine(out, "SetConsoleTitleA   PROTO :DWORD ", "");
		Out::WriteLine(out, "GetStdHandle       PROTO :DWORD", "");
		Out::WriteLine(out, "WriteConsoleA      PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD", "");
		Out::WriteLine(out, "ExitProcess	PROTO   :DWORD", "");
		for (int i = 0; i < IT.libcur; i++)				//прототипы библиотечных функций
		{
			unsigned char* name = new unsigned char[7];
			strcpy_s((char*)name, 7, (const char*)IT.library[i].name);
			Out::WriteLine(out, "extrn ", (const char*)name, " : proc", "");
		}
		Out::WriteLine(out, ";--------------------------------", "");
	}
	void consts(Out::OUT out, IT::IdTable IT)
	{
		Out::WriteLine(out, ".stack 4096", "");
		Out::WriteLine(out, ".const", "");
		for (int i = 0; i < IT.current; i++)
		{
			if (IT.table[i].idtype == IT::IDTYPE::L)
			{
				char* buf = new char[300];
				switch (IT.table[i].iddatatype)
				{
				case IT::IDDATATYPE::INT:
				{
					sprintf_s(buf, 300, "%s  SDWORD  %d", IT.table[i].fullID, IT.table[i].value.vint);
				}break;
				case IT::IDDATATYPE::SYM:
				{
					sprintf_s(buf, 300, "%s  BYTE  '%c'", IT.table[i].fullID, IT.table[i].value.vsym);
				}break;
				case IT::IDDATATYPE::STR:
				{
					sprintf_s(buf, 300, "%s  DB  %s,0", IT.table[i].fullID, IT.table[i].value.vstr.str);
				}break;
				}
				Out::WriteLine(out, (const char*)buf, "");
			}
		}
		Out::WriteLine(out, ";--------------------------------", "");
	}
	void data(Out::OUT out, IT::IdTable IT)
	{
		Out::WriteLine(out, ".data", "");
		for (int i = 0; i < IT.current; i++)
		{
			if (IT.table[i].idtype == IT::IDTYPE::V)
			{
				char* buf = new char[300];
				switch (IT.table[i].iddatatype)
				{
				case IT::IDDATATYPE::INT:
				{
					sprintf_s(buf, 300, "%s  SDWORD  0", IT.table[i].fullID);
				}break;
				case IT::IDDATATYPE::SYM:
				{
					sprintf_s(buf, 300, "%s  BYTE  ' '", IT.table[i].fullID);
				}break;
				case IT::IDDATATYPE::STR:
				{
					sprintf_s(buf, 300, "%s  BYTE 256 dup(0)", IT.table[i].fullID);
				}break;
				}
				Out::WriteLine(out, (const char*)buf, "");
			}
		}
		Out::WriteLine(out, ";--------------------------------", "");
	}
	void proc_head(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		int parms = 0;
		i++;
		LT::Entry func = LT.table[i]; // объвление функции+перескочили на скобку
		i++;
		int ITind = func.idxTI;
		char* begin = new char[16];
		sprintf_s(begin, 16, "%s proc :", IT.table[func.idxTI].id);
		Out::WriteLine(out, (const char*)begin, "");
		while (LT.table[i].lexema[0] != LEX_RIGHTHESIS)
		{

			char* params = new char[70];
			char* type = new char[12];
			if (LT.table[i].lexema[0] == LEX_ID)
			{
				parms++;
				switch (IT.table[LT.table[i].idxTI].iddatatype)
				{
				case IT::IDDATATYPE::INT:
				{
					if (parms != IT.funcs[IT.table[ITind].Funcind].params) sprintf_s(type, 12, "%s: %s,", IT.table[LT.table[i].idxTI].id, "sdword");
					else sprintf_s(type, 12, "%s: %s", IT.table[LT.table[i].idxTI].id, "sdword");
				}break;
				case IT::IDDATATYPE::SYM:
				{
					if (parms != IT.funcs[IT.table[ITind].Funcind].params) sprintf_s(type, 12, "%s: %s,", IT.table[LT.table[i].idxTI].id, "byte");
					else sprintf_s(type, 12, "%s: %s", IT.table[LT.table[i].idxTI].id, "byte");
				}break;
				case IT::IDDATATYPE::STR: // какой тип данных если передаем строку????
				{
					if (parms != IT.funcs[IT.table[ITind].Funcind].params) sprintf_s(type, 12, "%s: %s,", IT.table[LT.table[i].idxTI].id, "dword");
					else sprintf_s(type, 12, "%s: %s", IT.table[LT.table[i].idxTI].id, "dword");
				}break;
				}
				Out::WriteLine(out, (const char*)type, "");
			}
			i++;
		}
	}
	void expression(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		int destination = i;
		// после i стоит =
		i += 2; // первая лексема выражения
		if (LT.table[i + 1].lexema[0] == LEX_ID) // i=i;
		{

		}
	}
	void proc_body(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		switch (LT.table[i].lexema[0])		//какая лексема стоит после {? n, i, o, I - варианты, n пропускаем
		{
		case LEX_ID: // выражение
		{

		}break;
		}
	}
	void code(Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		Out::WriteLine(out, ".code", "");
		int i = 0;
		while(i < LT.current)
		{
			char* buf = new char[200];
			if (LT.table[i].lexema[0] == LEX_FUNCTION)
			{
				proc_head(i, out, LT, IT); //остановились на закрывающей скобке )
				i += 2;					   //перешли на первую после { лексему
			}
			else i++;
		}
	}
	void Generate(Out::OUT out, LT::LexTable &LT, IT::IdTable &IT)
	{
		start(out);
		protos(out, IT, LT);
		consts(out, IT);
		data(out, IT);
		code(out, LT, IT);
	}
}