#include "pch.h"
#include "IT.h"
#include "LT.h"
#include "Error.h"

namespace IT
{
	IdTable Create()
	{
		IdTable* rc = new IdTable();
		return *rc;
	}
	void Add(IdTable &idtab, Entry en)
	{
		if (idtab.current == IT_MAXSIZE) throw ERROR_THROW(155);
		idtab.table[idtab.current] = en;
		idtab.current++;
	}
	Entry GetEntry(IdTable &idtab, int n)
	{
		Entry rc = idtab.table[n];
		return rc;
	}
	void Delete(IdTable &idtab)
	{
		delete &idtab;
	}

}