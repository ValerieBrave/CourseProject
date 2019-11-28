#include "pch.h"
#include "Error.h"
#include "LT.h"
namespace LT
{
	LexTable Create(int size)  //создать новую пустую таблицу лексем
	{
		if (size > LT_MAXSIZE)  throw ERROR_THROW(114)
		else
		{
			LexTable *rc = new LexTable(size);
			return *rc;
		}
	}
	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.current == LT_MAXSIZE) throw ERROR_THROW(114);
		lextable.table[lextable.current] = entry;
		lextable.current++;
	}
	Entry GetEntry(LexTable& lextable, int n)
	{
		Entry rc = lextable.table[n];
		return rc;
	}
	void Delete(LexTable& lextable)
	{
		delete &lextable;
	}

}