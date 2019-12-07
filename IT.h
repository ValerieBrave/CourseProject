#pragma once
#include <iostream>
#include <algorithm>
#include "Parse.h"
#include "Log.h"
#define ID_MAXSIZE 5               //максимальное количество символов в идентификаторе
#define IT_MAXSIZE 4096            //максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT 0x00000000  //значение по умолчанию для типа integer
#define TI_STR_DEFAULT 0x00        //значение по умолчанию для типа string
#define TI_NULLIDX 0xffffffff      //нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE 255         
namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2, SYM = 3, DEF = 4 };  //типы данных идентификаторов: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, LIB = 5, DF = 6 };//типы идентификаторов: переменная, функция, параметр, литерал, библиотечная функция, дефолтное

	struct Entry
	{
		int idxfirstLE;                   // индекс первой строки в таблице лексем
		int LTind;							//  индекс первого появления в таблице лексем
		char id[ID_MAXSIZE + 1];              // идентификатор (автоматически усекается до ID_MAXSIZE)
		IDDATATYPE iddatatype;            // тип данных
		IDTYPE idtype;                    // тип идентификатора
		unsigned char* fullID;
		unsigned char* libname;			  // для имен библиотечных функций
		union
		{
			int vint;                    // если тип integer, тут будет число
			struct                       // если тип string, заполняется эта структура
			{
				unsigned char len;                //количество символов в строке типа string
				char str[TI_STR_MAXSIZE - 1];//сама строка
			} vstr;
			struct
			{
				char sym;
			} vsym;
		} value;                        //
		Entry()
		{
			this->idxfirstLE = 0;
			this->LTind = 0;
			*this->id = 0x00;
			this->iddatatype = IDDATATYPE::INT;
			this->idtype = IDTYPE::V;
			this->fullID = new unsigned char[2 * IT_MAXSIZE + 1];
			memset(this->fullID, ' ', sizeof(char)* (2 * IT_MAXSIZE + 1));
			this->libname = new unsigned char[20];
			this->value.vint = TI_INT_DEFAULT;
			*this->value.vstr.str = 0x00;
		}
	};
	struct IdTable
	{
		int capacity = IT_MAXSIZE; // емкость
		int current; // текущий размер
		Entry* table; // строки таблицы
		IdTable()
		{
			this->current = 0;
			this->table = new Entry[this->capacity];
		}
		IdTable(int size)
		{
			this->current = 0;
			this->table = new Entry[size];
		}
		void print(Log::LOG lg)
		{
			Log::WriteLine(lg, "--------Таблица идентификаторов-------", "");
			for (int i = 0; i < this->current; i++)
			{
				char *tbuf = new char[200];
				if (this->table[i].idtype == IDTYPE::L && this->table[i].iddatatype == IDDATATYPE::INT)
				{
					sprintf_s(tbuf, 200, "%d       %s       %d", this->table[i].idxfirstLE, this->table[i].fullID, this->table[i].value.vint);
				}
				else if (this->table[i].idtype == IDTYPE::L && this->table[i].iddatatype == IDDATATYPE::STR)
				{
					sprintf_s(tbuf, 200, "%d       %s       %s", this->table[i].idxfirstLE, this->table[i].fullID, this->table[i].value.vstr.str);
				}
				else if (this->table[i].idtype == IDTYPE::LIB)
				{
					sprintf_s(tbuf, 200, "%d       %s", this->table[i].idxfirstLE, this->table[i].libname);
				}
				else sprintf_s(tbuf, 200, "%d       %s", this->table[i].idxfirstLE, this->table[i].fullID);
				Log::WriteLine(lg, tbuf, "");
				delete tbuf;
			}
		}
		int here(Entry en) //Entry en
		{
			bool here = false;
			int in = -1;
			int i = 0;
			if (this->current > 0)
			{
				while (!here && i < this->current)
				{
					here = !strcmp((const char*)this->table[i].fullID, (const char*)en.fullID);
					if (here) in = i;
					i++;
				}
			} // fullID - имя идентификатора с префиксом, для учета области видимости
			return in; // вернет индекс вхождения в таблицу ИДЕНТИФИКАТОРОВ
		}
	};
	IdTable Create();
	void Add(IdTable &idtab, Entry en);
	Entry GetEntry(IdTable &idtab, int n);
	void Delete(IdTable &idtab);
}