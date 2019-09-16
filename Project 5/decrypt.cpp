
#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include <cctype>
using namespace std;



void make_copy(const char string[], char copy[], int& length) { //makes copies of const strings that i can modify
    int i=0;
    while (string[i] != '\0'){
        copy[i] = string[i];
        length++;
        i++;
        }
    }
void make_copy_crib(const char string[], char copy[], int& length) { //makes copies of const strings that i can modify
    int i=0;
    int j=0;
    while (string[i] != '\0'){
        if (isalpha(string[i]) || (string[i] == ' ' && (j == 0 || copy[j-1] != ' '))) {
        copy[j] = string[i];
        j++;
        length++;
        }
        i++;
    }
   
        
}


void lower(char string[]) { //makes all the characters lowercase, only change the ones you decrypt to uppercase
    int i = 0;
    while (string[i] != '\0') {
        if (isalpha(string[i]))
            string[i] = tolower(string[i]);
        i++;
    }
}

void tokenizer(char string[], int& index, int words[], int length) { //makes an array of ints that tells you the number of letters in each word, basically an array that has e.g. (3,4,5) has three words, the first has 3 chars, the 2nd has 4, the third has 5
    int i = 0;
    int counter = 0;
    index = 0;
   
    
    while (i < length) {
    
        while (!isalpha(string[i]) && i < length) {
            i++;
        }
        
        while (isalpha(string[i]) && i < length) {
            counter++;
            i++;
        }
        
        words[index] = counter;
        index++;
        counter = 0;
        //i++;
    }
    
}


int subsequence(int a1[], int indexCT, int a2[], int indexC, bool& match) { //checks if theres a subsequence using the tokenizers, if a crib phrase has the same amount of words, with the same amount of letters as something in the phrase
    if (indexCT < 0 || indexC < 0)
        return -1;
    
    for (int k1 = 0; k1 < indexCT - indexC + 1; k1++)
        
    {
        match = true;
        for (int k2 = 0; k2 < indexC; k2++)
        {
            if (a1[k1+k2] != a2[k2])
            {
                match = false;
                break;
            }
        }
        if (match) // We never found a mismatch, so they match
            return k1;
    }
    return -1;
}


 void get_words(char ciphertext[], int position, char crib_substring[], int sum) {
 int j = 0;
 for (int i= position; i < position + sum; i++) {
 crib_substring[j] = ciphertext[i];
 j++;
 }
 }


void decrypt_that_shit(char copyc[], int length_crib, int length_original, char copyct[], char copy[]) {
    for (int i=0; i < length_crib; i++) {
        char replace_with = copyc[i];
        char replace = copy[i];
        for (int j=0; j < length_original; j++) {
            if (copyct[j] == replace) {
                copyct[j] = toupper(replace_with);
            }
        }
    }
}

bool decrypt(const char ciphertext[], const char cribc[]) {

char original[4805];
int original_length;
    make_copy(ciphertext, original, original_length);
char crib[4805];
int crib_length;
    make_copy_crib(cribc, crib, crib_length);
    if (crib_length == 0 || original_length == 0) {
        return false;
    }

lower(original);
lower(crib);

int number_of_words_original[4805];
int size_of_number_array_original;
    tokenizer(original, size_of_number_array_original, number_of_words_original, original_length);
int number_of_words_crib[4805];
int size_of_number_array_crib;
    tokenizer(crib, size_of_number_array_crib, number_of_words_crib, crib_length);

bool match;
int position = subsequence(number_of_words_original, size_of_number_array_original, number_of_words_crib, size_of_number_array_crib, match);

int position_of_first_letter = 0;
    int letters = 0;
    for(int i=0; i < position; i++) {
        letters = letters + number_of_words_original[i] + 1;
    }
   
    
char crib_substring_in_original[4805];
get_words(original, letters, crib_substring_in_original, crib_length);

decrypt_that_shit(crib, crib_length, original_length, original, crib_substring_in_original);


if (match == true) {
    for (int i=0; i < original_length; i++) {
        cout << original[i];
    }
    return true;
}
else
    return false;
}

void runtest(const char ciphertext[], const char crib[])
{
    cout << "====== " << crib << endl;
    bool result = decrypt(ciphertext, crib);
    cout << "Return value: " << result << endl;
}

int main()
{
    cout.setf(ios::boolalpha); // output bools as "true"/"false"
    
    //runtest("Zqysrsuu jysqjtsgj bw zrquucwcsx cgwbytqjcbg cu xqgesybmu.\nNrsqus ysrsqus qgo xbzmtsgju obm qzhmcys jb Icfcrsqfu.\nXbg'j ysrsqus qgojdcge stvqyyquucge jb mu; is stvqyyquu bmyusrksu hmcjs isrr.\nzu 31 cu zdqrrsgecge!\n", "CLASSIFIED INFORMATION");
    runtest("Zqysrsuu jysqjtsgj bw zrquucwcsx cgwbytqjcbg cu xqgesybmu.\nNrsqus ysrsqus qgo xbzmtsgju obm qzhmcys jb Icfcrsqfu.\nXbg'j ysrsqus qgojdcge stvqyyquucge jb mu; is stvqyyquu bmyusrksu hmcjs isrr.\nzu 31 cu zdqrrsgecge!\n",
            "CLASSIFIED   --  -   -- !5INFORMATION");
}



