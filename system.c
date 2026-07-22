// developed by Arthur Padilha de Oliveira 26.1.4014
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

#define ANSI_RESET            "\x1b[0m"
#define ANSI_BOLD             "\x1b[1m"

#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"
#define ANSI_BG_COLOR_ORANGE  "\x1b[48;5;208m"

#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET
#define BG_ORANGE(string)  ANSI_BG_COLOR_ORANGE  string ANSI_RESET

int main () {
    srand(time(NULL));
    int t = 1; // this will control the dowhile of the main menu
    int t2 = 1; //this will controll the dowhile of the second menus

    int t3 = 0; // to control if the person colors option is avaible

    char option; // this will control the options inside the main menu
    int op; //this will control options inside secundary menus
    char userName[202]; // to get the user name and do the comparisons
    char FILENAME[128] = "games/"; // this string has the name of the file that the progress are gonna be saved, so the file keeps organized
    char fileName[60]; // to get the file name that the user wants to save the game or load

    int w = 1; // to control if the person won or not;
    int *try; // to control the user tries
    int *v; // this is the array that will control the random sequence to show the results of the user tries

    int d = 0; // this will control how many colors are used in each difficult

    User U = {0}; // this is the struct that has the user data
    
    U.trials = 0; // starts with zero because i need it to validade if the person had started to play or not, then the person will be able or not to save a progress

    char sejaBemVindo[100] = "Seja bem-vindo(a) ao jogo Código secreto . . !";
    char developedBy[100] = "Este jogo foi desenvolvido por ArthurPadilha 26.1.4014";
    
    system("clear");
    printf("\n\n    ");
    showStringWithEffect(sejaBemVindo, strlen(sejaBemVindo));

    system("sleep 1");
    
    system("clear");
    printf("\n\n    ");
    showStringWithEffect(developedBy, strlen(developedBy));

    
    system("sleep 1");
    
    do {
        system("clear");
        printf("Opções de jogo:\n\n");
        printf("A - Ajuda\n");
        printf("N - Novo Jogo\n");
        printf("C - Carregar Jogo\n");
        printf("R - Ranking\n");
        printf("S - Salvar Jogo\n");
        printf("X - Sair\n\n");
        printf("Digite uma opção: ");

        scanf(" %c", &option);
        while (getchar() != '\n');

        switch (option) {
            case 'A': // ajuda
                system("clear");

                printf(BOLD("====================== AJUDA ======================\n\n"));

                printf("OBJETIVO DO JOGO\n");
                printf("---------------------------------------------------\n");
                printf("O computador gera uma sequência secreta de cores.\n");
                printf("Seu objetivo é descobrir essa sequência antes que\n");
                printf("o número máximo de tentativas seja atingido.\n\n");

                printf("NÍVEIS DE DIFICULDADE\n");
                printf("---------------------------------------------------\n");
                printf("1 - Fácil   : 4 cores e até 10 tentativas.\n");
                printf("2 - Médio   : 5 cores e até 12 tentativas.\n");
                printf("3 - Difícil : 6 cores e até 15 tentativas.\n\n");

                printf("CORES DISPONÍVEIS\n");
                printf("---------------------------------------------------\n");

                printf("1 - ");
                printColor(1);
                printf(" Vermelho\n");

                printf("2 - ");
                printColor(2);
                printf(" Azul\n");

                printf("3 - ");
                printColor(3);
                printf(" Verde\n");

                printf("4 - ");
                printColor(4);
                printf(" Amarelo\n");

                printf("5 - ");
                printColor(5);
                printf(" Roxo\n");

                printf("6 - ");
                printColor(6);
                printf(" Laranja\n\n");

                printf("COMO JOGAR\n");
                printf("---------------------------------------------------\n");
                printf("Em cada rodada digite uma sequência de números,\n");
                printf("cada número representa uma cor.\n");
                printf("Exemplo (modo Fácil):\n");
                printf("    1 3 4 2\n\n");

                printf("APÓS CADA TENTATIVA\n");
                printf("---------------------------------------------------\n");
                printf("O jogo informa o resultado da sua jogada de forma aleatória.\n");

                printf("C -> Cor correta na posição correta.\n");
                printf("E -> Cor existe na sequência secreta,\n");
                printf("     mas está na posição errada.\n");
                printf("- -> Cor não faz parte da sequência secreta.\n\n");

                printf("DICAS\n");
                printf("---------------------------------------------------\n");
                printf("- As cores da sequência secreta não se repetem\n");
                printf("- Analise o resultado de cada tentativa antes de\n");
                printf("  fazer a próxima jogada.\n");
                printf("- Quanto menos tentativas você usar, melhor será\n");
                printf("  seu desempenho.\n\n");

                printf("Boa sorte e divirta-se!\n\n");

                printf("Pressione ENTER para voltar ao menu...");
                getchar();
                break;

            case 'N': // new game            
                system("clear");
                printf("\nOlá jogador..! O seu jogo será iniciado em algumas etapas..!\n\n");
                printf("Digite o seu nome: ");
                fgets(userName, 200, stdin);

                userName[strlen(userName)-1] = '\0';

                w = 1;
                t2 = 1; //controll invalid options for the game difficult

                do{
                    system("clear");
                    char userWelcome[250] = "Olá jogador ";
                    strcat(userWelcome, userName);
                    strcat(userWelcome, ", para iniciar o seu jogo escolha um nível de dificuldade...");

                    printf("%s", userWelcome);

                    printf("\n\n1 - Fácil (4 cores & 10 tentativas)\n2 - Médio (5 cores & 12 tentativas)\n3 - Dificil (6 cores & 15 tentativas)\n\nDigite uma opção: ");
                    scanf(" %d", &op);

                    while (getchar() != '\n');
                    /*
                    * easy 4 colors 10 tries
                    * medium 5 colors 12 tried
                    * hard 6 colors 15 tries
                    */
                    if(U.colorsSecretSequency != NULL)
                        freeUser(&U, try, v);

                    switch(op) {
                        case 1:
                            d = 4;
                            createNewGame(&U, userName, d);
                            try = malloc(d * sizeof(int)); // player tries array
                            v = malloc(d * sizeof(int)); // array that indicates the random sequence to show the letters from the result
                            createARandomShowSequence(v, d);
                            playGame(&U, d, 10, &w, &t2, try, v, option);
                            break;

                        case 2:
                            d = 5;
                            createNewGame(&U, userName, d);
                            try = malloc(d * sizeof(int)); // player tries array
                            v = malloc(d * sizeof(int)); // array that indicates the random sequence to show the letters from the result
                            createARandomShowSequence(v, d);
                            playGame(&U, d, 12, &w, &t2, try, v, option);
                            break;

                        case 3:
                            d = 6;
                            createNewGame(&U, userName, d);
                            try = malloc(d * sizeof(int)); // player tries array
                            v = malloc(d * sizeof(int)); // array that indicates the random sequence to show the letters from the result
                            createARandomShowSequence(v, d);
                            playGame(&U, d, 15, &w, &t2, try, v, option);
                            break;

                        default: // for any option thats diferent of the avaible ones
                            invalidOption();
                            break;
                    }
                } while(t2);    

                break;

            case 'C': // load a game
                system("clear");
                printf("\nDigite o nome do arquivo que você deseja carregar o seu progresso: ");
                fgets(fileName, 58, stdin);
                fileName[strlen(fileName)-1] = '\0';

                strcpy(FILENAME, "games/");
                strcat(FILENAME, fileName);
                strcat(FILENAME, ".cor");
                FILE *file = fopen(FILENAME, "r");

                if(file != NULL){
                    fclose(file);

                    if(U.colorsSecretSequency != NULL) // so it get the U free before you start a new game
                        freeUser(&U, try, v);

                    loadGame(&U, fileName);

                    switch(U.gameDifficulty){
                        case 'F':
                            d = 4;
                            w = 1;    
                            try = malloc(d * sizeof(int)); // player tries array
                            v = malloc(d * sizeof(int)); // array that indicates the random sequence to show the letters from the result
                            createARandomShowSequence(v, d);

                            for(int i = 0; i < d; i++)
                                try[i] = U.plays[U.trials-1][i];

                            playGame(&U, 4, 10, &w, &t2, try, v, option);
                            break;

                        case 'M':
                            d = 5;
                            w = 1;    
                            try = malloc(d * sizeof(int)); // player tries array
                            v = malloc(d * sizeof(int)); // array that indicates the random sequence to show the letters from the result
                            createARandomShowSequence(v, d);

                            for(int i = 0; i < d; i++)
                                try[i] = U.plays[U.trials-1][i];

                            playGame(&U, 5, 12, &w, &t2, try, v, option);
                            break;

                        case 'D':
                            d = 6;
                            w = 1;    
                            try = malloc(d * sizeof(int)); // player tries array
                            v = malloc(d * sizeof(int)); // array that indicates the random sequence to show the letters from the result
                            createARandomShowSequence(v, d);

                            for(int i = 0; i < d; i++)
                                try[i] = U.plays[U.trials-1][i];

                            playGame(&U, 6, 15, &w, &t2, try, v, option);
                            break;
                    }
                }
                else{
                    system("clear");
                    printf("\n\nNão há nenhum jogo salvo em um arquivo com esse nome !!!\n\n\n");
                    system("sleep 1");
                }
                break;
            
            case 'R': // It shows the game ranking
                showRanking();
                break;

            case 'S': // save progress
                if(U.trials != 0){
                    system("clear");
                    printf("\nDigite o nome do arquivo que você deseja salvar o seu progresso: ");
                    fgets(fileName, 58, stdin);
                    fileName[strlen(fileName)-1] = '\0';

                    strcpy(FILENAME, "games/");
                    strcat(FILENAME, fileName);
                    strcat(FILENAME, ".cor");
                    FILE *file = fopen(FILENAME, "r");

                    if(file != NULL){
                        fclose(file);
                        do{
                            system("clear");
                            printf("Arquivo já existente!!!\n\nDeseja sobrepor este arquivo (1 - sim, 2 - não)?\n\nDigite uma opção: ");
                            scanf(" %d", &op);
                            
                            while(getchar() != '\n');

                            switch (op){
                                case 1:
                                    saveGame(&U, fileName);
                                    freeUser(&U, try, v);
                                    U.trials = 0;
                                    system("sleep 1");
                                    break;
                                case 2:
                                    break;
                                default:
                                    invalidOption();
                                    break;
                            }
                        }while(op != 1 && op != 2);
                    }
                    else{
                        saveGame(&U, fileName);
                        freeUser(&U, try, v);
                        U.trials = 0;
                    }
                }

                else{
                    system("clear");
                    printf("\n\nNão há nenhum jogo iniciado para ser salvo !!!\n\n\n");
                    system("sleep 1");
                }
                break;

            case 'X': // get out from the game
                if(U.trials != 0){
                    do {
                        system("clear");
                        
                        printf("Você deseja salvar o jogo? \n\nS - Sim\nN - Não\n\nDigite uma opção: ");
                        scanf(" %c", &option);

                        while (getchar() != '\n');

                        switch (option){ // this switch case will control if the user wants to save or not, and if the option is not avaible in the menu
                            case 'S': // put the function do save the progress of the game
                                printf("\nDigite o nome do arquivo que você deseja salvar o seu progresso: ");
                                fgets(fileName, 58, stdin);
                                fileName[strlen(fileName)-1] = '\0';

                                strcpy(FILENAME, "games/");
                                strcat(FILENAME, fileName);
                                strcat(FILENAME, ".cor");
                                FILE *file = fopen(FILENAME, "r");

                                if(file != NULL){
                                    fclose(file);
                                    do{
                                        system("clear");
                                        printf("Arquivo já existente!!!\n\nDeseja sobrepor este arquivo (1 - sim, 2 - não)?\n\nDigite uma opção: ");
                                        scanf(" %d", &op);
                                        
                                        while(getchar() != '\n');

                                        switch (op){
                                            case 1:
                                                saveGame(&U, fileName);
                                                freeUser(&U, try, v);
                                                U.trials = 0;
                                                break;
                                            case 2:
                                                freeUser(&U, try, v);
                                                break;
                                            default:
                                                invalidOption();
                                                break;
                                        }
                                    }while(op != 1 && op != 2);
                                }
                                else{
                                    saveGame(&U, fileName);
                                    freeUser(&U, try, v);
                                    U.trials = 0;
                                }
                                
                                t = 0;
                                break;
                            
                            case 'N': 
                                t = 0;
                                break;

                            default: // for any option thats diferent of the avaible ones
                                invalidOption();
                                break;
                        }
                    } while (t);
                }    
                system("clear");
                printf("\n\nBye Bye..!\n\n\n");
                t = 0;
                break;

            default: // for any option thats diferent of the avaible ones
                invalidOption();
                break;
        }
    } while(t);

    return 0;
}