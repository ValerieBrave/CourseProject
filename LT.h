#pragma once
#include <iostream>
#include "Log.h"

#define LEXEMA_FIXSIZE 1 //������������� ������ �������
#define LT_MAXSIZE 4096  //������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX 0xffffffff  //��� �������� ������� ���������������
#define LEX_ENTER 'e'      //������� ��� main
#define LEX_INTEGER 't'  //������� ��� integer
#define LEX_STRING 't'  //������� ��� string
#define LEX_SYMBOL 't' // ������� ��� symbol
#define LEX_ID 'i'  //������� ��� ��������������
#define LEX_LITERAL 'l'  //������� ��� ��������
#define LEX_FUNCTION 'f'  //������� ��� function
#define LEX_NEW 'n'  //������� ��� declare
#define LEX_RETURN 'r'  //������� ��� return
#define LEX_OUTPUT 'u'  //������� ��� print
#define LEX_SEMOCOLON ';'  //������� ��� ;
#define LEX_COMMA ','  //������� ��� ,
#define LEX_LEFTBRACE '{'  //������� ��� {
#define LEX_BRACELET '}'  //������� ��� }
#define LEX_LEFTHESIS '('  //������� ��� (
#define LEX_RIGHTHESIS ')'  //������� ��� )
#define LEX_LESS 'v'  //������� ��� <
#define LEX_MORE 'v'  //������� ��� >
#define LEX_ELESS 'L' // <=
#define LEX_EMORE 'M' // >=
#define LEX_NOT '!'  //������� ��� !
#define LEX_EQUALS '='
#define LEX_DEQUALS 'E' //==
#define LEX_NEQUALS 'N' // !=
#define LEX_STRCPY 'b' // ������������ �������
#define LEX_STRCAT 'b'

namespace LT
{
	enum LITTYPE { NOT = 0, N = 1, S = 2, F = 3 };// ��� �������� - �� ������� \ ��������� \ ��������� \ ������������ �������
	struct Entry // ������ ������� ������
	{
		char lexema[2]; // �������
		int sn;                      // ����� ������ � �������� ������
		int idxTI;                   // ������ � ������� ��������������� ��� LT_TI_NULLIDX
		int globalIndex;
		char operation[3];
		int priority;
		LITTYPE littype;
		Entry()
		{
			*this->lexema = 0x00;
			this->sn = 0;
			this->idxTI = -3;
			this->globalIndex = 0;
			//this->operation = ' ';
			strcpy_s(this->operation, " ");
			this->priority = -1;
			this->littype = LITTYPE::NOT;
		}
		Entry(char lex, int line)
		{
			this->lexema[0] = lex;
			this->lexema[1] = 0x00;
			this->sn = line;
			this->idxTI = -3;
			this->globalIndex = 0;
			strcpy_s(this->operation, " ");
			this->priority = -1;
			this->littype = LITTYPE::NOT;
		}
		Entry(char lex, int line, int glob, int idXTI, LITTYPE ltype, const char oper[3], int prio)
		{
			this->lexema[0] = lex;
			this->lexema[1] = 0x00;
			this->sn = line;
			this->globalIndex = glob;
			this->idxTI = idXTI;
			this->littype = ltype;
			for (int i = 0; i < 3; i++) this->operation[i] = oper[i];
			this->priority = prio;
		}
	};
	struct LexTable // ��������� ������� ������
	{
		int maxsize;                 // ������� ������� ������ < LT_MAXSIZE
		int size;                    // ������ ������� < maxsize
		int current;				 // ������� ������ � ������� ��� ����
		Entry* table;                // ������ ����� ������� ������
		LexTable()
		{
			this->maxsize = LT_MAXSIZE;
			this->size = 0;
			this->current = 0;
			this->table = nullptr;
		}
		LexTable(int sz)
		{
			this->maxsize = LT_MAXSIZE;
			this->size = sz;
			this->current = 0;
			this->table = new Entry[sz];
		}
		void print_coded(Log::LOG lg)
		{
			Log::WriteLine(lg, "----��� �������----\n", "");
			int i = 0;
			while (i < this->current)
			{
				int ind = 0;
				char *line = new char[100];
				int cur_line = this->table[i].sn;
				while (this->table[i].sn == cur_line)
				{
					line[ind] = this->table[i].lexema[0];
					ind++;
					i++;
				}
				line[ind] = 0x00;
				char *tbuf = new char[200];
				sprintf_s(tbuf, 200, "%d   %s", cur_line, line);
				Log::WriteLine(lg, tbuf, "");
			}
			i = 0;
			Log::WriteLine(lg, "----������ �� ������� ���������������----\n", "");
			while (i < this->current)
			{
				if (this->table[i].idxTI != LT_TI_NULLIDX)
				{
					char *tbuf = new char[200];
					sprintf_s(tbuf, 200, " %d) %s - %d", this->table[i].sn, this->table[i].lexema, this->table[i].idxTI);
					Log::WriteLine(lg, tbuf, "");
				}
				i++;
			}
		}

	};

	LexTable Create(int size);       //������� ������� ������
	void Add(LexTable& lextable, Entry entry);// �������� � ������� ������
	Entry GetEntry(LexTable& lextable, int n);// �������� ������ � ���������� �������
	void Delete(LexTable& lextable);          // ������� ������� ������ (���������� ������)
};
