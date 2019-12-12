#pragma once
#include "LT.h"
#include "IT.h"
namespace Sem
{
	IT::PARMTYPE define_ret(LT::LexTable LT, int LTind, Parse::Words all_units);
	void define_params(IT::Func &func, LT::LexTable LT, IT::IdTable &IT, Parse::Words all_units);
	void define_dtype(LT::LexTable LT, IT::Entry &en, Parse::Words all_units);
	void to_polish(LT::LexTable &LT, IT::IdTable IT, Parse::Words all_units);
	void CompleteIDTab(LT::LexTable LT, IT::IdTable &IT, Parse::Words all_units);
}