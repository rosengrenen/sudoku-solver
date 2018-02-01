#pragma once

#include <string>
#include <vector>

#include "Board.h"

template <int _Size = 9, bool _Vertical = true>
class Sudoku
{
public:
  void setBoard(const std::string& input)
  {
    this->solvedBoards.clear();
    this->board.setBoard(input);
  }

  void setBoard(const std::array<std::array<int, _Size>, _Size> board)
  {
    this->solvedBoards.clear();
    this->board.setBoard(board);
  }

  void setBoard(const Board<_Size, _Vertical>& board)
  {
    this->solvedBoards.clear();
    this->board = board;
  }

  std::string getBoard(bool beautify) const
  {
    if (beautify)
    {
      return this->board.toStringFormatted();

    }
    else
    {
      return this->board.toString();
    }
  }

  bool solve()
  {
    if (this->solvedBoards.empty())
    {
      for (int column = 0; column < _Size; ++column)
      {
        for (int row = 0; row < _Size; ++row)
        {

        }
      }
      this->solver();
    }
    return !this->solvedBoards.empty();
  }

  int solutions()
  {
    if (this->solvedBoards.empty())
    {
      this->solver();
    }
    return this->solvedBoards.size();
  }

  const std::vector<Board<_Size, _Vertical>>& getSolvedBoards() const
  {
    return this->solvedBoards;
  }

  bool isSolvable()
  {
    return this->solve();
  }

  bool isUnique()
  {
    if (this->solvedBoards.empty())
    {
      this->solver();
    }
    return this->solvedBoards.size() == 1;
  }
private:
  Board<_Size, _Vertical> board;
  std::vector<Board<_Size, _Vertical>> solvedBoards;
  void solver()
  {
    if (this->solvedBoards.size() > 9999)
    {
      return;
    }
    bool solved = true;
    int xPos = 0, yPos = 0, count, legalValue, min = _Size;
    for (int x = 0; x < _Size; ++x)
    {
      for (int y = 0; y < _Size; ++y)
      {
        if (this->board.getSquare(x, y) == 0)
        {
          solved = false;
          count = 0;
          for (int value = 0; value < _Size; ++value)
          {
            if (this->board.isLegal(x, y, value))
            {
              legalValue = value;
              count++;
            }
          }
          if (count == 0)
          {
            return;
          }
          else if (count == 1)
          {
            this->board.setSquare(x, y, legalValue + 1);
            this->solver();
            this->board.setSquare(x, y, 0);
            return;
          }
          else if (count < min)
          {
            min = count;
            xPos = x;
            yPos = y;
          }
        }
      }
    }
    if (solved)
    {
      this->solvedBoards.push_back(this->board);
      return;
    }
    for (int value = 0; value < _Size; ++value)
    {
      if (this->board.isLegal(xPos, yPos, value))
      {
        this->board.setSquare(xPos, yPos, value + 1);
        this->solver();
      }
    }
    this->board.setSquare(xPos, yPos, 0);
  }
};


