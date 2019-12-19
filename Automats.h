#pragma once
#include "FST.h"
#define GRAPH_ENTER	  FST::NODE(1, FST::RELATION('e', 1)),\
					  FST::NODE(1, FST::RELATION('n', 2)),\
					  FST::NODE(1, FST::RELATION('t', 3)),\
					  FST::NODE(1, FST::RELATION('e', 4)),\
					  FST::NODE(1, FST::RELATION('r', 5)),\
					  FST::NODE()
#define GRAPH_NEW  FST::NODE(1, FST::RELATION('n', 1)),\
				   FST::NODE(1, FST::RELATION('e', 2)),\
				   FST::NODE(1, FST::RELATION('w', 3)),\
				   FST::NODE()
#define GRAPH_INTEGER FST::NODE(1, FST::RELATION('i', 1)),\
					  FST::NODE(1, FST::RELATION('n', 2)),\
					  FST::NODE(1, FST::RELATION('t', 3)),\
					  FST::NODE(1, FST::RELATION('e', 4)),\
					  FST::NODE(1, FST::RELATION('g', 5)),\
					  FST::NODE(1, FST::RELATION('e', 6)),\
					  FST::NODE(1, FST::RELATION('r', 7)),\
					  FST::NODE()
#define GRAPH_STRINGTYPE  FST::NODE(1, FST::RELATION('s', 1)),\
					  FST::NODE(1, FST::RELATION('t', 2)),\
					  FST::NODE(1, FST::RELATION('r', 3)),\
					  FST::NODE(1, FST::RELATION('i', 4)),\
					  FST::NODE(1, FST::RELATION('n', 5)),\
					  FST::NODE(1, FST::RELATION('g', 6)),\
					  FST::NODE()
#define GRAPH_SYMBOLTYPE  FST::NODE(1, FST::RELATION('s', 1)),\
					  FST::NODE(1, FST::RELATION('y', 2)),\
					  FST::NODE(1, FST::RELATION('m', 3)),\
					  FST::NODE(1, FST::RELATION('b', 4)),\
					  FST::NODE(1, FST::RELATION('o', 5)),\
					  FST::NODE(1, FST::RELATION('l', 6)),\
					  FST::NODE()
#define GRAPH_FUNCTION FST::NODE(1, FST::RELATION('f', 1)),\
					   FST::NODE(1, FST::RELATION('u', 2)),\
					   FST::NODE(1, FST::RELATION('n', 3)),\
					   FST::NODE(1, FST::RELATION('c', 4)),\
					   FST::NODE(1, FST::RELATION('t', 5)),\
					   FST::NODE(1, FST::RELATION('i', 6)),\
					   FST::NODE(1, FST::RELATION('o', 7)),\
					   FST::NODE(1, FST::RELATION('n', 8)),\
					   FST::NODE()
#define GRAPH_OUTPUT  FST::NODE(1, FST::RELATION('o', 1)),\
					  FST::NODE(1, FST::RELATION('u', 2)),\
					  FST::NODE(1, FST::RELATION('t', 3)),\
					  FST::NODE(1, FST::RELATION('p', 4)),\
					  FST::NODE(1, FST::RELATION('u', 5)),\
					  FST::NODE(1, FST::RELATION('t', 6)),\
					  FST::NODE()
#define GRAPH_IF	 FST::NODE(1, FST::RELATION('i', 1)),\
					 FST::NODE(1, FST::RELATION('f', 2)),\
					 FST::NODE()
#define GRAPH_ELSE	 FST::NODE(1, FST::RELATION('e', 1)),\
					 FST::NODE(1, FST::RELATION('l', 2)),\
					 FST::NODE(1, FST::RELATION('s', 3)),\
					 FST::NODE(1, FST::RELATION('e', 4)),\
					 FST::NODE()
#define GRAPH_RETURN  FST::NODE(1, FST::RELATION('r', 1)),\
					  FST::NODE(1, FST::RELATION('e', 2)),\
					  FST::NODE(1, FST::RELATION('t', 3)),\
					  FST::NODE(1, FST::RELATION('u', 4)),\
					  FST::NODE(1, FST::RELATION('r', 5)),\
					  FST::NODE(1, FST::RELATION('n', 6)),\
					  FST::NODE()
#define GRAPH_STRCAT FST::NODE(1, FST::RELATION('c', 1)),\
					 FST::NODE(1, FST::RELATION('a', 2)),\
					 FST::NODE(1, FST::RELATION('t', 3)),\
					 FST::NODE()
