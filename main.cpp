#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <charconv>
#include <algorithm>
#include <iterator>

using namespace std;

void print(int guesses = 0) // print the hangman
{ 
    if (guesses >= 1) {cout << "  | ";}
    if (guesses >= 2) {cout << "\n  | ";}
    if (guesses >= 3) {cout << "\n  O ";}
    if (guesses == 4) {cout << "\n /";}
    if (guesses == 5) {cout << "\n /|";}
    if (guesses >= 6) {cout << "\n /|\\";}
    if (guesses == 7) {cout << "\n / ";}
    if (guesses >= 8) {cout << "\n / \\";}
    if (guesses >= 9) {cout << "\n ___";}
    if (guesses == 10) {cout << "\n|   |\nYOU LOST!";}
}

void printoptions() // print options
{
    cout << "\nSelect One The Following Option:"
         << "\n[1] Guess a letter"
         << "\n[2] Guess the word"
         << "\n[3] Check guessed letters"
         << "\n[4] View options again"
         << "\n[5] Quit game" << endl
         << "[6] Check Current Word (FOR TESTING ONLY)\n";
}

void printword(const string word, const vector<char> cg) // function to print
{
    int i;
    for (i = 0; i < word.length(); ++i)
    {
        if (count(cg.begin(), cg.end(), word[i]))
        {
            std::cout << word[i] << " ";
        }
        else
        {
            cout << "_ ";
        }
    }
}

int main()
{
    bool isGameRunning{true};                                                                              // turns the game on or off
    const int maxguesses{10};                                                                              // max number of guess before the user loses
    char input;                                                                                            // for user's letter guesses
    int choice;                                                                                            // for user choice
    string wordinput;                                                                                      // for when user wants to guess the entire word
    vector<char> guessedchar;                                                                              // array for all the letters the user have guessed
    vector<string> list{"special", "random", "roast", "firetruck", "throw", "trend", "blast", "gasoline"}; // list of possible questions
    vector<char> correctguesses;                                                                           // letters that were guessed correctly
    int guesses{0};                                                                                        // number of guesses by the user
    srand(time(NULL));
    int random = rand() % list.size(); // randomise the word
    string word = list[random];
    printoptions(); // to print the options
    // Start Code
    while (isGameRunning == false) // when game is not running
    {
        return 0;
    }
    while (guesses <= maxguesses && isGameRunning == true) // for when game is running
    {    
        cout << "Remaining Guesses: " << maxguesses - guesses << endl;
        print(guesses); // print hangman
        cout << endl;
        if (guesses == maxguesses) // if user has lost the game
        {
            cout << "\nMission Failed. We'll get them next time." << endl;
            cout << "\nThe word is " << word << "." << endl;
            cout << "Would you like to play again? (Y/N)" << endl;
            input = ' '; // resets the char 'input'
            while (input != 'y' || input != 'Y')
            {
                cin >> input;
                if (input == 'y' || input == 'Y')
                {
                    guesses = 0;
                    guessedchar.clear();
                    int random = rand() % list.size(); // randomise the word
                    string word = list[random];
                    printoptions();
                    break;
                }
                else if (input == 'n' || input == 'N')
                {
                    isGameRunning = false;
                }
                else
                {
                    cout << "Invalid option please type either 'y' or 'n'" << endl;
                }
            }
        }
        else if (guesses < maxguesses) // if user still has guesses remaining
        {
            cout << "The word is " << word.length() << " characters long." << endl;
            printword(word, correctguesses); // print the question
            cout << "\nYou have " << word.length() - correctguesses.size() << " letters remaining." << endl;
            cout << "\nChoose your option: ";
            cin >> choice;
            while (cin.fail()) // check for valid input
            {
                cout << "Invalid Input. Please enter a valid number. Enter '4' to view options again" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> choice;
            }
            cout << "\nYou have chosen [" << choice << "]\n";
        }
        switch (choice)
        {
        case 1: // when user decides to guess a letter
            cout << "Enter your letter: ";
            cin >> input;
            if (count(guessedchar.begin(), guessedchar.end(), input))
            {
                cout << "You have chosen that letter. Please choose another." << endl;
            }
            else if (count(word.begin(), word.end(), input))
            {
                guessedchar.push_back(input);
                correctguesses.push_back(input);
                cout << "You are correct!" << endl;
            }
            else
            {
                guesses++;
                guessedchar.push_back(input);
                cout << "Incorrect letter! Try again." << endl;
            }
            if (word.length() == correctguesses.size())
            {
                cout << "Congratulations! You won." << endl;
                cout << "\nThe word is " << word << "." << endl;
                cout << "Would you like to play again? (Y/N)" << endl;
                input = ' '; // resets the char 'input'
                while (input != 'y' || input != 'Y')
                {
                    cin >> input;
                    if (input == 'y' || input == 'Y')
                    {
                        guesses = 0;
                        guessedchar.clear();
                        int random = rand() % list.size(); // randomise the word
                        string word = list[random];
                        printoptions();
                        break;
                    }
                    else if (input == 'n' || input == 'N')
                    {
                        isGameRunning = false;
                    }
                    else
                    {
                        cout << "Invalid option please type either 'y' or 'n'" << endl;
                    }
                }
            }
            break;
        case 2: // when user decides to guess a word
            cout << "WARNING: You lose 2 tries if you fail to guess the word.\nUse lowercase ONLY." << endl;
            cin >> wordinput;
            if (wordinput == word)
            {
                cout << "Congratulations! You won." << endl;
                cout << "\nThe word is " << word << "." << endl;
                input = ' '; // resets the char 'input'
                cout << "Would you like to play again? (Y/N)" << endl;
                while (input != 'y' || input != 'Y')
                {
                    cin >> input;
                    if (input == 'y' || input == 'Y')
                    {
                        guesses = 0;
                        guessedchar.clear();
                        srand(time(NULL));
                        int random = rand() % list.size(); // randomise the word
                        string word = list[random - 1];
                        printoptions();
                        break;
                    }
                    else if (input == 'n' || input == 'N')
                    {
                        isGameRunning = false;
                    }
                    else
                    {
                        cout << "Invalid option please type either 'y' or 'n'" << endl;
                    }
                }
            }
            else
            {
                cout << "\nCorrect...NOT. Try again." << endl;
                guesses += 2;
            }
            break;
        case 3: // when user wants to view all the guessed letter
            if (guessedchar.size() == 0)
            {
                cout << "\nYou have not guessed any letters" << endl;
            }
            else
            {
                cout << "\nguessed letters: ";
                copy(guessedchar.begin(),
                     guessedchar.end(),
                     ostream_iterator<char>(cout, ", "));
                cout << endl;
            }
            break;
        case 4:
            printoptions();
            break;
        case 5: // when user quits the game
            cout << "Quitting Game..." << endl;
            isGameRunning = false;
            break;
        case 6: // FOR TESTING ONLY, checks current word
            cout << word << "\n"
                 << endl;
            break;
        default:
            cout << "Invalid option. Please enter a valid number. Enter '4' to view options again" << endl;
            break;
        }
    }
} // End Code
