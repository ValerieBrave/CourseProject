#pragma once
#include "In.h"
#include "Log.h"
#include "FST.h"
#include "LT.h"




namespace Parse
{
	struct Words
	{
		int size;
		unsigned char** words;
		Words()
		{
			this->size = 0;
			this->words = new unsigned char*[LT_MAXSIZE];
		}
	};
	unsigned char* parse(unsigned char* pos, In::IN in);
	unsigned char* cutID(int maxsize, unsigned char* str);
	Words find_lexems(In::IN in);
	LT::LexTable auto_check(Words &all_units, FST::FST_lexems *auto_array, int auto_amount, In::IN in, Log::LOG lg);

};