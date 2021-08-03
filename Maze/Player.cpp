#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// ������ �����ϱ� ������ ��� ����
	Pos dest = board->GetExitPos();
	
	// ������ ���� �ϴ°� �迭�� ���� ����� �ش�
	Pos front[4] =
	{
		Pos {-1, 0},	// UP
		Pos {0, -1},	// LEFT
		Pos {1, 0},		// DOWN
		Pos {0, 1},		// RIGHT
	};


	while (pos != dest)
	{
		// 1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ��
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT; // ȸ���� �ʿ��� �� �����ϰ� ����� �� �ִ� ��

		if (CanGo(pos + front[newDir]))
		{
			// ������ �������� 90�� ȸ��
			_dir = newDir;
			// ������ �� �� ����
			pos += front[_dir];

			// ���ο� ��ǥ�� ����
			_path.push_back(pos);

		}

		// 2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ��
		else if (CanGo(pos + front[_dir]))
		{
			// ������ �� �� ����
			pos += front[_dir];

			// ���ο� ��ǥ�� ����
			_path.push_back(pos);
		}

		else
		{
			// ���� �������� 90�� ȸ��
			// �̰� Rookiss�� ó������ ��Ģ���� ������ pch.h�� ������ ���ڷ� �����ؼ� ������ �ڵ�
			_dir = (_dir + 1) % DIR_COUNT; // switch���� ��ü�� �� �ִ�.

			//switch (_dir)
			//{
			//case DIR_UP:
			//	_dir = DIR_LEFT;
			//	break;

			//case DIR_LEFT:
			//	_dir = DIR_DOWN;
			//	break;

			//case DIR_DOWN:
			//	_dir = DIR_RIGHT;
			//	break;

			//case DIR_RIGHT:
			//	_dir = DIR_UP;
			//	break;

			//default:
			//	break;
			//}
		}
		
	}
} // end of init

void Player::Update(uint64 deltaTick)
{
	if (_pathindex >= _path.size())
	{
		return;
	}

	_sumTick += deltaTick;

	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathindex];
		_pathindex++;

	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);

	return tileType == TileType::EMPTY;
}
