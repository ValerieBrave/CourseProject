# CourseProject
This is my course project for "programming languages" dicipline. The task was to develop simple compiler for my special programming language.

##Before i started, i was given specification for my languge. There were some points like:

+ realization of conditional operator
+ realization of such operators as ==, !=, <=, >=, <, > (no algebra)
+ at least two types of data (i made integer, string and symbol)
+ number literals must be represented in binary and octal systems.
So, what i've made? I created an application that reads file with program written in my SVV-2019 languge, then carries out lexical analysis,
syntax and semantical analysis, then generates code in Assembly language.

###Let me describe my files:

1) Parm.h + Parm.cpp - contain methods for reading IN params and creating names for OUT and LOG, if necessery
2) In.h + In.cpp - contain methods for reading IN file and checking for forbidden symbols
3) Error.h + Error.cpp - my personal system of generating exceptions
4) Log.h + Log.cpp - contain methods for generating logger
5) Out.h + Out.cpp - contain methods for generating asm file
6) FST.h + FST.cpp - description of finite state machines and regime of their work
7) LT.h + LT.cpp - description of lexems table
8) IT.h + IT.cpp - description of identificators table
9) Parse.h + Parse.cpp - contain methods for parsing IN file into array of single words, then passing them into array of finite state machines.
10) If the word is defined, it goes to table of lexems
11) ITform.h + ITform.cpp - methods for creating table of identificators and literals from table of lexems
12) MFST.h + MFST.cpp - description of finite state machines with store memory and it regime of work
13) GRB.h + GRB.cpp - grammatics for SVV-2019 language
14) Semantica.h + Semantica.cpp - methods for semantical analysis of code
15) Generation.h + Generation.cpp - methods for assembly code generation
16) Automats.h - graphs for fst

Here is my test case:
```
integer function inmax(integer a, integer b)
{
new integer max;
if(a>=b)
{
max = a;
} 
else
{
max = b; 
}
return max;
}
symbol function symin(symbol k, symbol d)
{
new symbol min;
if(k<d)
{
min = k;
}
else
{
min = d;
}
return min;
} 
enter
{
new integer inta;
new integer intb;
new symbol symc;
new symbol symd;
new string stre;
new string strf;
inta = -07;
intb = 10;
stre = "first";
strf = "second";
new integer max;
max = inmax(inta, intb);
if(max == inta)
{
output(max);
}
else
{
output(max);
}
symc='c';
symd= 'd';
new symbol min;
min = symin(symc, symd);
if(min != symc)
{
output("symc is greater than symd");
}
new integer ct;
ct = cat(stre, strf);
output(stre);
output(ct);
new integer copy;
copy = cpy(strf, stre);
return 0;
}
```