#define GRAPH_STRCPY FST::NODE(1, FST::RELATION('c', 1)),\
					 FST::NODE(1, FST::RELATION('p', 2)),\
					 FST::NODE(1, FST::RELATION('y', 3)),\
					 FST::NODE()
#define GRAPH_IDENTIFICATOR FST::NODE(104, FST::RELATION('a', 1), FST::RELATION('b', 1),\
										  FST::RELATION('c', 1), FST::RELATION('d', 1),\
										  FST::RELATION('e', 1), FST::RELATION('f', 1),\
										  FST::RELATION('g', 1), FST::RELATION('h', 1),\
										  FST::RELATION('i', 1), FST::RELATION('j', 1),\
										  FST::RELATION('k', 1), FST::RELATION('l', 1),\
										  FST::RELATION('m', 1), FST::RELATION('n', 1),\
										  FST::RELATION('o', 1), FST::RELATION('p', 1),\
										  FST::RELATION('q', 1), FST::RELATION('r', 1),\
										  FST::RELATION('s', 1), FST::RELATION('t', 1),\
										  FST::RELATION('u', 1), FST::RELATION('v', 1),\
										  FST::RELATION('w', 1), FST::RELATION('x', 1),\
										  FST::RELATION('y', 1), FST::RELATION('z', 1),\
FST::RELATION('A', 1), FST::RELATION('B', 1),\
FST::RELATION('C', 1), FST::RELATION('D', 1),\
FST::RELATION('E', 1), FST::RELATION('F', 1),\
FST::RELATION('G', 1), FST::RELATION('H', 1),\
FST::RELATION('I', 1), FST::RELATION('J', 1),\
FST::RELATION('K', 1), FST::RELATION('L', 1),\
FST::RELATION('M', 1), FST::RELATION('N', 1),\
FST::RELATION('O', 1), FST::RELATION('P', 1),\
FST::RELATION('Q', 1), FST::RELATION('R', 1),\
FST::RELATION('S', 1), FST::RELATION('T', 1),\
FST::RELATION('U', 1), FST::RELATION('V', 1),\
FST::RELATION('W', 1), FST::RELATION('X', 1),\
FST::RELATION('Y', 1), FST::RELATION('Z', 1),\
										  FST::RELATION('a', 2), FST::RELATION('b', 2),\
										  FST::RELATION('c', 2), FST::RELATION('d', 2),\
										  FST::RELATION('e', 2), FST::RELATION('f', 2),\
										  FST::RELATION('g', 2), FST::RELATION('h', 2),\
										  FST::RELATION('i', 2), FST::RELATION('j', 2),\
										  FST::RELATION('k', 2), FST::RELATION('l', 2),\
										  FST::RELATION('m', 2), FST::RELATION('n', 2),\
										  FST::RELATION('o', 2), FST::RELATION('p', 2),\
										  FST::RELATION('q', 2), FST::RELATION('r', 2),\
										  FST::RELATION('s', 2), FST::RELATION('t', 2),\
										  FST::RELATION('u', 2), FST::RELATION('v', 2),\
										  FST::RELATION('w', 2), FST::RELATION('x', 2),\
										  FST::RELATION('y', 2), FST::RELATION('z', 2),\
