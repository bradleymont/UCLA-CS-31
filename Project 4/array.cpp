//
//  array.cpp
//  array
//
//  Created by Bradley Mont on 10/31/17.
//  Copyright © 2017 Bradley Mont. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;


//function prototypes

int appendToAll(string a[], int n, string value);

int lookup(const string a[], int n, string target);

int positionOfMax(const string a[], int n);

int rotateLeft(string a[], int n, int pos);

int countRuns(const string a[], int n);

int flip(string a[], int n);

int differ(const string a1[], int n1, const string a2[], int n2);

int subsequence(const string a1[], int n1, const string a2[], int n2);

int lookupAny(const string a1[], int n1, const string a2[], int n2);

int split(string a[], int n, string splitter);

void swapValues(string a[], int x, int y);  //for flip

void rotateRight(string a[], int pos);  //for split


int main()
{
    string h[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
    assert(lookup(h, 7, "logan") == 5);
    assert(lookup(h, 7, "diana") == 2);
    assert(lookup(h, 2, "diana") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "selina", "reed", "peter", "sue" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "selina?" && g[3] == "sue?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "peter?" && g[3] == "reed?");
    
    string e[4] = { "diana", "tony", "", "logan" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d[5] = { "reed", "reed", "reed", "tony", "tony" };
    assert(countRuns(d, 5) == 2);
    
    string f[3] = { "peter", "diana", "steve" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "steve" && f[2] == "peter");
    
    assert(split(h, 7, "peter") == 3);
    
    cout << "All tests succeeded" << endl;
}




int appendToAll(string a[], int n, string value)
{
    if (n < 0)  //no negative amount of elements
    {
        return -1;
    }
    
    for (int k = 0; k < n; k++)
    {
        a[k] += value;  //append value to the end
    }
    
    return n;
}



int lookup(const string a[], int n, string target)
{
    if (n <= 0) //if the first array has no positions, you can't return a position
    {
        return -1;
    }
    
    for(int position = 0; position < n; position++)
    {
        if (a[position] == target)  //found an element in the array equal to target
        {
            return position;
        }
    }
    
    return -1;  //no such string found
}




int positionOfMax(const string a[], int n)
{
    if (n <= 0) //if the first array has no positions, you can't return a position
    {
        return -1;
    }
    
    int maxPosition = 0;
    for (int position = 0; position < n; position++)
    {
        if (a[position] > a[maxPosition])   //if it finds a value that's greater than the current max value
        {
            maxPosition = position;
        }
    }
    
    return maxPosition;
}



int rotateLeft(string a[], int n, int pos)
{
    if (n <= 0 || pos >= n)  //if the first array has no positions, you can't return a position. Also, if the pos >= n, it's out of bounds
    {
        return -1;
    }
    
    if (pos == n - 1)   //if it's already in the last position, nothing moves
    {
        return pos;
    }
    
    string lastPosition = a[pos];   //save the value that's being stuck at the last position because it will get copied over in the for loop
    
    for (int position = pos; position < n - 1; position++)
    {
        a[position] = a[position + 1];  //shift left
    }
    
    a[n - 1] = lastPosition;    //put the value in the final position
    
    return pos;
}



int countRuns(const string a[], int n)
{
    if (n < 0)  //no negative amount of elements
    {
        return -1;
    }
    if (n == 0) //zero sequences if no elements
    {
        return 0;
    }
    
    int numSequences = 1;   //as long as there's at least one item, the number of sequences will start at 1
    string currentItem = a[0];
    
    for (int k = 1; k < n; k++) // check the n
    {
        if (a[k] != currentItem)    //if it's the start of a new sequence
        {
            numSequences++;
        }
        
        currentItem = a[k];
    }
    
    return numSequences;
}





int flip(string a[], int n)
{
    if (n < 0)  //no negative amount of elements
    {
        return -1;
    }
    
    
    //start at each end, swap those, move in one spot each, swap those until you hit the middle
    int x = 0;
    int y = n - 1;
    
    while (y > x)   //so there's no repeated swapping
    {
        swapValues(a, x, y);
        x++;
        y--;
    }
    
    return n;
}



int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)   //no negative amount of elements
    {
        return -1;
    }
    
    int lesserN = n1;
    if (n2 < n1)
    {
        lesserN = n2;
    }
    
    for (int position = 0; position < lesserN; position++)
    {
        if (a1[position] != a2[position])   //if the 2 arrays differ at that position
        {
            return position;
        }
    }
    
    return lesserN;
}



int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0 || n2 > n1)    //n2 can't be larger
    {
        return -1;
    }
    
    if (n2 == 0 || (n2 == 0 && n1 == 0))    //if the 2nd sequence is empty, you consider the empty sequence to match at position zero. this also accounts for both empty
    {
        return 0;
    }
    
    int subsequenceLength = 0;
    int startofSubsequence = 0;
    int positionA2 = 0;
    
    for (int positionA1 = 0; positionA1 < n1; positionA1++)
    {
        if (a1[positionA1] == a2[positionA2])   //equal values in both arrays
        {
            if (subsequenceLength == 0) //not currently in a subsequence
            {
                startofSubsequence = positionA1;    //start the subsequence here
            }
            
            subsequenceLength++;
            
            if (subsequenceLength == n2)    //the whole subsequence is in a2
            {
                return startofSubsequence;
            }
            
            positionA2++;
        }
        else    //values differ
        {
            subsequenceLength = 0;
        }
    }

    return -1;  //a1 doesn't contain a2 as a contiguous sequence
}




int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 <= 0 || n2 < 0)    //if the array has no positions, you can't return a position
    {
        return -1;
    }
    
    for (int positionA1 = 0; positionA1 < n1; positionA1++) //go through a1
    {
        for (int positionA2 = 0; positionA2 < n2; positionA2++) //go through a2
        {
            if (a2[positionA2] == a1[positionA1])   //it found an equal value
            {
                return positionA1;
            }
            
        }
    }
    
    return -1;  //no matches
}




int split(string a[], int n, string splitter)
{
    if (n < 0)  //no negative amount of elements
    {
        return -1;
    }
    
    for (int position = 0; position < n; position++)
    {
        
        if (a[position] > splitter)    //greater than splitter
        {
            rotateLeft(a, n, position); //put that value at the end
        }
        
        
        if (a[position] < splitter) //less than splitter - stick at the beginning
        {
            rotateRight(a, position);   //put that value at the beginner
        }
    }
    
    //after rearrangement
    
    for (int k = 0; k < n; k++)
    {
        if (a[k] >= splitter)   //first value not < splitter
        {
            return k;
        }
    }

    return n;
}


void swapValues(string a[], int x, int y)   // for flip
{
    string temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}





void rotateRight(string a[], int pos)   //for split
{
    string firstPosition = a[pos];
 
    for (int k = pos; k > 0; k--)
    {
        a[k] = a[k - 1];
    }
    
    a[0] = firstPosition;
}
