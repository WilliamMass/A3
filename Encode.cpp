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

char * encode(char *);      // Function to encapsulate the disperate encoding functions
char * grabparagraph();     // Function to open a static file containing a paragraph, and load that paragraph into an array, then return.
void encrypt(char *, char *);
//int decode();                        // This has been commented out because I couldn't get it working properly
//char unencrypt();                    // Only used by decode, so commented.

int main(int argc, char * argv[])      // avoids passing empty arguments to main
{
   int c;
   char * pararray = grabparagraph(), * encarray = nullptr;          // initializing to nullptr, it will store encarray after
   do
   {
      cout << endl << "Would you like to encode or decode a message?" << endl;
      cout << "Please enter E for encode or D for decode:"; 
      c = ::getchar();                    // replacement for cin; getchar returns ints and supports EOF 
      if ((c == 'E' || c == 'e'))         // TODO: toupper/tolower
         encode(pararray);
      else if ((c == 'D' || c == 'd'))    // TODO: toupper/tolower
         cout << "Apologies, the decoder isn't operable at this time.  Please try again." << endl;
      else
         cout << "I didn't understand your input. Please try again." << endl;
      if (encarray != nullptr) {
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
   if (pararray == nullptr)
      return nullptr;
   string filename;
   char * encarray = new char[1028];
   memset(encarray, 0, 1028);
   cout << "Please enter the name of the .txt file where you have stored your secret message: ";
   cin >> filename;
   cout << filename << endl; 
   ifstream in_File(filename.c_str()); // converts string to char to pass filename correctly to in_File
   if (in_File.is_open()) {
      in_File.read(encarray, 1028);
      encrypt(encarray, pararray);
      ofstream out_File("totallynotasecretmessage.txt");
      if (out_File.is_open()) {
         out_File.write(pararray, strlen(pararray)-1);        // only writes to the end of the filled portion of the paragraph
         out_File.close();
         cout << "Sucessfully encrypted message to totallynotasecretmessage.txt!" << endl;
      }
      in_File.close();
   }
   else
      cout << "Error! File '" << &in_File << "' not found!" << endl;
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
   ifstream paragraph;
   char * pararray = new char[1028];
   memset(pararray, 0, 1028);
   paragraph.open("Paragraph.txt");
   if (paragraph.is_open()) {
      paragraph.read(pararray, 1028);
      paragraph.close();
   }
   else
      cout << "Error, file containing paragraph to code message into not found! " << endl;
   return pararray;
}

void encrypt(char * encarray, char * pararray)
{
   if (encarray == nullptr || pararray == nullptr)       // checking nullptr to _safely_ look for a null value
      return;
   int y = 0;
   int plen = strlen(pararray);
   int elen = strlen(encarray);
   if (elen > 0) elen--;                       // adjusts length so that it doesn't encode the end of string char
   if (plen > 0) plen--;                       // same for plen
      for (int x = 0; x < plen; x++)    // iterates through each position in the paragraph, based on the value of x
      {
         if (y != elen)
         {
            if (isalnum(pararray[x]) && (x == 0 || (x > 0 && isspace(pararray[x-1]))))
            {
               if (y > 0 && isspace(encarray[y-1]))
                  pararray[x] = ::toupper(encarray[y++]); // accessing global namespace
               else
                  pararray[x] = encarray[y++];    // writes the encode array value to the appropriate encode array, then increments y
            }    
         }
      }
   }
