#pragma once
#define PARM_IN  "-in:"  // ключ для файла исходного кода
#define PARM_OUT  "-out:"  // ключ для файла объектного кода
#define PARM_LOG  "-log:"   // ключ для файла журнала
#define PARM_MAX_SIZE 300    //макс. длина строки параметра
#define PARM_OUT_DEFAULT_EXT  ".out"  // расширение по умолчанию для объектного
#define PARM_LOG_DEFAULT_EXT  ".log"   // расширение по умолчанию для протокола

namespace Parm
{
	struct PARM
	{
		char in[PARM_MAX_SIZE]; // имя файла исходного кода
		char out[PARM_MAX_SIZE]; // имя для объектного кода
		char log[PARM_MAX_SIZE]; // имя для файла протокола
		PARM()
		{
			this->in[0] = 0x00;
			this->out[0] = 0x00;
			this->log[0] = 0x00;
		}
	};

	PARM getparm(int argc, char* argv[]);
};