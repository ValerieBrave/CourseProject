#include "pch.h"
#include <stack>
#include "Semantica.h"

namespace Sem
{
	void to_polish(LT::LexTable &LT)
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
}