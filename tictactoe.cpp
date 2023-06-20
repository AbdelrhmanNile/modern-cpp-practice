#include <algorithm>
#include <array>
#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <string>
#include <tuple>
using std::cout, std::endl, std::cin;

class TicTacToe {
public:
  // board is a 3x3 array of chars
  std::array<std::array<char, 3>, 3> board;

  TicTacToe() {
    for (auto &row : board) {
      for (auto &col : row) {
        col = ' ';
      }
    }
  }

  // print board
  void printBoard() {
    cout << "-------------" << endl;
    for (const auto &row : board) {
      for (const auto &col : row) {
        cout << col << " | ";
      }
      cout << endl;
    }
    cout << "-------------" << endl;
  }

  auto posToRowCol(const int &pos) {
    // pos is 1-9
    // 1 2 3
    // 4 5 6
    // 7 8 9
    // convert pos to row and col
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;
    return std::make_tuple(row, col);
  }

  bool isEmpty(const int &pos) {
    auto [row, col] = posToRowCol(pos);
    if (board[row][col] == ' ')
      return true;
    else
      return false;
  }

  void play(const int &pos, const char &player) {
    auto [row, col] = posToRowCol(pos);
    board[row][col] = player;
  }

  // check if player has won
  bool checkWin(const char &player) {
    // check rows
    for (const auto &row : board) {
      auto win = std::all_of(row.begin(), row.end(),
                             [&](const char &c) { return c == player; });
      if (win)
        return true;
    }

    // check cols
    for (int i = 0; i < 3; ++i) {
      auto win = std::all_of(
          board.begin(), board.end(),
          [&](const std::array<char, 3> &row) { return row[i] == player; });
      if (win)
        return true;
    }

    // check all diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
      return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
      return true;

    return false;
  }

  bool isFull() {
    for (const auto &row : board) {
      for (const auto &col : row) {
        if (col == ' ')
          return false;
      }
    }
    return true;
  }

  void startGame() {
    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "Player 1 is X, Player 2 is O" << endl;
    cout << "Player 1 goes first" << endl;
    cout << "Enter a number 1-9 to place your piece" << endl;
    cout << "1 2 3" << endl;
    cout << "4 5 6" << endl;
    cout << "7 8 9" << endl;
    char turn = 'X';
    while (!isFull()) {
      printBoard();
      printf("It is %c turn!\n", turn);
      int pos;
      printf("Enter position: ");
      cin >> pos;

      // check if empty
      if (!isEmpty(pos)) {
        // clear console
        system("clear");
        printf("Position %d is not empty!\n", pos);
        continue;
      }

      // play
      play(pos, turn);

      // check if win
      if (checkWin(turn)) {
        system("clear");
        printBoard();
        printf("%c wins!\n", turn);
        break;
      }

      // check if draw
      if (isFull()) {
        system("clear");
        printBoard();
        printf("Draw!\n");
        break;
      }

      // switch turn
      if (turn == 'X')
        turn = 'O';
      else
        turn = 'X';

      system("clear");
    }
  }
};

int main() {
  TicTacToe game;
  game.startGame();
}