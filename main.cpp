#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

/// Globals
char matrix[5][5] = {
    '#',
};
char alphabets[100] = {
    '#',
};
string original;

string toUpperCase(string str)
{
    string stringUpper;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] >= 65 && str[i] <= 90) // uppercase
            stringUpper += str[i];
        else if (str[i] >= 97 && str[i] <= 122)
            stringUpper += char(str[i] - 32);
    }

    return stringUpper;
}
string onlyChar(string str)
{

    string chars;
    for (int i = 0; i < str.length(); i++)
    {
        if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))

            chars += str[i];
    }
    return chars;
}
string replaceJWithI(string str)
{
    for (int i = 0; i < str.length(); i++)
        str[i] = str[i] == 'J' ? str[i] - 1 : str[i];
    return str;
}
string unique(string key)
{

    string uniqueKey;
    //take only chars from the key
    key = onlyChar(key);

    /// transforming key into uppercase
    key = toUpperCase(key);

    /// replacing J with I
    key = replaceJWithI(key);

    for (int i = 0; i < key.length(); i++)
    {

        if (key[i] != '#')
        {

            uniqueKey += key[i];
            for (int j = i + 1; j < key.length(); j++)
            {
                if (key[i] == key[j] || key[j] == ' ')
                    key[j] = '#';
            }
        }
    }
    return uniqueKey;
}
bool isChar(char ch)
{
    if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
        return true;
    return false;
}

void createMatrix(string key)
{

    char *ht = alphabets;
    int n = 0;
    int l = int(key.length());
    int _i;
    int _j;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (n < l)
            {
                matrix[i][j] = key[n];
                _i = i;
                _j = j;
                ht[key[n] - 65] = '#';
                n++;
            }
        }
    }
    n = 0;

    int i = _j == 4 ? _i + 1 : _i;
    int j = _j == 4 ? 0 : _j + 1;
    for (; i < 5; i++)
    {
        while (j < 5)
        {
            if (ht[n] != '#' && ht[n] != 'J')
            {
                matrix[i][j] = ht[n];
                j++;
            }
            n++;
        }
        j = 0;
    }
}

void displayMatrix()
{
    cout << "The matrix : " << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int *indexOf(char ch)
{

    //    int index[] = {0, 0};
    int *index = new int[2];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                index[0] = i;
                index[1] = j;
                return index;
            }
        }
    }
    return index;
}

string encrypt(string plainText)
{

    string pairs[100];
    string enPairs[100];

    //take only letters from the plaintext
    plainText = onlyChar(plainText);

    /// transforming plain text into uppercase
    plainText = toUpperCase(plainText);
    /// replacing J with I in plain text
    plainText = replaceJWithI(plainText);

    if (plainText.length() % 2 != 0)
        plainText += 'X';

    int n = 0;
    for (int i = 0; i < plainText.length(); i += 2)
    {
        pairs[n++] = plainText.substr(i, 2);
    }

    for (int i = 0; i < n; i++)
    {
        // cout<<pairs[i]<<endl;
        int i1 = indexOf(pairs[i][0])[0];
        int j1 = indexOf((pairs[i][0]))[1];
        int i2 = indexOf(pairs[i][1])[0];
        int j2 = indexOf((pairs[i][1]))[1];
        // cout<<"("<<i1<<","<<j1<<") ("<<i2<<", "<<j2<<")"<<endl;
        if (i1 != i2 && j1 != j2)
        {
            // diagonal
            enPairs[i] += matrix[i1][j2];
            enPairs[i] += matrix[i2][j1];
        }
        else if (i1 == i2)
        {
            // same row
            j1 = (j1 + 1) % 5;
            j2 = (j2 + 1) % 5;
            enPairs[i] += matrix[i1][j1];
            enPairs[i] += matrix[i2][j2];
        }
        else if (j1 == j2)
        {
            // same column
            i1 = (i1 + 1) % 5;
            i2 = (i2 + 1) % 5;
            enPairs[i] += matrix[i1][j1];
            enPairs[i] += matrix[i2][j2];
        }
    }
    string encryptedText;
    for (int i = 0; i < plainText.length() / 2; i++)
    {
        encryptedText += enPairs[i];
    }

    return encryptedText;
}

void decrypt(string encryptedText)
{

    string pairs[100];
    string enPairs[100];

    int n = 0;
    for (int i = 0; i < encryptedText.length(); i += 2)
    {
        pairs[n++] = encryptedText.substr(i, 2);
    }

    for (int i = 0; i < n; i++)
    {
        // cout << pairs[i] << endl;
        int i1 = indexOf(pairs[i][0])[0];
        int j1 = indexOf((pairs[i][0]))[1];
        int i2 = indexOf(pairs[i][1])[0];
        int j2 = indexOf((pairs[i][1]))[1];
        // cout << "(" << i1 << "," << j1 << ") (" << i2 << ", " << j2 << ")" << endl;
        if (i1 != i2 && j1 != j2)
        {
            // diagonal
            enPairs[i] += matrix[i1][j2];
            enPairs[i] += matrix[i2][j1];
        }
        else if (i1 == i2)
        {
            // same row
            j1 = (j1 - 1) >= 0 ? (j1 - 1) : 5 + (j1 - 1);
            j2 = (j2 - 1) >= 0 ? (j2 - 1) : 5 + (j2 - 1);
            enPairs[i] += matrix[i1][j1];
            enPairs[i] += matrix[i2][j2];
        }
        else if (j1 == j2)
        {
            // same column
            i1 = (i1 - 1) >= 0 ? (i1 - 1) : 5 + (i1 - 1);
            i2 = (i2 - 1) >= 0 ? (i2 - 1) : 5 + (i2 - 1);
            enPairs[i] += matrix[i1][j1];
            enPairs[i] += matrix[i2][j2];
        }
    }
    string decryptedText;
    for (int i = 0; i < encryptedText.length() / 2; i++)
    {

        decryptedText += enPairs[i];
    }
    int k = 0;
    for (int i = 0; i < original.length(); i++)
    {
        if (isChar(original[i]))
        {
            if(original[i] == 'j' ){
                original[i] = 'j';
                k++;
            }
            else if(original[i] == 'J'){
                original[i] = 'J';
                k++;
            }

            else if ((original[i] >= 65 && original[i] <= 90))
            {
                original[i] = toupper(decryptedText[k++]);
            }
            else
                original[i] = tolower(decryptedText[k++]);
        }
    }
}
int main()
{
    cout<<"PLAYFAIR CIPHER"<<endl;
    string key;
    string plainText;
    // plainText = new char[100];

    // initializing alphabets array
    for (int i = 0; i < 26; i++)
        alphabets[i] = char(i + 65);

    // getting the key
    cout << "Enter the key : ";
    getline(cin, key);
    cout << endl;

    // unique characters of the key
    string keyUniqueChars = unique(key);
    // cout<<keyUniqueChars<<endl;

    // creating the matrix
    createMatrix(keyUniqueChars);

    // displaying the matrix
    displayMatrix();

    // getting the plain text
    cout << "Enter the plain text : ";
    getline(cin, plainText);
    cout << endl;
    original = plainText;

    // the encrypted text

    string encryptedText = encrypt(plainText);
    cout << "The encrypted text : " << encryptedText << endl;

    // the decrypted text

    decrypt(encryptedText);
    cout << "The decrypted text : " << original << endl;
}
