#pragma once
#include "ConsoleHelper.h"

// Ŭ���� ���漱��
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

	void			Init(int32 size, Player* player); // �ʱ�ȭ �Լ�
	void			Render(); // �� �׸��� �Լ�

	void			GenerateMap(); // �� �����Լ�
	TileType		GetTileType(Pos pos); // ��ġ�� ���� Ÿ�� �Լ�
	ConsoleColor	GetTileColor(Pos pos); // ��ġ�� ���� ���� �Լ�

	// �Ա� / �ⱸ
	Pos				GetEnterPos() { return Pos{ 1, 1 }; }
	Pos				GetExitPos() { return Pos{ _size - 2, _size - 2 }; }


private:
	// �ڷ����� TileType�̱� ������ ��ȯ ���� 0, 1, 2, �� �ϳ��̴�
	TileType		_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	int32			_size = 0;
	Player*			_player = nullptr;

};

