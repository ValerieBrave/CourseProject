#pragma once
#include "Parse.h"
#include "IT.h"
#include "LT.h"
namespace Sem
{
	IT::IdTable getIDTable(LT::LexTable &LT, Parse::Words all_units);
	IT::IDDATATYPE define_dtype(Parse::Words all_units, LT::LexTable LT, int position);
	IT::IDTYPE define_type(LT::LexTable LT, int position);
	int checkNum(LT::LexTable LT, Parse::Words all_units, int position);
	void fillInVstr(LT::LexTable LT, IT::Entry &en, Parse::Words all_units, int position);
	unsigned char* genNumName(int glob);
};