#include "pch.h"
#include "Error.h"
#include <iostream>
namespace Error
{
	//серии ошибок   0-99 - системные ошибки
	// 100-109 - ошибки параметров
	// 110-119 - ошибки открытия и чтения файлов
	ERROR errors[ERROR_MAX_ENTRY] = //таблица ошибок
	{
		ERROR_ENTRY(0,"Недопустимый код ошибки"), // код ошибки вне диапазона 0-ERROR_MAX_ENTRY
		ERROR_ENTRY(1,"Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "lex: Ошибка разбора автоматом "),
		ERROR_ENTRY(114, "lex: Превышен размер таблицы лексем"),
		ERROR_ENTRY(115, "lex: Превышен размер таблицы идентификаторов"),
		ERROR_ENTRY(116, "lex: Недопустимое значение литерала"),
		ERROR_ENTRY(117, "lex: Превышена максимальная длина строки"),
		ERROR_ENTRY(118, "lex: Невозможно определить тип данных"),
		ERROR_ENTRY(119, "lex: Использование необъявленного идентификатора"),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "syn: Неправильная структура программы"),
		ERROR_ENTRY(601, "syn: Ошибочный оператор"),
		ERROR_ENTRY(602, "syn: Ошибка в выражении"),
		ERROR_ENTRY(603, "syn: Ошибка в записи выражения"),
		ERROR_ENTRY(604, "syn: Ошибка в передаче формальных параметров"),
		ERROR_ENTRY(605, "syn: Ошибка в передаче фактических параметров"),
		ERROR_ENTRY(606, "syn: Ошибка в объявлении функции"),
		ERROR_ENTRY(607, "syn: Синтаксический анализ выполнен с ошибкой"),
		ERROR_ENTRY_NODEF(608), ERROR_ENTRY_NODEF(609), ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY(700, "sem: Выражение должно быть левосторонним"),
		ERROR_ENTRY(701, "sem: Тип не соответствует ожидаемому"),
		ERROR_ENTRY(702, "sem: Возвращаемый тип не соответствует заявленному"),
		ERROR_ENTRY(703, "sem: Операнды имеют разные типы данных"),
		ERROR_ENTRY(704, "sem: Функция должна принимать параметры"),
		ERROR_ENTRY(705, "sem: Функция не принимает параметров"),
		ERROR_ENTRY(706, "sem: Фактические параметры вызываемой функции не совпадают с требуемыми по типу"),
		ERROR_ENTRY(707, "sem: Переменной строчного типа нельзя присвоить значение"),
		ERROR_ENTRY(708, "sem: При вызове функции передано недостаточно параметров"),
		ERROR_ENTRY_NODEF10(720), ERROR_ENTRY_NODEF10(730), ERROR_ENTRY_NODEF10(740),ERROR_ENTRY_NODEF10(750),ERROR_ENTRY_NODEF10(760),
		ERROR_ENTRY_NODEF10(770), ERROR_ENTRY_NODEF10(780), ERROR_ENTRY_NODEF10(790),
		ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		ERROR* rc = new ERROR;
		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			rc->id = id;
			strcpy_s(rc->message, errors[id].message);
		}
		else
		{
			rc->id = errors[0].id;
			strcpy_s(rc->message, errors[0].message);
		}
		return *rc;
	}
	ERROR geterrorin(int id, int line, int col)
	{
		ERROR *rc = new ERROR;
		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			rc->id = id;
			strcpy_s(rc->message, errors[id].message);
			rc->inext.col = col;
			rc->inext.line = line;
		}
		else
		{
			rc->id = errors[0].id;
			strcpy_s(rc->message, errors[0].message);
		}
		return *rc;
	}
};