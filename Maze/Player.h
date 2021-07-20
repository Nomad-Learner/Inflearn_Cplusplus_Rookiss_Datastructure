#pragma once

class Board;

class Player
{
public:
	void		Init(Board* board);
	void		Update(uint64 deltaTick);

	void		SetPos(Pos pos) { _pos == pos; }
	Pos			GetPos() { return _pos; }

private:

	Pos			_pos = { };
	int32		_dir = DIR_UP;
	// 내가 위치해 있는 맵 자체를 포인터로 들고 있다
	Board*		_board = nullptr;

};

