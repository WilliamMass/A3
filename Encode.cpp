//*******************************************************************************
// (c) William Mass, 2018                                                     
//
// Here are the functions:
// Have user input a message to encode.  Store this code in an array char values.
//    use strlen or int is_space? to determine length of input string.
// Pull a paragraph from a static, pre-created file for encryption.  Look at this
//    string and seperate it at the white spaces, then save each word as an
//    element in the array (string type in array)
//
// 
//
//
// for the paragraph, save each word into an array, then call it forth one
//    element at a time, and replace element zero of each of THOSE elements
//    with the next character in the message.
//
//*******************************************************************************

#include<iostream>
#include<fstream>    // needed to open files
#include<string>     // needed for processing strings

using namespace std;

char encode(char pararray);       // Function to encapsulate the disperate encoding functions
char grabparagraph();                  // Function to open a static file containing a paragraph, and load that paragraph into an array, then return.
char encrypt(char pararray, char encarray);
//int decode();                        // This has been commented out because I couldn't get it working properly
//char unencrypt();                    // Only used by decode, so commented.

int main(int argc, char * argv[])      // avoids passing empty arguments to main
{
   char c;
   grabparagraph;
   while (c != 'e' && c != 'E' && c != 'd' && c != 'D')
   {
      cout << "Would you like to encode or decode a message?" << endl;
      cout << "Please enter E for encode or D for decode:"; 
      if ((c == 'E' || c == 'e'))
         encode();
      else if ((c == 'D' || c == 'd')) { // TODO: toupper/tolower
         c = 0;
         cout << "Apologies, the decoder isn't operable at this time.  Please try again." << endl;
      }
      else {
         cout << "I didn't understand your input. Please try again." << endl;
      }
   }
    return 0;
}

int encode(pararray)
{
   string filename;
   char encarray[1028] = { 0 };
   cout << "Please enter the name of the .txt file where you have stored your secret message: ";
   cin >> filename;
   cout << filename << endl; 
   ifstream in_File(filename.c_str());
   if (in_File.is_open()) {            // converts string input to char to open file
      cout << "File opened." << endl;  // PLACEHOLDER to make sure things are working
      in_File >> encarray;
      encrypt(encarray, pararray);
   }
   else {
      cout << "Error! File '" << &in_File << "' not found!" << endl;
   }
}

/*
int decode( )
{
   string filename;
   char encarray[1028] = { 0 };
   cout << "Please enter the filename of the encoded .txt file: ";
   cin >> filename;
   cout << filename << endl;
   ifstream in_File(filename.c_str()); // converts string input to char to open file
   if (in_File.is_open()) {            
      cout << "File opened." << endl;  // PLACEHOLDER to make sure things are working
      in_File >> encarray;
      // needs to pull first char, then look for white space, then pull each char after white space
   }
   else {
      cout << "Error! File '" << &in_File << "' not found!" << endl;
   }
}
*/

char grabparagraph()
{
   ifstream paragraph;
   char pararray[1028] = { 0 };
   paragraph.open("Paragraph.txt");
   if (paragraph.is_open()) {
      cout << "Loading file to encode message into array... DONE! "; // placeholder message
      paragraph >> pararray;
      return pararray;
   }
   else if (!paragraph.is_open()) {
      cout << "Error, file containing paragraph to code message into not found! " << endl;
   }
}

char encrypt(encarray, pararray)
{
   int y = 0;
   for (int x = 0; x < pararray.len; x++)    // iterates through each position in the paragraph, based on the value of x
   {
      if (y != encarray.length())      // needs () because it's a function
      {
         // iterate through, finding the first letter of the paragraph, then continue on to each letter directly after a white space
         pararray[x] = encarray[y++];    // writes the encode array value to the appropriate encode array, then increments y
      }
   }
}
