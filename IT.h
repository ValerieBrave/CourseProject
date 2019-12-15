#pragma once
#include <iostream>
#include <algorithm>
#include "Parse.h"
#include "Log.h"
#define ID_MAXSIZE 5               //������������ ���������� �������� � ��������������
#define IT_MAXSIZE 4096            //������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT 0x00000000  //�������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT 0x00        //�������� �� ��������� ��� ���� string
#define TI_NULLIDX 0xffffffff      //��� �������� ������� ���������������
#define TI_STR_MAXSIZE 255         
namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2, SYM = 3, DEF = 4 };  //���� ������ ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, LIB = 5, DF = 6 };//���� ���������������: ����������, �������, ��������, �������, ������������ �������, ���������

	struct Entry
	{
		int idxfirstLE;                   // ������ ������ ������ � ������� ������
		int LTind;							//  ������ ������� ��������� � ������� ������
		int Funcind;						// ������ ������� � ������� �������
		char id[ID_MAXSIZE + 1];              // ������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE iddatatype;            // ��� ������
		IDTYPE idtype;                    // ��� ��������������
		unsigned char* fullID;
		unsigned char* libname;			  // ��� ���� ������������ �������
		union
		{
			int vint;                    // ���� ��� integer, ��� ����� �����
			struct                       // ���� ��� string, ����������� ��� ���������
			{
				unsigned char len;                //���������� �������� � ������ ���� string
				char str[TI_STR_MAXSIZE - 1];//���� ������
			} vstr;
			struct
			{
				char sym;
			} vsym;
		} value;                        //
		Entry()
		{
			this->idxfirstLE = 0;
			this->LTind = 0;
			this->Funcind = 0;
			*this->id = 0x00;
			this->iddatatype = IDDATATYPE::INT;
			this->idtype = IDTYPE::V;
			this->fullID = new unsigned char[2 * IT_MAXSIZE + 1];
			memset(this->fullID, ' ', sizeof(char)* (2 * IT_MAXSIZE + 1));
			this->libname = new unsigned char[20];
			this->value.vint = TI_INT_DEFAULT;
			*this->value.vstr.str = 0x00;
		}
	};
	enum PARMTYPE { I = 1, SM = 2, SR = 3, NO = 4 };
	struct Func
	{
		int LTposition; //LT
		unsigned char* name; //
		int params; // ����� ����������
		IDDATATYPE ret;
		IDDATATYPE* types;
		Func()
		{
			this->LTposition = 0;
			this->name = new unsigned char[6];
			this->params = 0;
			this->ret = IDDATATYPE::DEF;
			this->types = new IDDATATYPE[5];
		}
		Func(int pos, unsigned char* name)
		{
			this->LTposition = pos;
			this->name = new unsigned char[6];
			strcpy_s((char*)this->name, 6, (const char*)name);
			this->ret = IDDATATYPE::DEF;
			this->params = 0;
			this->types = new IDDATATYPE[5];
		}
		Func(int pos, unsigned char* nm, int par, IDDATATYPE ret, IDDATATYPE* prms)
		{
			this->LTposition = pos;
			this->name = new unsigned char[6];
			strcpy_s((char*)this->name, 7, (const char*)nm);
			this->params = par;
			this->ret = ret;
			this->types = new IDDATATYPE[5];
			for (int i = 0; i < par; i++) this->types[i] = prms[i];
		}
	};
	struct IdTable
	{
		int capacity = IT_MAXSIZE; // �������
		int current; // ������� ������
		Entry* table; // ������ �������
		int fcurrent; // funcs current
		int libcur;
		Func* funcs;
		Func* library;
		IdTable()
		{
			this->current = 0;
			this->table = new Entry[this->capacity];
			this->funcs = new Func[this->capacity / 16];
			this->library = new Func[this->capacity / 16];
			this->fcurrent = 0;
			this->libcur = 0;
		}
		IdTable(int size)
		{
			this->current = 0;
			this->table = new Entry[size];
			this->funcs = new Func[size/2];
			this->library = new Func[size / 2];
			this->fcurrent = 0;
			this->libcur = 0;
		}
		void print(Log::LOG lg)
		{
			Log::WriteLine(lg, "--------������� ���������������-------", "");
			for (int i = 0; i < this->current; i++)
			{
				char *tbuf = new char[200];
				if (this->table[i].idtype == IDTYPE::L && this->table[i].iddatatype == IDDATATYPE::INT)
				{
					sprintf_s(tbuf, 200, "%d       %s       %d", this->table[i].idxfirstLE, this->table[i].fullID, this->table[i].value.vint);
				}
				else if (this->table[i].idtype == IDTYPE::L && this->table[i].iddatatype == IDDATATYPE::STR)
				{
					sprintf_s(tbuf, 200, "%d       %s       %s", this->table[i].idxfirstLE, this->table[i].fullID, this->table[i].value.vstr.str);
				}
				else if (this->table[i].idtype == IDTYPE::LIB)
				{
					sprintf_s(tbuf, 200, "%d       %s", this->table[i].idxfirstLE, this->table[i].libname);
				}
				else sprintf_s(tbuf, 200, "%d       %s", this->table[i].idxfirstLE, this->table[i].fullID);
				Log::WriteLine(lg, tbuf, "");
				delete tbuf;
			}
		}
		int here(Entry en) //Entry en
		{
			bool here = false;
			int in = -1;
			int i = 0;
			if (this->current > 0)
			{
				while (!here && i < this->current)
				{
					here = !strcmp((const char*)this->table[i].fullID, (const char*)en.fullID);
					if (here) in = i;
					i++;
				}
			} // fullID - ��� �������������� � ���������, ��� ����� ������� ���������
			return in; // ������ ������ ��������� � ������� ���������������
		}
		int Fhere(unsigned char* name)
		{
			int rc = -1;
			for (int i = 0; i < this->fcurrent; i++)
			{
				if (!strcmp((const char*)name, (const char*)this->funcs[i].name)) rc = i;
			}
			return rc;
		}
		int Lhere(unsigned char* name)
		{
			int rc = -1;
			for (int i = 0; i < this->libcur; i++)
			{
				if (!strcmp((const char*)name, (const char*)this->library[i].name)) rc = i;
			}
			return rc;
		}

	};
	IdTable Create();
	void Add(IdTable &idtab, Entry en);
	Entry GetEntry(IdTable &idtab, int n);
	void Delete(IdTable &idtab);
}