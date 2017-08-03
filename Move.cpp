#include "Move.hpp"

Move::Move()
{
	startPos = Vector2c(0, 0);
	endPos = Vector2c(0, 0);
	movingPieceID = 0;
	newPieceID = 0;
}

Move::Move(Vector2c s, Vector2c e, unsigned char pid, unsigned char npid)
{
	startPos = s;
	endPos = e;
	movingPieceID = pid;
	newPieceID = npid;
}
