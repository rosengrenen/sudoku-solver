#pragma once

#include <random>

#include "Board.h"
#include "Sudoku.h"

template <int _Size = 9, bool _Vertical = true>
class Generator
{
public:
  Generator() :
    gen(rd())
  { }
  void generate()
  {
    std::uniform_int_distribution<> dis(0, _Size - 1);
    volatile int column, row, number;
    bool found = false;
    for (int i = 0; i < 20; ++i)
    {
      found = false;
      while (!found)
      {
        // Check if there is a square with only one possible
        column = dis(gen);
        row = dis(gen);
        if (this->board.getSquare(column, row) == 0)
        {
          while (this->board.getSquare(column, row) == 0)
          {
            number = dis(gen);
            if (this->board.isLegal(column, row, number))
            {
              this->board.setSquare(column, row, number + 1);
              found = true;
            }
          }
        }
      }
    }
  }
  std::string getBoard(bool beautify)
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
private:
  Board<_Size, _Vertical> board;
  std::random_device rd;
  std::mt19937 gen;
};