#include "pch.h"
#include "GRB.h"
#define GRB_ERROR_SERIES 600
namespace GRB
{
	Greibach getGreibach()
	{
		Greibach greibach(NS('S'), TS('$'), 9,
			Rule(NS('S'), GRB_ERROR_SERIES + 0, 6,
				Rule::Chain(7, TS('e'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}')),
				Rule::Chain(8, TS('e'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}'), NS('F')),
				Rule::Chain(17, TS('t'), TS('f'), TS('i'), NS('P'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}'), TS('e'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}')),
				Rule::Chain(18, TS('t'), TS('f'), TS('i'), NS('P'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}'), NS('F'), TS('e'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}')),
				Rule::Chain(18, TS('t'), TS('f'), TS('i'), NS('P'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}'), TS('e'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}'), NS('F')),
				Rule::Chain(19, TS('t'), TS('f'), TS('i'), NS('P'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}'), NS('F'), TS('e'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}'), NS('F'))),
			Rule(NS('F'), GRB_ERROR_SERIES + 0, 2,
				Rule::Chain(10, TS('t'), TS('f'), TS('i'), NS('P'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}')),
				Rule::Chain(11, TS('t'), TS('f'), TS('i'), NS('P'), TS('{'), NS('B'), TS('r'), NS('X'), TS(';'), TS('}'), NS('F'))),
			Rule(NS('B'), GRB_ERROR_SERIES + 1, 12,
				Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),
				Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('B')),

				Rule::Chain(4, TS('i'), TS('='), NS('X'), TS(';')),
				Rule::Chain(5, TS('i'), TS('='), NS('X'), TS(';'), NS('B')),

				Rule::Chain(5, TS('o'), TS('('), TS('i'), TS(')'), TS(';')),
				Rule::Chain(6, TS('o'), TS('('), TS('i'), TS(')'), TS(';'), NS('B')),

				Rule::Chain(5, TS('o'), TS('('), TS('l'), TS(')'), TS(';')),
				Rule::Chain(6, TS('o'), TS('('), TS('l'), TS(')'), TS(';'), NS('B')),

				Rule::Chain(7, TS('I'), TS('('), NS('X'), TS(')'), TS('{'), NS('B'), TS('}')),
				Rule::Chain(8, TS('I'), TS('('), NS('X'), TS(')'), TS('{'), NS('B'), TS('}'), NS('B')),

				Rule::Chain(11, TS('I'), TS('('), NS('X'), TS(')'), TS('{'), NS('B'), TS('}'), TS('E'), TS('{'), NS('B'), TS('}')),
				Rule::Chain(12, TS('I'), TS('('), NS('X'), TS(')'), TS('{'), NS('B'), TS('}'), TS('E'), TS('{'), NS('B'), TS('}'), NS('B'))),
			Rule(NS('X'), GRB_ERROR_SERIES + 2, 8,
				Rule::Chain(1, TS('i')),
				Rule::Chain(1, TS('l')),
				Rule::Chain(3, TS('i'), NS('Z'), TS('i')),
				Rule::Chain(3, TS('i'), NS('Z'), TS('l')),
				Rule::Chain(3, TS('l'), NS('Z'), TS('i')),
				Rule::Chain(3, TS('l'), NS('Z'), TS('l')),
				Rule::Chain(2, TS('b'), NS('C')),
				Rule::Chain(2, TS('i'), NS('C'))),
			Rule(NS('Z'), GRB_ERROR_SERIES + 3, 5,
				Rule::Chain(1, TS('v')),
				Rule::Chain(1, TS('L')),
				Rule::Chain(1, TS('M')),
				Rule::Chain(1, TS('D')),
				Rule::Chain(1, TS('N'))),
			Rule(NS('P'), GRB_ERROR_SERIES + 4, 2, // формальные параметры
				Rule::Chain(2, TS('('), TS(')')),
				Rule::Chain(3, TS('('), NS('R'), TS(')'))),
			Rule(NS('R'), GRB_ERROR_SERIES + 4, 4,
				Rule::Chain(2, TS('t'), TS('i')),
				Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('R')),
				Rule::Chain(1, TS('l')),
				Rule::Chain(3, TS('l'), TS(','), NS('R'))),
			Rule(NS('C'), GRB_ERROR_SERIES + 5, 2, // фактические параметры
				Rule::Chain(2, TS('('), TS(')')),
				Rule::Chain(3, TS('('), NS('W'), TS(')'))),
			Rule(NS('W'), GRB_ERROR_SERIES + 5, 4,
				Rule::Chain(1, TS('i')),
				Rule::Chain(1, TS('l')),
				Rule::Chain(3, TS('i'), TS(','), NS('W')),
				Rule::Chain(3, TS('l'), TS(','), NS('W')))
		);
		return greibach;
	}


}