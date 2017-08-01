#include "Rules.hpp"

History::History()
{
	
}

History::~History() {}

bool History::whoHasToMoveNext()
{
	return moves.size() % 2 != 0;
}

bool moveIfPossible(unsigned int len, char *board, Vector2c startPos, Vector2c endPos, History gameHistory)
{
	if(startPos == endPos)
		return false;	
	
	char brd[len][len];
	bool col = false;
	unsigned int pieceID = 0;
	
	for(size_t dx = 0; dx < len; dx++)
	{
		for(size_t dy = 0; dy < len; dy++)
		{
			brd[dx][dy] = *(board + dx * len + dy);
		}
	}
	
	if(startPos.x >= 0 && startPos.x < len && startPos.y >= 0 && startPos.y < len && endPos.x >= 0 && endPos.x < len && endPos.y >= 0 && endPos.y < len)
	{
		col = brd[startPos.x][startPos.y] > 7;
		
		if(col != gameHistory.whoHasToMoveNext())
			return false;
		
		pieceID = brd[startPos.x][startPos.y];
		
		if(col)
			pieceID -= 7;
		
		switch(pieceID)
		{
			case 1: // Pawn
				
			break;
			case 2: // Rook
				if(abs(startPos.x - endPos.x) > 0 && startPos.y == endPos.y) // Move Horizontal
				{
					for(int offsetX = 1; offsetX < abs(startPos.x - endPos.x); offsetX++)
					{
						if(startPos.x > endPos.x)
						{
							char check = brd[startPos.x - offsetX][startPos.y];
							if(check != 0)
								return false;
						}
						else
						{
							char check = brd[endPos.x - offsetX][startPos.y];
							if(check != 0)
								return false;
						}
					}
				}
				else if(abs(startPos.y - endPos.y) > 0 && abs(startPos.x - endPos.x) == 0) // Move Vertical
				{
					for(int offsetY = 1; offsetY < abs(startPos.y - endPos.y); offsetY++)
					{
						if(startPos.x > endPos.x)
						{
							char check = brd[startPos.x][startPos.y - offsetY];
							if(check != 0)
								return false;
						}
						else
						{
							char check = brd[startPos.x][endPos.y - offsetY];
							if(check != 0)
								return false;
						}
					}
				}
				else
					return false;
					
				if(brd[endPos.x][endPos.y] % 7 != 6 && ((!col && brd[endPos.x][endPos.y] > 7) || (col && brd[endPos.x][endPos.y] < 7) || brd[endPos.x][endPos.y] == 0))
				{
					brd[endPos.x][endPos.y] = brd[startPos.x][startPos.y];
					brd[startPos.x][startPos.y] = 0;
				}
				else
					return false;
			break;
			case 3: // Knight
				if((abs(startPos.x - endPos.x) == 2 && abs(startPos.y - endPos.y) == 1) || (abs(startPos.x - endPos.x) == 1 && abs(startPos.y - endPos.y) == 2))
				{
					if(brd[endPos.x][endPos.y] % 7 != 6 && ((!col && brd[endPos.x][endPos.y] > 7) || (col && brd[endPos.x][endPos.y] < 7) || brd[endPos.x][endPos.y] == 0))
					{
						brd[endPos.x][endPos.y] = brd[startPos.x][startPos.y];
						brd[startPos.x][startPos.y] = 0;
					}
					else
						return false;
				}
			break;
			case 4: // Bishop
				if(abs(startPos.x - endPos.x) == abs(startPos.x - endPos.y))
				{
					if(endPos.x > startPos.x && endPos.y > startPos.y)
					{
						for(int offset = 1; offset < endPos.x - startPos.x; offset++)
						{
							if(brd[startPos.x + offset][startPos.y + offset] != 0)
								return false;
						}
					}
					else if(endPos.x > startPos.x && endPos.y < startPos.y)
					{
						for(int offset = 1; offset < endPos.x - startPos.x; offset++)
						{
							if(brd[startPos.x + offset][startPos.y - offset] != 0)
								return false;
						}
					}
					else if(endPos.x < startPos.x && endPos.y > startPos.y)
					{
						for(int offset = 1; offset < startPos.x - endPos.x; offset++)
						{
							if(brd[startPos.x - offset][startPos.y + offset] != 0)
								return false;
						}
					}
					else if(endPos.x < startPos.x && endPos.y < endPos.y)
					{
						for(int offset = 1; offset < startPos.x - endPos.x; offset++)
						{
							if(brd[startPos.x - offset][startPos.y - offset] != 0)
								return false;
						}
					}
					
					if(brd[endPos.x][endPos.y] % 7 != 6 && ((!col && brd[endPos.x][endPos.y] > 7) || (col && brd[endPos.x][endPos.y] < 7) || brd[endPos.x][endPos.y] == 0))
					{
						brd[endPos.x][endPos.y] = brd[startPos.x][startPos.y];
						brd[startPos.x][startPos.y] = 0;
					}
					else
						return false;
				}
			break;
			case 5: // Queen
				if(abs(startPos.x - endPos.x) == abs(startPos.x - endPos.y))
			break;
			case 6: // King
				
			break;
			default:
				return false;
			break;
		}
	}
	else
		return false;
		
	
}

bool threatened(unsigned int len, char *board, bool col)
{
	
}
