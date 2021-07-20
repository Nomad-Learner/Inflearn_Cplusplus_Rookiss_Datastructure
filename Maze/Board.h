#pragma once
#include "ConsoleHelper.h"

// 클래스 전방선언
class Player;

enum
{
	BOARD_MAX_SIZE = 100,
};

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL,
};

class Board
{
public:

	Board();
	~Board();

	void			Init(int32 size, Player* player); // 초기화 함수
	void			Render(); // 맵 그리는 함수

	void			GenerateMap(); // 맵 생성함수
	TileType		GetTileType(Pos pos); // 위치에 따른 타일 함수
	ConsoleColor	GetTileColor(Pos pos); // 위치에 따른 색상 함수

	// 입구 / 출구
	Pos				GetEnterPos() { return Pos{ 1, 1 }; }
	Pos				GetExitPos() { return Pos{ _size - 2, _size - 2 }; }


private:
	// 자료형이 TileType이기 때문에 반환 값이 0, 1, 2, 중 하나이다
	TileType		_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	int32			_size = 0;
	Player*			_player = nullptr;

};

