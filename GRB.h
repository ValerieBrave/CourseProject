#pragma once
#include <iostream>
#include "Error.h"
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
typedef short GRBALPHABET; // символы алфавита грамматики: терминалы >0, нетерминалы <0
namespace GRB
{
	struct Rule // правило в грамматике Грейбах
	{
		GRBALPHABET nn; // нетерминал (левый символ правила) <0
		int iderror; // идентификатор диагностического сообщения
		short size; // количество цепочек - правых частей правила
		struct Chain
		{
			short size; // Длина цепочки
			GRBALPHABET* nt; // цепочка терминалов и нетерминалов
			Chain()
			{
				this->size = 0;
				this->nt = 0;
			}
			Chain(short psize, GRBALPHABET s, ...)
			{
				this->nt = new GRBALPHABET[this->size = psize];
				int *p = (int*)&s;
				for (short i = 0; i < psize; i++) this->nt[i] = (GRBALPHABET)p[i];
			}
			char* getCChain(char* b) /*правая сторона правила*/
			{
				for (int i = 0; i < this->size; i++) b[i] = Chain::alphabet_to_char(this->nt[i]);
				b[this->size] = 0x00;
				return b;
			}
			static GRBALPHABET T(char t) { return GRBALPHABET(t); };
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); };
			static bool isT(GRBALPHABET s) { return s > 0; };
			static bool isN(GRBALPHABET s) { return !isT(s); };
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); };
		}*chains;
		Rule()
		{
			this->nn = 0x00;
			this->size = 0;
			this->iderror = 0;
			this->chains = 0;
		}
		Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...)
		{
			this->nn = pnn;
			this->iderror = iderror;
			this->chains = new Chain[this->size = psize];
			Chain* p = &c;
			for (int i = 0; i < psize; i++) this->chains[i] = p[i];
		}
		void CopyIn(Rule &r)
		{
			r.iderror = this->iderror;
			r.nn = this->nn;
			r.size = this->size;
			for (int i = 0; i < this->size; i++) r.chains[i] = this->chains[i];
		}
		char* getCRule(char *buf, short nchain)
		{
			char bchain[200];
			buf[0] = Rule::Chain::alphabet_to_char(this->nn);
			buf[1] = '-';
			buf[2] = '>';
			buf[3] = 0x00;
			this->chains[nchain].getCChain(bchain);
			strcat_s(buf, sizeof(bchain) + 5, bchain);
			return buf;
		}
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j) // t-первый символ цепочки,pchain - вернуть эту цепочку, j текущая
		{
			short rc = -1;
			while (j < size && chains[j].nt[0] != t) ++j;
			rc = (j < size ? j : -1);
			if (rc >= 0) pchain = this->chains[rc];
			return rc;
		}
	};
	struct Greibach
	{
		short size; // количество правил
		GRBALPHABET startN; //стартовый символ
		GRBALPHABET stbottomT; // дно стека
		Rule* rules; // множество правил
		Greibach()
		{
			this->size = 0;
			this->startN = 0;
			this->stbottomT = 0;
			this->rules = 0;
		}
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...)
		{
			this->startN = pstartN;
			this->stbottomT = pstbottomT;
			this->rules = new Rule[this->size = psize];
			Rule *p = &r;
			for (int i = 0; i < psize; i++) this->rules[i] = p[i];
		}
		short getRule(GRBALPHABET pnn, Rule& prule)
		{
			short rc = -1;
			short k = 0;
			while (k < this->size && this->rules[k].nn != pnn) k++;
			if (k < this->size) prule = this->rules[rc = k];
			return rc;
		}
		Rule getRule(short n)
		{
			Rule rc;
			if (n < this->size) rc = rules[n];
			return rc;
		}

	};
	Greibach getGreibach();

}