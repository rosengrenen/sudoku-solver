#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<math.h>
#include <fstream>
using namespace std;
class Calculator
{
private:
  complex <double> value = 0;
  complex <double> x = 0;
  complex <double> y = 0;
  complex <double> z = 0;
  bool isError = false;
  const double PI = 3.14159265358979;
  const double EULER = 2.71828182845904;
  const complex <double> I = { 0, 1 };
public:
  Calculator()
  { };
  complex <double> getValue()
  {
    return value;
  }
  void setValue(complex <double> numValue)
  {
    value = numValue;
  }
  bool getError()
  {
    return isError;
  }
  void setError(bool errorBool)
  {
    isError = errorBool;
  }
  void error(string text);
  string removeSpaces(string input);
  int factorial(complex <double> n);
  complex <double> power(complex <double> basis, complex <double> exponent);
  complex <double> sin(complex <double> x);
  complex <double> cos(complex <double> x);
  complex <double> tan(complex <double> x);
  complex <double> sinh(complex <double> x);
  complex <double> cosh(complex <double> x);
  complex <double> tanh(complex <double> x);
  complex <double> calc(string input);
  string primfact(string input);
  void output(complex <double> answer);
};
void Calculator::error(string text)
{
  if (isError == true)
  {
    return;
  }
  cout << text << endl;
  isError = true;
  return;
}
string Calculator::removeSpaces(string input)
{
  string output = "";
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] != ' ')
    {
      output = output + input[i];
    }
  }
  return output;
}
int Calculator::factorial(complex <double> num)
{		//derives the factorial num! if num is an integer
  int n = (int) num.real();
  if (num.real() - n != 0 || num.imag() != 0)
  {
    error("factorial can only be used on real integers");
    return 1;
  }
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}
complex <double> Calculator::power(complex <double> basis, complex <double> exponent)
{	//calculates the power recursively, if the exponent is an integer, because it is more accurate then
  if (exponent.imag() == 0 && exponent.real() - (int) exponent.real() == 0)
  {
    if (exponent.real() < 0)
    {
      return (complex <double>)1 / power(basis, -exponent);
    }
    return (exponent.real() == 0) ? 1 : power(basis, exponent - (complex <double>)1) * basis;
  }
  return pow(basis, exponent);
}
complex <double> Calculator::sin(complex <double> x)
{
  return (pow(EULER, I*x) - pow(EULER, -I * x)) / (complex <double>)2 / I;
}
complex <double> Calculator::cos(complex <double> x)
{
  return (pow(EULER, I*x) + pow(EULER, -I * x)) / (complex <double>)2;
}
complex <double> Calculator::tan(complex <double> x)
{
  return sin(x) / cos(x);
}
complex <double> Calculator::sinh(complex <double> x)
{
  return (pow(EULER, x) - pow(EULER, -x)) / (complex <double>)2;
}
complex <double> Calculator::cosh(complex <double> x)
{
  return (pow(EULER, x) + pow(EULER, -x)) / (complex <double>)2;
}
complex <double> Calculator::tanh(complex <double> x)
{
  return sinh(x) / cosh(x);
}
complex <double> Calculator::calc(string input)
{			//input processing function which recursively breaks the input string apart in substrings, and calculates them together afterwards
  int bracketCount = 0;
  vector <int> checklist { };
  string checkchars = "";
  complex <double> num1;
  complex <double> num2;
  int operatorPos;
  int inputSize = input.size();
  if (input == "ans")
  {
    return value;
  }
  if (input == "pi")
  {
    return PI;
  }
  if (input == "e")
  {
    return EULER;
  }
  if (input == "i")
  {
    return I;
  }
  if (input == "x")
  {
    return x;
  }
  if (input == "y")
  {
    return y;
  }
  if (input == "z")
  {
    return z;
  }
  if (input.substr(0, 2) == "x=")
  {
    x = (calc(input.substr(2, input.size() - 2)));
    error("x was set successfully");
    return 1;
  }
  if (input.substr(0, 2) == "y=")
  {
    y = (calc(input.substr(2, input.size() - 2)));
    error("y was set successfully");
    return 1;
  }
  if (input.substr(0, 2) == "z=")
  {
    z = (calc(input.substr(2, input.size() - 2)));
    error("z was set successfully");
    return 1;
  }
  if (input[0] == '+' || input[0] == '-')
  {
    return calc("0" + input);
  }
  if (input.substr(0, 4) == "sin(" && input[inputSize - 1] == ')')
  {
    return sin(calc(input.substr(4, inputSize - 5)));
  }
  if (input.substr(0, 4) == "cos(" && input[inputSize - 1] == ')')
  {
    return cos(calc(input.substr(4, inputSize - 5)));
  }
  if (input.substr(0, 4) == "tan(" && input[inputSize - 1] == ')')
  {
    return tan(calc(input.substr(4, inputSize - 5)));
  }
  if (input.substr(0, 5) == "sinh(" && input[inputSize - 1] == ')')
  {
    return sinh(calc(input.substr(5, inputSize - 6)));
  }
  if (input.substr(0, 5) == "cosh(" && input[inputSize - 1] == ')')
  {
    return cosh(calc(input.substr(5, inputSize - 6)));
  }
  if (input.substr(0, 5) == "tanh(" && input[inputSize - 1] == ')')
  {
    return tanh(calc(input.substr(5, inputSize - 6)));
  }
  if (input.substr(0, 3) == "ln(" && input[inputSize - 1] == ')')
  {
    return log(calc(input.substr(3, inputSize - 4)));
  }
  if (input.substr(0, 4) == "log(" && input[inputSize - 1] == ')')
  {
    return log(calc(input.substr(4, inputSize - 5))) / log(10);
  }
  if (input.substr(0, 5) == "log_(" && input[inputSize - 1] == ')')
  {
    if (input.find(")(", 5) == 4294967295)
    {
      error("logarithm has to be used in one of the forms 'ln()', 'log()', 'log_()()'");
    }
    operatorPos = input.find(")(", 5);
    return log(calc(input.substr(operatorPos + 2, inputSize - operatorPos - 3))) / log(calc(input.substr(5, operatorPos - 5)));
  }
  for (int i = 0; i < inputSize; i++)
  {					//finds out which characters are not part of a bracket
    if (input[i] == '(')
    {
      bracketCount++;
    }
    else if (input[i] == ')')
    {
      bracketCount--;
      if (bracketCount < 0)
      {
        error("too many )");
        return 1;
      }
    }
    else if (bracketCount == 0)
    {
      checklist.push_back(i);
      checkchars = checkchars + input[i];
    }
  }
  if (bracketCount > 0)
  {
    error("not enough )");
    return 1;
  }
  if (checklist.empty() == 1)
  {
    if (inputSize == 0)
    {
      error("syntax error");
      return 1;
    }
    return calc(input.substr(1, inputSize - 2));
  }
  int checkSize = checkchars.size();
  if (checkchars.rfind('+', inputSize) != 4294967295)
  {	//checks for +
    operatorPos = checklist.at(checkchars.rfind('+', checkSize - 1));
    num1 = calc(input.substr(0, operatorPos));
    num2 = calc(input.substr(operatorPos + 1, inputSize - operatorPos - 1));
    return num1 + num2;
  }
  if (checkchars.rfind('-', inputSize) != 4294967295)
  {	//checks for -
    operatorPos = checklist.at(checkchars.rfind('-', checkSize - 1));
    num1 = calc(input.substr(0, operatorPos));
    num2 = calc(input.substr(operatorPos + 1, inputSize - operatorPos - 1));
    return num1 - num2;
  }
  if (checkchars.rfind('*', inputSize) != 4294967295)
  {	//checks for *
    operatorPos = checklist.at(checkchars.rfind('*', checkSize - 1));
    num1 = calc(input.substr(0, operatorPos));
    num2 = calc(input.substr(operatorPos + 1, inputSize - operatorPos - 1));
    return num1 * num2;
    if (checkchars.rfind('/', inputSize) != 4294967295)
    {	//checks for /
    }
    operatorPos = checklist.at(checkchars.rfind('/', checkSize - 1));
    num1 = calc(input.substr(0, operatorPos));
    num2 = calc(input.substr(operatorPos + 1, inputSize - operatorPos - 1));
    return num1 / num2;
  }
  if (checkchars.rfind('%', inputSize) != 4294967295)
  {	//checks for %
    operatorPos = checklist.at(checkchars.rfind('%', checkSize - 1));
    num1 = calc(input.substr(0, operatorPos));
    num2 = calc(input.substr(operatorPos + 1, inputSize - operatorPos - 1));
    if (num1.real() - (int) num1.real() != 0 || num2.real() - (int) num2.real() != 0 || num1.imag() != 0 || num2.imag() != 0)
    {
      error("modulo can only be used on real integers");
      return 1;
    }
    return (int) num1.real() % (int) num2.real();
  }
  if (checkchars.rfind('^', inputSize) != 4294967295)
  {	//checks for ^
    operatorPos = checklist.at(checkchars.rfind('^', checkSize - 1));
    num1 = calc(input.substr(0, operatorPos));
    num2 = calc(input.substr(operatorPos + 1, inputSize - operatorPos - 1));
    return power(num1, num2);
  }
  if (input[inputSize - 1] == '!')
  {						//checks for !
    return factorial(calc(input.substr(0, inputSize - 1)));
  }
  try
  {													//without an operator, the rest of the string has to be a number, or an invalid input
    if (input[inputSize - 1] == 'i')
    {
      return stod(input.substr(0, inputSize - 1))*I;
    }
    if (input[inputSize - 1] == 'x')
    {
      return stod(input.substr(0, inputSize - 1))*x;
    }
    if (input[inputSize - 1] == 'y')
    {
      return stod(input.substr(0, inputSize - 1))*y;
    }
    if (input[inputSize - 1] == 'z')
    {
      return stod(input.substr(0, inputSize - 1))*z;
    }
    return stod(input);
  }
  catch (...)
  {
    error("invalid input");
    return 1;
  }
}
string Calculator::primfact(string input)
{
  complex <double> num = calc(input);
  if (num.imag() != 0 || num.real() - (int) num.real() != 0 || (int) num.real() < 2 || num.real() > 2147483647)
  {
    error("prime factorization can only be used on natural numbers from 2 to 2147483647");
    return "";
  }
  int intNum = (int) num.real();
  int maxPrime = (int) pow(intNum, 0.5);
  string answer = "";
  char letter;
  string prime = "";
  int counter;
  ifstream reader("primes.txt", ios::in);
  while (intNum != 1)
  {
    reader.get(letter);
    if (letter == '\t' || letter == '\n')
    {
      if (stoi(prime) > maxPrime)
      {
        if (answer == "")
        {
          answer = to_string(intNum);
        }
        else
        {
          answer = answer + " * " + to_string(intNum);
        }
        return answer;
      }
      counter = 0;
      while (intNum%stoi(prime) == 0)
      {
        counter++;
        if (counter == 1)
        {
          if (answer == "")
          {
            answer = prime;
          }
          else
          {
            answer = answer + " * " + prime;
          }
        }
        intNum = intNum / stoi(prime);
      }
      if (counter > 1)
      {
        answer = answer + "^" + to_string(counter);
      }
      prime = "";
    }
    else
    {
      prime = prime + letter;
    }
  }
  return answer;
}
void Calculator::output(complex <double> answer)
{
  cout << "ans = ";
  if (answer.imag() == 0)
  {
    cout << answer.real() << endl;
    return;
  }
  if (answer.real() == 0)
  {
    if (answer.imag() == 1)
    {
      cout << "i" << endl;
      return;
    }
    if (answer.imag() == -1)
    {
      cout << "-i" << endl;
      return;
    }
    cout << answer.imag() << "i" << endl;
    return;
  }
  if (answer.imag() < 0)
  {
    if (answer.imag() == -1)
    {
      cout << answer.real() << "-i" << endl;
      return;
    }
    cout << answer.real() << "-" << -answer.imag() << "i" << endl;
    return;
  }
  if (answer.imag() == 1)
  {
    cout << answer.real() << "+i" << endl;
    return;
  }
  cout << answer.real() << "+" << answer.imag() << "i" << endl;
  return;
}
int main()
{
  Calculator ans = Calculator();
  Calculator x = Calculator();
  Calculator y = Calculator();
  Calculator z = Calculator();
  complex <double> answer = 0;
  string input;
  string answerString;
  cout << "I'm a calculator!" << endl;
  cout << "available commands: help, end" << endl;
  while (true)
  {
    ans.setError(false);
    getline(cin, input);
    input = ans.removeSpaces(input);
    if (input == "end")
    {
      return 0;
    }
    if (input == "help")
    {
      cout << "input has to start and end with a number" << endl;
      cout << "brackets () aswell as ans are treated as numbers" << endl;
      cout << "every two numbers have to be seperated by an operator (+,-,*,/,%,^)" << endl;
      cout << "factorial is available" << endl;
      cout << "constants pi and e are available" << endl;
      cout << "complex numbers are available" << endl;
      cout << "trigonometric and hyperbolic functions are available" << endl;
      cout << "logarithm in the form of ln(), log() and log_()() are available" << endl;
    }
    else if (input.substr(0, 9) == "primfact("&&input[input.size() - 1] == ')')
    {
      answerString = ans.primfact(input.substr(9, input.size() - 10));
      if (ans.getError() == false)
      {
        cout << "ans = " << answerString << endl;
      }
    }
    else
    {
      answer = ans.calc(input);
      if (ans.getError() == false)
      {
        ans.setValue(answer);
        ans.output(answer);
      }
    }
  }
}
#if 0
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Generator.h"
#include "Sudoku.h"

