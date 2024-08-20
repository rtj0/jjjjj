#include "toolkit.cpp"
#include "../lib/dependencies.h"
/* TicTacToe */
class TicTacToe
{
private:
    char squares[3][3] =
        {
            {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

public:
    void printBoard()
    {
        std::string arr[2] = {"\n   |   |   ", "\n___|___|___"};

        std::string top = std::string("\n ") + squares[0][0] + " | " + squares[0][1] + " | " + squares[0][2] + " ";
        std::string middle = std::string("\n ") + squares[1][0] + " | " + squares[1][1] + " | " + squares[1][2] + " ";
        std::string bottom = std::string("\n ") + squares[2][0] + " | " + squares[2][1] + " | " + squares[2][2] + " ";

        std::cout << arr[0] + top + arr[1] + arr[0] + middle + arr[1] + arr[0] + bottom + arr[0] << std::endl;
        std::cout.flush();
    }

    void computerTurn()
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        while (true)
        {
            int row = std::rand() % 3;
            int col = std::rand() % 3;

            if (squares[row][col] == ' ')
            {
                squares[row][col] = 'O';
                break;
            }
        }
        std::cout << "\n\n";
        clear(12);
        printBoard();
    }

    bool checkForWin()
    {
        bool wasWin = false;
        // Horizontal Check
        for (int i = 0; i < 3; i++)
        {
            if (squares[i][0] == squares[i][1] && squares[i][0] == squares[i][2] && squares[i][0] != ' ')
            {
                wasWin = true;
            }
        }

        // Vertical check
        for (int i = 0; i < 3; i++)
        {
            if (squares[0][i] == squares[1][i] && squares[0][i] == squares[2][i] && squares[0][i] != ' ')
            {
                wasWin = true;
            }
        }

        // Diagonal Check
        if (squares[0][0] == squares[1][1] && squares[0][0] == squares[2][2] && squares[0][0] != ' ')
        {
            wasWin = true;
        }
        if (squares[0][2] == squares[1][1] && squares[0][2] == squares[2][0] && squares[0][2] != ' ')
        {
            wasWin = true;
        }
        return wasWin;
    }

    void startGame()
    {
        printBoard();
        int row, col;
        int count = 0;
        while (true)
        {
            std::cout << "\nEnter your move (row and column separated by a space, e.g., '1 1'): ";
            std::cin >> row >> col;

            if (std::cin.fail() || row < 1 || row > 3 || col < 1 || col > 3)
            {
                std::cin.clear();            // clear the error flag on cin
                std::cin.ignore(1000, '\n'); // discard invalid input
                std::cout << "Invalid input. Please enter numbers between 1 and 3." << std::endl;
                continue;
            }

            if (squares[row - 1][col - 1] != ' ')
            {
                std::cout << "That square is already taken. Please choose another one." << std::endl;
                continue;
            }

            squares[row - 1][col - 1] = 'X';
            clear(12);
            printBoard();
            if (checkForWin())
            {
                std::cout << "You win!" << std::endl;
                break;
            }
            count++;
            if (count == 9)
            {
                std::cout << "Draw!" << std::endl;
                break;
            }

#ifdef _WIN32
            Sleep(1); // Sleep for 1 second
#else
            sleep(1);
#endif

            computerTurn();
            if (checkForWin())
            {
                std::cout << "You lose!" << std::endl;
                break;
            }
            count++;
            if (count == 9)
            {
                std::cout << "Draw!" << std::endl;
                break;
            }
        }
    }
};

/** CodeGuesser game */
class CodeGuesser
{

private:
    std::vector<std::string> words;
    std::vector<std::string> guesses;
    int index;

    static int generateRandomIndex(size_t size)
    {
        if (size == 0)
        {
            throw std::invalid_argument("Size of words vector must be greater than 0");
        }
        std::random_device rd;                            // Seed
        std::mt19937 gen(rd());                           // Mersenne Twister engine
        std::uniform_int_distribution<> dis(0, size - 1); // Distribution range
        return dis(gen);
    };

public:
    CodeGuesser()
        : words(split(getFileContent("../reasources/cg_words.txt"), '\n')),
          index(generateRandomIndex(words.size())) {}

    void start()
    {
        bool success = false;
        int count = 0;
        while (count < 5)
        {
            std::cout << "Please enter the five lettered passcode: " + std::to_string(5 - count) + " guesses remaining\n\n";
            printGuesses();

            if (addGuess())
            {
                success = true;
                break;
            }
            clear(4 + count);
            count++;
        }

        if (success)
        {
            std::cout << "Passcode Accepted!";
        }
        else
        {
            std::cout << "Too many failed attempts! Please restart";
        }
    }

    bool addGuess()
    {
        // Yellow, Green, Reset
        std::string colorCodes[] = {"\033[43m", "\033[42m", "\033[0m"};
        std::string guess, coloredGuess;
        std::cin >> guess;

        bool correct = true;

        for (int i = 0; i < 5; i++)
        {
            if (words.at(index).at(i) == guess.at(i))
            {
                coloredGuess.append(colorCodes[1] + guess.substr(i, 1) + colorCodes[2] + " ");
                continue;
            }
            else
            {
                correct = false;
            }
            bool contains = false;
            for (int j = 0; j < 5; j++)
            {
                if (words.at(index).at(j) == guess.at(i))
                {
                    contains = true;
                    break;
                }
            }
            if (contains)
            {
                coloredGuess.append(colorCodes[0] + guess.substr(i, 1) + colorCodes[2] + " ");
            }
            else
            {
                coloredGuess.append(guess.substr(i, 1) + " ");
            }
        }
        guesses.push_back(coloredGuess);
        return correct;
    }

    void printGuesses()
    {
        for (const auto &guess : guesses)
        {
            std::cout << guess << "\n";
        }
        std::cout << +"\npasscode: ";
    }

    void printWords()
    {
        for (int i = 0; i < words.size(); i++)
        {
            std::cout << words.at(i) + "\n";
        }
    }
};
