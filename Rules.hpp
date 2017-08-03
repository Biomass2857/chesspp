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
	Move();
	Move(Vector2c, Vector2c, unsigned char, unsigned char);
	Vector2c startPos;
	Vector2c endPos;
	unsigned char movingPieceID;
	unsigned char newPieceID;
};

typedef struct Move Move;

class History
{
	public:
		History();
		~History();

		bool whoHasToMoveNext();
		void addMove(Move move);
		
		void reset();
		
		bool castleLeftEnabled(bool);
		bool castleRightEnabled(bool);
		
	protected:
		vector<Move> moves;
		bool castleWhiteRight;
		bool castleWhiteLeft;
		bool castleBlackRight;
		bool castleBlackLeft;
};

bool threatened(unsigned int, char*, bool);

bool isMovePossible(unsigned int, char*, Vector2c, Vector2c, History);

void hardWriteToBoard(unsigned int, char*, Vector2c, Vector2c, History&);

#endif
