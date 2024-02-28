#include<iostream>
#include<cstring>
using namespace std;

///Globals
char matrix[5][5] = {'#',};
char alphabets[100] = {'#',};

char* toUpperCase(char* str ){
    char* stringUpper;
    stringUpper = new char[100];
    int n =0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] >= 65 && str[i] <= 90)//uppercase
            stringUpper[n++] = str[i];
        else if(str[i] >= 97 && str[i] <= 122)
            stringUpper[n++] = char(str[i] - 32);

    }
    stringUpper[n] = '\0';
    return stringUpper;
}
char* replaceJWithI(char str[100]){
    for(int i = 0; i < strlen(str); i++)
        str[i] = str[i] == 'J' ? str[i] - 1 : str[i];
    return str;
}
string unique(char key[100]){

    string uniqueKey;
    /// transforming key into uppercase
    key = toUpperCase(key);
    ///replacing J with I
    key = replaceJWithI(key);
    cout<<key<<endl;
    ///taking only alphabets from the plain text
    string onlyAlpha;
    for(int i = 0; i < strlen(key); i++){
        if(key[i] >= 65 && key[i] <= 90){
            onlyAlpha += key[i];
        }
    }

    for(int i = 0; i < strlen(key); i++){

        if(key[i] != '#' ){

            uniqueKey += key[i];
            for(int j = i + 1; j < strlen(key); j++){
                if( key[i] == key[j] || key[j] == ' ')
                    key[j] = '#';
            }
        }
    }
    return uniqueKey;
}

void createMatrix(string key){

    ///cout<<key<<endl;
    char* ht = alphabets;
    int n = 0;
    int l = int(key.length());
    int _i;
    int _j;
    for(int i = 0; i < 5; i++ ){
        for(int j = 0; j < 5; j++){
            if(n < l){
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
    for(; i < 5; i++) {
        while(j < 5) {
            if(ht[n] != '#' && ht[n] != 'J') {
                matrix[i][j] = ht[n];
                j++;
            }
            n++;
        }
        j = 0;
    }
}

void displayMatrix(){
    cout<<"The matrix : "<<endl;
    for(int i = 0; i < 5; i++ ){
        for(int j = 0; j < 5; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int* indexOf(char ch){

//    int index[] = {0, 0};
    int* index = new int[2];
    for(int i = 0; i < 5; i++ ){
        for(int j = 0; j < 5; j++){
            if(matrix[i][j] == ch){
                index[0] = i;
                index[1] = j;
                return index;
            }
        }
    }
    return index;
}

string encrypt(char* plainText){

    string pairs[100];
    string enPairs[100];

    /// transforming plain text into uppercase
    plainText = toUpperCase(plainText);

    ///replacing J with I in plain text
    plainText = replaceJWithI(plainText);
    cout<<plainText<<endl;

    if(strlen(plainText) % 2 != 0)
        plainText += 'X';


    int n = 0;
    for(int i = 0; i < strlen(plainText); i += 2){
        pairs[n++] = string(1, plainText[i]) + string(1, plainText[i + 1]);
    }


    for(int i = 0; i < n; i++){
        cout<<pairs[i]<<endl;
        int i1 = indexOf(pairs[i][0])[0];
        int j1 = indexOf((pairs[i][0]))[1];
        int i2 = indexOf(pairs[i][1])[0];
        int j2 = indexOf((pairs[i][1]))[1];
        ///cout<<"("<<i1<<","<<j1<<") ("<<i2<<", "<<j2<<")"<<endl;
        if(i1 != i2 && j1 != j2){
            //diagonal
            enPairs[i] += matrix[i1][j2];
            enPairs[i] += matrix[i2][j1];
        }else if(i1 == i2){
            //same row
            j1 = (j1 + 1) % 5;
            j2 = (j2 + 1) % 5;
            enPairs[i] += matrix[i1][j1];
            enPairs[i] += matrix[i2][j2];
        }else if(j1 == j2){
            //same column
            i1 = (i1 + 1) % 5;
            i2 = (i2 + 1) % 5;
            enPairs[i] += matrix[i1][j1];
            enPairs[i] += matrix[i2][j2];
        }

    }
    string encryptedText ;
    for(int i = 0; i < strlen(plainText) / 2; i++){
        encryptedText += enPairs[i];
    }


    return encryptedText;
}

int main(){

    char key[100];
    char* plainText;
    plainText = new char[100];

    //initializing alphabets array
    for (int i = 0; i < 26; i++)
        alphabets[i] = char(i + 65);

    //getting the key
    cout<<"Enter the key : ";
    cin.getline(key, 100);
    cout<<endl;

    //unique characters of the key
    string keyUniqueChars = unique(key);
    //cout<<keyUniqueChars<<endl

    //creating the matrix
    createMatrix(keyUniqueChars);

    //displaying the matrix
    displayMatrix();

    //getting the plain text
    cout<<"Enter the plain text : ";
    cin.getline(plainText, 100);
    cout<<endl;

    //the encrypted text
    cout<<"The encrypted text : ";
    cout<<encrypt(plainText)<<endl;


}
