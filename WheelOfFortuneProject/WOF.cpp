// Creating a Wheel of Fortune inspired game to demonstrate understanding of C++ at a basic level. 
// main is at bottom


#include <iostream>
#include <string>
#include <vector>
#include <random>


class WOF {

    // Creating the list of random sentences the game will choose for the player as well as their guess limit and potential list of prizes
private:
    const std::vector<std::string> sentence = { "apples to apples", "apple", "grape", "orange", "pear", "strawberry", "id like to solve the puzzle" };
    const std::vector<std::string> prizes = { "100", "200", "300", "400", "500", "BANKRUPT", "LOSE A GUESS" };
    const int max_guesses = 6;


    //Initializing variables that will be manipulated later
    std::string puzzle = "";
    std::string unscramble = "";
    std::string guessedLetters = "";
    int prizeMoney = 0;
    int numGuesses = max_guesses;




public:
    // Create Accessors and Mutators to manipulate our puzzle data. This is key to "scrambling" sentences and forming the correct guess iterations.

    std::string getRandomSentence() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, sentence.size() - 1);
        int index = dis(gen);
        unscramble = sentence[index];
        return sentence[index];
    }

    std::string setPuzzle(std::string sentence) {
        std::string notLetterList = "-&!?. ";
        for (size_t i = 0; i < sentence.length(); i++) {
            char currentLetter = sentence[i];
            if (notLetterList.find(currentLetter) != std::string::npos) {
                puzzle += currentLetter;
            }
            else {
                puzzle += "_";
            }
        }
        return puzzle;
    }

    std::string getPuzzle() {
        return puzzle;
    }

    int getPrizeMoney() {
        return prizeMoney;
    }

    std::string getGuessedLetters() {
        return guessedLetters;
    }

    int getNumGuesses() {
        return numGuesses;
    }


    // The main chunk of our game. This checks if the letter has been guessed, if its in the word, and the appropriate response to both.
    void makeGuess(char letter) {
        if (guessedLetters.find(letter) != std::string::npos) {
            std::cout << "You already guessed that letter. Try again." << std::endl;
            std::cout << std::endl;
            return;
        }
        guessedLetters += letter;

        if (unscramble.find(letter) != std::string::npos) {
            std::string newPuzzle = "";
            for (size_t i = 0; i < puzzle.length(); i++) {
                char currentLetter = unscramble[i];
                if (currentLetter == letter) {
                    newPuzzle += letter;
                }
                else {
                    newPuzzle += puzzle[i];
                }
            }
            puzzle = newPuzzle;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, prizes.size() - 1);
            std::string prize = prizes[dis(gen)];
            if (prize != "BANKRUPT" && prize != "LOSE A GUESS") {
                prizeMoney += std::stoi(prize);
            }
            else if (prize == "BANKRUPT") {
                prizeMoney = 0;
                std::cout << "Unlucky! You rolled a BANKRUPT prize and lost your points" << std::endl;
            }
            else {
                numGuesses--;
                std::cout << "Unlucky! You rolled a LOSE A GUESS prize and lost a guess" << std::endl;
            }
        }
        else {
            numGuesses--;
        }

        if (numGuesses == 0) {
            std::cout << "Sorry, you ran out of guesses. The puzzle was: " << unscramble << std::endl;
        }
        std::cout << std::endl;
    }

    // a boolean for checking if the game is over. It will tell us the game is over if there are no guesses or if the word is guessed fully.
    bool isGameOver() {
        return numGuesses == 0 || puzzle.find('_') == std::string::npos;
        
    }

    // This is where the game is being run. It will loop through itself to allow for constant user input until the game is complete
    // while calling functions from within itself.
    void runGame() {

        WOF game;
        std::cout << "Welcome to Wheel of Fortune!" << std::endl;
        std::string sentence = game.getRandomSentence();
        std::cout << "Puzzle: " << game.setPuzzle(sentence) << std::endl;


        while (!game.isGameOver()) {


            std::cout << "Guessed letters: " << game.getGuessedLetters() << std::endl;
            std::cout << "Prize money: " << game.getPrizeMoney() << std::endl;
            std::cout << "Guesses remaining: " << game.getNumGuesses() << std::endl;

            std::cout << "Guess a letter: ";
            char letter;
            std::cin >> letter;
            game.makeGuess(letter);

            if (!game.isGameOver()){
            std::cout << "Puzzle: " << game.getPuzzle() << std::endl;
            std::cout << "-----------------------" << std::endl;
        }
            
        }

        if (game.getPuzzle().find('_') == std::string::npos) {
            std::cout << "Congratulations! You won " << game.getPrizeMoney() << " fake points!" << std::endl;
        }
        else {
            std::cout << "Better luck next time!" << std::endl;
        }

        std::cout << "Would you like to play again? (Y/N)" << std::endl;

        bool booDone = false;
        char YN;
        while (!booDone) {
            std::cin >> YN;
            if (YN == 'Y') {
                booDone = true;
                this->runGame();

            }
            else if (YN == 'N') {
                std::cout << "Thank you for playing!" << std::endl;
                booDone = true;
            }
            else {
                std::cout << "Please enter Y or N to play again or quit" << std::endl;
            }
        }         

    }

};



int main() {
    
    WOF gameOwner;
    gameOwner.runGame();

    

    return 0;
}