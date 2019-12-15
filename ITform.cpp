#include "pch.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "Error.h"
#include "IT.h"
#include "ITform.h"
namespace Form
{
	IT::IDDATATYPE define_dtype(Parse::Words all_units, LT::LexTable LT, int position)
	{
		IT::IDDATATYPE dtype = IT::IDDATATYPE::DEF;
		while (*LT.table[position].lexema != 't' && position != 0) position--;
		if (!strcmp((const char*)all_units.words[LT.table[position].globalIndex], "string")) dtype = IT::IDDATATYPE::STR;
		else if (!strcmp((const char*)all_units.words[LT.table[position].globalIndex], "integer")) dtype = IT::IDDATATYPE::INT;
		if (dtype == IT::IDDATATYPE::DEF) throw ERROR_THROW_IN(118, LT.table[position].sn, position)
			return dtype;
	}
	IT::IDTYPE define_type(LT::LexTable LT, int position) // тип идентификатора КРОМЕ ЛИТЕРАЛОВ
	{
		IT::IDTYPE type = IT::IDTYPE::DF;
		if (*LT.table[position - 2].lexema == LEX_NEW) type = IT::IDTYPE::V; // объявление переменной
		if (*LT.table[position - 2].lexema == LEX_LEFTHESIS || *LT.table[position - 2].lexema == LEX_COMMA) type = IT::IDTYPE::P; // объявление параметра
		if (*LT.table[position - 1].lexema == LEX_FUNCTION || *LT.table[position + 1].lexema == LEX_LEFTHESIS) type = IT::IDTYPE::F; // объявление функции
		if (type == IT::IDTYPE::DF) throw ERROR_THROW_IN(119, LT.table[position].sn, position)
			return type;
	}
	void AddPref(unsigned char* prefix, LT::LexTable LT, Parse::Words all_units, IT::Entry &en, int i)
	{
		int k = 0;
		int fullLen = strlen((const char*)prefix) + strlen((const char*)all_units.words[LT.table[i].globalIndex]);//+1
		for (; k < strlen((const char*)prefix); k++) en.fullID[k] = prefix[k];
		en.fullID[k++] = '~';
		for (; k < fullLen + 1; k++) en.fullID[k] = all_units.words[LT.table[i].globalIndex][k - strlen((const char*)prefix) - 1]; // поменять индексы
		en.fullID[k] = 0x00;
	}
	int checkNum8(LT::LexTable LT, Parse::Words all_units, int position)//текущая позиция в таблице лексем
	{
		if (strlen((const char*)all_units.words[LT.table[position].globalIndex]) > 11) throw ERROR_THROW(116);
		char* end;
		long value = strtol((const char*)all_units.words[LT.table[position].globalIndex], &end, 8);
		if (value > INT_MAX || value < INT_MIN) value = TI_INT_DEFAULT;
		return (int)value;
	}
	int checkNum2(LT::LexTable LT, Parse::Words all_units, int position)//текущая позиция в таблице лексем
	{
		if (strlen((const char*)all_units.words[LT.table[position].globalIndex]) > 31) throw ERROR_THROW(116);
		char* end;
		long value = strtol((const char*)all_units.words[LT.table[position].globalIndex], &end, 2);
		if (value > INT_MAX || value < INT_MIN) value = TI_INT_DEFAULT;
		return (int)value;
	}
	void fillInVstr(LT::LexTable LT, IT::Entry &en, Parse::Words all_units, int position)
	{
		if (strlen((const char*)all_units.words[LT.table[position].globalIndex]) > TI_STR_MAXSIZE + 2) throw ERROR_THROW(117);
		strcpy_s(en.value.vstr.str, (const char*)all_units.words[LT.table[position].globalIndex]);
		en.value.vstr.len = (unsigned char)strlen(en.value.vstr.str);
	}
	void fillInVsym(LT::LexTable LT, IT::Entry &en, Parse::Words all_units, int position)
	{
		if (strlen((const char*)all_units.words[LT.table[position].globalIndex]) > 3) throw ERROR_THROW(116);
		en.value.vsym.sym = all_units.words[LT.table[position].globalIndex][1];
	}
	void genStrName(IT::Entry &en, int glob)
	{
		unsigned char* name = new unsigned char[8];
		sprintf_s((char*)name, 8, "st%d", glob);
		strcpy_s(en.id, (const char*)name);
		strcpy_s((char*)en.fullID, 2 * ID_MAXSIZE - 1, (const char*)name);
	}
	void genSymName(IT::Entry &en, int glob)
	{
		unsigned char* name = new unsigned char[8];
		sprintf_s((char*)name, 8, "sy%d", glob);
		strcpy_s(en.id, (const char*)name);
		strcpy_s((char*)en.fullID, 2 * ID_MAXSIZE - 1, (const char*)name);
	}
	void genNumName(IT::Entry &en, int glob)
	{
		unsigned char* name = new unsigned char[8];
		sprintf_s((char*)name, 8, "nu%d", glob);
		strcpy_s(en.id, (const char*)name);
		strcpy_s((char*)en.fullID, 2 * ID_MAXSIZE - 1, (const char*)name);
	}
	IT::IdTable getIDTable(LT::LexTable &LT, Parse::Words all_units)
	{
		IT::IdTable IDTab = IT::IdTable(LT.current);
		unsigned char* prefix = new unsigned char[2 * ID_MAXSIZE + 1];
		bool if_flag = false, if_pref = false;
		for (int i = 0; i < LT.current; i++) // из всей таблицы лексем ищем идентификаторы
		{
			
			if (*LT.table[i].lexema == LEX_FUNCTION)
			{
				prefix = all_units.words[LT.table[i + 1].globalIndex]; //  нашли префикс для идентификаторов
			}
			else if (*LT.table[i].lexema == LEX_ENTER)
			{
				prefix = all_units.words[LT.table[i].globalIndex];
			}
			/*else if (*LT.table[i].lexema == LEX_IF)
			{
				if_flag = true;
			}
			else if (*LT.table[i].lexema == LEX_ELSE)
			{
				sprintf_s((char*)prefix, 8, "%s%d", all_units.words[LT.table[i].globalIndex], i);
			}
			else if (*LT.table[i].lexema == LEX_LEFTBRACE && if_flag)
			{
				if_pref = true;
				sprintf_s((char*)prefix, 8, "if%d", i);
			}
			else if (*LT.table[i].lexema == LEX_BRACELET && if_flag)
			{
				if_flag = false;
				if_pref = false;
			}*/
			if (LT.table[i].idxTI != TI_NULLIDX) // если элемент - идентификатор 
			{
				if (LT.table[i].littype == LT::LITTYPE::NOT) //НЕ ЛИТЕРАЛ => переменная либо имя функции
				{
					IT::Entry en = IT::Entry();
					if(if_flag == true && if_pref==false) AddPref(prefix, LT, all_units, en, i); // к имени добавляет префикс
					else if(if_flag == true && if_pref==true)  AddPref(prefix, LT, all_units, en, i);
					else if(if_flag == false && if_pref == false) AddPref(prefix, LT, all_units, en, i);
					if (*LT.table[i + 1].lexema == LEX_LEFTHESIS) strcpy_s((char*)en.fullID, 2 * ID_MAXSIZE - 1, (const char*)all_units.words[LT.table[i].globalIndex]);
					// дальше проверка на вхождение
					if (IDTab.here(en) == -1) // если вхождений нет
					{
						strcpy_s(en.id, (const char*)all_units.words[LT.table[i].globalIndex]);
						IT::IDTYPE idtype = define_type(LT, i);
						if (idtype == IT::IDTYPE::F) strcpy_s((char*)en.fullID, 2 * ID_MAXSIZE - 1, (const char*)en.id);
						en.idxfirstLE = LT.table[i].sn;
						en.LTind = i;
						en.iddatatype = IT::IDDATATYPE::DEF;
						if (idtype == IT::IDTYPE::F)
						{
							en.idtype = IT::IDTYPE::F;
							IDTab.funcs[IDTab.fcurrent] = IT::Func(i, all_units.words[LT.table[i].globalIndex]);
							en.Funcind = IDTab.fcurrent;
							IDTab.fcurrent++;
						}
						else en.idtype = IT::IDTYPE::DF;
						en.value.vint = TI_INT_DEFAULT;
						LT.table[i].idxTI = IDTab.current;
						IT::Add(IDTab, en);
					}
					else LT.table[i].idxTI = IDTab.here(en);
				}
				else if (LT.table[i].littype == LT::LITTYPE::F)
				{
					IT::Entry en = IT::Entry();
					en.idxfirstLE = LT.table[i].sn;
					en.LTind = i;
					en.idtype = IT::IDTYPE::LIB;
					strcpy_s((char*)en.libname, 20, (const char*)all_units.words[LT.table[i].globalIndex]);
					LT.table[i].idxTI = IDTab.current;
					IT::Add(IDTab, en);
				}
				else if (LT.table[i].littype == LT::LITTYPE::N2) // численный литерал
				{
					IT::Entry en = IT::Entry();
					en.idxfirstLE = LT.table[i].sn;
					en.LTind = i;
					en.iddatatype = IT::IDDATATYPE::INT;
					en.idtype = IT::IDTYPE::L;
					en.value.vint = checkNum2(LT, all_units, i);
					genNumName(en, LT.table[i].globalIndex);
					LT.table[i].idxTI = IDTab.current;
					IT::Add(IDTab, en);
				}
				else if (LT.table[i].littype == LT::LITTYPE::N8)
				{
					IT::Entry en = IT::Entry();
					en.idxfirstLE = LT.table[i].sn;
					en.LTind = i;
					en.iddatatype = IT::IDDATATYPE::INT;
					en.idtype = IT::IDTYPE::L;
					en.value.vint = checkNum8(LT, all_units, i);
					genNumName(en, LT.table[i].globalIndex);
					LT.table[i].idxTI = IDTab.current;
					IT::Add(IDTab, en);
				}
				else if (LT.table[i].littype == LT::LITTYPE::S) // строковый литерал
				{
					IT::Entry en = IT::Entry();
					en.LTind = i;
					en.idxfirstLE = LT.table[i].sn;
					en.iddatatype = IT::IDDATATYPE::STR;
					en.idtype = IT::IDTYPE::L;
					fillInVstr(LT, en, all_units, i);
					genStrName(en, LT.table[i].globalIndex);
					LT.table[i].idxTI = IDTab.current;
					IT::Add(IDTab, en);
				}
				else if (LT.table[i].littype == LT::LITTYPE::SY)
				{
					IT::Entry en = IT::Entry();
					en.LTind = i;
					en.idxfirstLE = LT.table[i].sn;
					en.iddatatype = IT::IDDATATYPE::SYM;
					en.idtype = IT::IDTYPE::L;
					fillInVsym(LT, en, all_units, i);
					genSymName(en, LT.table[i].globalIndex);
					LT.table[i].idxTI = IDTab.current;
					IT::Add(IDTab, en);
				}
			}
		}
		return IDTab;
	}
}