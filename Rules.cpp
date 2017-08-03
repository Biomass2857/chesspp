#include "Rules.hpp"

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

History::History()
{
	reset();
}

History::~History() {}

bool History::whoHasToMoveNext()
{
	return moves.size() % 2 != 0;
}

void History::addMove(Move move)
{
	moves.push_back(move);
	
	if(move.movingPieceID == 6)
	{
		castleWhiteRight = false;
		castleWhiteLeft = false;
	}
	else if(move.movingPieceID == 13)
	{
		castleBlackRight = true;
		castleBlackLeft = true;
	}
	else if(move.movingPieceID == 2)
	{
		if(move.startPos.x == 0 && move.startPos.y == 0)
			castleWhiteLeft = false;
		else if(move.startPos.x == 7 && move.startPos.y == 0)
			castleWhiteRight = false;
	}
	else if(move.movingPieceID == 9)
	{
		if(move.startPos.x == 0 && move.startPos.y == 7)
			castleBlackLeft = false;
		else if(move.startPos.x == 7 && move.startPos.y == 7)
			castleWhiteLeft = false;
	}
}

void History::inc()
{
	moves.push_back(Move());
}

void History::reset()
{
	castleWhiteRight = true;
	castleWhiteLeft = true;
	castleBlackRight = true;
	castleBlackLeft = true;
	moves.clear();
}

bool History::castleLeftEnabled(bool col)
{
	if(!col)
	{
		return castleWhiteLeft;
	}
	else
	{
		return castleBlackLeft;
	}
}

