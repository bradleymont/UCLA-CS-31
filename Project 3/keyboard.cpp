//
//  main.cpp
//  keyboard
//
//  Created by Bradley Mont on 10/23/17.
//  Copyright © 2017 Bradley Mont. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;


//function prototypes
bool hasCorrectSyntax(string song);

int encodeSong(string song, string& instructions, int& badBeat);

char encodeNote(int octave, char noteLetter, char accidentalSign);

bool isCorrectBeat(string beat);

bool containsSlash(string song);

bool isCorrectBeatSyntax(string beat);

bool isCorrectNoteSyntax(string note);


int main()
{
    if (hasCorrectSyntax("D5//D/"))
        cout << "Passed test 1: hasCorrectSyntax(\"D5//D/\")" << endl;
    if (!hasCorrectSyntax("D5//Z/"))
        cout << "Passed test 2: !hasCorrectSyntax(\"D5//Z/\")" << endl;
}

//check if a valid song string
bool hasCorrectSyntax(string song)
{
    while (containsSlash(song)) //while the string still has beats left
    {
        for (int k = 0; k < song.size(); k++)
        {
            if (song[k] == '/') //if the end of a beat - to divide into beats
            {
                if (  !    (    isCorrectBeatSyntax(song.substr(0,k))  )  ) //if beat is incorrect, return false
                {
                    return false;
                }
                song = song.substr(k + 1);  //start at the next beat
                k = -1; //reset k to -1 because it is iterated to 0
            }
        }
    }
    return song == "";
}


int encodeSong(string song, string& instructions, int& badBeat)
{
    string tempInstructions;
    if ( !    hasCorrectSyntax(song)   )
    {
        return 1;
    }
    
    while (containsSlash(song))
    {
        int beatCounter = 0;
        for (int k = 0; k < song.size(); k++)
        {
            if (song[k] == '/')
            {
                
                beatCounter++;
                
                int noteCounter = 0;
                string beat = song.substr(0,k);
                for (int n = 1; n < beat.size(); n++)
                {
                    if (isupper(beat[n]))
                    {
                        string note = beat.substr(0, n);
                        noteCounter++;
                        if (note.size() == 1)
                        {
                            tempInstructions += encodeNote(4, note[0], ' ');
                        }
                        else if (note.size() == 2)
                        {
                            if (note[1] == 'b' || note[1] == '#')
                            {
                                tempInstructions += encodeNote(4, note[0], note[1]);
                            }
                            else
                            {
                                tempInstructions += encodeNote(note[1] - 48, note[0], ' ');
                            }
                        }
                        else if (note.size() == 3)
                        {
                            tempInstructions += encodeNote(note[2] - 48, note[0], note[1]);
                        }
                        
                        beat = beat.substr(n);
                        n = 0;
                        
                        if (tempInstructions[tempInstructions.size() - 1] == ' ' && noteCounter != 0)
                        {
                            badBeat = beatCounter;
                            return 2;
                        }
                    }
                }
                
                
                //CHECK LAST NOTE
                string note = beat;
                if (note.size() == 1)
                {
                    tempInstructions += encodeNote(4, note[0], ' ');
                    noteCounter++;
                }
                else if (note.size() == 2)
                {
                    noteCounter++;
                    if (note[1] == 'b' || note[1] == '#')
                    {
                        tempInstructions += encodeNote(4, note[0], note[1]);
                    }
                    else
                    {
                        tempInstructions += encodeNote(note[1] - 48, note[0], ' ');
                    }
                }
                else if (note.size() == 3)
                {
                    noteCounter++;
                    tempInstructions += encodeNote(note[2] - 48, note[0], note[1]);
                }
                if (tempInstructions[tempInstructions.size() - 1] == ' ' && noteCounter != 0)
                {
                    badBeat = beatCounter;
                    return 2;
                }
                
                
                song = song.substr(k + 1);
                k = -1;
                
                if (noteCounter > 1)
                {
                    tempInstructions.insert(tempInstructions.size() - noteCounter, "[");
                    tempInstructions += ']';
                    
                }
                else if (noteCounter == 0)
                {
                    tempInstructions += " ";
                }
                
                noteCounter = 0;
                
            }   //GOES WITH THE IF
        }
    }
    
    
    instructions = tempInstructions;
    
    
    return 0;
}




//*************************************
//  encodeNote
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note is encoded as if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  encodeNote(4, 'A', ' ') returns 'Q'
//            encodeNote(4, 'A', '#') returns '%'
//            encodeNote(4, 'H', ' ') returns ' '

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** encodeNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':  note =  0; break;
        case 'D':  note =  2; break;
        case 'E':  note =  4; break;
        case 'F':  note =  5; break;
        case 'G':  note =  7; break;
        case 'A':  note =  9; break;
        case 'B':  note = 11; break;
        default:   return ' ';
    }
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}







bool containsSlash(string song)
{
    for (int k = 0; k < song.size(); k++)
    {
        if (song[k] == '/')
            return true;
    }
    return false;
}





bool isCorrectBeatSyntax(string beat)
{
    
    if (beat == "")
    {
        return true;
    }
    
    
    if (   !     (  beat[0] >= 'A' && beat[0] <= 'G'    )     )
    {
        return false;
    }
    
    
    
    for (int k = 1; k < beat.size(); k++)
    {
        if (isupper(beat[k]))
        {
            if ( ! isCorrectNoteSyntax(beat.substr(0, k)))
            {
                return false;
            }
            beat = beat.substr(k);
            k = 0;
        }
    }
    return isCorrectNoteSyntax(beat);
}



bool isCorrectNoteSyntax(string note)
{
    if ( !   (note[0] >= 'A' && note[0] <= 'G' )    )
    {
        return false;
    }
    
    if (note.size() == 1)
    {
        return true;
    }
    else if (note.size() == 2)
    {
        return  (note[1] == 'b' || note[1] == '#'    ||     (isdigit(note[1]))      );
    }
    else if (note.size() == 3)
    {
        return       ( note[1] == 'b' || note[1] == '#' )    &&      isdigit(note[2]);
    }
    else
    {
        return false;
    }
}
