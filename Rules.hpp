#ifndef RULES_HPP
#define RULES_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include "util.hpp"

using namespace std;
using namespace sf;

struct Move
{
	Move() {}
	Vector2c start;
	Vector2c end;
	bool castling;
	unsigned char newPieceID;
};

typedef struct Move Move;

class History
{
	public:
		History();
		~History();

		bool whoHasToMoveNext();
		
		void inc();
		
	protected:
		vector<Move> moves;
		unsigned int len;
};

bool threatened(unsigned int, char*, bool);

bool isMovePossible(unsigned int, char*, Vector2c, Vector2c, History);

void hardWriteToBoard(unsigned int, char*, Vector2c, Vector2c, History&);

#endif
