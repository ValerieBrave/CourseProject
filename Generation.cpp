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
		for (int i = 0; i < IT.libcur; i++)				//��������� ������������ �������
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
					sprintf_s(buf, 300, "%s  DWORD  ?", IT.table[i].fullID);
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
		LT::Entry func = LT.table[i]; // ��������� �������+����������� �� ������
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
				case IT::IDDATATYPE::STR: // ����� ��� ������ ���� �������� ������????
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
		// ����� i ����� =
		i += 2; //i= ������ ������� ���������
		if (LT.table[i].lexema[0] == LEX_ID && LT.table[i + 1].lexema[0] == LEX_SEMOCOLON) // i=i;
		{
			char* buf = new char[50];
			sprintf_s(buf, 50, "mov eax, %s \n mov %s, eax", IT.table[LT.table[i].idxTI].id, IT.table[LT.table[i -2].idxTI].id);
			Out::WriteLine(out, (const char*)buf, "");
			i += 3;																	// ����������� �� ��������� ����� ��������� �������
		}
		else if (LT.table[i].lexema[0] == LEX_LITERAL && LT.table[i + 1].lexema[0] == LEX_SEMOCOLON) //i=l;
		{
			char* buf = new char[50];
			sprintf_s(buf, 50, "mov eax, %s \n mov %s, eax", IT.table[LT.table[i].idxTI].fullID, IT.table[LT.table[i - 2].idxTI].id);
			Out::WriteLine(out, (const char*)buf, "");
			i += 3;																	// ����������� �� ��������� ����� ��������� �������
		}
		else if ((LT.table[i].lexema[0] == LEX_ID || LT.table[i].lexema[0]==LEX_LITERAL )&&	(LT.table[i + 2].lexema[0] == LEX_LESS || LT.table[i + 2].lexema[0] == LEX_MORE ||
				 LT.table[i + 2].lexema[0] == LEX_ELESS || LT.table[i + 2].lexema[0] == LEX_EMORE || LT.table[i + 2].lexema[0] == LEX_DEQUALS ||
				 LT.table[i + 2].lexema[0] == LEX_NEQUALS))// i = i ���� i;
			 {
				 switch (LT.table[i + 2].lexema[0])
				 {
					 case LEX_LESS: // + LEX_MORE
					 {
						 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						 {
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 if(!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call int_less", "");
							 else Out::WriteLine(out, "call int_more", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						 {
							 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call str_less", "");
							 else Out::WriteLine(out, "call str_more", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
						 {
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call sym_less", "");
							 else Out::WriteLine(out, "call sym_more", "");
						 }
						 Out::WriteLine(out, "mov ", (const char*)IT.table[LT.table[destination].idxTI].id, ", eax", "");
						 i += 4;									// ������� �� ��������� ����� ; �������
					 }break;
					 case LEX_ELESS:
					 {
						 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						 {
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call int_eless", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						 {
							 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call str_eless", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
						 {
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call sym_eless", "");
						 }
						 Out::WriteLine(out, "mov ", (const char*)IT.table[LT.table[destination].idxTI].id, ", eax", "");
						 i += 4;									// ������� �� ��������� ����� ; �������
					 }break;
					 case LEX_EMORE:
					 {
						 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						 {
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call int_emore", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						 {
							 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call str_emore", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
						 {
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call sym_emore", "");
						 }
						 Out::WriteLine(out, "mov ", (const char*)IT.table[LT.table[destination].idxTI].id, ", eax", "");
						 i += 4;									// ������� �� ��������� ����� ; �������
					 }break;
					 case LEX_DEQUALS:
					 {
						 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						 {
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call int_equals", "");
						 }

						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						 {
							 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call str_equals", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
						 {
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call sym_equals", "");
						 }
						 Out::WriteLine(out, "mov ", (const char*)IT.table[LT.table[destination].idxTI].id, ", eax", "");
						 i += 4;									// ������� �� ��������� ����� ; �������
					 }break;
					 case LEX_NEQUALS:
					 {
						 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						 {
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call int_nequals", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						 {
							 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call str_nequals", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
						 {
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 1].idxTI].id, "");
							 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
							 Out::WriteLine(out, "call sym_nequals", "");
						 }
						 Out::WriteLine(out, "mov ", (const char*)IT.table[LT.table[destination].idxTI].id, ", eax", "");
						 i += 4;									// ������� �� ��������� ����� ; �������
					 }break;
				 }
			 }
		else if (LT.table[i].lexema[0] == LEX_STRCAT)						// i = i..i@b###;+ LEX_STRCPY
		{
			while(LT.table[i].lexema[0] != LEX_SEMOCOLON)
			{
				// ������ � ���� ���� �� ����� �������, ����� ����� ������� � ������� �� ��������� ������
				i++;
			}
		}
	}
	void proc_body(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		while (LT.table[i].lexema[0] != LEX_BRACELET)
		{
			switch (LT.table[i].lexema[0])		//����� ������� ����� ����� {? n, i, o, I - ��������, n ����������
			{
			case LEX_NEW:
			{
				while (LT.table[i].lexema[0] != LEX_SEMOCOLON) i++;
				i++;							//������� �� ��������� ������
			}break;
			case LEX_ID: // ���������
			{
				expression(i, out, LT, IT);
			}break;
			}
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
				proc_head(i, out, LT, IT); //������������ �� ����������� ������ )
				i += 2;					   //������� �� ������ ����� { �������
				proc_body(i, out, LT, IT);
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