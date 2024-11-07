/*
Vigenere Ciper
By: Alan Zetzer

This is a Vigenere Cipher that takes in a file as an argument and encrypts/decrypts
the contents based on a password. the contents are then put into "encrypted.txt" or
"out.txt" depending on the function selected.

The method only works for Linux systems as the line feed char is used to denote the
end of the string.

Some future imporvements for this program would be dymamic memory allocation for the
strings invloved, and encrypting more than one line by taking into account factors such as tab
and line feed.
*/
#include <stdio.h>
#include <string.h>
#define sideLen 95
#define LF 0x0a

//encrypts input using vigenere table and password
char* encrypt(char array[sideLen][sideLen], char* inputString, char* password)
{
        int inputLen = strlen(inputString);
        static char codeString[500];
        int passwordLen = strlen(password);
        for(int i = 0; i < inputLen; i++){
                codeString[i] = array[(int)inputString[i] - 32][(int)password[i%passwordLen] - 32];
        }
        codeString[inputLen] = LF;
        codeString[inputLen + 1] =  '\0';
        return codeString;
}

//decrypts input using the vigenere table and password to return original string
char* decrypt(char array[sideLen][sideLen], char* codeString, char* password)
{
        int codeLen = strlen(codeString);
        static char deciperedString[500];
        int passwordLen = strlen(password);
        for(int i = 0; i < codeLen; i++){
                int count = 0;
                int row = (int)password[i % passwordLen] - 32;
                while(array[row][count] != codeString[i]){
                        count++;
                }
                deciperedString[i] = array[0][count];
        }
        deciperedString[codeLen] = LF;
        deciperedString[codeLen + 1] = '\0';
        return deciperedString;
}

//display menu / get option
int menu(void)
{
        printf("Enter '1' to encrypte.\nEnter '2' to decipher.\nEnter '3' to quit.\n");
        int selection;
        scanf("%d", &selection);
        return selection;
}


int main(int argc, char* argv[])
{
    //get input file
    FILE* filePtr;
    filePtr = fopen(argv[1], "r");
    if(NULL == filePtr){printf("file can not be opened:(\n");}
    char inputString[500];
    char password[20];

    int fileLen = 0;
    char ch = fgetc(filePtr);
    //read first line of file
    while(ch != LF){
       inputString[fileLen++] = ch;
       ch = fgetc(filePtr);
    }
    fclose(filePtr);

    //generate table
    char newTable[sideLen][sideLen];
    for(int i = 0; i < sideLen; i++){
        for(int k = 0; k < sideLen; k++) {
            newTable[i][k] = ' ' + (i + k) % sideLen;
        }
    }

    printf("Welcome to the VIGENERE CIPHER!\n");
    int option = menu();

    //encrpt a file and export to encrypt.txt
    if(option == 1){
       printf("Enter new password(no spaces): ");
       scanf("%s", password);
       char* result = encrypt(newTable, inputString, password);
       printf("Result: %sSaved to encrypt.txt\n", result);
       FILE* encryped = fopen("encrypt.txt", "w");
       if(encryped != NULL){fprintf(encryped, "%s", result);}

    //decrypt a file and export to out.txt
    }else if(option == 2){
       printf("Enter password for file: ");
       scanf("%s", password);
       char* result = decrypt(newTable, inputString, password);
       printf("Result: %sSaved to out.txt\n", result);
       FILE* fout = fopen("out.txt", "w");
       if(fout != NULL){fprintf(fout, "%s", result);}

    //exit
    }else{return 0;}
}