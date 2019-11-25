#include "pch.h"
#include <iostream>
#include <string>
#include "Parm.h"
#include "Error.h"
namespace Parm
{
	char* substring(char* str, int start, int len)
	{
		char* rc = new char[len + 1];
		for (int i = 0; i < len; i++) rc[i] = str[i];
		rc[len] = 0x00;
		return rc;
	}
	char* write_parm(int argc, char* argv[], const char* key)
	{
		char* rc = nullptr;
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(substring(argv[i], 0, strlen(key)), key) == 0)
			{
				if (strlen(argv[i] + strlen(key)) > PARM_MAX_SIZE) throw ERROR_THROW(104);
				rc = argv[i] + strlen(key);
			}
		}
		return rc;
	}
	PARM getparm(int argc, char* argv[])
	{
		PARM *rc = new PARM;
		switch (argc)
		{
		case 0: throw ERROR_THROW(100); break;
		case 1: throw ERROR_THROW(100); break;
		default:
		{
			if (write_parm(argc, argv, PARM_IN) == nullptr) throw ERROR_THROW(100);
			strcpy_s(rc->in, write_parm(argc, argv, PARM_IN));

			if (write_parm(argc, argv, PARM_OUT) == nullptr)
			{
				strcpy_s(rc->out, rc->in);
				strcat_s(rc->out, PARM_OUT_DEFAULT_EXT);
			}
			else strcpy_s(rc->out, write_parm(argc, argv, PARM_OUT));

			if (write_parm(argc, argv, PARM_LOG) == nullptr)
			{
				strcpy_s(rc->log, rc->in);
				strcat_s(rc->log, PARM_LOG_DEFAULT_EXT);
			}
			else strcpy_s(rc->log, write_parm(argc, argv, PARM_LOG));
		}
		break;
		}
		return *rc;
	}
}