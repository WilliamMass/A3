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
// for the paragraph, save each word into an array, then call it forth one
//    element at a time, and replace element zero of each of THOSE elements
//    with the next character in the message.
//
//*******************************************************************************

#include<iostream>
#include<fstream>    // needed to open files
#include<string>     // needed for processing strings
#include<cstring>    // included for memset command, to easily initalize arrays

using namespace std;

char * encode(char *);                 // Function to encapsulate the disperate encoding functions
char * grabparagraph();                // Function to open a file containing a paragraph and load that paragraph into an array, then return.
void encrypt(char *, char *);          // This function contains the algorithm and performs the encryption
//int decode();                        // This has been commented out because I couldn't get it working properly
//char unencrypt();                    // Only used by decode, so commented.

int main(int argc, char * argv[])      // avoids passing empty arguments to main
{
   int c;                                                            // I know we were supposed to avoid using single char vars. I tried.
   char * pararray = grabparagraph(), * encarray = nullptr;          // initializing to nullptr, it will store encarray after.
   do
   {
      cout << endl << "Would you like to encode or decode a message?" << endl;
      cout << "Please enter E for encode or D for decode:"; 
      c = ::getchar();                             // replacement for cin since we're just getting one char; getchar returns ints and supports EOF 
      if ((c == 'E' || c == 'e'))                  // This could have been accomplished with toupper or tolower
         encode(pararray);                         // calls encode function, passing in the array we'll create in
      else if ((c == 'D' || c == 'd'))
         cout << "Apologies, the decoder isn't operable at this time.  Please try again." << endl;
      else
         cout << "I didn't understand your input. Please try again." << endl;
      if (encarray != nullptr) {          // checking to make sure there's a value in the array
         delete[] encarray;               // shouldn't change pointer, just deletes the memory
         encarray = nullptr;
      }
   } while (c != 'e' && c != 'E' && c != 'd' && c != 'D');
   if (pararray != nullptr) delete[] pararray;     // end of function, making sure it doesn't evaluate to nullptr, and then deletes it
   if (encarray != nullptr) delete[] encarray;     // same, for other array
   return 0;
}

char * encode(char * pararray)
{
   if (pararray == nullptr)               // again, initializing an array to null value without explicitly calling null
      return nullptr;
   string filename;                       // declare a var we'll use to read in a filename from user input
   char * encarray = new char[1028];      // creating the array for the message we'll read in from the user input file
   memset(encarray, 0, 1028);             // initializing it to zero using memset (rather than a for loop)
   cout << "Please enter the name of the .txt file where you have stored your secret message: ";
   cin >> filename;
   cout << filename << endl; 
   ifstream in_File(filename.c_str());    // converts string to char to pass filename correctly to in_File
   if (in_File.is_open()) {               // making sure our input file is open prior to attempting to perform operations on it
      in_File.read(encarray, 1028);       // reads in the entirety of the file.
      encrypt(encarray, pararray);
      ofstream out_File("totallynotasecretmessage.txt"); // after encryption, prepares to write encrypted message to a file.
      if (out_File.is_open()) {                          // checks if the file it just created is open, prior to performing operations on it
         out_File.write(pararray, strlen(pararray)-1);        // Only writes to the end of the filled portion of the paragraph
         out_File.close();                                     // otherwise, it would write the end of string char and cause a weird line break.
         cout << "Sucessfully encrypted message to totallynotasecretmessage.txt!" << endl;
      }
      in_File.close();                    // closing file for memory purposes
   }
   else
      cout << "Error! File not found!" << endl;
   return encarray;
}

/*
int decode()
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

char * grabparagraph()
{
   ifstream paragraph;                          // opens the file we're taking the paragraph from
   char * pararray = new char[1028];            // sets array
   memset(pararray, 0, 1028);                   // memset to initialize array to zero, avoiding a for loop
   paragraph.open("Paragraph.txt");
   if (paragraph.is_open()) {                   // ensures file is open before performing operations
      paragraph.read(pararray, 1028);           // reads the whole paragraph into the array til EOF
      paragraph.close();                        // closes the file up when done, so we avoid memory leaks
   }
   else
      cout << "Error, file containing paragraph to code message into not found! " << endl;
   return pararray;
}

void encrypt(char * encarray, char * pararray)
{
   if (encarray == nullptr || pararray == nullptr)       // checking nullptr to _safely_ look for a null value
      return;
   int y = 0;                                  // another one letter variable, I know... I tried.
   int plen = strlen(pararray);                // plen and elen are the length of the individual arrays
   int elen = strlen(encarray);                // 
   if (elen > 0) elen--;                       // adjusts length so that it doesn't encode the end of string char
   if (plen > 0) plen--;                       // same for plen, but I don't think this is necessary, now that I'm going back and looking?
   for (int x = 0; x < plen; x++)    // iterates through each position in the paragraph, based on the value of x
   {
      if (y != elen)                   // if we aren't at the end of the array where we're storing the user's code
      {
         if (isalnum(pararray[x]) && (x == 0 || (x > 0 && isspace(pararray[x-1])))) // isalnum checks if the char in the paragraph is alphanumeric
         {     // AND checks if it's the first char in the paragraph, or if the char before it is a space (isspace)
            if (y > 0 && isspace(encarray[y-1]))
               pararray[x] = ::toupper(encarray[y++]);
            else
               pararray[x] = encarray[y++];    // writes the encode array value to the appropriate encode array, then increments y
         }    
      }
   }
}