#include <random>

int main(int argc, char **argv)
{
  std::random_device rd;
  unsigned int random = rd();
  Generator<> g;
  g.generate();
  std::cout << g.getBoard(true);
  Sudoku<> s;
  s.setBoard(g.getBoard(false));
  std::string board = g.getBoard(false);
  std::cout << s.getBoard(true);
  s.solve();
  std::cout << s.solutions();
  Sudoku<6> sudoku;
  std::ifstream file { "test.txt" };
  std::stringstream ss;
  std::string line;
  while (std::getline(file, line))
  {
    ss << line;
  }
  sudoku.setBoard(ss.str());
  if (sudoku.isSolvable())
  {
    std::cout << "Yes" << std::endl;
    std::cout << sudoku.getSolvedBoards().at(0).toStringFormatted();
  }
  else
  {
    std::cout << "No" << std::endl;
  }
  return 0;
}
#endif
#if 0
/*
 * This program takes a file with n number of sudokus and outputs n
 * number of files containing all the possible solutions to each
 * sudoku.
 */
int main(int argc, char **argv)
{

  std::cout <<
    R"(Usage: "[file-name] [beatify]" where <file-name> is a valid path to a file containing an unsolved sudoku and where <beatify> is an optional parameter which can be either "0" or "1", indicating whether the outputted sudokus are to be formatted nicely.)" << std::endl;
  bool quit = false;
  std::string input;
  while (!quit)
  {
    bool beautify = false;
    std::cout << "> ";
    std::getline(std::cin, input);
    // Parse the input
    std::istringstream iss { input };
    std::vector<std::string> tokens { std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
    if (tokens.size() > 1)
    {
      if (tokens.at(1) == "1")
      {
        beautify = true;
      }
      else
      {
        beautify = false;
      }
    }
    std::ifstream file { tokens.at(0) };
    if (!file.fail())
    {
      quit = true;
      std::stringstream ss;
      std::string line;
      while (std::getline(file, line))
      {
        ss << line;
      }
      if (ss.str().size() % 81 != 0)
      {
        std::cout << "Invalid file, check for extra whitespaces";
      }
      Sudoku sudoku;
      std::ofstream output;
      for (int i = 0; i < ss.str().size() / 81; ++i)
      {
        sudoku.setBoard(ss.str().substr(81 * i, 81));
        sudoku.solve();
        auto solutions = sudoku.getSolvedBoards();
        output.open("sudoku-solved-" + std::to_string(i) + ".txt");
        output << "This sudoku has " << solutions.size() << " solution" << (solutions.size() == 1 ? "" : "s") << std::endl;
        output << sudoku.getBoard(beautify ? true : false) << std::endl;
        if (!solutions.empty())
        {
          output << "Solutions:" << std::endl;
          for (int j = 0; j < solutions.size(); ++j)
          {
            output << "#" << j + 1 << std::endl;
            if (beautify)
            {
              std::string formatted = solutions[j].toStringFormatted();
              output << solutions[j].toStringFormatted();
            }
            else
            {
              output << solutions[j].toString();
            }
          }
        }
        output.close();
      }
    }
    else
    {
      std::cout << "> The file does not exist, or is opened by another process" << std::endl;
    }
  }
  std::cout << "Completed successfully! You should now find one text file for each sudoku entered containing the solutions for each of them." << std::endl;
  std::cout << "Press enter to exit..." << std::endl;
  std::cin.get();
  return 0;
  }
#endif