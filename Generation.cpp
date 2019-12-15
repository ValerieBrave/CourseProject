#include "pch.h"
#include "Generation.h"
namespace Gen
{
	void start(Out::OUT out)
	{
		Out::WriteLine(out, ".586", "");
		Out::WriteLine(out, ".MODEL flat, stdcall", "");
		Out::WriteLine(out, "includelib kernel32.lib", "");
		Out::WriteLine(out, "includelib msvcrt.lib", "");
	}
	void Generate(Out::OUT out, LT::LexTable LT, IT::IdTable IT)
	{
		start(out);
	}
}