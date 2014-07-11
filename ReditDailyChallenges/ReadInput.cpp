//
//  main.cpp
//  ReditDailyChallenges
//
//  Created by Aamir Jawaid on 2014-07-10.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//

//WEEK 1
//Lets read in strings. we will give n the number of strings then the strings.
//Example:
//5
//Huey
//Dewey
//Louie
//Donald
//Scrooge


/*
The following solution is okay, but it doesn't really handle spaces that will so if you pasted somethinglike
3
Billy 92 87 96
Sarah 98 97 95
Joe 100 94 96

you would get

3
Billy 92 87 96
Sarah 98 97 95
Joe 100 94 96The strings inputted were:
Billy
92
87
Program ended with exit code: 0

#include <iostream>
using namespace std;
int main(int argc, const char * argv[])
{
    int NumberOfStrings = 0;
    cin >> NumberOfStrings;
    string* AllStrings = new string[NumberOfStrings];
    
    for (int i = 0; i < NumberOfStrings; i++)
        cin >> AllStrings[i];
    cout << "The strings inputted were:\n";
    for (int i = 0; i < NumberOfStrings; i++)
        cout << AllStrings[i] + "\n";
    delete[] AllStrings;
    return 0;
}
*/

/*
 The following solution is okay, but it doesn't really handle spaces that will so if you pasted somethinglike
 3
 Billy 92 87 96
 Sarah 98 97 95
 Joe 100 94 96
 
 you would get
 
 3
 Billy 92 87 96
 Sarah 98 97 95
 Joe 100 94 96The strings inputted were:
 Billy
 92
 87
 Program ended with exit code: 0
 */
 #include <iostream>
 #include <vector>
 using namespace std;
 int main(int argc, const char * argv[])
 {
     // Vector is a more powerful data structure
     vector<string> myStrings;
     int n = 0;
     string temp;
     getline(cin, temp);
     n = atoi(&temp[0]);
     //cin.ignore();   //needed to clear the buffer it seems.
     for (int i = 0; i < n; ++i)
     {
         getline(cin, temp);
         myStrings.push_back(temp);
     }
     cout << "The strings inputted were: \n";
     for (vector<string>::iterator iter = myStrings.begin(); iter != myStrings.end(); ++iter)
     {
         cout << *iter + "\n";
     }
     
 }


