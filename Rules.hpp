#ifndef RULES_HPP
#define RULES_HPP
#include <vector>
#include <cmath>

struct Move
{
	Vector2c start;
	Vector2c end;
	bool rochade;
	unsigned char newPieceID;
};

typedef struct Move Move;

class History
{
	public:
		History();
		~History();
		
		bool whoHasToMoveNext();
		
	protected:
		vector<Move> moves;
		unsigned int len;
};

bool moveIfPossible(unsigned int, char*, Vector2c, Vector2c, History);

bool threatened(unsigned int, char*, bool);

#endif