##For testing an assembly code you will need static library:
```
#include "stdafx.h"
#include <iostream>
extern "C"
{
	int  cpy(char* destination, char* sourse)
	{
		int is = 0, id = 0, i = 0;
		while (sourse[is] != 0x00) is++;
		while (i < is)
		{
			destination[i] = sourse[i];
			i++;
		}
		return i;
	}
	int cat(char* str1, char* str2)
	{
		int len1 = 0, len2 = 0;
		while (str1[len1] != 0x00) len1++;
		while (str2[len2] != 0x00) len2++;
		for (int i = 0; i < len2; i++) str1[len1 + i] = str2[i];
		return 0;
	}
	int int_output(int a)
	{
		std::cout << a << std::endl;
		return 0;
	}
	int char_output(char a)
	{
		std::cout << a << std::endl;
		return 0;
	}
	int str_output(char* a)
	{
		std::cout << a << std::endl;
		return 0;
	}
	int int_less(int a, int b)
	{
		if (a < b) return 1;
		else return 0;
	}
	int int_eless(int a, int b)
	{
		if (a <= b) return 1;
		else return 0;
	}
	int int_more(int a, int b)
	{
		if (a > b) return 1;
		else return 0;
	}
	int int_emore(int a, int b)
	{
		if (a >= b) return 1;
		else return 0;
	}
	int sym_less(char a, char b)
	{
		if (a < b) return 1;
		else return 0;
	}
	int sym_eless(char a, char b)
	{
		if (a <= b) return 1;
		else return 0;
	}
	int sym_more(char a, char b)
	{
		if (a > b) return 1;
		else return 0;
	}
	int sym_emore(char a, char b)
	{
		if (a >= b) return 1;
		else return 0;
	}
	int str_less(char* str1, char* str2)
	{
		int len1 = 0, len2 = 0;
		bool stop = false;
		while (str1[len1] != 0x00) len1++;
		while (str2[len2] != 0x00) len2++;
		if (len1 < len2) return 1;
		else if (len1 > len2) return 0;
		else
		{
			int i = 0;
			while (!stop || i==len1)
			{
				if (stop = str1[i] >= str2[i]) return 0;
				i++;
			}
			return 1;
		}
	}
	int str_eless(char* str1, char* str2)
	{
		int len1 = 0, len2 = 0;
		bool stop = false;
		while (str1[len1] != 0x00) len1++;
		while (str2[len2] != 0x00) len2++;
		if (len1 < len2 ) return 1;
		else if (len1 > len2) return 0;
		else
		{
			int i = 0;
			while (!stop || i == len1)
			{
				stop = str1[i] > str2[i];
				if (stop) return 0;
				i++;
			}
			return 1;
		}
	}
	int str_more(char* str1, char* str2)
	{
		int len1 = 0, len2 = 0;
		bool stop = false;
		while (str1[len1] != 0x00) len1++;
		while (str2[len2] != 0x00) len2++;
		if (len1 > len2) return 1;
		else if (len1 < len2) return 0;
		else
		{
			int i = 0;
			while (!stop || i == len1)
			{
				if (stop = str1[i] <= str2[i]) return 0;
				i++;
			}
			return 1;
		}
	}
	int str_emore(char* str1, char* str2)
	{
		int len1 = 0, len2 = 0;
		bool stop = false;
		while (str1[len1] != 0x00) len1++;
		while (str2[len2] != 0x00) len2++;
		if (len1 > len2) return 1;
		else if (len1 < len2) return 0;
		else
		{
			int i = 0;
			while (!stop || i == len1)
			{
				if (stop = str1[i] < str2[i]) return 0;
				i++;
			}
			return 1;
		}
	}
	int int_equals(int a, int b)
	{
		if (a == b) return 1;
		else return 0;
	}
	int int_nequals(int a, int b)
	{
		if (a != b) return 1;
		else return 0;
	}
	int sym_equals(char a, char b)
	{
		if (a == b) return 1;
		else return 0;
	}
	int sym_nequals(char a, char b)
	{
		if (a != b) return 1;
		else return 0;
	}
	int str_equals(char* str1, char* str2)
	{
		int len1 = 0, len2 = 0;
		bool stop = false;
		while (str1[len1] != 0x00) len1++;
		while (str2[len2] != 0x00) len2++;
		if (len1 != len2) return 0;
		else
		{
			int i = 0;
			bool stop = false;
			while (!stop && i != len1)
			{
				if (stop = str1[i] != str2[i]) return 0;
				i++;
			}
			return 1;
		}
	}
	int str_nequals(char* str1, char* str2)
	{
		int len1 = 0, len2 = 0;
		bool stop = false;
		while (str1[len1] != 0x00) len1++;
		while (str2[len2] != 0x00) len2++;
		if (len1 != len2) return 1;
		else
		{
			int i = 0;
			bool stop = false;
			while (!stop && i != len1)
			{
				if (stop = str1[i] != str2[i]) return 1;
				i++;
			}
			return 0;
		}
	}
}
```

