//
//  SwissTourny.cpp
//  ReditDailyChallenges
//
//  Created by Aamir Jawaid on 2014-07-14.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;


// Slightly modified from the original tokenizeString in RummyChecker. This version converts the strings directly into integers
static const vector<int> tokenizeStrings(string input, string delimiter, int NumberOfSpacesAfterDelimiter)
{
    vector<int> output;
    size_t start;
    size_t found = -1 - NumberOfSpacesAfterDelimiter;  //Two because of spaces after delimiter
    string temp;
    do {
        start = found + 1 + NumberOfSpacesAfterDelimiter;  //Two because of spaces
        found = input.find_first_of(delimiter, start);
        temp = input.substr(start, found - start);
        output.push_back(atoi(&temp[0]));
    } while(found != string::npos);
    return output;
}

void printMatrix(int* matrix, int N)
{
    cout << "\n";
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cout << matrix[r*N + c] << " ";
        }
        cout << "\n";
    }
}
void rotateMatrix(int* matrix, int N)
{
    //Work from outside, and rotate inwards
    double layerLimit = (double)N/2.0;
    for (int layer = 1; layer <= ceil(layerLimit); layer++)
    {
        int tempSource, tempTarget, tempIndex1, tempIndex2;
        for (int i = 0; i < N - 2*layer + 1; i++)
        {
            tempIndex1 = (layer - 1)*N - 1 + layer + i;
            tempIndex2 = (layer - 1)*N + N*(i + 1) -layer;
            tempTarget = matrix[tempIndex2];
            matrix[tempIndex2] = matrix[tempIndex1];
            tempSource = tempTarget;
            tempIndex2 = N*N - (layer - 1)*N - layer - i;
            tempTarget = matrix[tempIndex2];
            matrix[tempIndex2] = tempSource;
            tempSource = tempTarget;
            tempIndex2 = N*(N - i - 1) - (layer - 1)*N + layer - 1;
            tempTarget = matrix[tempIndex2];
            matrix[tempIndex2] = tempSource;
            matrix[tempIndex1] = tempTarget;
        }
    }
}

int main(int argc, char** argv)
{
    int* TwoDArr = nullptr;
    int N = 0;
    string input;
    cout << "N = ";
    getline(cin, input);
    N = atoi(&input[0]);
    TwoDArr = new int[N*N];
    cout << "What is the array?:\n";
    for (int i = 0; i < N; i++)
    {
        getline(cin, input);
        memcpy(&TwoDArr[i*N], &(tokenizeStrings(input, " ", 0))[0], sizeof(int) * N);
    }
    cout << "rotate? y/n: \n";
    getline(cin, input);
    while (input == "y")
    {
        rotateMatrix(TwoDArr, N);
    
        printMatrix(TwoDArr, N);
        cout << "rotate? y/n: \n";
        getline(cin, input);
    }
    //cleanup
    delete[] TwoDArr;
    return 0;
}