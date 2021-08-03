#pragma once

class Board;

class Player
{
	enum
	{
		MOVE_TICK = 100
	};
	
public:
	void		Init(Board* board);
	void		Update(uint64 deltaTick);

	void		SetPos(Pos pos) { _pos == pos; }
	Pos			GetPos() { return _pos; }
	bool		CanGo(Pos pos);
private:

	Pos			_pos = { };
	int32		_dir = DIR_UP;
	// 내가 위치해 있는 맵 자체를 포인터로 들고 있다
	Board*		_board = nullptr;

	vector<Pos>	_path;
	uint32		_pathindex = 0;
	uint64		_sumTick = 0;
};

