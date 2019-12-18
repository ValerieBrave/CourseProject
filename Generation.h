#pragma once
#include "LT.h"
#include "IT.h"
#include "Out.h"
namespace Gen
{
	void start(Out::OUT out);
	void protos(Out::OUT out, IT::IdTable IT, LT::LexTable LT);
	void data(Out::OUT out, IT::IdTable IT);
	void proc_head(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT);
	void expression(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT);
	void output(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT);
	void if_block(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT);
	void ret(int &i, Out::OUT out, LT::LexTable LT, IT::IdTable IT);
	void Generate(Out::OUT out, LT::LexTable &LT, IT::IdTable &IT);
}