#pragma once
#include "Parse.h"
#include "IT.h"
#include "LT.h"
namespace Form
{
	IT::IdTable getIDTable(LT::LexTable &LT, Parse::Words all_units);
	IT::IDDATATYPE define_dtype(Parse::Words all_units, LT::LexTable LT, int position);
	IT::IDTYPE define_type(LT::LexTable LT, int position);
	int checkNum8(LT::LexTable LT, Parse::Words all_units, int position);
	int checkNum2(LT::LexTable LT, Parse::Words all_units, int position);
	void fillInVstr(LT::LexTable LT, IT::Entry &en, Parse::Words all_units, int position);
	void fillInVsym(LT::LexTable LT, IT::Entry &en, Parse::Words all_units, int position);
	void genNumName(IT::Entry &en, int glob);
	void genStrName(IT::Entry &en, int glob);
	void genSymName(IT::Entry &en, int glob);
};