FST::RELATION('A', 2), FST::RELATION('B', 2), \
FST::RELATION('C', 2), FST::RELATION('D', 2), \
FST::RELATION('E', 2), FST::RELATION('F', 2), \
FST::RELATION('G', 2), FST::RELATION('H', 2), \
FST::RELATION('I', 2), FST::RELATION('J', 2), \
FST::RELATION('K', 2), FST::RELATION('L', 2), \
FST::RELATION('M', 2), FST::RELATION('N', 2), \
FST::RELATION('O', 2), FST::RELATION('P', 2), \
FST::RELATION('Q', 2), FST::RELATION('R', 2), \
FST::RELATION('S', 2), FST::RELATION('T', 2), \
FST::RELATION('U', 2), FST::RELATION('V', 2), \
FST::RELATION('W', 2), FST::RELATION('X', 2), \
FST::RELATION('Y', 2), FST::RELATION('Z', 2)),\
							FST::NODE(104, FST::RELATION('a', 1), FST::RELATION('b', 1),\
										  FST::RELATION('c', 1), FST::RELATION('d', 1),\
										  FST::RELATION('e', 1), FST::RELATION('f', 1),\
										  FST::RELATION('g', 1), FST::RELATION('h', 1),\
										  FST::RELATION('i', 1), FST::RELATION('j', 1),\
										  FST::RELATION('k', 1), FST::RELATION('l', 1),\
										  FST::RELATION('m', 1), FST::RELATION('n', 1),\
										  FST::RELATION('o', 1), FST::RELATION('p', 1),\
										  FST::RELATION('q', 1), FST::RELATION('r', 1),\
										  FST::RELATION('s', 1), FST::RELATION('t', 1),\
										  FST::RELATION('u', 1), FST::RELATION('v', 1),\
										  FST::RELATION('w', 1), FST::RELATION('x', 1),\
										  FST::RELATION('y', 1), FST::RELATION('z', 1),\
FST::RELATION('A', 1), FST::RELATION('B', 1),\
FST::RELATION('C', 1), FST::RELATION('D', 1),\
FST::RELATION('E', 1), FST::RELATION('F', 1),\
FST::RELATION('G', 1), FST::RELATION('H', 1),\
FST::RELATION('I', 1), FST::RELATION('J', 1),\
FST::RELATION('K', 1), FST::RELATION('L', 1),\
FST::RELATION('M', 1), FST::RELATION('N', 1),\
FST::RELATION('O', 1), FST::RELATION('P', 1),\
FST::RELATION('Q', 1), FST::RELATION('R', 1),\
FST::RELATION('S', 1), FST::RELATION('T', 1),\
FST::RELATION('U', 1), FST::RELATION('V', 1),\
FST::RELATION('W', 1), FST::RELATION('X', 1),\
FST::RELATION('Y', 1), FST::RELATION('Z', 1),\
										FST::RELATION('a', 2), FST::RELATION('b', 2), \
										FST::RELATION('c', 2), FST::RELATION('d', 2), \
										FST::RELATION('e', 2), FST::RELATION('f', 2), \
										FST::RELATION('g', 2), FST::RELATION('h', 2), \
										FST::RELATION('i', 2), FST::RELATION('j', 2), \
										FST::RELATION('k', 2), FST::RELATION('l', 2), \
										FST::RELATION('m', 2), FST::RELATION('n', 2), \
										FST::RELATION('o', 2), FST::RELATION('p', 2), \
										FST::RELATION('q', 2), FST::RELATION('r', 2), \
										FST::RELATION('s', 2), FST::RELATION('t', 2), \
										FST::RELATION('u', 2), FST::RELATION('v', 2), \
										FST::RELATION('w', 2), FST::RELATION('x', 2), \
										FST::RELATION('y', 2), FST::RELATION('z', 2), \
FST::RELATION('A', 2), FST::RELATION('B', 2), \
FST::RELATION('C', 2), FST::RELATION('D', 2), \
FST::RELATION('E', 2), FST::RELATION('F', 2), \
FST::RELATION('G', 2), FST::RELATION('H', 2), \
FST::RELATION('I', 2), FST::RELATION('J', 2), \
FST::RELATION('K', 2), FST::RELATION('L', 2), \
FST::RELATION('M', 2), FST::RELATION('N', 2), \
FST::RELATION('O', 2), FST::RELATION('P', 2), \
FST::RELATION('Q', 2), FST::RELATION('R', 2), \
FST::RELATION('S', 2), FST::RELATION('T', 2), \
FST::RELATION('U', 2), FST::RELATION('V', 2), \
FST::RELATION('W', 2), FST::RELATION('X', 2), \
FST::RELATION('Y', 2), FST::RELATION('Z', 2)),\
							FST::NODE()
#define GRAPH_NUMBER8 FST::NODE(1, FST::RELATION('0', 1)),\
					 FST::NODE(16, FST::RELATION('0', 2), FST::RELATION('1', 2),\
								   FST::RELATION('2', 2), FST::RELATION('3', 2),\
								   FST::RELATION('4', 2), FST::RELATION('5', 2),\
								   FST::RELATION('6', 2), FST::RELATION('7', 2),\
								   FST::RELATION('0', 3), FST::RELATION('1', 3),\
								   FST::RELATION('2', 3), FST::RELATION('3', 3),\
								   FST::RELATION('4', 3), FST::RELATION('5', 3),\
								   FST::RELATION('6', 3), FST::RELATION('7', 3)),\
					 FST::NODE(16, FST::RELATION('0', 2), FST::RELATION('1', 2),\
								   FST::RELATION('2', 2), FST::RELATION('3', 2),\
								   FST::RELATION('4', 2), FST::RELATION('5', 2),\
								   FST::RELATION('6', 2), FST::RELATION('7', 2),\
								   FST::RELATION('0', 3), FST::RELATION('1', 3),\
								   FST::RELATION('2', 3), FST::RELATION('3', 3),\
								   FST::RELATION('4', 3), FST::RELATION('5', 3),\
								   FST::RELATION('6', 3), FST::RELATION('7', 3)),\
								   FST::NODE()
