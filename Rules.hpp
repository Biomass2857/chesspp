#ifndef RULES_HPP
#define RULES_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include "util.hpp"
#include "NetworkHandler.hpp"
#include "Move.hpp"

using namespace std;
using namespace sf;

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

		int getMoveNumber();

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
