// CourseProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Error.h"
#include "In.h"
#include "Parm.h"
#include "Log.h"
#include "LT.h"
#include "IT.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG lg = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		lg = Log::getlog(parm.log);
		Log::WriteLog(lg);
		Log::WriteParm(lg, parm);
	}
	catch (Error::ERROR er)
	{
		Log::WriteError(lg, er);
		std::cout << er.id << " " << er.message << " " << er.inext.line;
		Log::Close(lg);
	}
	system("pause");
	return 0;
}


