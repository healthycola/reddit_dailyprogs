//
//  File.cpp
//  ReditDailyChallenges
//
//  Created by Aamir Jawaid on 2014-07-12.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//
// Response to RummyChecker challenge on Reddit
// http://www.reddit.com/r/dailyprogrammer/comments/2a9u0a/792014_challenge_170_intermediate_rummy_checker/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;
int RunLength = 3;
int SetLength = 3;

enum Suite
{
    Spades, Hearts, Clubs, Diamonds, Unknown
};

static const vector<string> tokenizeStrings(string input, string delimiter, int NumberOfSpacesAfterDelimiter)
{
    vector<string> output;
    size_t start;
    size_t found = -1 - NumberOfSpacesAfterDelimiter;  //Two because of spaces after delimiter
    string temp;
    do {
        start = found + 1 + NumberOfSpacesAfterDelimiter;  //Two because of spaces
        found = input.find_first_of(delimiter, start);
        temp = input.substr(start, found - start);
        output.push_back(temp);
    } while(found != string::npos);
    return output;
}


struct Card
{
    Suite m_suite;
    int m_value;
    
    static const string CardValues[13];
    static const string CardSuits[4];
    static const int ConvertCardValueToInt(string Card)
    {
        int output = 0;
        if (Card == "ace"){
            output = 1;
        }
        else if (Card == "king"){
            output = 13;
        }
        else if (Card == "queen"){
            output = 12;
        }
        else if (Card == "jack"){
            output = 11;
        }
        else if (Card == "ten"){
            output = 10;
        }
        else if (Card == "nine"){
            output = 9;
        }
        else if (Card == "eight"){
            output = 8;
        }
        else if (Card == "seven"){
            output = 7;
        }
        else if (Card == "six"){
            output = 6;
        }
        else if (Card == "five"){
            output = 5;
        }
        else if (Card == "four"){
            output = 4;
        }
        else if (Card == "three"){
            output = 3;
        }
        else if (Card == "two"){
            output = 2;
        }
        else
        {
            output = 0;
        }
        return output;
    }
    
    static const string ConvertIntToCardValue(int Val)
    {
        if (Val > 0 && Val <= 13)
            return CardValues[Val - 1];
        
        return "";
    }

    
    static const Suite ConvertCardStringToSuite(string input)
    {
        Suite s = Unknown;
        if (input == "spades")
            s = Spades;
        else if (input == "hearts")
            s = Hearts;
        else if (input == "clubs")
            s = Clubs;
        else if (input == "diamonds")
            s = Diamonds;
        
        return s;
    }
    
    static const string ConvertCardSuitToString(Suite input)
    {
        if (input >= 0 && input <= 3)
            return CardSuits[input];
        
        return "";
    }

    
    Card(string CardInput)
    {
        //Accepts inputs such as Ace of Diamonds
        vector<string> temp = tokenizeStrings(CardInput, " ", 0);
        m_value = ConvertCardValueToInt(temp[0]);
        m_suite = ConvertCardStringToSuite(temp[2]);
    }
};

const string Card::CardValues[13] = { "ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king" };
const string Card::CardSuits[4] = { "spades", "hearts", "clubs", "diamonds" };

template <class T>
void deletePtr(T* ptr)
{
    delete ptr;
}


struct Hand
{
    vector<Card*> m_hand;
    void AddCard(Card *card)
    {
        m_hand.push_back(card);
    }
    
    void cleanUp()
    {
        for_each(m_hand.begin(), m_hand.end(), deletePtr<Card>);
    }
    
    static bool sorter(Card* i, Card* j)
    {
        if (i->m_suite != j->m_suite)
            return (int)(i->m_suite) < (int)(j->m_suite);
        else
            return i->m_value < j->m_value;
    }
    
    void sortHand()
    {
        sort(m_hand.begin(), m_hand.end(), Hand::sorter);
    }
    
    Card* CheckForSet(Card _card)
    {
        int NewSet = _card.m_value;
        int NumberOfCardsForSet = 1;
        for (vector<Card*>::iterator card = m_hand.begin(); card != m_hand.end(); card++)
        {
            if ((*card)->m_value == NewSet)
                NumberOfCardsForSet++;
        }
        if (NumberOfCardsForSet >= SetLength)
        {
            // Means we have a set
            for (vector<Card*>::iterator card = m_hand.begin(); card != m_hand.end(); card++)
            {
                if ((*card)->m_value != NewSet)
                    return *card;
            }
        }
        return nullptr;
    }
    
