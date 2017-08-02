#include "Rules.hpp"

History::History()
{
	
}

History::~History() {}

bool History::whoHasToMoveNext()
{
	return moves.size() % 2 != 0;
}

bool threatened(unsigned int len, char *board, bool col)
{
	Vector2c king = Vector2c(0, 0);
	
	char brd[len][len];
	
	for(size_t dx = 0; dx < len; dx++)
	{
		for(size_t dy = 0; dy < len; dy++)
		{
			brd[dx][dy] = *(board + dx * len + dy);
			if(*(board + dx * len + dy) == 6 + col * 7)
				king = Vector2c(dx, dy);
		}
	}
	
	// King
	for(int offsetX = -1; offsetX < 2; offsetX++)
	{
		for(int offsetY = -1; offsetY < 2; offsetY++)
		{
			if(offsetX != 0 && offsetY != 0)
			{
				if(king.x + offsetX >= 0 && king.x + offsetX < len && king.y + offsetY >= 0 && king.y + offsetY < len)
				{
					if(brd[king.x + offsetX][king.y + offsetY] == 6 + 7 * !col)
						return true;
				}
			}
		}
	}
	
	// Knight
	if(king.x + 2 < len && king.y + 1 < len)
	{
		if(brd[king.x + 2][king.y + 1] == 3 + col * 7)
			return true;
	}
	
	if(king.x + 2 < len && king.y - 1 >= 0)
	{
		if(brd[king.x + 2][king.y - 1] == 3 + col * 7)
			return true;
	}
	
	if(king.x - 2 >= 0 && king.y + 1 < len)
	{
		if(brd[king.x - 2][king.y + 1] == 3 + col * 7)
			return true;
	}
	
	if(king.x - 2 >= 0 && king.y - 1 >= 0)
	{
		if(brd[king.x - 2][king.y - 1] == 3 + col * 7)
			return true;
	}
	
	if(king.x + 1 < len && king.y + 2 < len)
	{
		if(brd[king.x + 1][king.y + 2] == 3 + col * 7)
			return true;
	}
	
	if(king.x + 1 < len && king.y - 2 >= 0)
	{
		if(brd[king.x + 1][king.y - 2] == 3 + col * 7)
			return true;
	}
	
	if(king.x - 1 >= 0 && king.y + 2 < len)
	{
		if(brd[king.x - 1][king.y + 2] == 3 + col * 7)
			return true;
	}
	
	if(king.x - 1 >= 0 && king.y - 2 >= 0)
	{
		if(brd[king.x - 1][king.y - 2] == 3 + col * 7)
			return true;
	}
	
	// Pawn
	if(!col)
	{
		if(king.x + 1 < len && king.y + 1 < len)
		{
			if(brd[king.x + 1][king.y + 1] == 8)
				return true;
		}
		
		if(king.x - 1 >= 0 && king.y + 1 < len)
		{
			if(brd[king.x - 1][king.y + 1] == 8)
				return true;
		}
	}
	else
	{
		if(king.x + 1 < len && king.y - 1 >= 0)
		{
			if(brd[king.x + 1][king.y - 1] == 1)
				return true;
		}
		
		if(king.x - 1 >= 0 && king.y - 1 >= 0)
		{
			if(brd[king.x - 1][king.y - 1] == 1)
				return true;
		}
	}
	
	// Rook & partial queen
	for(int dx = king.x + 1; dx < len; dx++)
	{
		if(brd[dx][king.y] != 0 && brd[dx][king.y] != 2 + 7 * !col && brd[dx][king.y] != 5 + 7 * !col)
			break;
		
		if(brd[dx][king.y] == 2 + 7 * !col || brd[dx][king.y] == 5 + 7 * !col)
			return true;
	}
	
	for(int dx = king.x - 1; dx >= 0; dx--)
	{
		if(brd[dx][king.y] != 0 && brd[dx][king.y] != 2 + 7 * !col && brd[dx][king.y] != 5 + 7 * !col)
			break;
			
		if(brd[dx][king.y] == 2 + 7 * !col || brd[dx][king.y] == 5 + 7 * !col)
			return true;
	}
	
	for(int dy = king.y + 1; dy < len; dy++)
	{
		if(brd[king.x][dy] != 0 && brd[king.x][dy] != 2 + 7 * !col && brd[king.x][dy] != 5 + 7 * !col)
			break;
			
		if(brd[king.x][dy] == 2 + 7 * !col || brd[king.x][dy] == 5 + 7 * !col)
			return true;
	}
	
	for(int dy = king.y - 1; dy >= 0; dy--)
	{
		if(brd[king.x][dy] != 0 && brd[king.x][dy] != 2 + 7 * !col && brd[king.x][dy] != 5 + 7 * !col)
			break;
			
		if(brd[king.x][dy] == 2 + 7 * !col || brd[king.x][dy] == 5 + 7 * !col)
			return true;
	}
	
	// Bishop & partial queen
	for(int offset = 1; (king.x + offset < len) && (king.y + offset < len); offset++)
	{
		if(brd[king.x + offset][king.y + offset] != 0 && brd[king.x + offset][king.y + offset] != 4 + 7 * !col && brd[king.x + offset][king.y + offset] != 5 + 7 * !col)
			break;
		
		if(brd[king.x + offset][king.y + offset] == 4 + 7 * !col || brd[king.x + offset][king.y + offset] == 5 + 7 * !col)
			return true;
	}
	
	for(int offset = 1; (king.x - offset >= 0) && (king.y + offset < len); offset++)
	{
		if(brd[king.x - offset][king.y + offset] != 0 && brd[king.x - offset][king.y + offset] != 4 + 7 * !col && brd[king.x - offset][king.y + offset] != 5 + 7 * !col)
			break;
		
		if(brd[king.x - offset][king.y + offset] == 4 + 7 * !col || brd[king.x - offset][king.y + offset] == 5 + 7 * !col)
			return true;
	}
	
	for(int offset = 1; (king.x + offset < len) && (king.y - offset >= 0); offset++)
	{
		if(brd[king.x + offset][king.y - offset] != 0 && brd[king.x + offset][king.y - offset] != 4 + 7 * !col && brd[king.x + offset][king.y - offset] != 5 + 7 * !col)
			break;
			
		if(brd[king.x + offset][king.y - offset] == 4 + 7 * !col || brd[king.x + offset][king.y - offset] == 5 + 7 * !col)
			return true;
	}
	
	for(int offset = 1; (king.x - offset >= len) && (king.y - offset >= len); offset++)
	{
		if(brd[king.x - offset][king.y - offset] != 0 && brd[king.x - offset][king.y - offset] != 4 + 7 * !col && brd[king.x - offset][king.y - offset] != 5 + 7 * !col)
			break;
		
		if(brd[king.x - offset][king.y - offset] == 4 + 7 * !col || brd[king.x - offset][king.y - offset] == 5 + 7 * !col)
			return true;
	}
	
	return false;
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
				if(!col)
				{
					if(startPos.x == endPos.x)
					{
						if(endPos.y < startPos.y)
							return false;
						else if(endPos.y - startPos.y > 2)
							return false;
						else if(endPos.y - startPos.y == 2 && startPos.y != 1)
							return false;
						else if(brd[endPos.x][endPos.y] != 0)
							return false;
					}
					else
					{
						if(abs(startPos.x - endPos.x) != 1 || abs(startPos.x - endPos.x) != 1)
							return false;
					}
				}
				else
				{
					if(startPos.x == endPos.x)
					{
						if(endPos.y > startPos.y)
							return false;
						else if(startPos.y - endPos.y > 2)
							return false;
						else if(startPos.y - endPos.y == 2 && startPos.y != 7)
							return false;
						else if(brd[endPos.x][endPos.y] != 0)
							return false;
					}
					else
					{
						if(abs(startPos.x - endPos.x) != 1 || abs(startPos.x - endPos.x) != 1)
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
			break;
			case 2: // Rook
				if(startPos.y == endPos.y) // Move Horizontal
				{
					for(int offsetX = 1; offsetX < abs(startPos.x - endPos.x); offsetX++)
					{
						if(startPos.x > endPos.x)
						{
							if(brd[startPos.x - offsetX][startPos.y] != 0)
								return false;
						}
						else
						{
							if(brd[endPos.x - offsetX][startPos.y] != 0)
								return false;
						}
					}
				}
				else if(startPos.x == endPos.x) // Move Vertical
				{
					for(int offsetY = 1; offsetY < abs(startPos.y - endPos.y); offsetY++)
					{
						if(startPos.x > endPos.x)
						{
							if(brd[startPos.x][startPos.y - offsetY] != 0)
								return false;
						}
						else
						{
							if(brd[startPos.x][endPos.y - offsetY] != 0)
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
				}
				else if(startPos.x == endPos.x)
				{
					for(int offsetY = 1; offsetY < abs(startPos.y - endPos.y); offsetY++)
					{
						if(startPos.x > endPos.x)
						{
							if(brd[startPos.x][startPos.y - offsetY] != 0)
								return false;
						}
						else
						{
							if(brd[startPos.x][endPos.y - offsetY] != 0)
								return false;
						}
					}
				}
				else if(startPos.y == endPos.y)
				{
					for(int offsetX = 1; offsetX < abs(startPos.x - endPos.x); offsetX++)
					{
						if(startPos.x > endPos.x)
						{
							if(brd[startPos.x - offsetX][startPos.y] != 0)
								return false;
						}
						else
						{
							if(brd[endPos.x - offsetX][startPos.y] != 0)
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
			case 6: // King
				if(abs(startPos.x - endPos.x) > 1 || abs(startPos.y - endPos.y) > 1)
					return false;
			break;
			default:
				return false;
			break;
		}
		
		if(!threatened(len, &brd[0][0], col))
		{
			for(int dx = 0; dx < len; dx++)
			{
				for(int dy = 0; dy < len; dy++)
				{
					*(board + dx * len + dy) = brd[dx][dy];
				}
			}
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
