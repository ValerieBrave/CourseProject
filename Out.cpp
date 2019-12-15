#include "pch.h"
#include <iostream>
#include "Error.h"
#include "Out.h"
namespace Out
{
	OUT getout(char outfile[])
	{
		OUT *rc = new OUT;
		rc->stream = new std::ofstream;
		rc->stream->open(outfile);
		if (!rc->stream->is_open()) throw ERROR_THROW(112)
		else
		{
			strcpy_s(rc->outfile, outfile);
		}
		return *rc;
	}
	void Close(OUT log)
	{
		log.stream->close();
	}
	void WriteLine(OUT out, const char* c, ...)
	{
		const char** str = &c;
		int len = 0;
		while (**str != 0x00)
		{
			len += strlen(*str);
			str++;
		}
		if (len >= 0)
		{
			char *line = new char[len + 1];
			line[0] = 0x00;
			str = &c;
			while (**str != 0x00)
			{
				strcat_s(line, strlen(*str) + strlen(line) + 1, *str);
				str++;
			}
			*(out.stream) << line << '\n';
		}
	}
}