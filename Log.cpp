#include "pch.h"
#include <iostream>
#include <time.h>
#include "Log.h"

namespace Log
{
	LOG getlog(char logfile[])
	{
		LOG *rc = new LOG;
		rc->stream = new std::ofstream;
		rc->stream->open(logfile);
		if (!rc->stream->is_open()) throw ERROR_THROW(112)
		else
		{
			strcpy_s(rc->logfile, logfile);
		}
		return *rc;
	}
	void Close(LOG log)
	{
		log.stream->close();
	}
	void WriteLine(LOG log, const char* c, ...)
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
			*(log.stream) << line << '\n';
		}
	}
	void WriteLog(LOG log)
	{
		struct tm timeinfo;
		time_t rawtime = time(NULL);
		localtime_s(&timeinfo, &rawtime);
		char *tbuf = new char[100];
		sprintf_s(tbuf, 100, " Дата: %d.%d.%d Время: %d:%d:%d", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900,
			timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
		WriteLine(log, "----Протокол--- ", tbuf, "-----", "\n", "");
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		WriteLine(log, "-----Параметры-----\n", "");
		WriteLine(log, "-in:", parm.in, "\n", "");
		WriteLine(log, "-out:", parm.out, "\n", "");
		WriteLine(log, "-log:", parm.log, "\n", "");
	}
	void WriteIn(LOG log, In::IN in)
	{
		char *tbuf = new char[100];
		WriteLine(log, "------Исходные данные----\n", "");
		sprintf_s(tbuf, 100, "Количество символов: %d\n", in.size);
		WriteLine(log, tbuf, "");
		tbuf[0] = 0x00;
		sprintf_s(tbuf, 100, "Проигнорировано: %d\n", in.ignor);
		WriteLine(log, tbuf, "");
		tbuf[0] = 0x00;
		sprintf_s(tbuf, 100, "Количество строк: %d\n", in.lines);
		WriteLine(log, tbuf, "");
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		char *b1 = new char[30];
		char *b2 = new char[30];
		char *b3 = new char[30];
		sprintf_s(b1, 30, "Ошибка: %d : ", error.id);
		sprintf_s(b2, 30, "строка: %d ", error.inext.line);
		sprintf_s(b3, 30, "позиция: %d", error.inext.col);
		WriteLine(log, b1, error.message, b2, b3, "");
	}
}