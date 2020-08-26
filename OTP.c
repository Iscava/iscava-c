#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <math.h>

// --- Function declaration ---

int *cripto(int *binMessage, int *key, char *msg, int *criptMsg);
int *keyGenerator(char *msg, int *keyArray);
int *decConverter(char *msg, int *decArray);
int *binConverter(int numb, int *binArray);
int xorFunction(int num1, int num2);
int decBinConverter(int *binArray);
char *charDecConverter(int *decArray, char *msg, char *string);

int main(){

    setlocale(LC_ALL,"");
    char opt='t';
    char inputOption[2];
    char *message = (char *) malloc(128);
    int *binMsg = (int *) malloc(4096); // 128(msg) * 8(bin) * 4(bytes)

    char *criptedMsg = (char *) malloc(1024); // 128(msg) * 8(bin)
    int *binCriptedMsg = (int *) malloc(4096); // 128(msg) * 8(bin) * 4(bytes)
    char *keyCharMsg = (char *) malloc(1024); // 128(msg) * 8(bin)
    int *keyMsg = (int *) malloc(4096); // 128(msg) * 8(bin) * 4(bytes)
    char *messageDescript = (char *) malloc(128);
    int *decArray = (int *) malloc(512); // 128(msg) * 4(bytes)

    int *keyArray = (int *) malloc(4096); // 128(msg) * 8(bin) * 4(bytes)
    int *binArray = (int *) malloc(8);
    int *criptMsg = (int *) malloc(4096); // 128(msg) * 8(bin) * 4(bytes)
    int *decArrayList = (int *) malloc(512);// 128 * 4
    char *string = (char *) malloc(128);

    int c;

    while(opt!='0'){
        printf("\n//////////////////////////////////////////////////////////////////////\n\n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        printf("\n*                                                                   *\n*");
        printf("      OTP                                                          *\n");
        printf("*                                                                   *");
        printf("\n*                                                                   *\n*");
        printf("   O que você deseja ?                                             *");
        printf("\n*                                                                   *\n*");
        printf("   Digite 1 para inserir a mensagem a ser criptografada            *");
        printf("\n*                                                                   *\n*");
        printf("   Digite 2 para inserir a mensagem a ser descriptografada         *");
        printf("\n*                                                                   *\n*");
        printf("   Digite 0 para sair do programa                                  *");
        printf("\n*                                                                   *\n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        printf("\n\n   Escolha: ");
        scanf(" %[^\n]s\n", &inputOption);

        opt = inputOption[0];

        if((opt!='0' && opt!='1' && opt!='2') || strlen(inputOption)>1){
            printf("\n   Não existe essa opção. Tente novamente!\n");
            opt='t';
            continue;
        }
        else if(opt=='0'){
            free(message);
            free(binMsg);
            free(criptedMsg);
            free(binCriptedMsg);
            free(keyCharMsg);
            free(keyMsg);
            free(messageDescript);
            free(decArray);
            free(keyArray);
            free(binArray);
            free(criptMsg);
            free(decArrayList);
            free(string);
        }
        else if(opt=='1'){
            printf("\n   ATENÇÃO: A mensagem deve ter no máximo 128 caracteres.\n\n   Insira sua mensagem: ");
            scanf(" %[^\n]s",  &message[0]);
            printf("\n   Sua mensagem em texto: %s\n", message);
            int len = strlen(message) * 8;

                int *decPrt = decConverter(message, decArrayList);
                int x = 0;
                int *binPrt;

                for(int i = 0; i < strlen(message); i++){
                        binPrt = binConverter(decPrt[i], binArray);
                        for(int z = 0; z < 8; z++){
                            binMsg[x] = binPrt[z];
                            x++;
                        }
                }

                //

                c = 0;
                printf("\n   Sua mensagem em binário: ");
                for(int v = 0; v < len; v++){
                    if(c==8){
                        printf(" - ");
                        c=0;
                    }
                    printf(" %d ", binMsg[v]);
                    c++;
                }

                printf("\n");

                //

                c = 0;
                int *keyPrt = keyGenerator(message, keyArray);
                int *msgResult = cripto(binMsg, keyPrt, message, criptMsg);
                printf("\n   Sua mensagem criptografada: ");
                for(int p = 0; p < len; p++){
                    if(c==8){
                        printf(" - ");
                        c=0;
                    }
                    printf(" %d ", msgResult[p]);
                    c++;
                }

                printf("\n");

                //

                c = 0;
                printf("\n   Sua chave: ");
                for(int i = 0; i < len; i++){
                    if(c==8){
                        printf(" - ");
                        c=0;
                    }
                    printf(" %d ", keyPrt[i]);
                    c++;
                }

                printf("\n");

        }
        else if(opt=='2'){

            printf("\n   Insira sua mensagem criptografada: ");
            scanf(" %[^\n]s",  &criptedMsg[0]);
            int msgLen = strlen(criptedMsg);

            for(int i = 0; i < msgLen; i++){
                binCriptedMsg[i] = criptedMsg[i] - '0';
            }

            printf("\n   Insira a key: ");
            scanf(" %[^\n]s",  &keyCharMsg[0]);
            int keyLen = strlen(keyCharMsg);

            for(int i = 0; i < keyLen; i++){
                keyMsg[i] = keyCharMsg[i] - '0';
            }

            if(msgLen!=keyLen){
                printf("\n   A mensagem e a chave não combinam. Tente novamente!\n");
                continue;
            }

            c = 0;
            printf("\n   Sua mensagem criptografada: ");
            for(int p = 0; p < msgLen; p++){
                    if(c==8){
                        printf(" - ");
                        c=0;
                    }
                    printf(" %d ", binCriptedMsg[p]);
                    c++;
            }

            printf("\n");

            c = 0;
            printf("\n   Sua key: ");
            for(int p = 0; p < keyLen; p++){
                    if(c==8){
                        printf(" - ");
                        c=0;
                    }
                    printf(" %d ", keyMsg[p]);
                    c++;
            }

            printf("\n");

            int *msgBinDescript = cripto(binCriptedMsg, keyMsg, criptedMsg, criptMsg);
            c = 0;
            printf("\n   Sua mensagem descriptografada em binário: ");
            for(int p = 0; p < msgLen; p++){
                    if(c==8){
                        printf(" - ");
                        c=0;
                    }
                    printf(" %d ", msgBinDescript[p]);
                    c++;
            }

            printf("\n");

            int binVector[8];
            c = 0;
            for(int p = 0; p < msgLen/8; p++){
                for(int z = 0; z < 8; z++){
                    binVector[z] = msgBinDescript[c];
                    c++;
                }
                decArray[p] = decBinConverter(binVector);
            }

            char *msgCharDescript = charDecConverter(decArray, criptedMsg, string);
            printf("\n   Sua mensagem descriptografada: ");
            for(int p = 0; p < msgLen/8; p++){
                    printf("%c", msgCharDescript[p]);
            }

            printf("\n");

        }


    }
return 0;
}

// --- FUNCTION THAT GENERATES A KEY ---

int *keyGenerator(char *msg, int *keyArray){
    srand(time(NULL));
    int len = strlen(msg) * 8;
    for (int i=0; i < len; i++){
        keyArray[i] = rand() % 2;
    }
    return keyArray;
}

// --- FUNCTION THAT CONVERTS DEC TO BIN ---

int *binConverter(int numb, int *binArray){
    for(int i=7; i>=0; i--){
        binArray[i] = (numb % 2) == 0 ? 0 : 1;
        numb = numb/2;
    }
return binArray;
}

// --- FUNCTION THAT CONVERTS BIN TO DEC ---

int decBinConverter(int *binArray){
    int decNumb = 0;
    int e = 0;
    for(int i=7; i>=0; i--){
        if(binArray[i]==1){
            decNumb += pow(2,e);
        }
        e++;
    }
return decNumb;
}

// --- FUNCTION THAT ENCRYPTS THE MESSAGE ---

int *cripto(int *binMessage, int *key, char *msg, int *criptMsg){
    int len = strlen(msg) * 8;
    for(int i = 0; i < len; i++){
        criptMsg[i] = xorFunction(binMessage[i], key[i]);
    }
return criptMsg;
}

// --- XOR FUNCTION ---

int xorFunction(int num1, int num2){
    if(num1 == num2) return 0;
    else return 1;
}

// --- FUNCTION THAT RETURNS THE DEC OF EACH CHAR OF THE MESSAGE ---

int *decConverter(char *msg, int *decArray){
    for (int i=0; i < strlen(msg); i++){
        switch (msg[i]){
        case '\0': decArray[i] = '\0';
        break;
        case ' ': decArray[i] = 32;
        break;
        case '!': decArray[i] = 33;
        break;
        case '"': decArray[i] = 34;
        break;
        case '#': decArray[i] = 35;
        break;
        case '$': decArray[i] = 36;
        break;
        case '%': decArray[i] = 37;
        break;
        case '&': decArray[i] = 38;
        break;
        case '?': decArray[i] = 39;
        break;
        case '(': decArray[i] = 40;
        break;
        case ')': decArray[i] = 41;
        break;
        case '*': decArray[i] = 42;
        break;
        case '+': decArray[i] = 43;
        break;
        case ',': decArray[i] = 44;
        break;
        case '-': decArray[i] = 45;
        break;
        case '.': decArray[i] = 46;
        break;
        case '/': decArray[i] = 47;
        break;
        case '0': decArray[i] = 48;
        break;
        case '1': decArray[i] = 49;
        break;
        case '2': decArray[i] = 50;
        break;
        case '3': decArray[i] = 51;
        break;
        case '4': decArray[i] = 52;
        break;
        case '5': decArray[i] = 53;
        break;
        case '6': decArray[i] = 54;
        break;
        case '7': decArray[i] = 55;
        break;
        case '8': decArray[i] = 56;
        break;
        case '9': decArray[i] = 57;
        break;
        case ':': decArray[i] = 58;
        break;
        case ';': decArray[i] = 59;
        break;
        case '<': decArray[i] = 60;
        break;
        case '=': decArray[i] = 61;
        break;
        case '>': decArray[i] = 62;
        break;
        //case '?': decArray[i] = 63;
        //break;
        case '@': decArray[i] = 64;
        break;
        case 'A': decArray[i] = 65;
        break;
        case 'B': decArray[i] = 66;
        break;
        case 'C': decArray[i] = 67;
        break;
        case 'D': decArray[i] = 68;
        break;
        case 'E': decArray[i] = 69;
        break;
        case 'F': decArray[i] = 70;
        break;
        case 'G': decArray[i] = 71;
        break;
        case 'H': decArray[i] = 72;
        break;
        case 'I': decArray[i] = 73;
        break;
        case 'J': decArray[i] = 74;
        break;
        case 'K': decArray[i] = 75;
        break;
        case 'L': decArray[i] = 76;
        break;
        case 'M': decArray[i] = 77;
        break;
        case 'N': decArray[i] = 78;
        break;
        case 'O': decArray[i] = 79;
        break;
        case 'P': decArray[i] = 80;
        break;
        case 'Q': decArray[i] = 81;
        break;
        case 'R': decArray[i] = 82;
        break;
        case 'S': decArray[i] = 83;
        break;
        case 'T': decArray[i] = 84;
        break;
        case 'U': decArray[i] = 85;
        break;
        case 'V': decArray[i] = 86;
        break;
        case 'W': decArray[i] = 87;
        break;
        case 'X': decArray[i] = 88;
        break;
        case 'Y': decArray[i] = 89;
        break;
        case 'Z': decArray[i] = 90;
        break;
        case '[': decArray[i] = 91;
        break;
        //case '\': decArray[i] = 92;
        //break;
        case ']': decArray[i] = 93;
        break;
        case '^': decArray[i] = 94;
        break;
        case '_': decArray[i] = 95;
        break;
        //case '?': decArray[i] = 96;
        //break;
        case 'a': decArray[i] = 97;
        break;
        case 'b': decArray[i] = 98;
        break;
        case 'c': decArray[i] = 99;
        break;
        case 'd': decArray[i] = 100;
        break;
        case 'e': decArray[i] = 101;
        break;
        case 'f': decArray[i] = 102;
        break;
        case 'g': decArray[i] = 103;
        break;
        case 'h': decArray[i] = 104;
        break;
        case 'i': decArray[i] = 105;
        break;
        case 'j': decArray[i] = 106;
        break;
        case 'k': decArray[i] = 107;
        break;
        case 'l': decArray[i] = 108;
        break;
        case 'm': decArray[i] = 109;
        break;
        case 'n': decArray[i] = 110;
        break;
        case 'o': decArray[i] = 111;
        break;
        case 'p': decArray[i] = 112;
        break;
        case 'q': decArray[i] = 113;
        break;
        case 'r': decArray[i] = 114;
        break;
        case 's': decArray[i] = 115;
        break;
        case 't': decArray[i] = 116;
        break;
        case 'u': decArray[i] = 117;
        break;
        case 'v': decArray[i] = 118;
        break;
        case 'w': decArray[i] = 119;
        break;
        case 'x': decArray[i] = 120;
        break;
        case 'y': decArray[i] = 121;
        break;
        case 'z': decArray[i] = 122;
        break;
        case '{': decArray[i] = 123;
        break;
        case '|': decArray[i] = 124;
        break;
        case '}': decArray[i] = 125;
        break;
        case '~': decArray[i] = 126;
        break;
        //case '?': decArray[i] = 127;
        //break;
        case 'Ç': decArray[i] = 128;
        break;
        //case '?': decArray[i] = 129;
        //break;
        case 'é': decArray[i] = 130;
        break;
        case 'â': decArray[i] = 131;
        break;
        //case '?': decArray[i] = 132;
        //break;
        case 'à': decArray[i] = 133;
        break;
        //case '?': decArray[i] = 134;
        //break;
        case 'ç': decArray[i] = 135;
        break;
        case 'ê': decArray[i] = 136;
        break;
        //case '?': decArray[i] = 137;
        //break;
        case 'è': decArray[i] = 138;
        break;
        //case '?': decArray[i] = 139;
        //break;
        case 'î': decArray[i] = 140;
        break;
        case 'ì': decArray[i] = 141;
        break;
        //case '?': decArray[i] = 142;
        //break;
        //case '?': decArray[i] = 143;
        //break;
        case 'É': decArray[i] = 144;
        break;
        //case '?': decArray[i] = 145;
        //break;
        //case '?': decArray[i] = 146;
        //break;
        case 'ô': decArray[i] = 147;
        break;
        //case '?': decArray[i] = 148;
        //break;
        case 'ò': decArray[i] = 149;
        break;
        case 'û': decArray[i] = 150;
        break;
        case 'ù': decArray[i] = 151;
        break;
        //case '?': decArray[i] = 152;
        //break;
        //case '?': decArray[i] = 153;
        //break;
        //case '?': decArray[i] = 154;
        //break;
        //case '?': decArray[i] = 155;
        //break;
        //case '?': decArray[i] = 156;
        //break;
        //case '?': decArray[i] = 157;
        //break;
        //case '?': decArray[i] = 158;
        //break;
        //case '?': decArray[i] = 159;
        //break;
        case 'á': decArray[i] = 160;
        break;
        case 'í': decArray[i] = 161;
        break;
        case 'ó': decArray[i] = 162;
        break;
        case 'ú': decArray[i] = 163;
        break;
        case 'ñ': decArray[i] = 164;
        break;
        case 'Ñ': decArray[i] = 165;
        break;
        //case '?': decArray[i] = 166;
        //break;
        case '°': decArray[i] = 167;
        break;
        //case '?': decArray[i] = 168;
        //break;
        //case '?': decArray[i] = 169;
        //break;
        case '¬': decArray[i] = 170;
        break;
        }
    }
return decArray;
}

// --- FUNCTION THAT RETURNS THE CHAR OF EACH DEC OF THE MESSAGE ---

char *charDecConverter(int *decArray, char *msg, char *string){
    for (int i=0; i < strlen(msg)/8; i++){
        switch (decArray[i]){
        case '\0': string[i] = '\0';
        break;
        case 32: string[i] = ' ';
        break;
        case 33: string[i] = '!';
        break;
        case 34: string[i] = '"';
        break;
        case 35: string[i] = '#';
        break;
        case 36: string[i] = '$';
        break;
        case 37: string[i] = '%';
        break;
        case 38: string[i] = '&';
        break;
        case 39: string[i] = '?';
        break;
        case 40: string[i] = '(';
        break;
        case 41: string[i] = ')';
        break;
        case 42: string[i] = '*';
        break;
        case 43: string[i] = '+';
        break;
        case 44: string[i] = ',';
        break;
        case 45: string[i] = '-';
        break;
        case 46: string[i] = '.';
        break;
        case 47: string[i] = '/';
        break;
        case 48: string[i] = '0';
        break;
        case 49: string[i] = '1';
        break;
        case 50: string[i] = '2';
        break;
        case 51: string[i] = '3';
        break;
        case 52: string[i] = '4';
        break;
        case 53: string[i] = '5';
        break;
        case 54: string[i] = '6';
        break;
        case 55: string[i] = '7';
        break;
        case 56: string[i] = '8';
        break;
        case 57: string[i] = '9';
        break;
        case 58: string[i] = ':';
        break;
        case 59: string[i] = ';';
        break;
        case 60: string[i] = '<';
        break;
        case 61: string[i] = '=';
        break;
        case 62: string[i] = '>';
        break;
        case 63: string[i] = '?';
        break;
        case 64: string[i] = '@';
        break;
        case 65: string[i] = 'A';
        break;
        case 66: string[i] = 'B';
        break;
        case 67: string[i] = 'C';
        break;
        case 68: string[i] = 'D';
        break;
        case 69: string[i] = 'E';
        break;
        case 70: string[i] = 'F';
        break;
        case 71: string[i] = 'G';
        break;
        case 72: string[i] = 'H';
        break;
        case 73: string[i] = 'I';
        break;
        case 74: string[i] = 'J';
        break;
        case 75: string[i] = 'K';
        break;
        case 76: string[i] = 'L';
        break;
        case 77: string[i] = 'M';
        break;
        case 78: string[i] = 'N';
        break;
        case 79: string[i] = 'O';
        break;
        case 80: string[i] = 'P';
        break;
        case 81: string[i] = 'Q';
        break;
        case 82: string[i] = 'R';
        break;
        case 83: string[i] = 'S';
        break;
        case 84: string[i] = 'T';
        break;
        case 85: string[i] = 'U';
        break;
        case 86: string[i] = 'V';
        break;
        case 87: string[i] = 'W';
        break;
        case 88: string[i] = 'X';
        break;
        case 89: string[i] = 'Y';
        break;
        case 90: string[i] = 'Z';
        break;
        case 91: string[i] = '[';
        break;
        case 92: string[i] = '?';
        break;
        case 93: string[i] = ']';
        break;
        case 94: string[i] = '^';
        break;
        case 95: string[i] = '_';
        break;
        case 96: string[i] = '?';
        break;
        case 97: string[i] = 'a';
        break;
        case 98: string[i] = 'b';
        break;
        case 99: string[i] = 'c';
        break;
        case 100: string[i] = 'd';
        break;
        case 101: string[i] = 'e';
        break;
        case 102: string[i] = 'f';
        break;
        case 103: string[i] = 'g';
        break;
        case 104: string[i] = 'h';
        break;
        case 105: string[i] = 'i';
        break;
        case 106: string[i] = 'j';
        break;
        case 107: string[i] = 'k';
        break;
        case 108: string[i] = 'l';
        break;
        case 109: string[i] = 'm';
        break;
        case 110: string[i] = 'n';
        break;
        case 111: string[i] = 'o';
        break;
        case 112: string[i] = 'p';
        break;
        case 113: string[i] = 'q';
        break;
        case 114: string[i] = 'r';
        break;
        case 115: string[i] = 's';
        break;
        case 116: string[i] = 't';
        break;
        case 117: string[i] = 'u';
        break;
        case 118: string[i] = 'v';
        break;
        case 119: string[i] = 'w';
        break;
        case 120: string[i] = 'x';
        break;
        case 121: string[i] = 'y';
        break;
        case 122: string[i] = 'z';
        break;
        case 123: string[i] = '{';
        break;
        case 124: string[i] = '|';
        break;
        case 125: string[i] = '}';
        break;
        case 126: string[i] = '~';
        break;
        case 127: string[i] = '?';
        break;
        case 128: string[i] = 'Ç';
        break;
        case 129: string[i] = '?';
        break;
        case 130: string[i] = 'é';
        break;
        case 131: string[i] = 'â';
        break;
        case 132: string[i] = '?';
        break;
        case 133: string[i] = 'à';
        break;
        case 134: string[i] = '?';
        break;
        case 135: string[i] = 'ç';
        break;
        case 136: string[i] = 'ê';
        break;
        case 137: string[i] = '?';
        break;
        case 138: string[i] = 'è';
        break;
        case 139: string[i] = '?';
        break;
        case 140: string[i] = 'î';
        break;
        case 141: string[i] = 'ì';
        break;
        case 142: string[i] = '?';
        break;
        case 143: string[i] = '?';
        break;
        case 144: string[i] = 'É';
        break;
        case 145: string[i] = '?';
        break;
        case 146: string[i] = '?';
        break;
        case 147: string[i] = 'ô';
        break;
        case 148: string[i] = '?';
        break;
        case 149: string[i] = 'ò';
        break;
        case 150: string[i] = 'û';
        break;
        case 151: string[i] = 'ù';
        break;
        case 152: string[i] = '?';
        break;
        case 153: string[i] = '?';
        break;
        case 154: string[i] = '?';
        break;
        case 155: string[i] = '?';
        break;
        case 156: string[i] = '?';
        break;
        case 157: string[i] = '?';
        break;
        case 158: string[i] = '?';
        break;
        case 159: string[i] = '?';
        break;
        case 160: string[i] = 'á';
        break;
        case 161: string[i] = 'í';
        break;
        case 162: string[i] = 'ó';
        break;
        case 163: string[i] = 'ú';
        break;
        case 164: string[i] = 'ñ';
        break;
        case 165: string[i] = 'Ñ';
        break;
        case 166: string[i] = '?';
        break;
        case 167: string[i] = '°';
        break;
        case 168: string[i] = '?';
        break;
        case 169: string[i] = '?';
        break;
        case 170: string[i] = '¬';
        break;
        }
    }
return string;
}