#define GRAPH_NUMBER2 FST::NODE(4, FST::RELATION('0', 1), FST::RELATION('1', 1),\
								   FST::RELATION('0', 2), FST::RELATION('1', 2)),\
					  FST::NODE(4, FST::RELATION('0', 1), FST::RELATION('1', 1),\
								   FST::RELATION('0', 2), FST::RELATION('1', 2)),\
					  FST::NODE()
#define GRAPH_SYMBOL  FST::NODE(1, FST::RELATION('\'', 1)),\
					  FST::NODE(52, FST::RELATION('a', 2), FST::RELATION('A', 2),\
									FST::RELATION('b', 2), FST::RELATION('B', 2),\
									FST::RELATION('c', 2), FST::RELATION('C', 2),\
									FST::RELATION('d', 2), FST::RELATION('D', 2),\
									FST::RELATION('e', 2), FST::RELATION('E', 2),\
									FST::RELATION('f', 2), FST::RELATION('F', 2),\
									FST::RELATION('g', 2), FST::RELATION('G', 2),\
									FST::RELATION('h', 2), FST::RELATION('H', 2),\
									FST::RELATION('i', 2), FST::RELATION('I', 2),\
									FST::RELATION('j', 2), FST::RELATION('J', 2),\
									FST::RELATION('k', 2), FST::RELATION('K', 2),\
									FST::RELATION('l', 2), FST::RELATION('L', 2),\
									FST::RELATION('m', 2), FST::RELATION('M', 2),\
									FST::RELATION('n', 2), FST::RELATION('N', 2),\
									FST::RELATION('o', 2), FST::RELATION('O', 2),\
									FST::RELATION('p', 2), FST::RELATION('P', 2),\
									FST::RELATION('q', 2), FST::RELATION('Q', 2),\
									FST::RELATION('r', 2), FST::RELATION('R', 2),\
									FST::RELATION('s', 2), FST::RELATION('S', 2),\
									FST::RELATION('t', 2), FST::RELATION('T', 2),\
									FST::RELATION('u', 2), FST::RELATION('U', 2),\
									FST::RELATION('v', 2), FST::RELATION('V', 2),\
									FST::RELATION('w', 2), FST::RELATION('W', 2),\
									FST::RELATION('x', 2), FST::RELATION('X', 2),\
									FST::RELATION('y', 2), FST::RELATION('Y', 2),\
									FST::RELATION('z', 2), FST::RELATION('Z', 2)),\
					   FST::NODE(1, FST::RELATION('\'', 3)),\
					   FST::NODE()
