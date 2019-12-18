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
		i += 2;						// ������� �� ��������� ������
	}
	void expression(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		bool callF = false;
		int k = i;
		while (!callF && LT.table[k].lexema[0] != LEX_SEMOCOLON) { callF = (LT.table[k].lexema[0] == '@'); k++; }
		int destination = i;
		// ����� i ����� =
		i += 2; //i= ������ ������� ���������
		if (LT.table[i].lexema[0] == LEX_ID && LT.table[i + 1].lexema[0] == LEX_SEMOCOLON) // i=i;
		{
			char* buf = new char[50];
			char* dest = new char[15];
			char *source = new char[15];
			if (IT.table[LT.table[destination].idxTI].idtype == IT::IDTYPE::P) strcpy_s(dest, 15, IT.table[LT.table[destination].idxTI].id);
			else strcpy_s(dest, 15, (char*)IT.table[LT.table[destination].idxTI].fullID);
			if (IT.table[LT.table[i].idxTI].idtype == IT::IDTYPE::P) strcpy_s(source, 15, IT.table[LT.table[i].idxTI].id);
			else strcpy_s(source, 15, (char*)IT.table[LT.table[i].idxTI].fullID);
			switch (IT.table[LT.table[i].idxTI].iddatatype)				// ������ �� ����� ����
			{
			case IT::IDDATATYPE::INT:
			{
				sprintf_s(buf, 50, "mov eax, %s \n mov %s, eax", source, dest);
				Out::WriteLine(out, (const char*)buf, "");
			}break;
			case IT::IDDATATYPE::SYM:
			{
				Out::WriteLine(out, "mov eax, 0", "");
				Out::WriteLine(out, "mov al, ", source, "");
				Out::WriteLine(out, "mov ", dest, ", eax", "");
			}break;
			}
			i += 2;																	// ����������� �� ��������� ����� ��������� �������
		}
		else if (LT.table[i].lexema[0] == LEX_LITERAL && LT.table[i + 1].lexema[0] == LEX_SEMOCOLON) //i=l;
		{
			char* buf = new char[50];
			char* dest = new char[15];
			if (IT.table[LT.table[destination].idxTI].idtype == IT::IDTYPE::P) strcpy_s(dest, 15, IT.table[LT.table[destination].idxTI].id);
			else strcpy_s(dest, 15, (char*)IT.table[LT.table[destination].idxTI].fullID);
			switch (LT.table[i].littype)
			{
			case LT::LITTYPE::N2:
			{
				sprintf_s(buf, 50, "mov eax, %s \n mov %s, eax", IT.table[LT.table[i].idxTI].fullID, dest);
				Out::WriteLine(out, (const char*)buf, "");
			}break;
			case LT::LITTYPE::N8:
			{
				sprintf_s(buf, 50, "mov eax, %s \n mov %s, eax", IT.table[LT.table[i].idxTI].fullID, dest);
				Out::WriteLine(out, (const char*)buf, "");
			}break;
			case LT::LITTYPE::SY:
			{
				Out::WriteLine(out, "mov eax, 0", "");
				Out::WriteLine(out, "mov al, ", (const char*)IT.table[LT.table[i].idxTI].fullID, "");
				Out::WriteLine(out, "mov ", dest, ", eax", "");
			}break;
			case LT::LITTYPE::S:
			{
				Out::WriteLine(out, "mov eax, OFFSET ", (const char*)IT.table[LT.table[i].idxTI].fullID, "");
				Out::WriteLine(out, "mov %s, eax", dest, "");
			}break;
			}
			i += 2;																	// ����������� �� ��������� ����� ��������� �������
		}
		else if (LT.table[i].lexema[0] == LEX_ID &&	(LT.table[i + 2].lexema[0] == LEX_LESS || LT.table[i + 2].lexema[0] == LEX_MORE ||
				 LT.table[i + 2].lexema[0] == LEX_ELESS || LT.table[i + 2].lexema[0] == LEX_EMORE || LT.table[i + 2].lexema[0] == LEX_DEQUALS ||
				 LT.table[i + 2].lexema[0] == LEX_NEQUALS))// i = i ���� � �� ����� ���
			 {
				 char* par1 = new char[12];
				 if (IT.table[LT.table[i+1].idxTI].idtype == IT::IDTYPE::P) strcpy_s(par1, 12, IT.table[LT.table[i+1].idxTI].id);
				 else strcpy_s(par1, 12, (char*)IT.table[LT.table[i+1].idxTI].fullID);
				 char* par2 = new char[12];
				 if (IT.table[LT.table[i].idxTI].idtype == IT::IDTYPE::P) strcpy_s(par2, 12, IT.table[LT.table[i].idxTI].id);
				 else strcpy_s(par2, 12, (char*)IT.table[LT.table[i].idxTI].fullID);
				 char* dest = new char[12];
				 if (IT.table[LT.table[destination].idxTI].idtype == IT::IDTYPE::P) strcpy_s(dest, 12, IT.table[LT.table[destination].idxTI].id);
				 else strcpy_s(dest, 12, (char*)IT.table[LT.table[destination].idxTI].fullID);

				 switch (LT.table[i + 2].lexema[0])
				 {
					 case LEX_LESS: // + LEX_MORE
					 {
						 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						 {
							 Out::WriteLine(out, "push ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 if(!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call int_less", "");
							 else Out::WriteLine(out, "call int_more", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						 {
							 if(LT.table[i + 1].littype == LT::LITTYPE::NOT) Out::WriteLine(out, "push ", par1, "");
							 else Out::WriteLine(out, "push OFFSET ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call str_less", "");
							 else Out::WriteLine(out, "call str_more", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
						 {
							 Out::WriteLine(out, "push ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call sym_less", "");
							 else Out::WriteLine(out, "call sym_more", "");
						 }
						 Out::WriteLine(out, "mov ", dest, ", eax", "");
						 i += 4;									// ������� �� ��������� ����� ; �������
					 }break;
					 case LEX_ELESS:
					 {
						 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						 {
							 Out::WriteLine(out, "push ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 Out::WriteLine(out, "call int_eless", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						 {
							 if (LT.table[i + 1].littype == LT::LITTYPE::NOT) Out::WriteLine(out, "push ", par1, "");
							 else Out::WriteLine(out, "push OFFSET ", par1, "");
							 Out::WriteLine(out, "push OFFSET ", par2, "");
							 Out::WriteLine(out, "call str_eless", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
						 {
							 Out::WriteLine(out, "push ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 Out::WriteLine(out, "call sym_eless", "");
						 }
						 Out::WriteLine(out, "mov ", dest, ", eax", "");
						 i += 4;									// ������� �� ��������� ����� ; �������
					 }break;
					 case LEX_EMORE:
					 {
						 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						 {
							 Out::WriteLine(out, "push ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 Out::WriteLine(out, "call int_emore", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						 {
							 if (LT.table[i + 1].littype == LT::LITTYPE::NOT) Out::WriteLine(out, "push ", par1, "");
							 else Out::WriteLine(out, "push OFFSET ", par1, "");
							 Out::WriteLine(out, "push OFFSET ", par2, "");
							 Out::WriteLine(out, "call str_emore", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
						 {
							 Out::WriteLine(out, "push ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 Out::WriteLine(out, "call sym_emore", "");
						 }
						 Out::WriteLine(out, "mov ", dest, ", eax", "");
						 i += 4;									// ������� �� ��������� ����� ; �������
					 }break;
					 case LEX_DEQUALS:
					 {
						 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						 {
							 Out::WriteLine(out, "push ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 Out::WriteLine(out, "call int_equals", "");
						 }

						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						 {
							 if (LT.table[i + 1].littype == LT::LITTYPE::NOT) Out::WriteLine(out, "push ", par1, "");
							 else Out::WriteLine(out, "push OFFSET ", par1, "");
							 Out::WriteLine(out, "push OFFSET ", par2, "");
							 Out::WriteLine(out, "call str_equals", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
						 {
							 Out::WriteLine(out, "push ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 Out::WriteLine(out, "call sym_equals", "");
						 }
						 Out::WriteLine(out, "mov ", dest, ", eax", "");
						 i += 4;									// ������� �� ��������� ����� ; �������
					 }break;
					 case LEX_NEQUALS:
					 {
						 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						 {
							 Out::WriteLine(out, "push ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 Out::WriteLine(out, "call int_nequals", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						 {
							 if (LT.table[i + 1].littype == LT::LITTYPE::NOT) Out::WriteLine(out, "push ", par1, "");
							 else Out::WriteLine(out, "push OFFSET ", par1, "");
							 Out::WriteLine(out, "push OFFSET ", par2, "");
							 Out::WriteLine(out, "call str_nequals", "");
						 }
						 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
						 {
							 Out::WriteLine(out, "push ", par1, "");
							 Out::WriteLine(out, "push ", par2, "");
							 Out::WriteLine(out, "call sym_nequals", "");
						 }
						 Out::WriteLine(out, "mov ", dest, ", eax", "");
						 i += 4;									// ������� �� ��������� ����� ; �������
					 }break;
				 }
			 }
		else if (LT.table[i].lexema[0] == LEX_LITERAL && (LT.table[i + 2].lexema[0] == LEX_LESS || LT.table[i + 2].lexema[0] == LEX_MORE ||
			LT.table[i + 2].lexema[0] == LEX_ELESS || LT.table[i + 2].lexema[0] == LEX_EMORE || LT.table[i + 2].lexema[0] == LEX_DEQUALS ||
			LT.table[i + 2].lexema[0] == LEX_NEQUALS))
			 {
				 char* par1 = new char[12];
				 if (IT.table[LT.table[i + 1].idxTI].idtype == IT::IDTYPE::P) strcpy_s(par1, 12, IT.table[LT.table[i + 1].idxTI].id);
				 else strcpy_s(par1, 12, (char*)IT.table[LT.table[i + 1].idxTI].fullID);
				 char* dest = new char[12];
				 if (IT.table[LT.table[destination].idxTI].idtype == IT::IDTYPE::P) strcpy_s(dest, 12, IT.table[LT.table[destination].idxTI].id);
				 else strcpy_s(dest, 12, (char*)IT.table[LT.table[destination].idxTI].fullID);
			 switch (LT.table[i + 2].lexema[0])
			 {
			 case LEX_LESS:
			 {
				 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				 {
					 Out::WriteLine(out, "push ", par1, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call int_less", "");
					 else Out::WriteLine(out, "call int_more", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				 {
					 Out::WriteLine(out, "push OFFSET", par1, "");
					 if (LT.table[i].littype != LT::LITTYPE::NOT) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call str_less", "");
					 else Out::WriteLine(out, "call str_more", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
				 {
					 Out::WriteLine(out, "push ", par1, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call sym_less", "");
					 else Out::WriteLine(out, "call sym_more", "");
				 }
				 Out::WriteLine(out, "mov ", dest, ", eax", "");
				 i += 4;
			 }break;
			 case LEX_ELESS:
			 {
				 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				 {
					 Out::WriteLine(out, "push ", par1, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call int_eless", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				 {
					 Out::WriteLine(out, "push OFFSET", par1, "");
					 if (LT.table[i].littype != LT::LITTYPE::NOT) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call str_eless", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
				 {
					 Out::WriteLine(out, "push ", par1, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call sym_eless", "");
				 }
				 Out::WriteLine(out, "mov ", dest, ", eax", "");
				 i += 4;
			 }break;
			 case LEX_EMORE:
			 {
				 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				 {
					 Out::WriteLine(out, "push ", par1, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call int_emore", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				 {
					 Out::WriteLine(out, "push OFFSET", par1, "");
					 if (LT.table[i].littype != LT::LITTYPE::NOT) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call str_emore", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
				 {
					 Out::WriteLine(out, "push ", par1, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call sym_emore", "");
				 }
				 Out::WriteLine(out, "mov ", dest, ", eax", "");
				 i += 4;
			 }break;
			 case LEX_DEQUALS:
			 {
				 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				 {
					 Out::WriteLine(out, "push ", par1, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call int_equals", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				 {
					 Out::WriteLine(out, "push OFFSET", par1, "");
					 if (LT.table[i].littype != LT::LITTYPE::NOT) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call str_equals", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
				 {
					 Out::WriteLine(out, "push ", par1, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call sym_equals", "");
				 }
				 Out::WriteLine(out, "mov ", dest, ", eax", "");
				 i += 4;
			 }break;
			 case LEX_NEQUALS:
			 {
				 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				 {
					 Out::WriteLine(out, "push ", par1, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call int_nequals", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				 {
					 Out::WriteLine(out, "push OFFSET", par1, "");
					 if (LT.table[i].littype != LT::LITTYPE::NOT) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call str_nequals", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
				 {
					 Out::WriteLine(out, "push ", par1, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call sym_nequals", "");
				 }
				 Out::WriteLine(out, "mov ", dest, ", eax", "");
				 i += 4;
			 }break;
			 }
			 }
		else if (callF)						// i = i..i@b/i###;
		{
			while(LT.table[i].lexema[0] != '@')
			{
				// ������ � ���� ���� �� ����� �������, ����� ����� ������� � ������� �� ��������� ������
				char *par = new char[12];
				if (IT.table[LT.table[i].idxTI].idtype == IT::IDTYPE::P) strcpy_s(par, 12, IT.table[LT.table[i].idxTI].id);
				else strcpy_s(par, 12, (char*)IT.table[LT.table[i].idxTI].fullID);
				if(LT.table[i].littype != LT::LITTYPE::S) Out::WriteLine(out, "push ", par, "");
				else Out::WriteLine(out, "push OFFSET", par, "");
				i++;
			}
			i++;			//������� �� ����� �������
			switch (LT.table[i].lexema[0])			// ���� ������������ ���� ����������������
			{
			case LEX_STRCAT:
			{
				Out::WriteLine(out, "call ", (const char*)IT.library[IT.Fhere(IT.table[LT.table[i].idxTI].libname)].name, "");
			}break;
			case LEX_ID:
			{
				Out::WriteLine(out, "call ", (const char*)IT.funcs[IT.table[LT.table[i].idxTI].Funcind].name, "");
			}break;
			}
			Out::WriteLine(out, "mov ", (const char*)IT.table[LT.table[destination].idxTI].id, ", eax", "");
			while (LT.table[i].lexema[0] != LEX_SEMOCOLON) i++;					// ����������� �� ;
			i++;																// ������� �� ��������� ������
		}
	}
	void output(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		//i+2 - �� ��� ���� �������
		i += 2;
		switch (IT.table[LT.table[i].idxTI].iddatatype)
		{
		case IT::IDDATATYPE::INT:
		{
			Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
			Out::WriteLine(out, "call int_output", "");
		}break;
		case IT::IDDATATYPE::SYM:
		{
			Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
			Out::WriteLine(out, "call char_output", "");
		}break;
		case IT::IDDATATYPE::STR:
		{
			if(LT.table[i].littype == LT::LITTYPE::S) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
			else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
			Out::WriteLine(out, "call str_output", "");
		}break;
		}
		i += 3;								// ������� �� ��������� ������
	}
	void if_block(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		//i - if
		char* orig = new char[5];			//��� ������������ �����
		sprintf_s(orig, 5, "%d", i);
		i += 2;			// ������� �� ������ ������� ���������
		if ((LT.table[i].lexema[0] == LEX_ID || LT.table[i].lexema[0] == LEX_LITERAL) && LT.table[i + 1].lexema[0] == LEX_RIGHTHESIS)// if(i/l)=> �������� ��������
		{
			switch (IT.table[LT.table[i].idxTI].iddatatype)
			{
			case IT::IDDATATYPE::INT:
			{
				Out::WriteLine(out, "mov eax, ", (const char*)IT.table[LT.table[i].idxTI].id, "");
				Out::WriteLine(out, "cmp eax, 0", "");
				Out::WriteLine(out, "jne ELSE", (const char*)orig, ":", "");
			}break;
			case IT::IDDATATYPE::SYM:
			{
				Out::WriteLine(out, "mov eax, 0", "");
				Out::WriteLine(out, "mov al, ", (const char*)IT.table[LT.table[i].idxTI].id, "");
				Out::WriteLine(out, "cmp eax, 0", "");
				Out::WriteLine(out, "jne ELSE", (const char*)orig, ":", "");
			}break;
			case IT::IDDATATYPE::STR:
			{
				if (LT.table[i].lexema[0] == LEX_ID)
				{
					Out::WriteLine(out, "mov eax, ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					Out::WriteLine(out, "cmp [eax], 0", "");
					Out::WriteLine(out, "jne ELSE", (const char*)orig, ":", "");
				}
				else
				{
					Out::WriteLine(out, "mov eax, 0", "");
					Out::WriteLine(out, "mov al, ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					Out::WriteLine(out, "cmp eax, 0", "");
					Out::WriteLine(out, "jne ELSE", (const char*)orig, ":", "");
				}
			}break;
			}
			i += 3;				//������� �� ������� ����� {

		}
		else if (LT.table[i].lexema[0] == LEX_ID  && (LT.table[i + 1].lexema[0] == LEX_LESS || LT.table[i + 1].lexema[0] == LEX_MORE ||
			LT.table[i + 1].lexema[0] == LEX_ELESS || LT.table[i + 1].lexema[0] == LEX_EMORE || LT.table[i + 1].lexema[0] == LEX_DEQUALS ||
			LT.table[i + 1].lexema[0] == LEX_NEQUALS))							//������������� � �� ����� ���
			 {
				switch (LT.table[i + 1].lexema[0])
				{
				case LEX_LESS:
				{
					if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
					{
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call int_less", "");
						else Out::WriteLine(out, "call int_more", "");
					}
					else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
					{
						if(LT.table[i + 2].littype == LT::LITTYPE::NOT) Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						else Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call str_less", "");
						else Out::WriteLine(out, "call str_more", "");
					}
					else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
					{
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call sym_less", "");
						else Out::WriteLine(out, "call sym_more", "");
					}
					Out::WriteLine(out, "cmp eax, 0", "");
					Out::WriteLine(out, "je ELSE", (const char*)orig, ":", "");
					i += 5;				//�� ��������� ������� - �.� � ���� ��
				}break;
				case LEX_ELESS:
				{
					if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
					{
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call int_eless", "");
					}
					else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
					{
						if (LT.table[i + 2].littype == LT::LITTYPE::NOT) Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						else Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call str_eless", "");
					}
					else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
					{
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call sym_eless", "");
					}
					Out::WriteLine(out, "cmp eax, 0", "");
					Out::WriteLine(out, "je ELSE", (const char*)orig, ":", "");
					i += 5;
				}break;
				case LEX_EMORE:
				{
					if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
					{
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call int_emore", "");
					}
					else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
					{
						if (LT.table[i + 2].littype == LT::LITTYPE::NOT) Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						else Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call str_emore", "");
					}
					else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
					{
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call sym_emore", "");
					}
					Out::WriteLine(out, "cmp eax, 0", "");
					Out::WriteLine(out, "je ELSE", (const char*)orig, ":", "");
					i += 5;
				}break;
				case LEX_DEQUALS:
				{
					if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
					{
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call int_equals", "");
					}
					else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
					{
						if (LT.table[i + 2].littype == LT::LITTYPE::NOT) Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						else Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call str_equals", "");
					}
					else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
					{
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call sym_equals", "");
					}
					Out::WriteLine(out, "cmp eax, 0", "");
					Out::WriteLine(out, "je ELSE", (const char*)orig, ":", "");
					i += 5;
				}break;
				case LEX_NEQUALS:
				{
					if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
					{
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call int_nequals", "");
					}
					else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
					{
						if (LT.table[i + 2].littype == LT::LITTYPE::NOT) Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						else Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call str_nequals", "");
					}
					else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
					{
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
						Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
						Out::WriteLine(out, "call sym_nequals", "");
					}
					Out::WriteLine(out, "cmp eax, 0", "");
					Out::WriteLine(out, "je ELSE", (const char*)orig, ":", "");
					i += 5;

				}break;
				}
			 }
		else if (LT.table[i].lexema[0] == LEX_LITERAL && (LT.table[i + 1].lexema[0] == LEX_LESS || LT.table[i + 1].lexema[0] == LEX_MORE ||
			LT.table[i + 1].lexema[0] == LEX_ELESS || LT.table[i + 1].lexema[0] == LEX_EMORE || LT.table[i + 1].lexema[0] == LEX_DEQUALS ||
			LT.table[i + 1].lexema[0] == LEX_NEQUALS))						// ������� � �� ����� ���
			 {
			 switch (LT.table[i + 1].lexema[0])
			 {
			 case LEX_LESS:
			 {
				 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				 {
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call int_less", "");
					 else Out::WriteLine(out, "call int_more", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				 {
					 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 if(LT.table[i].littype!=LT::LITTYPE::NOT) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call str_less", "");
					 else Out::WriteLine(out, "call str_more", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
				 {
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 if (!strcmp(LT.table[i].operation, "<")) Out::WriteLine(out, "call sym_less", "");
					 else Out::WriteLine(out, "call sym_more", "");
				 }
				 Out::WriteLine(out, "cmp eax, 0", "");
				 Out::WriteLine(out, "jne ELSE", "");
				 i += 5;				//�� ��������� ������� - �.� � ���� ��
			 }break;
			 case LEX_ELESS:
			 {
				 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				 {
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call int_eless", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				 {
					 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 if (LT.table[i].littype != LT::LITTYPE::NOT) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call str_eless", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
				 {
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call sym_eless", "");
				 }
				 Out::WriteLine(out, "cmp eax, 0", "");
				 Out::WriteLine(out, "jne ELSE", "");
				 i += 5;
			 }break;
			 case LEX_EMORE:
			 {
				 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				 {
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call int_emore", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				 {
					 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 if (LT.table[i].littype != LT::LITTYPE::NOT) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call str_emore", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
				 {
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call sym_emore", "");
				 }
				 Out::WriteLine(out, "cmp eax, 0", "");
				 Out::WriteLine(out, "jne ELSE", "");
				 i += 5;
			 }break;
			 case LEX_DEQUALS:
			 {
				 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				 {
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call int_equals", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				 {
					 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 if (LT.table[i].littype != LT::LITTYPE::NOT) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call str_equals", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
				 {
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call sym_equals", "");
				 }
				 Out::WriteLine(out, "cmp eax, 0", "");
				 Out::WriteLine(out, "jne ELSE", "");
				 i += 5;
			 }break;
			 case LEX_NEQUALS:
			 {
				 if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
				 {
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call int_nequals", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
				 {
					 Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 if (LT.table[i].littype != LT::LITTYPE::NOT) Out::WriteLine(out, "push OFFSET", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 else Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call str_nequals", "");
				 }
				 else if (IT.table[LT.table[i].idxTI].iddatatype == IT::IDDATATYPE::SYM)
				 {
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i + 2].idxTI].id, "");
					 Out::WriteLine(out, "push ", (const char*)IT.table[LT.table[i].idxTI].id, "");
					 Out::WriteLine(out, "call sym_nequals", "");
				 }
				 Out::WriteLine(out, "cmp eax, 0", "");
				 Out::WriteLine(out, "jne ELSE", "");
				 i += 5;

			 }break;
			 }
			 }
			 // ������ �� ������ ������� ����� ��
		while (LT.table[i].lexema[0] != LEX_BRACELET)			// ���� �� ���������� ���� ��
		{
			switch (LT.table[i].lexema[0])			// �������� - o, i
			{
			case LEX_ID: // ���������
			{
				expression(i, out, LT, IT);
			}break;
			case LEX_OUTPUT:	// ����� �� �������
			{
				output(i, out, LT, IT);
			}break;
			}
		}
		
		Out::WriteLine(out, "jmp AFTER", (const char*)orig, "");
		i++;					//��� ����� ����� ����?
		if (LT.table[i].lexema[0] == LEX_ELSE)
		{
			i += 2;				//������� �� ������ ������� �����
			Out::WriteLine(out, "ELSE", (const char*)orig,":", "");
			while (LT.table[i].lexema[0] != LEX_BRACELET)			// ���� �� ���������� ���� ��
			{
				switch (LT.table[i].lexema[0])			// �������� - o, i
				{
				case LEX_ID: // ���������
				{
					expression(i, out, LT, IT);
				}break;
				case LEX_OUTPUT:	// ����� �� �������
				{
					output(i, out, LT, IT);
				}break;
				}
			}
			Out::WriteLine(out, "AFTER", (const char*)orig, ":", "");
			i++;				// ������� �� ������� ����� ��������� ����� ���
		}
	}
	void ret(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		if (LT.table[i].lexema[0] == LEX_ID && LT.table[i + 1].lexema[0] == LEX_SEMOCOLON)				//return i;
		{
			switch (IT.table[LT.table[i].idxTI].iddatatype)
			{
			case IT::IDDATATYPE::INT:
			{
				Out::WriteLine(out, "mov eax, 0", "");
				Out::WriteLine(out, "mov eax, ", (const char*)IT.table[LT.table[i].idxTI].id, "");
				Out::WriteLine(out, "ret", "");
			}break;
			case IT::IDDATATYPE::SYM:
			{
				Out::WriteLine(out, "mov eax, 0", "");
				Out::WriteLine(out, "mov al, ", (const char*)IT.table[LT.table[i].idxTI].id, "");
				Out::WriteLine(out, "ret", "");
			}break;
			case IT::IDDATATYPE::STR:
			{
				Out::WriteLine(out, "mov eax, 0", "");
				Out::WriteLine(out, "mov eax, ", (const char*)IT.table[LT.table[i].idxTI].id, "");
				Out::WriteLine(out, "ret", "");
			}break;
			}
			i += 2;					// ������� �� ��������� ������ �.�. �� }
		}
		else if (LT.table[i].lexema[0] == LEX_ID && LT.table[i + 1].lexema[0] == LEX_SEMOCOLON)			// return l;
		{
			switch (LT.table[i].littype)
			{
			case LT::LITTYPE::N2:
			{
				Out::WriteLine(out, "mov eax, ", (const char*)IT.table[LT.table[i].idxTI].id, "");
				Out::WriteLine(out, "ret", "");
			}break;
			case LT::LITTYPE::N8:
			{
				Out::WriteLine(out, "mov eax, ", (const char*)IT.table[LT.table[i].idxTI].id, "");
				Out::WriteLine(out, "ret", "");
			}break;
			case LT::LITTYPE::SY:
			{
				Out::WriteLine(out, "mov eax, 0","");
				Out::WriteLine(out, "mov al, ", (const char*)IT.table[LT.table[i].idxTI].id, "");
				Out::WriteLine(out, "ret", "");
			}break;
			case LT::LITTYPE::S:
			{
				Out::WriteLine(out, "mov eax, OFFSET ", (const char*)IT.table[LT.table[i].idxTI].id, "");
				Out::WriteLine(out, "ret", "");
			}break;
			}
			i += 2;
		}

	}
	void proc_body(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		while (LT.table[i].lexema[0] != LEX_RETURN)
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
			case LEX_OUTPUT:	// ����� �� �������
			{
				output(i, out, LT, IT);
			}break;
			case LEX_IF:	// �������� ��������
			{
				if_block(i, out, LT, IT);
			}break;
			}
		}
		i++;							// ������� �� ������������ �������� - ����� ���� ��, ������� ��� ���������
		ret(i, out, LT, IT);
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
				char* name = new char[10];
				strcpy_s(name, 10, (const char*)IT.funcs[IT.table[LT.table[i+1].idxTI].Funcind].name);
				proc_head(i, out, LT, IT); //������������ �� ����������� ������ )
				proc_body(i, out, LT, IT);
				Out::WriteLine(out, (const char*)name, " ENDP", "");
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