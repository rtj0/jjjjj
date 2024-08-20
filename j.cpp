#include "../helper/combat.cpp"
/**
 * @brief Calculates the sum of two integers.
 * 
 * This function adds two integers and returns the result.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * @return The sum of `a` and `b`.
 */
int main()
{
#if defined(_WIN32) || defined(_WIN64)
  SetConsoleSize(800, 600);
#else
  SetTerminalSize(24, 80);
#endif

  // typePrint(getFileContent("../reasources/intro.txt"));
  // combatV1(100, 100, 2000);
  // TicTacToe game;
  // game.startGame();

  CodeGuesser ggame;
  ggame.start();

  return 0;
}