#define GRAPH_STRING FST::NODE(1, FST::RELATION('"', 1)),\
				  FST::NODE(139, FST::RELATION(' ', 2), FST::RELATION('a', 2), FST::RELATION('b', 2),\
								FST::RELATION('c', 2), FST::RELATION('d', 2),\
								FST::RELATION('e', 2), FST::RELATION('f', 2),\
								FST::RELATION('g', 2), FST::RELATION('h', 2),\
								FST::RELATION('i', 2), FST::RELATION('j', 2),\
								FST::RELATION('k', 2), FST::RELATION('l', 2),\
								FST::RELATION('m', 2), FST::RELATION('n', 2),\
								FST::RELATION('o', 2), FST::RELATION('p', 2),\
								FST::RELATION('q', 2), FST::RELATION('r', 2),\
								FST::RELATION('s', 2), FST::RELATION('t', 2),\
								FST::RELATION('u', 2), FST::RELATION('v', 2),\
								FST::RELATION('w', 2), FST::RELATION('x', 2),\
								FST::RELATION('y', 2), FST::RELATION('z', 2),\
FST::RELATION('à', 2), FST::RELATION('á', 2), FST::RELATION('â', 2), FST::RELATION('ã', 2),\
FST::RELATION('ä', 2), FST::RELATION('å', 2), FST::RELATION('¸', 2), FST::RELATION('æ', 2),\
FST::RELATION('ç', 2), FST::RELATION('è', 2), FST::RELATION('é', 2), FST::RELATION('ê', 2),\
FST::RELATION('ë', 2), FST::RELATION('ì', 2), FST::RELATION('í', 2), FST::RELATION('î', 2),\
FST::RELATION('ï', 2), FST::RELATION('ð', 2), FST::RELATION('ñ', 2), FST::RELATION('ò', 2),\
FST::RELATION('î', 2), FST::RELATION('ô', 2), FST::RELATION('õ', 2), FST::RELATION('ö', 2),\
FST::RELATION('÷', 2), FST::RELATION('ø', 2), FST::RELATION('ù', 2), FST::RELATION('ú', 2),\
FST::RELATION('û', 2), FST::RELATION('ü', 2), FST::RELATION('ý', 2), FST::RELATION('þ', 2), FST::RELATION('ÿ', 2),\
								FST::RELATION('0', 2), FST::RELATION('1', 2),\
								FST::RELATION('2', 2), FST::RELATION('3', 2),\
								FST::RELATION('4', 2), FST::RELATION('5', 2),\
								FST::RELATION('6', 2), FST::RELATION('7', 2),\
								FST::RELATION('8', 2), FST::RELATION('9', 2),\
								FST::RELATION('a', 3), FST::RELATION('b', 3),\
								FST::RELATION('c', 3), FST::RELATION('d', 3),\
								FST::RELATION('e', 3), FST::RELATION('f', 3),\
								FST::RELATION('g', 3), FST::RELATION('h', 3),\
								FST::RELATION('i', 3), FST::RELATION('j', 3),\
								FST::RELATION('k', 3), FST::RELATION('l', 3),\
								FST::RELATION('m', 3), FST::RELATION('n', 3),\
								FST::RELATION('o', 3), FST::RELATION('p', 3),\
								FST::RELATION('q', 3), FST::RELATION('r', 3),\
								FST::RELATION('s', 3), FST::RELATION('t', 3),\
								FST::RELATION('u', 3), FST::RELATION('v', 3),\
								FST::RELATION('w', 3), FST::RELATION('x', 3),\
								FST::RELATION('y', 3), FST::RELATION('z', 3),\
FST::RELATION('à', 3), FST::RELATION('á', 3), FST::RELATION('â', 3), FST::RELATION('ã', 3),\
FST::RELATION('ä', 3), FST::RELATION('å', 3), FST::RELATION('¸', 3), FST::RELATION('æ', 3),\
FST::RELATION('ç', 3), FST::RELATION('è', 3), FST::RELATION('é', 3), FST::RELATION('ê', 3),\
FST::RELATION('ë', 3), FST::RELATION('ì', 3), FST::RELATION('í', 3), FST::RELATION('î', 3),\
FST::RELATION('ï', 3), FST::RELATION('ð', 3), FST::RELATION('ñ', 3), FST::RELATION('ò', 3),\
FST::RELATION('î', 3), FST::RELATION('ô', 3), FST::RELATION('õ', 3), FST::RELATION('ö', 3),\
FST::RELATION('÷', 3), FST::RELATION('ø', 3), FST::RELATION('ù', 3), FST::RELATION('ú', 3),\
FST::RELATION('û', 3), FST::RELATION('ü', 3), FST::RELATION('ý', 3), FST::RELATION('þ', 3), FST::RELATION('ÿ', 3),\
								FST::RELATION('0', 3), FST::RELATION('1', 3),\
								FST::RELATION('2', 3), FST::RELATION('3', 3),\
								FST::RELATION('4', 3), FST::RELATION('5', 3),\
								FST::RELATION('6', 3), FST::RELATION('7', 3),\
								FST::RELATION('8', 3), FST::RELATION('9', 3)),\
				  FST::NODE(139,FST::RELATION(' ', 2), FST::RELATION('a', 2), FST::RELATION('b', 2),\
								FST::RELATION('c', 2), FST::RELATION('d', 2),\
								FST::RELATION('e', 2), FST::RELATION('f', 2),\
								FST::RELATION('g', 2), FST::RELATION('h', 2),\
								FST::RELATION('i', 2), FST::RELATION('j', 2),\
								FST::RELATION('k', 2), FST::RELATION('l', 2),\
								FST::RELATION('m', 2), FST::RELATION('n', 2),\
								FST::RELATION('o', 2), FST::RELATION('p', 2),\
								FST::RELATION('q', 2), FST::RELATION('r', 2),\
								FST::RELATION('s', 2), FST::RELATION('t', 2),\
								FST::RELATION('u', 2), FST::RELATION('v', 2),\
								FST::RELATION('w', 2), FST::RELATION('x', 2),\
								FST::RELATION('y', 2), FST::RELATION('z', 2),\
FST::RELATION('à', 2), FST::RELATION('á', 2), FST::RELATION('â', 2), FST::RELATION('ã', 2),\
FST::RELATION('ä', 2), FST::RELATION('å', 2), FST::RELATION('¸', 2), FST::RELATION('æ', 2),\
FST::RELATION('ç', 2), FST::RELATION('è', 2), FST::RELATION('é', 2), FST::RELATION('ê', 2),\
FST::RELATION('ë', 2), FST::RELATION('ì', 2), FST::RELATION('í', 2), FST::RELATION('î', 2),\
FST::RELATION('ï', 2), FST::RELATION('ð', 2), FST::RELATION('ñ', 2), FST::RELATION('ò', 2),\
FST::RELATION('î', 2), FST::RELATION('ô', 2), FST::RELATION('õ', 2), FST::RELATION('ö', 2),\
FST::RELATION('÷', 2), FST::RELATION('ø', 2), FST::RELATION('ù', 2), FST::RELATION('ú', 2),\
FST::RELATION('û', 2), FST::RELATION('ü', 2), FST::RELATION('ý', 2), FST::RELATION('þ', 2), FST::RELATION('ÿ', 2),\
								FST::RELATION('0', 2), FST::RELATION('1', 2),\
								FST::RELATION('2', 2), FST::RELATION('3', 2),\
								FST::RELATION('4', 2), FST::RELATION('5', 2),\
								FST::RELATION('6', 2), FST::RELATION('7', 2),\
								FST::RELATION('8', 2), FST::RELATION('9', 2),\
								FST::RELATION('a', 3), FST::RELATION('b', 3),\
								FST::RELATION('c', 3), FST::RELATION('d', 3),\
								FST::RELATION('e', 3), FST::RELATION('f', 3),\
								FST::RELATION('g', 3), FST::RELATION('h', 3),\
								FST::RELATION('i', 3), FST::RELATION('j', 3),\
								FST::RELATION('k', 3), FST::RELATION('l', 3),\
								FST::RELATION('m', 3), FST::RELATION('n', 3),\
								FST::RELATION('o', 3), FST::RELATION('p', 3),\
								FST::RELATION('q', 3), FST::RELATION('r', 3),\
								FST::RELATION('s', 3), FST::RELATION('t', 3),\
								FST::RELATION('u', 3), FST::RELATION('v', 3),\
								FST::RELATION('w', 3), FST::RELATION('x', 3),\
								FST::RELATION('y', 3), FST::RELATION('z', 3),\
FST::RELATION('à', 3), FST::RELATION('á', 3), FST::RELATION('â', 3), FST::RELATION('ã', 3),\
FST::RELATION('ä', 3), FST::RELATION('å', 3), FST::RELATION('¸', 3), FST::RELATION('æ', 3),\
FST::RELATION('ç', 3), FST::RELATION('è', 3), FST::RELATION('é', 3), FST::RELATION('ê', 3),\
FST::RELATION('ë', 3), FST::RELATION('ì', 3), FST::RELATION('í', 3), FST::RELATION('î', 3),\
FST::RELATION('ï', 3), FST::RELATION('ð', 3), FST::RELATION('ñ', 3), FST::RELATION('ò', 3),\
FST::RELATION('î', 3), FST::RELATION('ô', 3), FST::RELATION('õ', 3), FST::RELATION('ö', 3),\
FST::RELATION('÷', 3), FST::RELATION('ø', 3), FST::RELATION('ù', 3), FST::RELATION('ú', 3),\
FST::RELATION('û', 3), FST::RELATION('ü', 3), FST::RELATION('ý', 3), FST::RELATION('þ', 3), FST::RELATION('ÿ', 3),\
								FST::RELATION('0', 3), FST::RELATION('1', 3),\
								FST::RELATION('2', 3), FST::RELATION('3', 3),\
								FST::RELATION('4', 3), FST::RELATION('5', 3),\
								FST::RELATION('6', 3), FST::RELATION('7', 3),\
								FST::RELATION('8', 3), FST::RELATION('9', 3)),\
				   FST::NODE(1, FST::RELATION('"', 4)),\
				   FST::NODE()