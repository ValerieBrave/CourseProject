#pragma once
#include <iostream>
#include "Log.h"

#define LEXEMA_FIXSIZE 1 //фиксированный размер лексемы
#define LT_MAXSIZE 4096  //максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX 0xffffffff  //нет элемента таблицы идентификаторов
#define LEX_ENTER 'e'      //лексема для main
#define LEX_INTEGER 't'  //лексема для integer
#define LEX_STRING 't'  //лексема для string
#define LEX_SYMBOL 't' // лексема для symbol
#define LEX_ID 'i'  //лексема для идентификатора
#define LEX_LITERAL 'l'  //лексема для литерала
#define LEX_FUNCTION 'f'  //лексема для function
#define LEX_NEW 'n'  //лексема для declare
#define LEX_RETURN 'r'  //лексема для return
#define LEX_OUTPUT 'u'  //лексема для print
#define LEX_SEMOCOLON ';'  //лексема для ;
#define LEX_COMMA ','  //лексема для ,
#define LEX_LEFTBRACE '{'  //лексема для {
#define LEX_BRACELET '}'  //лексема для }
#define LEX_LEFTHESIS '('  //лексема для (
#define LEX_RIGHTHESIS ')'  //лексема для )
#define LEX_LESS 'v'  //лексема для <
#define LEX_MORE 'v'  //лексема для >
#define LEX_ELESS 'L' // <=
#define LEX_EMORE 'M' // >=
#define LEX_NOT '!'  //лексема для !
#define LEX_EQUALS '='
#define LEX_DEQUALS 'E' //==
#define LEX_NEQUALS 'N' // !=
#define LEX_STRCPY 'b' // библиотечные функции
#define LEX_STRCAT 'b'

namespace LT
{
	enum LITTYPE { NOT = 0, N = 1, S = 2, F = 3 };// тип литерала - не литерал \ численный \ строковый \ библиотечная функция
	struct Entry // строка таблицы лексем
	{
		char lexema[2]; // лексема
		int sn;                      // номер строки в исходном тексте
		int idxTI;                   // индекс в таблице идентификаторов или LT_TI_NULLIDX
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
	struct LexTable // экземпляр таблицы лексем
	{
		int maxsize;                 // емкость таблицы лексем < LT_MAXSIZE
		int size;                    // размер таблицы < maxsize
		int current;				 // сколько лексем в таблице уже есть
		Entry* table;                // массив строк таблицы лексем
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
			Log::WriteLine(lg, "----Все лексемы----\n", "");
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
			Log::WriteLine(lg, "----Ссылки на таблицу идентификаторов----\n", "");
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

	LexTable Create(int size);       //создать таблицу лексем
	void Add(LexTable& lextable, Entry entry);// добавить в таблицу строку
	Entry GetEntry(LexTable& lextable, int n);// получить строку с конкретным номером
	void Delete(LexTable& lextable);          // удалить таблицу лексем (освободить память)
};
