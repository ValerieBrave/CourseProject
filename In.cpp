#include "pch.h"
#include <iostream>
#include <fstream>
#include "In.h"
#include "Error.h"
namespace In
{

	IN getin(const char* infile)
	{
		IN *rc = new IN;
		std::ifstream file;
		file.open(infile);
		if (!file.is_open()) throw ERROR_THROW(110);
		file.seekg(0, std::ios_base::end);
		rc->size = (int)file.tellg();
		file.seekg(0, std::ios_base::beg);
		if (rc->size != 0)
		{
			rc->text = new unsigned char[rc->size];
			int i = 0, l = 0, c = 0;
			char buf;
			while (!file.eof())
			{
				file.read(&buf, 1);
				if (buf == IN_CODE_ENDL) { l++; c = 0; }
				switch (rc->code[(unsigned char)buf])
				{
				case IN::F: throw ERROR_THROW_IN(111, l, c); break;
				case IN::T: rc->text[i] = buf; i++; break;
				case IN::I:rc->ignor++; break;
				case IN::R: rc->text[i] = buf; i++; break;
				case IN::B: rc->text[i] = buf; i++; break;
				case IN::Q: rc->text[i] = buf; i++; break;
				case IN::OQ: rc->text[i] = buf; i++; break;
				case IN::M: rc->text[i] = buf; i++; break;
				default:rc->text[i] = (unsigned char)rc->code[(unsigned char)buf]; i++; break;
				}
				c++;
			}
			rc->text[i - 1] = 0x00;
			rc->lines = l;
			rc->size -= rc->ignor;
		}
		file.close();
		return *rc;
	}
	unsigned char* IN::del_useless_blanks()
	{
		int len = strlen((const char*)this->text);
		unsigned char* buf = new unsigned char[len];
		int nb = 0; // количество подряд идущих пробелов и \n
		int ibuf = 0; // индекс для буфа
		for (int i = 0; i < len; i++)
		{
			if (this->text[i] == ' ') nb++;
			else
			{
				if (nb > 0)
				{
					buf[ibuf++] = ' ';// все равно записываем один пробел
					nb = 0;
				}
				buf[ibuf++] = this->text[i];
			}
		}
		buf[ibuf] = 0x00;
		if (buf[0] == ' ')
		{
			for (int i = 1; i < ibuf; i++) buf[i - 1] = buf[i]; // сдвигаем, если остался пробел в начале
			buf[ibuf - 1] = 0x00;
		}
		return buf;
	}
}