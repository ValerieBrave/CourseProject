#include "pch.h"
#include <stack>
#include "Semantica.h"
#include "Error.h"
#include "Parse.h"
#include "LT.h"
#include "IT.h"

namespace Sem
{
	void to_polish(LT::LexTable &LT, IT::IdTable IT, Parse::Words all_units)
	{
		for (int k = 0; k < LT.expressions.current; k++) // по всем выражениям; LT.expressions.expr[k] - позиция начала выражения
		{
			std::stack <LT::Entry> params;
			int i = LT.expressions.expr[k];
			if (LT.table[i + 1].lexema[0] != LEX_SEMOCOLON &&
				LT.table[i + 1].lexema[0] != LEX_LEFTHESIS) // если это не одна лексема и не вызов функции
			{
				switch (LT.table[LT.expressions.expr[k] + 1].lexema[0])// какая лексема следующая?
				{
				case 'v':
				{
					LT::Entry temp = LT::GetEntry(LT, i + 2);
					LT.table[i + 2] = LT.table[i + 1];
					LT.table[i + 1] = temp;
				}break;
				case 'L':
				{
					LT::Entry temp = LT::GetEntry(LT, i + 2);
					LT.table[i + 2] = LT.table[i + 1];
					LT.table[i + 1] = temp;
				}break;

				case 'M':
				{
					LT::Entry temp = LT::GetEntry(LT, i + 2);
					LT.table[i + 2] = LT.table[i + 1];
					LT.table[i + 1] = temp;
				}break;
				case 'D':
				{
					LT::Entry temp = LT::GetEntry(LT, i + 2);
					LT.table[i + 2] = LT.table[i + 1];
					LT.table[i + 1] = temp;
				}break;
				case 'N':
				{
					LT::Entry temp = LT::GetEntry(LT, i + 2);
					LT.table[i + 2] = LT.table[i + 1];
					LT.table[i + 1] = temp;
				}break;
				}
			}
			else if (LT.table[i + 1].lexema[0] == LEX_LEFTHESIS)
			{
				LT::Entry func = LT::GetEntry(LT, i); // вызов функции
				if (LT.table[i + 2].lexema[0] == LEX_RIGHTHESIS) // если у функции нет параметров - скобки уходят, появляется @ и #
				{
					LT.table[i] =  LT::Entry('@', LT.table[i].sn);
					LT.table[i + 1] = func;
					LT.table[i + 2] = LT::Entry('#', LT.table[i].sn);
				}
				else
				{
					int begin = i; i++;
					while (LT.table[i].lexema[0] != LEX_RIGHTHESIS)
					{
						if (LT.table[i].lexema[0] == LEX_LITERAL || LT.table[i].lexema[0] == LEX_ID)
						{
							params.push(LT.table[i]);
						}
						i++;
					}
					int end = i;
					while (!params.empty())
					{
						LT.table[begin] = params.top();
						params.pop();
						begin++;
					}
					LT.table[begin] = LT::Entry('@', LT.table[begin].sn); begin++;
					LT.table[begin] = func; begin++;
					while (begin <= i)
					{
						LT.table[begin] = LT::Entry('#', LT.table[begin].sn); begin++;
					}
				}
			}
		}
	}
	IT::PARMTYPE define_ret(LT::LexTable LT, int LTind, Parse::Words all_units)
	{
		IT::PARMTYPE ret = IT::PARMTYPE::NO;
		while (*LT.table[LTind].lexema != 't' && LTind != 0) LTind--;
		if (!strcmp((const char*)all_units.words[LT.table[LTind].globalIndex], "integer")) ret = IT::PARMTYPE::I;
		else if (!strcmp((const char*)all_units.words[LT.table[LTind].globalIndex], "string")) ret = IT::PARMTYPE::SR;
		else if (!strcmp((const char*)all_units.words[LT.table[LTind].globalIndex], "symbol")) ret = IT::PARMTYPE::SM;
		if (ret == IT::PARMTYPE::NO) throw ERROR_THROW(118)
			return ret;
	}
	void define_params(IT::Func &func, LT::LexTable LT, IT::IdTable &IT, Parse::Words all_units)
	{
		int pos = func.LTposition;
		while (LT.table[pos].lexema[0] != LEX_RIGHTHESIS)
		{
			if (LT.table[pos].lexema[0] == 't')
			{
				IT.table[LT.table[pos].idxTI].idtype = IT::IDTYPE::P;
				if (!strcmp((const char*)all_units.words[LT.table[pos].globalIndex], "integer"))
				{
					IT.table[LT.table[pos+1].idxTI].iddatatype = IT::IDDATATYPE::INT;
					func.types[func.params] = IT::PARMTYPE::I;
					func.params++;
				}
				else if (!strcmp((const char*)all_units.words[LT.table[pos].globalIndex], "string"))
				{
					IT.table[LT.table[pos+1].idxTI].iddatatype = IT::IDDATATYPE::STR;
					func.types[func.params] = IT::PARMTYPE::SR;
					func.params++;
				}
				else if (!strcmp((const char*)all_units.words[LT.table[pos].globalIndex], "symbol"))
				{
					IT.table[LT.table[pos+1].idxTI].iddatatype = IT::IDDATATYPE::SYM;
					func.types[func.params] = IT::PARMTYPE::SM;
					func.params++;
				}
			}
			else if (LT.table[pos].lexema[0] == LEX_LITERAL)
			{
				IT.table[LT.table[pos].idxTI].idtype = IT::IDTYPE::P;
				switch (LT.table[pos].littype)
				{
				case LT::LITTYPE::N2: 
				{
					func.types[func.params] = IT::PARMTYPE::I;
					func.params++;
				}break;
				case LT::LITTYPE::N8:
				{
					func.types[func.params] = IT::PARMTYPE::I;
					func.params++;
				}break;
				case LT::LITTYPE::S:
				{
					func.types[func.params] = IT::PARMTYPE::SR;
					func.params++;
				}break;
				case LT::LITTYPE::SY:
				{
					func.types[func.params] = IT::PARMTYPE::SM;
					func.params++;
				}break;
				}
			}
			pos++;
		}
		if (func.params == 0) func.types[0] = IT::PARMTYPE::NO;
	}
	void define_dtype(LT::LexTable LT, IT::Entry &en, Parse::Words all_units)
	{
		if (!(strcmp((const char*)all_units.words[LT.table[en.LTind].globalIndex], "integer"))) 
		{
			en.iddatatype = IT::IDDATATYPE::INT; 
			en.value.vint = 0;
		}
		else if (!(strcmp((const char*)all_units.words[LT.table[en.LTind].globalIndex], "string"))) 
		{
			en.iddatatype = IT::IDDATATYPE::STR; 
			en.value.vstr.len = 1;
			en.value.vstr.str[0] = 0x00;
		}
		else if (!(strcmp((const char*)all_units.words[LT.table[en.LTind].globalIndex], "symbol"))) 
		{
			en.iddatatype = IT::IDDATATYPE::SYM; 
			en.value.vsym.sym = ' ';
		}
	}
	void CompleteIDTab(LT::LexTable LT, IT::IdTable &IT, Parse::Words all_units)
	{
		for (int i = 0; i < IT.current; i++) // по всей таблице идентификаторов
		{
			if (IT.table[i].iddatatype == IT::IDDATATYPE::DEF && LT.table[IT.table[i].LTind].littype == LT::LITTYPE::NOT) // не знаем тип, либо функция, либо переменная
			{
				if (IT.table[i].idtype == IT::IDTYPE::F) // функция=>определить тип и параметры
				{
					IT.funcs[IT.table[i].Funcind].ret = define_ret(LT, IT.table[i].LTind, all_units);
					IT.table[i].iddatatype = IT::IDDATATYPE::DEF;
					define_params(IT.funcs[IT.table[i].Funcind], LT, IT, all_units);
				}
				else if (IT.table[i].idtype == IT::IDTYPE::DF)		// переменная => определить тип и задать дефолтное значение
				{
					IT.table[i].idtype = IT::IDTYPE::V;
					define_dtype(LT, IT.table[i], all_units);
				}
			}
		}
	}
}