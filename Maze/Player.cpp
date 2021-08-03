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

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = board->GetExitPos();
	
	// 앞으로 가야 하는걸 배열로 따로 만들어 준다
	Pos front[4] =
	{
		Pos {-1, 0},	// UP
		Pos {0, -1},	// LEFT
		Pos {1, 0},		// DOWN
		Pos {0, 1},		// RIGHT
	};


	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT; // 회전이 필요할 때 유용하게 사용할 수 있는 팁

		if (CanGo(pos + front[newDir]))
		{
			// 오른쪽 방향으로 90도 회전
			_dir = newDir;
			// 앞으로 한 보 전진
			pos += front[_dir];

			// 새로운 좌표를 저장
			_path.push_back(pos);

		}

		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 보 전진
			pos += front[_dir];

			// 새로운 좌표를 저장
			_path.push_back(pos);
		}

		else
		{
			// 왼쪽 방향으로 90도 회전
			// 이건 Rookiss가 처음부터 규칙성을 가지고 pch.h에 방향을 숫자로 정의해서 가능한 코드
			_dir = (_dir + 1) % DIR_COUNT; // switch문을 대체할 수 있다.

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
