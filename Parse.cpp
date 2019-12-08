#include "pch.h"
#include <iostream>
#include "Parse.h"
#include "IT.h"

namespace Parse
{
	LT::LexTable auto_check(Words &all_units, FST::FST_lexems *auto_array, int auto_amount, In::IN in, Log::LOG lg)
	{
		/*Words all_units = find_lexems(in);*/  //помещаем все выделенные лексемы в all_units
		LT::LexTable Tab = LT::Create(all_units.size);
		int i = 0, line = 0, ids = 0, exp=0; // i- по лексемам, line-строки, ids-количество идентификаторов, ids - для массива указателей на выражения
		while (i < all_units.size) // по всем выделенным лексемам
		{
			if ((unsigned char)(*all_units.words[i]) == IN_CODE_ENDL) line++; // перенос строки
			else if (in.code[(unsigned char)(*all_units.words[i])] == In::IN::R) // переносимый разделитель
			{
				switch (*all_units.words[i])
				{
				case LEX_SEMOCOLON: LT::Add(Tab, LT::Entry(LEX_SEMOCOLON, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "  ")); break;
				case LEX_COMMA: LT::Add(Tab, LT::Entry(LEX_COMMA, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "  ")); break;
				case LEX_LEFTBRACE: LT::Add(Tab, LT::Entry(LEX_LEFTBRACE, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "  ")); break;
				case LEX_BRACELET: LT::Add(Tab, LT::Entry(LEX_BRACELET, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "  ")); break;
				case LEX_LEFTHESIS: LT::Add(Tab, LT::Entry(LEX_LEFTHESIS, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "  ")); break;
				case LEX_RIGHTHESIS:LT::Add(Tab, LT::Entry(LEX_RIGHTHESIS, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "  ")); break;
				case LEX_EQUALS:
				{
					if (i + 1 < all_units.size && *all_units.words[i + 1] == LEX_EQUALS)
					{
						LT::Add(Tab, LT::Entry(LEX_DEQUALS, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "==")); 
						i++;
					}
					else {
						LT::Add(Tab, LT::Entry(LEX_EQUALS, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "= "));
						Tab.expressions.expr[exp] = Tab.current; exp++; Tab.expressions.current++;
					}
						
				}break;
				case LEX_NOT:
				{
					if (i + 1 < all_units.size && *all_units.words[i + 1] == LEX_EQUALS)
					{
						LT::Add(Tab, LT::Entry(LEX_NEQUALS, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "!="));
						i++;
					}
					else throw ERROR_THROW_IN(601, line, i);
				} break;
				case '<':
				{
					if (i + 1 < all_units.size && *all_units.words[i + 1] == LEX_EQUALS)
					{
						LT::Add(Tab, LT::Entry(LEX_ELESS, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "<="));
						i++;
					}
					else LT::Add(Tab, LT::Entry(LEX_LESS, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "< "));
				}break;
				case '>':
				{
					if (i + 1 < all_units.size && *all_units.words[i + 1] == LEX_EQUALS)
					{
						LT::Add(Tab, LT::Entry(LEX_EMORE, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, ">="));
						i++;
					}
					else LT::Add(Tab, LT::Entry(LEX_MORE, line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "> "));
				}break;
				}
			}
			else if (in.code[(unsigned char)(*all_units.words[i])] != In::IN::B) //не непереносимый символ=>проверка автоматом
			{
				bool parsed = false;
				int k = 0;
				while (k < auto_amount && !parsed) // && !parsed
				{
					auto_array[k].fst.reinit((const char*)all_units.words[i]);
					if (parsed = FST::execute(auto_array[k].fst))
					{
						switch (auto_array[k].fst.type)// какой автомат сработал
						{
						case FST::FST::LEXEM: LT::Add(Tab, LT::Entry(auto_array[k].lexem[0], line, i, LT_TI_NULLIDX, LT::LITTYPE::NOT, "  ")); break;
						case FST::FST::IDENTIFICATOR:
						{
							if (strlen(auto_array[k].fst.string) >= ID_MAXSIZE) all_units.words[i] = cutID(ID_MAXSIZE, (unsigned char*)auto_array[k].fst.string);
							LT::Add(Tab, LT::Entry(auto_array[k].lexem[0], line, i, ids, LT::LITTYPE::NOT, "  ")); // добавили в таблицу лексем
							ids++;
						}	break;
						case FST::FST::LIB_NAME:
						{
							LT::Add(Tab, LT::Entry(auto_array[k].lexem[0], line, i, ids, LT::LITTYPE::F, "  ")); // добавили в таблицу лексем
							ids++;
						}	break;
						case FST::FST::NUM8_LITERAL:
						{
							LT::Add(Tab, LT::Entry(auto_array[k].lexem[0], line, i, ids, LT::LITTYPE::N8, "  ")); // добавили в таблицу лексем
							ids++;
						}	break;
						case FST::FST::NUM2_LITERAL:
						{
							LT::Add(Tab, LT::Entry(auto_array[k].lexem[0], line, i, ids, LT::LITTYPE::N2, "  ")); // добавили в таблицу лексем
							ids++;
						}	break;
						case FST::FST::STR_LITERAL:
						{
							LT::Add(Tab, LT::Entry(auto_array[k].lexem[0], line, i, ids, LT::LITTYPE::S, "  ")); // добавили в таблицу лексем
							ids++;
						}	break;
						case FST::FST::SYM_LITERAL:
						{
							LT::Add(Tab, LT::Entry(auto_array[k].lexem[0], line, i, ids, LT::LITTYPE::SY, "  ")); // добавили в таблицу лексем
							ids++;
						}	break;
						}
					}
					k++;
				}
				if (parsed == false) throw ERROR_THROW_IN(113, line, 0);
			}
			i++;
		}
		return Tab;
	}
	Words find_lexems(In::IN in)
	{
		Words* rc = new Words[LT_MAXSIZE];
		unsigned char* pos = in.text;
		int i = 0;
		while (*pos != 0x00)
		{
			rc->words[i] = parse(pos, in);
			pos += strlen((const char*)rc->words[i]);
			i++;
		}
		rc->size = i;
		return *rc;
	}
	unsigned char* parse(unsigned char* pos, In::IN in)
	{
		unsigned char* rc = new unsigned char[strlen((const char*)in.text)];
		int i = 0;
		if (in.code[pos[0]] == In::IN::Q)//"
		{
			rc[0] = pos[0];
			i++;
			while (in.code[pos[i]] != In::IN::Q)
			{
				rc[i] = pos[i];
				i++;
			}
			rc[i] = pos[i];
			rc[i + 1] = 0x00;
		}
		else if (in.code[pos[0]] == In::IN::OQ)//'
		{
			rc[0] = pos[0];
			i++;
			while (in.code[pos[i]] != In::IN::OQ)
			{
				rc[i] = pos[i];
				i++;
			}
			rc[i] = pos[i];
			rc[i + 1] = 0x00;
		}
		else if (in.code[pos[0]] == In::IN::R || in.code[pos[0]] == In::IN::B)
		{
			rc[0] = pos[0];
			rc[1] = 0x00;
		}
		else
		{
			while (pos[i] != 0x00 && in.code[pos[i]] != In::IN::B && in.code[pos[i]] != In::IN::R)
			{
				rc[i] = pos[i];
				i++;
			}
			rc[i] = 0x00;
		}
		return rc; // возвращает отдельную лексему
	}
	unsigned char* cutID(int maxsize, unsigned char* str) // обрезает длинный идентификатор
	{
		str[maxsize] = 0x00;
		return str;
	}
}
