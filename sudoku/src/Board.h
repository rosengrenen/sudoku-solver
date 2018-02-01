#pragma once

#include <array>
#include <cassert>
#include <string>

template <int _Size, bool _Vertical>
class Board
{
public:
  Board()
  {
    if (_Size < 4 || _Size > 100)
    {
      throw "Size must not be less than 4, nor greater than 100";
    }
    std::vector<int> factors;
    for (int i = 2; i < _Size / 2 + 1; ++i)
    {
      if (_Size % i == 0)
      {
        factors.push_back(i);
      }
    }
    if (factors.empty())
    {
      throw "Prime numbers are not allowed";
    }
    int larger = factors.size() - 1, smaller = 0;
    int min = _Size;
    for (int i = 0; i < factors.size(); ++i)
    {
      for (int j = i + 1; j < factors.size(); ++j)
      {
        if (factors[j] - factors[i] < factors[smaller] - factors[larger])
        {
          larger = j;
          smaller = i;
        }
      }
    }
    if (factors[larger] > factors[smaller] && !_Vertical)
    {
      std::swap(larger, smaller);
    }
    this->blockWidth = factors[larger];
    this->blockHeight = factors[smaller];
    this->clear();
  };

  void setBoard(const std::string& input)
  {
    this->clear();
    std::stringstream ss;
    for (char i : input)
    {
      if (i == '.')
      {
        ss << '0';
      }
      else if (i - '0' >= 0 && i - '0' <= _Size)
      {
        ss << i - '0';
      }
      else if (i - 'a' >= 0 && i - 'a' <= _Size - 10)
      {
        ss << i - 'a';
      }
    }
    std::string board = ss.str();
    for (int column = 0; column < _Size; ++column)
    {
      for (int row = 0; row < _Size; ++row)
      {
        char value = board.at(row * _Size + column) - '0';
        if (value < 1 || value > _Size)
        {
          this->setSquare(column, row, 0);
        }
        else
        {
          this->setSquare(column, row, value);
        }
      }
    }
    this->initTags();
  }

  void setBoard(const std::array<std::array<int, _Size>, _Size> board)
  {
    this->board = board;
  }

  void setSquare(int column, int row, int value)
  {
    //TODO: assert boundaries
    if (this->board[column][row] > 0)
    {
      this->removeTag(column, row, this->board[column][row] - 1);
    }
    if (value > 0)
    {
      this->addTag(column, row, value - 1);
    }
    this->board[column][row] = value;
  }

  int getSquare(int column, int row) const
  {
    //TODO: asser boundaries
    return this->board[column][row];
  }

  bool isLegal(int column, int row, int value) const
  {
    //TODO: assert boundaries
    if (this->tagColumn[column][value])
    {
      return false;
    }
    if (this->tagRow[row][value])
    {
      return false;
    }
    if (this->tagBlock[column / this->blockWidth + (row / this->blockHeight) * this->blockHeight][value])
    {
      return false;
    }
    return true;
  }

  std::string toString() const
  {
    std::stringstream ss;
    for (int row = 0; row < _Size; ++row)
    {
      for (int column = 0; column < _Size; ++column)
      {
        ss << this->getSquare(column, row);
      }
      ss << std::endl;
    }
    return ss.str();
  }

  std::string toStringFormatted() const
  {
    std::stringstream ss;
    ss << "/";
    for (int i = 0; i < _Size / this->blockWidth; ++i)
    {
      if (i != 0)
      {
        ss << "v";
      }
      for (int j = 0; j < this->blockWidth * 2 + 1; ++j)
      {
        ss << "-";
      }
    }
    ss << "\\" << std::endl;
    for (int row = 0; row < _Size; ++row)
    {
      if (row % this->blockHeight == 0 && row != 0)
      {
        ss << ">";
        for (int i = 0; i < _Size / this->blockWidth; ++i)
        {
          if (i != 0)
          {
            ss << "+";
          }
          for (int j = 0; j < this->blockWidth * 2 + 1; ++j)
          {
            ss << "-";
          }
        }
        ss << "<" << std::endl;
      }
      ss << "| ";
      for (int column = 0; column < _Size; ++column)
      {
        if (column % this->blockWidth == 0 && column != 0)
          ss << "| ";
        if (this->getSquare(column, row) < 1 || this->getSquare(column, row) > _Size)
        {
          ss << " ";
        }
        else
        {
          ss << this->getSquare(column, row);
        }
        ss << " ";
      }
      ss << "|" << std::endl;
    }
    ss << "\\";
    for (int i = 0; i < _Size / this->blockWidth; ++i)
    {
      if (i != 0)
      {
        ss << "^";
      }
      for (int j = 0; j < this->blockWidth * 2 + 1; ++j)
      {
        ss << "-";
      }
    }
    ss << "/" << std::endl;
    return ss.str();
  }

private:
  // TODO: change these numbers
  int blockWidth;
  int blockHeight;
  std::array<std::array<int, _Size>, _Size> board;
  std::array<std::array<bool, _Size>, _Size> tagColumn;
  std::array<std::array<bool, _Size>, _Size> tagRow;
  std::array<std::array<bool, _Size>, _Size> tagBlock;
  void setTag(int column, int row, int value, int flag)
  {
    //TODO: assert boundaries
    this->tagColumn[column][value] = flag;
    this->tagRow[row][value] = flag;
    this->tagBlock[column / this->blockWidth + (row / this->blockHeight) * this->blockHeight][value] = flag;
  }

  void addTag(int column, int row, int value)
  {
    this->setTag(column, row, value, true);
  }

  void removeTag(int column, int row, int value)
  {
    this->setTag(column, row, value, false);
  }

  void initTags()
  {
    for (int column = 0; column < _Size; ++column)
    {
      for (int row = 0; row < _Size; ++row)
      {
        if (this->getSquare(column, row) > 0)
        {
          this->addTag(column, row, this->getSquare(column, row) - 1);
        }
      }
    }
  }

  void clearTags()
  {
    for (int i = 0; i < _Size; ++i)
    {
      for (int value = 0; value < _Size; ++value)
      {
        this->tagColumn[i][value] = false;
        this->tagRow[i][value] = false;
        this->tagBlock[i][value] = false;
      }
    }
  }

  void clearBoard()
  {
    for (int column = 0; column < _Size; ++column)
    {
      for (int row = 0; row < _Size; ++row)
      {
        this->board[column][row] = 0;
      }
    }
  }

  void clear()
  {
    this->clearBoard();
    this->clearTags();
  }
};