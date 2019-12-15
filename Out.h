#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
namespace Out
{
	struct OUT
	{
		char outfile[PARM_MAX_SIZE];
		std::ofstream * stream; // �������� ����� ����� ����������
	};
	static const OUT INITOUT = { "", NULL };
	OUT getout(char outfile[]);
	void Close(OUT log);
	void WriteLine(OUT out, const char* c, ...);
}