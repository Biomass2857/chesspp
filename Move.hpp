#ifndef MOVE_HPP
#define MOVE_HPP
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace sf
{
	typedef Vector2<char> Vector2c;
}

struct Move
{
	Move();
	Move(Vector2c, Vector2c, unsigned char, unsigned char);
	Vector2c startPos;
	Vector2c endPos;
	char movingPieceID;
	char newPieceID;
};

typedef struct Move Move;

#endif
