//
//  fare.cpp
//  fare
//
//  Created by Bradley Mont on 10/15/17.
//  Copyright © 2017 Bradley Mont. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    //declare variables
    
    int age;
    string studentStatus;
    string destination;
    int numBoundariesCrossed;
    double fare = 0;
    
    //format precision for printing monetary values
    cout.setf(ios :: fixed);    // fixed notation, not scientific
    cout.precision(2);    // 2 digits to the right of the decimal point (for printing out the fare)
    
    // gather input data
    
    cout << "Age of rider: ";
    cin >> age;
    
    //for when you need to retrieve a string after retrieving an int (so it doesn't take the \n as the string)
    cin.ignore(10000, '\n');    //ignore rest of line
    
    cout << "Student? (y/n) : ";
    getline(cin, studentStatus);
    
    cout << "Destination: ";
    getline(cin, destination);
    
    cout << "Number of zone boundaries crossed: ";
    cin >> numBoundariesCrossed;
    
   
    //print out "---" after
    cout << "---" << endl;
    
    
    //to check if age is negative
    if (age < 0)
    {
        cout << "The age must not be negative" << endl;
    }
    
    //to check if user didn't input y or n for student
    else if (studentStatus != "y" && studentStatus != "n")
    {
        cout << "You must enter y or n" << endl;
    }
    
    //to check if nothing was provided for the destination
    else if (destination == "")
    {
        cout << "You must enter a destination" << endl;
    }
    
    //to check if the number of boundaries crossed is negative
    else if (numBoundariesCrossed < 0)
    {
        cout << "The number of zone boundaries crossed must not be negative" << endl;
    }
    
    //if there are no errors in the user input
    else
    {
        if (numBoundariesCrossed <= 1)   // already have the negative covered - checking for 0 or 1 boundaries
        {
            if (age >= 65) //seniors crossing 0 or 1 boundaries
            {
                if (numBoundariesCrossed == 0) //seniors crossing 0 boundaries pay $0.45
                {
                    fare = 0.45;
                }
                else //seniors crossing 1 boundary
                {
                    if (studentStatus == "y") //seniors can use student discount to get cheapest price
                    {
                        fare = 0.65;
                    }
                    else // seniors that aren't students crossing one boundary
                    {
                        fare = 0.55 + (0.25 * numBoundariesCrossed); //fare is $0.55 plus $0.25 per boundary crossed
                    }
                }
            }
            else if (age < 18 || studentStatus == "y") //under 18 or students pay $0.65
            {
                fare = 0.65;
            }
            else    //no discount, 0 or 1 boundaries
            {
                fare = 1.35 + (0.55 * numBoundariesCrossed); //fare is $1.35 plus $0.55 per boundary crossed
            }
        }
        else if (age >= 65) //senior citizens crossing more than 1 boundary
        {
            fare = 0.55 + (0.25 * numBoundariesCrossed); //fare is $0.55 plus $0.25 per boundary crossed
        }
        else //no discount applies
        {
            fare = 1.35 + (0.55 * numBoundariesCrossed); //fare is $1.35 plus $0.55 per boundary crossed
        }
        
    //print fare price
    cout << "The fare to " << destination << " is " << "$" << fare << endl;
    }
}
