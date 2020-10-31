/*
File: proj1scrap.cpp

Project: CMSC 202 Project #1

Author: Hamza Qureshi

Date: 09/24/2020

Section: 23

Email: hamz1@umbc.edu

Description: This program evaluates if a three-word list can be made from previous words when removing exactly one letter. The user can continue to load new lists and check them until they opt out.
*/

//importing all allowed libraries
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int MAXSIZE = 100; // max size of the 2d array
const int MAXFIRST = 6; // max amount of letters for fisrt word
const int MAXSECOND = 5; // max amount of letters for second word
const int MAXTHIRD = 4; // max amount of letters for third word
const int ROWS = 3; // max amount of words in a 2d array
const int MAXFREQ = 256; // max size of letter frequency array, must be 256 because ascii  

int loadFile(string file, char myArray[][MAXSIZE]);
void countLetters(char myArray[][MAXSIZE]);
void checkAnswer(char myArray[][MAXSIZE]);
void checkAnswer2(char myArray[][MAXSIZE]);
void clearList(char myArray[][MAXSIZE]);

int main()
{
  char myArray[MAXSIZE][MAXSIZE] = {{'\0'}};
  
  // tracker used for tracking continuation of program, 0 = continue program, 1 = end program
  int tracker = 0;
  
  string check = "\0"; 
  string file;

  // increments and keeps track of tracker, calls functions
  do
    {
    cout << "Welcome to escalators!" << endl;
    cout << endl;
    
    tracker = loadFile(file, myArray);
    
    cout << endl;
    cout << "Check another list? (y/n):" << endl;
    cin >> check;
    
     // validates user input  
    while(check != "y" && check != "Y" && check != "n" && check != "N")
      {
	check.clear();
	cout << "Invalid selection! Must select y or n" << endl;
	cout << endl;
	cout << "Check another list? (y/n):" << endl;
	cin >> check;
	if(check == "y" or check == "n")
	{
	  break;
	}
      }
    
    if(check == "y" or check == "Y")
      {
	clearList(myArray);
	tracker = 0;
      }
    else if(check == "n" or check == "N")
      {
	cout << "Thank you for using Escalators!" << endl;
	tracker = 1;
      }
  }
  while(tracker == 0);
  
  return 0;
}

// Name: loadFile
// Opens given file, reads into 2-D array, calls countLetter function, returns user input tracker

int loadFile(string file, char myArray[][MAXSIZE])
{
  
  int tracker = 0;
  ifstream myFile;
  
  cout << "Enter a file:" << endl;
  cin >> file;
  myFile.open(file);

  // takes every line from file and populates array
  if(myFile.is_open())
    {
      for(int i = 0; i < MAXSIZE; i++)
	myFile.getline(myArray[i], MAXSIZE);
      
      countLetters(myArray);
    }
  else
    {
      cout << "No file found." << endl;
      // initialized to 1 to prompt user to end program or not
      tracker = 1;
    }
  
  myFile.close();
  return tracker;
}

// Name: countLeters
// Given 2D array, counts amount of letters in each word and displays them, calls checkAnswer

void countLetters(char myArray[][MAXSIZE])
{
  
   int firstCount = 0; 
   int secondCount = 0;
   int thirdCount = 0;

   // counts number of letters in first word
  for(int i = 0; i < MAXSIZE; i++)
    if(myArray[0][i] != '\0')
      {
	firstCount += 1;
      }

  //counts number of letters in second word
  for(int j = 0; j < MAXSIZE; j++)
    if(myArray[1][j] != '\0')
      {
	secondCount += 1;
      }
  
  // counts number of letter in third word
  for(int k = 0; k < MAXSIZE; k++)
    if(myArray[2][k] != '\0')
      {
	thirdCount += 1;
      }

  // displays the word along with number of letters it has
  if(firstCount == MAXFIRST && secondCount == MAXSECOND && thirdCount == MAXTHIRD)
    {
      cout << "1. " << myArray[0] << " (" << firstCount << " letters)" << endl;
      cout << "2. " << myArray[1] << " (" << secondCount << " letters)" << endl;
      cout << "3. " << myArray[2] << " (" << thirdCount << " letters)" << endl;
      cout << endl;
      checkAnswer(myArray);
    }
  else
    {
      cout << "Words are not correct length!" << endl;
      cout << endl;
      cout << "This is an INVALID list!" << endl;
    }
}

// Name: checkAnswer
// Given 2D array, calculates and compares letter frequency of first two words, calls checkAnswer2
// displays validity based upon first and second word

void checkAnswer(char myArray[][MAXSIZE])
{
 
  int freq[MAXFREQ] = {0};
  int freq2[MAXFREQ] = {0};
  
  // Calculates frequency of characters in first word
  for(int i = 0; myArray[0][i] != '\0'; i++)
    {
      freq[(unsigned char) myArray[0][i]]++;
    }
  
  // calculates frequency of characters in second word
  for(int i = 0; myArray[1][i] != '\0'; i++)
    {
      freq2[(unsigned char) myArray[1][i]]++;
    }
  
  // compares the frequency of letters between first and second word
  for(int i = 0; i < MAXFREQ; i++)
    {
      // when two letter frequencies dont match, compares the rest of the letter frequencies
      if(freq[i] != freq2[i])
	{
	  if(freq[i+1] == freq2[i+1])
	    {
	      // if the letter frequencies of the first word and second word match,
	      // calls checkAnswer2 to compare the frequencies of the second and third words
	      checkAnswer2(myArray);
	      break;
	    }
	  else
	    {
	      cout << "Words are not appropriate letter frequency!" << endl;
	      cout << endl;
	      cout << "This is an INVALID list!" << endl;
	      break;
	    }
	}
    }
}

// Name: checkAnswer2
// Given 2D array, calculates and compares letter frequency of last two words,
// displays validity based upon second and third word

void checkAnswer2(char myArray[][MAXSIZE])
{
  
  int freq2[MAXFREQ] = {0};
  int freq3[MAXFREQ] = {0};

  // calculates letter frequency of second word
  for(int i = 0; myArray[1][i] != '\0'; i++)
    {
      freq2[(unsigned char) myArray[1][i]]++;
    }

  // calculates letter frequency of third word
  for(int i = 0; myArray[2][i] != '\0'; i++)
    {
      freq3[(unsigned char) myArray[2][i]]++;
    }
  
  // compares letter frequencies 
  for(int i = 0; i < MAXFREQ; i++)
    {
      if(freq2[i] != freq3[i])
	{
	  if(freq2[i+1] == freq3[i+1])
	    {
	      cout << "List is VALID!" << endl;
	      break;
	    }
	  else
	    {
	      cout << "Words are not appropriate letter frequency!" << endl;
	      cout << endl;
	      cout << "This is an INVALID list!" << endl;
	      break;
	    }
	}
    }
}

// Name: clearList
// Given 2D array, clears entire array

void clearList(char myArray[][MAXSIZE])
{
  // iterates through each value and sets it equal to null like the original array
  for(int i = 0; i <= ROWS; i++)
    {
      for(int j = 0; j < MAXSIZE; j++)
	{
	  myArray[i][j] = {'\0'};
	}
    }
}
