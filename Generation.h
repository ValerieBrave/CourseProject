#pragma once
#include "LT.h"
#include "IT.h"
#include "Out.h"
namespace Gen
{
	void start(Out::OUT out);
	void protos(Out::OUT out, IT::IdTable IT, LT::LexTable LT);
	void data(Out::OUT out, IT::IdTable IT);
	void Generate(Out::OUT out, LT::LexTable &LT, IT::IdTable &IT);
}