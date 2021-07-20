#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"

const char* TILE = "■";

Board::Board()
{



}

Board::~Board()
{

}

void Board::Init(int32 size, Player* player)
{
    _size = size;
    _player = player;

    GenerateMap();
}

void Board::Render()
{
    ConsoleHelper::SetCursorPosition(0, 0);
    ConsoleHelper::ShowConsoleCursor(false);


    for (int32 y = 0; y < 25; y++)
    {
        for (int32 x = 0; x < 25; x++)
        {
            // 색상이 무엇인지 추출
            ConsoleColor color = GetTileColor( Pos{ y, x } );

            // 색상 이용해서 블록 색깔 바꿔치기
            ConsoleHelper::SetCursorColor(color);
            cout << TILE;
        }
        cout << endl;
    }
}

// Binary Tree 미로 생성 알고리즘 -> 초록색 점을 순회하면서 1/2 확률로 오른쪽 혹은
// 아래를 초록색으로 만들어준다.
// - Mazes For Programmers
void Board::GenerateMap()
{
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
                _tile[y][x] = TileType::WALL;
            else
                _tile[y][x] = TileType::EMPTY;
        }
    }

    // 랜덤으로 우측 혹은 아래로 길을 뚫는 작업
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            // 빨간색이면 넘어가기
            if (x % 2 == 0 || y % 2 == 0)
                continue;

            // 끝까지 오면 끝
            if (y == _size - 2 && x == _size - 2)
                continue;

            // 맨 아래쪽 -> 오른쪽으로만 가라
            if (y == _size - 2)
            {
                _tile[y][x + 1] = TileType::EMPTY;
                continue;
            }

            // 맨 오른쪽 -> 아래쪽으로만 가라
            if (x == _size - 2)
            {
                _tile[y + 1][x] = TileType::EMPTY;
                continue;
            }

            const int32 randValue = ::rand() % 2;
            if (randValue == 0)
            {
                // 우측 뚫기
                _tile[y][x + 1] = TileType::EMPTY;
            }
            else
            {   // 아래 뚫기
                _tile[y + 1][x] = TileType::EMPTY;
            }

        }
    }

}

TileType Board::GetTileType(Pos pos)
{
    if (pos.x < 0 || pos.x >= _size)
        return TileType::NONE;

    if (pos.y < 0 || pos.y >= _size)
        return TileType::NONE;

    return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
    if (_player && _player->GetPos() == pos)
        return ConsoleColor::YELLOW;

    if (GetExitPos() == pos)
        return ConsoleColor::BLUE;

    TileType tileType = GetTileType(pos);

    switch (tileType)
    {
    case TileType::NONE:
        break;
    case TileType::EMPTY:
        return ConsoleColor::GREEN;
        break;
    case TileType::WALL:
        return ConsoleColor::RED;
        break;
    }
    
    return ConsoleColor::WHITE;
}
          