##This is what you get after generation
```
.586
.MODEL flat, stdcall
includelib kernel32.lib
includelib libucrt.lib
includelib library.lib
SetConsoleTitleA   PROTO :DWORD 
GetStdHandle       PROTO :DWORD
WriteConsoleA      PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ExitProcess	PROTO   :DWORD
extrn cat : proc
extrn cpy : proc
extrn int_output : proc
extrn char_output : proc
extrn str_output : proc
extrn int_less : proc
extrn int_eless : proc
extrn int_more : proc
extrn int_emore : proc
extrn sym_less : proc
extrn sym_eless : proc
extrn sym_more : proc
extrn sym_emore : proc
extrn str_less : proc
extrn str_eless : proc
extrn str_more : proc
extrn str_emore : proc
extrn int_equals : proc
extrn int_nequals : proc
extrn sym_equals : proc
extrn sym_nequals : proc
extrn str_equals : proc
extrn str_nequals : proc
;--------------------------------
.stack 4096
.const
;--------------------------------
.data
inmax_max  SDWORD  0
symin_min  BYTE  ' '
ent_inta  SDWORD  0
ent_intb  SDWORD  0
ent_symc  BYTE  ' '
ent_symd  BYTE  ' '
ent_stre  BYTE 256 dup(0)
ent_strf  BYTE 256 dup(0)
nu180  SDWORD  -7
nu187  SDWORD  2
st194  BYTE  "first",0
st201  BYTE  "second",0
ent_max  SDWORD  0
sy256  BYTE  'c'
sy262  BYTE  'd'
ent_min  BYTE  ' '
st299  BYTE  "symc is greater than symd",0
ent_ct  SDWORD  0
ent_copy  SDWORD  0
nu359  SDWORD  0
;--------------------------------
.code
inmax proc a: sdword,b: sdword
push b
push a
call int_emore
cmp eax, 0
je ELSE15
mov eax, a 
 mov inmax_max, eax
jmp AFTER15
ELSE15:
mov eax, b 
 mov inmax_max, eax
AFTER15:
mov eax, 0
mov eax, inmax_max
ret
inmax ENDP
symin proc k: byte,d: byte
mov al, d
mov bl, k
push eax
push ebx
call sym_less
cmp eax, 0
je ELSE53
mov eax, 0
mov al, k
mov symin_min, al
jmp AFTER53
ELSE53:
mov eax, 0
mov al, d
mov symin_min, al
AFTER53:
mov eax, 0
mov al, symin_min
ret
symin ENDP
main PROC
START:
mov eax, nu180 
 mov ent_inta, eax
mov eax, nu187 
 mov ent_intb, eax
push OFFSET st194
push OFFSET ent_stre
call cpy
push OFFSET st201
push OFFSET ent_strf
call cpy
push  ent_intb
push  ent_inta
call inmax
mov ent_max, eax
push ent_inta
push ent_max
call int_equals
cmp eax, 0
je ELSE131
push ent_max
call int_output
jmp AFTER131
ELSE131:
push ent_max
call int_output
AFTER131:
mov eax, 0
mov al, sy256
mov ent_symc, al
mov eax, 0
mov al, sy262
mov ent_symd, al
mov al, ent_symd
push eax
mov al, ent_symc
push eax
call symin
mov ent_min, al
mov al, ent_symc
mov bl, ent_min
push eax
push ebx
call sym_nequals
cmp eax, 0
je AFTER173
push OFFSET st299
call str_output
jmp AFTER173
AFTER173:
push OFFSET ent_strf
push OFFSET ent_stre
call cat
mov ent_ct, eax
push OFFSET ent_stre
call str_output
push ent_ct
call int_output
push OFFSET ent_stre
push OFFSET ent_strf
call cpy
mov ent_copy, eax
push nu359
call ExitProcess
main ENDP
end main
```

I hope i've tested all cases, so generated code should be usable
Sorry, all mistakes are written in russian
I've spent a lot of time working on this project, so if you notice some mistakes in code generation, please contact me, i'll try to fix it
Thanks for reading=)