bool History::castleRightEnabled(bool col)
{
	if(!col)
	{
		return castleWhiteRight;
	}
	else
	{
		return castleBlackLeft;
	}
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
		if(brd[king.x + 2][king.y + 1] == 3 + !col * 7)
			return true;
	}
	
	if(king.x + 2 < len && king.y - 1 >= 0)
	{
		if(brd[king.x + 2][king.y - 1] == 3 + !col * 7)
			return true;
	}
	
	if(king.x - 2 >= 0 && king.y + 1 < len)
	{
		if(brd[king.x - 2][king.y + 1] == 3 + !col * 7)
			return true;
	}
	
	if(king.x - 2 >= 0 && king.y - 1 >= 0)
	{
		if(brd[king.x - 2][king.y - 1] == 3 + !col * 7)
			return true;
	}
	
	if(king.x + 1 < len && king.y + 2 < len)
	{
		if(brd[king.x + 1][king.y + 2] == 3 + !col * 7)
			return true;
	}
	
	if(king.x + 1 < len && king.y - 2 >= 0)
	{
		if(brd[king.x + 1][king.y - 2] == 3 + !col * 7)
			return true;
	}
	
	if(king.x - 1 >= 0 && king.y + 2 < len)
	{
		if(brd[king.x - 1][king.y + 2] == 3 + !col * 7)
			return true;
	}
	
	if(king.x - 1 >= 0 && king.y - 2 >= 0)
	{
		if(brd[king.x - 1][king.y - 2] == 3 + !col * 7)
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

bool isMovePossible(unsigned int len, char *board, Vector2c startPos, Vector2c endPos, History gameHistory)
{
	if(startPos == endPos)
		return false;

	char brd[len][len];
	bool col = false;
	bool castling = false;
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
		{
			if(gameHistory.whoHasToMoveNext()) cout << "Schwarz ist am zug" << endl; else cout << "Weiß ist am zug" << endl;
			
			return false;	
		}
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
						{
							cout << "Der Bauer kann nicht rückwärts laufen" << endl;
							return false;
						}
						else if(endPos.y - startPos.y > 2)
						{
							cout << "Der Bauer kann nicht weiter als maximal 2 Schritte gehen" << endl;
							return false;
						}
						else if(endPos.y - startPos.y == 2 && startPos.y != 1)
						{
							cout << "Der Bauer kann nur von seiner Grundposition aus 2 Schritte gehen" << endl;
							return false;
						}
						else if(brd[endPos.x][endPos.y] != 0)
						{
							cout << "Der Bauer kann nicht frontal schlagen" << endl;
							return false;
						}
					}
					else
					{
						if(abs(startPos.x - endPos.x) != 1 || abs(startPos.y - endPos.y) != 1 || brd[endPos.x][endPos.y] <= 7)
						{
							cout <<"Der Bauer kann nur schräg schlagen"<< endl;
							return false;
						}
					}
				}
				else
				{
					if(startPos.x == endPos.x)
					{
						if(endPos.y > startPos.y)
						{
							cout <<"Der Bauer kann nicht rückwärts laufen"<< endl;
							return false;
						}
						else if(startPos.y - endPos.y > 2)
						{
							cout <<"Der Bauer kann nicht weiter als maximal 2 Schritte gehen"<< endl;
							return false;
						}
						else if(startPos.y - endPos.y == 2 && startPos.y != 6)
						{
							cout <<"Der Bauer darf nur aus seiner Upsprungsposition 2 Schritte gehen"<< endl;
							return false;
						}
						else if(brd[endPos.x][endPos.y] != 0)
						{
							cout <<"Der Bauer darf nicht frontal schlagen"<< endl;
							return false;	
						}
					}
					else
					{
						if(abs(startPos.x - endPos.x) != 1 || abs(startPos.x - endPos.x) != 1 || brd[endPos.x][endPos.y] >= 7)
						{
							cout <<"Der Bauer darf nur schräg schlagen"<< endl;
							return false;
						}
					}
				}
			break;
			case 2: // Rook
				if(startPos.y == endPos.y) // Move Horizontal
				{
					for(int offsetX = 1; offsetX < abs(startPos.x - endPos.x); offsetX++)
					{
						if(startPos.x > endPos.x)
						{
							if(brd[startPos.x - offsetX][startPos.y] != 0)
							{
								cout <<"Der Turm darf sich nicht über andere Figuren bewegen"<< endl;
								return false;
							}
						}
						else
						{
							if(brd[endPos.x - offsetX][startPos.y] != 0)
							{
								cout <<"Der Turm darf sich nicht über andere Figuren bewegen"<< endl;
								return false;
							}
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
							{
								cout <<"Der Turm darf sich nicht über andere Figuren bewegen"<< endl;
								return false;
							}
						}
						else
						{
							if(brd[startPos.x][endPos.y - offsetY] != 0)
							{
								cout <<"Der Turm darf sich nicht über andere Figuren bewegen"<< endl;
								return false;
							}
						}
					}
				}
				else
				{
					cout <<"Der Turm kann nur gerade ziehen"<< endl;
					return false;
				}
			break;
			case 3: // Knight
				if((abs(startPos.x - endPos.x) != 2 || abs(startPos.y - endPos.y) != 1) && (abs(startPos.x - endPos.x) != 1 || abs(startPos.y - endPos.y) != 2))
				{
					cout <<"Der Springer kann nur L-förmig springen"<< endl;
					return false;
				}
			break;
			case 4: // Bishop
				if(abs(startPos.x - endPos.x) == abs(startPos.y - endPos.y))
				{
					if(endPos.x > startPos.x && endPos.y > startPos.y)
					{
						for(int offset = 1; offset < endPos.x - startPos.x; offset++)
						{
							if(brd[startPos.x + offset][startPos.y + offset] != 0)
							{
								cout <<"Der Läufer kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
						}
					}
					else if(endPos.x > startPos.x && endPos.y < startPos.y)
					{
						for(int offset = 1; offset < endPos.x - startPos.x; offset++)
						{
							if(brd[startPos.x + offset][startPos.y - offset] != 0)
							{
								cout <<"Der Läufer kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
						}
					}
					else if(endPos.x < startPos.x && endPos.y > startPos.y)
					{
						for(int offset = 1; offset < startPos.x - endPos.x; offset++)
						{
							if(brd[startPos.x - offset][startPos.y + offset] != 0)
							{
								cout <<"Der Läufer kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
						}
					}
					else if(endPos.x < startPos.x && endPos.y < endPos.y)
					{
						for(int offset = 1; offset < startPos.x - endPos.x; offset++)
						{
							if(brd[startPos.x - offset][startPos.y - offset] != 0)
							{
								cout <<"Der Läufer kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
						}
					}
				}
				else
				{
					cout <<"Der Läufer kann nur schräg ziehen"<< endl;
					return false;
				}
			break;
			case 5: // Queen
				if(abs(startPos.x - endPos.x) == abs(startPos.y - endPos.y))
				{
					if(endPos.x > startPos.x && endPos.y > startPos.y)
					{
						for(int offset = 1; offset < endPos.x - startPos.x; offset++)
						{
							if(brd[startPos.x + offset][startPos.y + offset] != 0)
							{
								cout <<"Die Dame kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
						}
					}
					else if(endPos.x > startPos.x && endPos.y < startPos.y)
					{
						for(int offset = 1; offset < endPos.x - startPos.x; offset++)
						{
							if(brd[startPos.x + offset][startPos.y - offset] != 0)
							{
								cout <<"Die Dame kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
						}
					}
					else if(endPos.x < startPos.x && endPos.y > startPos.y)
					{
						for(int offset = 1; offset < startPos.x - endPos.x; offset++)
						{
							if(brd[startPos.x - offset][startPos.y + offset] != 0)
							{
								cout <<"Die Dame kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
						}
					}
					else if(endPos.x < startPos.x && endPos.y < endPos.y)
					{
						for(int offset = 1; offset < startPos.x - endPos.x; offset++)
						{
							if(brd[startPos.x - offset][startPos.y - offset] != 0)
							{
								cout <<"Die Dame kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
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
							{
								cout <<"Die Dame kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
						}
						else
						{
							if(brd[startPos.x][endPos.y - offsetY] != 0)
							{
								cout <<"Die Dame kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
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
							{
								cout <<"Die Dame kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
						}
						else
						{
							if(brd[endPos.x - offsetX][startPos.y] != 0)
							{
								cout <<"Die Dame kann sich nicht über andere figuren bewegen"<< endl;
								return false;
							}
						}
					}
				}
				else
				{
					cout <<"Die Dame kann sich nur wie ein Turm oder ein Läufer bewegen"<< endl;
					return false;
				}
			break;
			case 6: // King
				if(abs(startPos.x - endPos.x) > 1 || abs(startPos.y - endPos.y) > 1)
				{
					if(abs(startPos.x - endPos.x) == 2 && startPos.y == endPos.y)
					{
						if(!threatened(len, &brd[0][0], col))
						{
							if(startPos.x - endPos.x > 0) // Left
							{
								if(gameHistory.castleLeftEnabled(col))
								{
									castling = true;
									for(int offset = 1; offset <= 2; offset++)
									{
										if(brd[startPos.x - offset][startPos.y] == 0)
										{					
											brd[startPos.x - offset][startPos.y] = brd[startPos.x + 1 - offset][startPos.y];
											brd[startPos.x + 1 - offset][startPos.y] = 0;
											
											if(threatened(len, &brd[0][0], col))
											{
												cout <<"Der König darf nicht über ein bedrohtes Feld laufen wenn er rochiert"<< endl;
												return false;
											}
										}
										else
										{
											cout <<"Der Bereich zwischen Turm und König muss für die Rochade leer sein."<< endl;
											return false;
										}
									}
									
									brd[startPos.x][startPos.y] = brd[endPos.x][endPos.y];
									brd[endPos.x][endPos.y] = 0;
								}
								else
								{
									cout <<"Der König darf nur rochieren wenn er und der entsprechende Turm sich noch nicht bewegt haben"<< endl;
									return false;
								}
							}
							else if(startPos.x - endPos.x < 0) // Right
							{
								if(gameHistory.castleRightEnabled(col))
								{
									castling = true;
									for(int offset = 1; offset <= 2; offset++)
									{
										if(brd[startPos.x + offset][startPos.y] == 0)
										{					
											brd[startPos.x + offset][startPos.y] = brd[startPos.x - 1 + offset][startPos.y];
											brd[startPos.x - 1 + offset][startPos.y] = 0;
										
											if(threatened(len, &brd[0][0], col))
											{
												cout <<"Der König darf nicht über ein bedrohtes Feld laufen wenn er rochiert"<< endl;
												return false;
											}
										}
										else
										{
											cout <<"Der Bereich zwischen Turm und König muss für die Rochade leer sein."<< endl;
											return false;
										}
									}
									
									brd[startPos.x][startPos.y] = brd[endPos.x][endPos.y];
									brd[endPos.x][endPos.y] = 0;
								}
								else
								{
									cout <<"Der König darf nur rochieren wenn er und der entsprechende Turm sich noch nicht bewegt haben"<< endl;
									return false;
								}
							}
						}
						else
						{
							cout <<"Der König darf nicht aus dem Schach hinaus rochieren"<< endl;
							return false;
						}
					}
					else
					{
						cout <<"Der König kann sich nur ein Feld fortbewegen"<< endl;
						return false;
					}
				}
			break;
			default:
				cout <<"Die PieceID "<< pieceID <<" ist mir unbekannt"<< endl;
				return false;
			break;
		}
		
		if(!castling)
		{
			if(brd[endPos.x][endPos.y] % 7 != 6 && ((!col && brd[endPos.x][endPos.y] > 7) || (col && brd[endPos.x][endPos.y] < 7) || brd[endPos.x][endPos.y] == 0))
			{
				brd[endPos.x][endPos.y] = brd[startPos.x][startPos.y];
				brd[startPos.x][startPos.y] = 0;
			}
			else
			{
				cout <<"Der König kann nicht geschlagen werden oder du kannst nur Gegner schlagen"<< endl;
				return false;
			}
		}
		
		if(!threatened(len, &brd[0][0], col))
		{
			return true;
		}
		else
		{
			cout <<"Dieser Zug ist ungültig, da dein König noch im Schach ist"<< endl;
			return false;
		}
	}
	else
	{
		cout <<"Start und End positionen müssen sich auf dem Spielfeld befinden"<< endl;
		return false;	
	}
}

void hardWriteToBoard(unsigned int len, char *board, Vector2c startPos, Vector2c endPos, History &history)
{
	if(startPos != endPos)
	{
		char brd[len][len];
	
		for(int dx = 0; dx < len; dx++)
		{
			for(int dy = 0; dy < len; dy++)
			{
				brd[dx][dy] = *(board + dx * len + dy);
			}
		}
	
		if(startPos.x >= 0 && startPos.x < len && startPos.y >= 0 && startPos.y < len && endPos.x >= 0 && endPos.x < len && endPos.y >= 0 && endPos.y < len)
		{
			if(brd[startPos.x][startPos.y] == 6 + 7 * history.whoHasToMoveNext() && abs(startPos.x - endPos.x) == 2 && startPos.y == endPos.y)
			{
				if(startPos.x - endPos.x > 0)
				{
					brd[endPos.x][endPos.y] = brd[startPos.x][startPos.y];
					brd[startPos.x][startPos.y] = 0;
					brd[endPos.x + 1][endPos.y] = brd[startPos.x - 4][7 * history.whoHasToMoveNext()];
					brd[startPos.x - 4][7 * history.whoHasToMoveNext()] = 0;
				}
				else if(startPos.x - endPos.x < 0)
				{
					brd[endPos.x][endPos.y] = brd[startPos.x][startPos.y];
					brd[startPos.x][startPos.y] = 0;
					brd[endPos.x - 1][endPos.y] = brd[startPos.x + 3][startPos.y];
					brd[startPos.x + 3][startPos.y] = 0;
				}
			}
			else
			{
				brd[endPos.x][endPos.y] = brd[startPos.x][startPos.y];
				brd[startPos.x][startPos.y] = 0;
			}
		}
	
		history.addMove(Move(startPos, endPos, *(board + startPos.x * len + startPos.y), 0));
	
		for(int dx = 0; dx < len; dx++)
		{
			for(int dy = 0; dy < len; dy++)
			{
				*(board + dx * len + dy) = brd[dx][dy];
			}
		}
	}
}
