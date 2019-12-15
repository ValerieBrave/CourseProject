#pragma once
#include "LT.h"
#include "IT.h"
#include "Out.h"
namespace Gen
{
	void start(Out::OUT out);
	void Generate(Out::OUT out, LT::LexTable LT, IT::IdTable IT);
}