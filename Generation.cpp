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
	}
	void Generate(Out::OUT out, LT::LexTable &LT, IT::IdTable &IT)
	{
		start(out);
		protos(out, IT, LT);
		consts(out, IT);
		data(out, IT);
	}
}