    Card* CheckForRun(Card _card)
    {
        //Messy as hell
        vector<Card*> Run;
        bool isRun = false;
        for (vector<Card*>::iterator card = m_hand.begin(); card != m_hand.end(); card++)
        {
            isRun = false;
            if ((*card)->m_suite != _card.m_suite)
            {
                continue;
            }
            
            Run.clear();
            Run.push_back(&_card);
            for (vector<Card*>::iterator card_set = card; card_set != m_hand.end(); card_set++)
            {
                if (Run.size() >= RunLength || (*card_set)->m_suite != _card.m_suite)
                    break;
                Run.push_back((*card_set));
            }
            
            if (Run.size() < RunLength)
            {
                //No runs possible
                isRun = false;
                break;
            }
            
            
            sort(Run.begin(), Run.end(), sorter);
            if ((*(Run.end()-1))->m_value - (*(Run.begin()))->m_value == RunLength - 1)
                isRun = true;
            
            //Found a Run?
            if (isRun)
            {
                vector<Card*>::iterator cardReturn = m_hand.begin();
                for (; cardReturn != m_hand.end(); cardReturn++)
                {
                    bool foundCardReturn = true;
                    for (vector<Card*>::iterator set_check = Run.begin(); set_check != Run.end() - 1; set_check++)
                    {
                        //CHeck if current cardReturn is in the Run.
                        if (*set_check == &_card)
                            continue;
                        
                        if (*cardReturn == *set_check)
                        {
                            // The card we want to return can't be in the set
                            foundCardReturn = false;
                            break;
                        }
                    }
                    if (foundCardReturn)
                    {
                        return *cardReturn;
                    }
                }
                break;
            }
        }
        
        return nullptr;
    }
};

void outputWin(Card* card)
{
    if (card)
    {
        cout << "Swap the new card with " << Card::ConvertIntToCardValue(card->m_value) << " of " << Card::ConvertCardSuitToString(card->m_suite) << " to win!\n";
    }
    else
    {
        printf("No possible winning hand.\n");
    }

}

int main(int argc, char** argv)
{
    //string sampleString = "Two of Diamonds, Three of Diamonds, Four of Diamonds, Seven of Diamonds, Seven of Clubs, Seven of Hearts, Jack of Hearts";
    //string newCard = "Five of Diamonds";
    
    string sampleString, newCard;
    cout << "What is the initial hand?: ";
    getline(cin, sampleString);
    cout << "What is the added hand?: ";
    getline(cin, newCard);
    
    
    Hand myHand;
    //transform everything to lower case
    transform(sampleString.begin(), sampleString.end(), sampleString.begin(), ::tolower);
    transform(newCard.begin(), newCard.end(), newCard.begin(), ::tolower);
    vector<string> hand = tokenizeStrings(sampleString, ",:", 1);
    
    // For each of the cards, we need to create cards out of them
    for (vector<string>::iterator _card = hand.begin(); _card != hand.end(); _card++)
        myHand.AddCard(new Card(*_card));
    myHand.sortHand();
    
    Card* swappableCard = new Card(newCard);
    
    cout << "Checking for a run with length " << RunLength << "\n";
    Card* swappedCard = myHand.CheckForRun(*swappableCard);
    outputWin(swappedCard);
    
    cout << "Checking for a set with length " << SetLength << "\n";
    swappedCard = myHand.CheckForSet(*swappableCard);
    outputWin(swappedCard);
    
    RunLength = 4;
    cout << "Checking for a run with length " << RunLength << "\n";
    swappedCard = myHand.CheckForRun(*swappableCard);
    outputWin(swappedCard);
    
    SetLength = 4;
    cout << "Checking for a set with length " << SetLength << "\n";
    swappedCard = myHand.CheckForSet(*swappableCard);
    outputWin(swappedCard);
    
    
    //Clean up
    delete swappableCard;
    myHand.cleanUp();
    
    return 0;
}