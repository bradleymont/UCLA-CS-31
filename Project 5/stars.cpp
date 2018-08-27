//
//  stars.cpp
//  stars
//
//  Created by Bradley Mont on 11/8/17.
//  Copyright © 2017 Bradley Mont. All rights reserved.
//

#include "utilities.h"
#include <iostream>
#include <cstring>  //to use C strings
#include <cctype>    //for isdigit, islower, etc
using namespace std;

//function prototypes

int runOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);

double calculateAverage(int totalTries, int roundNumber);

bool containsOnlyLowercase(const char word[MAXWORDLEN+1]);

//global constants

const char WORDFILENAME[] = "/Users/bradleymont/Desktop/P5.txt";

const int MAXWORDS = 9000;

int main()
{
    char wordList[MAXWORDS][MAXWORDLEN+1];  //declare an array of C strings from which the secret word will be selected
   
    int nWords = getWords(wordList, MAXWORDS, WORDFILENAME);
    
    if (nWords < 1) //if getWords returns a value less than 1, the program terminates without asking the player how many rounds to play
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }
    
    int numRounds;
    
    cout << "How many rounds do you want to play? ";    //ask the player how many rounds to play
    cin >> numRounds;
    
    if (numRounds <= 0)     //if the number of rounds entered is not positive, terminate the program
    {
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }
    
    int totalTries = 0;     //for calculating average, min, and max
    
    int minTries = 10000;   //extremely large number so the first score will be less than it
    int maxTries = 0;
    
    //for retrieving a c string after an int
    cin.ignore(10000, '\n');
    
    for (int roundNumber = 1; roundNumber < numRounds + 1; roundNumber++)   //play the game "numRounds" times
    {
        cout << "\n";   //skip a line before each round
        
        cout << "Round " << roundNumber << endl;    //print out the round number at the beginning of each round
        
        int randomPosition = randInt(0, nWords - 1);    //generate a random position of a word in the array
        
        cout << "The secret word is " << strlen(wordList[randomPosition]) << " letters long." << endl;
        
        //play a round of the game
        int score = runOneRound(wordList, nWords, randomPosition);
        
        if (score == 1)
        {
            cout << "You got it in 1 try." << endl;
        }
        else
        {
            cout << "You got it in " << score << " tries." << endl;
        }
        
        totalTries += score;    //add the score of the current round to the total score
        
        if (score < minTries)
        {
            minTries = score;
        }
        
        if (score > maxTries)
        {
            maxTries = score;
        }
        
        cout << "Average: " << calculateAverage(totalTries, roundNumber) << ", ";
        cout << "minimum: " << minTries << ", ";
        cout << "maximum: " << maxTries << endl;
    }
}

int runOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum)
{
    //if nWords is not positive, or if wordnum is less than 0 or greater than or equal to nWords, then return −1 without writing to cout.
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords)
    {
        return -1;
    }
    
    int numTries = 0;   //keep track of their "score" (number of attempts taken)
    
    char secretWord[MAXWORDLEN+1];  //declare the secret word (a c-string)
    
    strcpy(secretWord, words[wordnum]); //copy the word at the random position into secretWord
    
    //now the guessing begins
    while (true)    //to allow the user to infinitely keep guessing until he/she guesses the word
    {
        char probeWord[100];        //just in case the user inputs a word larger than 6 letters, have a large initial size
        
        cout << "Probe word: ";
        
        cin.getline(probeWord, 100);    //read in a probe word from the user
        
        //make sure the word is between 4 and 6 letters, and it is all lowercase
        if (    strlen(probeWord) < 4     ||    strlen(probeWord) > 6    ||    (  !  containsOnlyLowercase(probeWord))   )
        {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        
        bool isWordInArray = false;

        for (int k = 0; k < nWords; k++)
        {
            if (strcmp(probeWord,words[k]) == 0)
            {
                isWordInArray = true;
            }
        }

        if (isWordInArray == false)
        {
            cout << "I don't know that word." << endl;
            continue;
        }
        
        numTries++;     //since it is a valid probe word, add to the number of tries
        
        //check if they guessed the word
        if (strcmp(secretWord, probeWord) == 0)
        {
            return numTries;
        }
        
        bool hasStar[MAXWORDLEN];    //an array of bools that represents if a position in probeWord has a star
        bool hasPlanet[MAXWORDLEN];  //an array of bools that represents if a position in probeWord has a planet
        bool secretWordhasEither[MAXWORDLEN];   //an array of bools that represents if a position in secretWord has either a planet or a star
        
        //initialize all the bool arrays to all false
        for (int i = 0; i < MAXWORDLEN; i++)
        {
            hasStar[i] = false;
            hasPlanet[i] = false;
            secretWordhasEither[i] = false;
        }
        
        int stars = 0;
        int planets = 0;
        
        //to check for stars:
        for (int k = 0; probeWord[k] != '\0' && secretWord[k] != '\0'; k++)
        {
            if (probeWord[k] == secretWord[k])
            {
                stars++;
                hasStar[k] = true;
                secretWordhasEither[k] = true;
            }
        }
        
        //to check for planets:
        //first iterate through the probe word
        for (int probePosition = 0; probeWord[probePosition] != '\0'; probePosition++)
        {
            //then iterate through the secret word
            for (int secretPosition = 0; secretWord[secretPosition] != '\0'; secretPosition++)
            {
                if (probeWord[probePosition] == secretWord[secretPosition])
                {
                    if (probePosition != secretPosition     &&     (! hasStar[probePosition])    &&      (! hasPlanet[probePosition])   &&      ( ! secretWordhasEither[secretPosition]) )
                    {
                        planets++;
                        hasPlanet[probePosition] = true;
                        secretWordhasEither[secretPosition] = true;
                    }
                }
            }
        }
        
        cout << "Stars: " << stars << ", Planets: " << planets << endl;
    }
    
    return numTries;
}

double calculateAverage(int totalTries, int roundNumber)
{
    cout.setf(ios :: fixed);    // fixed notation, not scientific
    cout.precision(2);    // 2 digits to the right of the decimal point

    return static_cast<double>(totalTries)/roundNumber;
}

bool containsOnlyLowercase(const char word[MAXWORDLEN+1])
{
    for (int k = 0; word[k] != '\0'; k++)
    {
        if (  !  islower(word[k]))
        {
            return false;
        }
    }
    
    return true;
}
