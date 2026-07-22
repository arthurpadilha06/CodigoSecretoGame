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

// as funcoes em si vem aqui
/*
    struct format of User

    char name[202];
    char gameDifficulty;
    int colorsSecretSequency[6];
    int trials;
    int plays[15][6];
*/

void invalidOption(){
    system("clear");
    printf("\n\nOPÇÃO INVÁLIDA ! ! !\n\n");
    system("sleep 0.5");
}

void createNewGame(User *U, char userName[], int difficulty){
    strcpy(U->name, userName);
    int maxTrials;

    switch (difficulty){
        case 4:
            maxTrials = 10;
            U->gameDifficulty = 'F';
            break;
        
        case 5:
            maxTrials = 12;
            U->gameDifficulty = 'M';
            break;
        case 6:
            maxTrials = 15;
            U->gameDifficulty = 'D';
            break;
    }

    U->colorsSecretSequency = malloc(difficulty * sizeof(int));
    U->colorsSecretSequency[0] = rand() % 6 + 1;

    int i = 1; // for the while loop
    int t = 0; // for the for loop that will make sure that all numbers are different
    
    // 'i' starts with 1 because the first positions has been allocated
    
    while (i < difficulty){
        int number = rand() % 6 + 1;

        for(int j = 0; j < i; j++)
            if (number == U->colorsSecretSequency[j])
                t = 1; // there is a position with this random color already

        if (t == 0){ // if t == 0 its safe to save the value of the number variable with the random number, this code doesnt exist yet
            U->colorsSecretSequency[i] = number;
            i++;
        }

        t = 0;
    }       

    U->plays = malloc(maxTrials * sizeof(int *));
    for (int i = 0; i < maxTrials; i++)
        U->plays[i] = malloc(difficulty * sizeof(int));

    // initialization of the other variables with 0 so i can use this to make other logics

    for (int k = 0; k < maxTrials; k++)
        for(int j = 0; j < difficulty; j++)
            U->plays[k][j] = 0; // so it get all initialized the positions as zero

    U->trials = 0;
}

void savePlay(User *U, int try[], int difficulty, int w){

    for (int i = 0; i < difficulty; i++){
        U->plays[U->trials][i] = try[i];
    }

    U->trials++;
}

void printColor(int c){
    switch(c){
        case 1:
            printf(BG_RED("  "));
            break;

        case 2:
            printf(BG_BLUE("  "));
            break;

        case 3:
            printf(BG_GREEN("  "));
            break;

        case 4:
            printf(BG_ORANGE("  ")); // here should be yellow, but the yellow looks more like the orange, so i chaanged
            break;

        case 5:
            printf(BG_MAGENTA("  "));
            break;

        case 6:
            printf(BG_YELLOW("  "));
            break;
    }
}

void createARandomShowSequence(int v[], int d){
    v[0] = rand() % d; // this will get the first random value that will be compared 

    int i = 1;
    int t = 0;

    while (i < d){
        int number = rand() % d;

        for(int j = 0; j < i; j++)
            if (number == v[j])
                t = 1; // there is a position with this random color already

        if (t == 0){ // if t == 0 its safe to save the value of the number variable with the random number, this code doesnt exist yet
            v[i] = number;
            i++;
        }

        t = 0;
    }
}

int tryResult(User *U, int try[], int difficulty, int *w, int *v){
    
    char result[20] = "(";
    char correctResult[20] = "(";
    
    int count = 0;

    for (int i = 0; i < difficulty; i++){
        if(try[v[i]] == U->colorsSecretSequency[v[i]])
            strcat(result, "C "); // the position is correct
        else {
            for(int j = 0; j < difficulty; j++){
                if(try[v[i]] == U->colorsSecretSequency[j]){
                    strcat(result, "E "); // there is this color inside the secret sequence
                    count++;
                }
            }
            if(count == 0) { // if the count is zero its because there isnt this color inside the random sequence
                strcat(result, "- ");
            }
            count = 0;
        }
    }
    result[strlen(result)-1] = ')';

    printf("%s\n", result);

    for (int i = 0; i < difficulty; i++) { // this make the variable that would represent that its correct, for example for easy difficult (C C C C), medium (C C C C C), hard (C C C C C C)
        strcat(correctResult, "C");

        if (i == difficulty-1)
            strcat(correctResult, ")");
        else
            strcat(correctResult, " ");
 
    }

    if(strcmp(correctResult, result) == 0){ // then you won
        *w = 0;
        return 1;
    }
    
    return 0;
}

void playGame(User *U, int d, int maxTrials, int *w, int *t2, int *try, int *v, char op){
    int t3 = 0;
    int auxTry[d]; // needed this cuz when the user type 0 to get out from the game, the try array that used to go to the tryresult function would have the number 0 and it used to make the (C E ...) wrong, cuz there was the zero

    char continueOption; //to control the option if the user really want to get out from the game
    if(U->trials < maxTrials){
        if(U->trials != 0){
            for(int i = 0; i < d; i++)
                auxTry[i] = U->plays[U->trials-1][i];
        }
        do{
            do{
                t3 = 0; // control a invalid color
                system("clear");
                printf("Jogador: %s\n", U->name);
                printf("Nível de dificuldade: %c\n\n", U->gameDifficulty);
                printf("(1 - vermelho, 2 - azul, 3 - verde, 4 - amarelo, 5 - roxo, 6 - laranja)\n");
                printf("(0 - sair)\n\n");

                
                /*
                * used to show the solution so the programmer could make some tests with the code

                printf("A sequência correta era: ");
                for(int i = 0; i < d; i++){
                    printColor(U->colorsSecretSequency[i]);
                    printf(" ");                }
                printf("\n\n");
                */

                for(int i = 0; i < maxTrials; i++){
                    if(U->plays[i][0] == 0)
                        printf("\n");
                    else{
                        for(int j = 0; j < d; j++){
                            printColor(U->plays[i][j]);
                            printf(" ");
                        }
                        printf("\n");
                    }
                }

                printf("\n");

                if(U->trials == 0)
                    printf("\n");
                else {
                    if(tryResult(U, auxTry, d, w, v))
                            break; // if you won it breaks the do while loope cuz the function would return 1
                }

                int numberTry = U->trials +1;

                printf("Tentativa %d de %d -> Digite %d cores: ", numberTry, maxTrials, d);

                for(int i = 0; i < d; i++){
                    scanf("%d", &try[i]);

                    if(try[0] == 0 && i == 0){
                        int conti = 1;

                        while (conti){
                            while(getchar() != '\n');

                            printf("\nDeseja realmente sair (S/N)? ");
                            scanf("%c", &continueOption);

                            switch(continueOption){
                                case 'S':
                                    t3 = 0;
                                    conti = 0;
                                    break;
                                
                                case 'N':
                                    try[0] = -1; // gotta be any value different then 0
                                    conti = 0;
                                    break;

                                default:
                                    printf("Opção inválida, digite novamente!");
                                    system("sleep 0.2");
                                    system("clear");
                                    break;
                            }
                        }   
                        break;
                    }
                    else if(try[i] < 1 || try[i] > 6)
                        t3++;
                }

                while(getchar() != '\n');

                if(t3 && try[0] != 0)
                    invalidOption();

                if(!t3 && try[0] != -1){
                    for (int i = 0; i < d; i++)
                        auxTry[i] = try[i];
                }

            } while(t3);

            if(*w && try[0] > 0)
                savePlay(U, try, d, *w);

        } while(*w && U->trials < maxTrials && try[0] != 0);
    }

    else{
        system("clear");
        for(int i = 0; i < maxTrials; i++){
            if(U->plays[i][0] == 0)
                printf("\n");
            else{
                for(int j = 0; j < d; j++){
                    printColor(U->plays[i][j]);
                    printf(" ");
                }
                printf("\n");
            }
        }
    }

    if(*w == 0 && try[0] != 0){
        printf("\n\nPARABÉNS!\n\n");
        
        printf("A sequência correta era: ");
        for(int i = 0; i < d; i++){
            printColor(U->colorsSecretSequency[i]);
            printf(" ");
        
        }

        printf("\n\nVocê ganhou com %d tentativas!\n\n", U->trials); /////////////////////////////////////////////////////////////////////////////////
        *t2 = 0;

        
        ranking(U);

        // i gotta check if this person get into the ranking, and then save her progress
        printf("\n\nPressione ENTER para voltar ao menu...");
        while(getchar() != '\n');
    }
    else if (try[0] != 0){
        printf("\nVocê atingiu o número máximo de tentativas.\n\n");

        printf("A sequência correta era: ");
        for(int i = 0; i < d; i++){
            printColor(U->colorsSecretSequency[i]);
            printf(" ");
        }

        printf("\n\nPressione ENTER para voltar ao menu...");
        while(getchar() != '\n');

        *t2 = 0;
    }
    else{
        *t2 = 0;
    }
}

void showStringWithEffect(char name[], int sizeName) {
    struct timespec t = {0, 40000000}; 

    for (int i = 0; i < sizeName; i++) {
        printf("%c", name[i]);
        fflush(stdout);
        nanosleep(&t, NULL);
    }
}

void freeUser(User *U, int *try, int *v){
    free(v);
    free(try);
    free(U->colorsSecretSequency);
    U->colorsSecretSequency = NULL;

    if (U->plays != NULL){
        int lines;

        switch(U->gameDifficulty){
            case 'F':
                lines = 10;
                break;
            case 'M':
                lines = 12;
                break;
            case 'D':
                lines = 15;
                break;
            default:
                lines = 0;
        }

        for(int i = 0; i < lines; i++)
            free(U->plays[i]);

        free(U->plays);
        U->plays = NULL;
    }
}

void saveGame(User *U, char fileName[]){
    char FILENAME[60] = "games/";
    strcat(FILENAME, fileName);
    strcat(FILENAME, ".cor");

    FILE *file = fopen(FILENAME, "w");

    if(file != NULL){
        fprintf(file, "%s\n", U->name);
        fprintf(file, "%c\n", U->gameDifficulty);
        
        int colorsOfGameDifficulty;

        switch (U->gameDifficulty){
            case 'F':
                colorsOfGameDifficulty = 4;
                break;
            case 'M':
                colorsOfGameDifficulty = 5;
                break;
            case 'D':
                colorsOfGameDifficulty = 6;
                break;
        }

        for(int i = 0; i < colorsOfGameDifficulty; i++)
            fprintf(file, "%d ", U->colorsSecretSequency[i]);
        fprintf(file, "\n");
        
        fprintf(file, "%d", U->trials);
        fprintf(file, "\n");

        for(int i = 0; i < U->trials; i++){
            for(int j = 0; j < colorsOfGameDifficulty; j++)
                fprintf(file, "%d ", U->plays[i][j]);
            fprintf(file, "\n");
        }
        system("clear");
        printf("\n\nProgresso salvo com sucesso..!\n\n");
        system("sleep 1");
        fclose(file);
    }   
    else{
        system("clear");
        printf("\n\nERRO AO ABRIR O ARQUIVO!!!\n\n\n");
        system("sleep 1");
    }
}

void loadGame(User *U, char fileName[]){
    char FILENAME[60] = "games/";
    strcat(FILENAME, fileName);
    strcat(FILENAME, ".cor");

    FILE *file = fopen(FILENAME, "r");

    if(file != NULL){
        fgets(U->name, sizeof(U->name), file);
        U->name[strlen(U->name)-1] = '\0';
        
        fscanf(file, " %c", &U->gameDifficulty);

        int colorsOfGameDifficulty;
        int lines;

        switch (U->gameDifficulty){
            case 'F':
                colorsOfGameDifficulty = 4;
                lines = 10;
                break;

            case 'M':
                colorsOfGameDifficulty = 5;
                lines = 12;
                break;

            case 'D':
                colorsOfGameDifficulty = 6;
                lines = 15;
                break;
        }

        U->colorsSecretSequency = malloc(colorsOfGameDifficulty * sizeof(int));

        U->plays = malloc(lines * sizeof(int *));
        for(int i = 0; i < lines; i++)
            U->plays[i] = malloc(colorsOfGameDifficulty * sizeof(int));

        for (int k = 0; k < lines; k++)
            for(int j = 0; j < colorsOfGameDifficulty; j++)
                U->plays[k][j] = 0; // so it get all initialized the positions as zero

        for(int i = 0; i < colorsOfGameDifficulty; i++)
            fscanf(file, " %d", &U->colorsSecretSequency[i]);

        fscanf(file, " %d", &U->trials);

        for(int i = 0; i < U->trials; i++){
            for(int j = 0; j < colorsOfGameDifficulty; j++)
                fscanf(file, " %d", &U->plays[i][j]);
        }

        system("clear");
        printf("\n\nProgresso carregado com sucesso..!\n\n");
        system("sleep 1");
        fclose(file);
    }
    else{
        system("clear");
        printf("\n\nERRO AO ABRIR O ARQUIVO!!!\n\n\n");
        system("sleep 1");
    }
}

void ranking(User *U){
    FILE *file;
    User rnkUser[11]; // 10 of the ranking and a new user
    int total = 0;
    int alreadyRanked = 0; // check if the user is already in the ranking

    file = fopen("ranking/ranking.rmk", "rb");

    if(file != NULL){
        while(total < 10 && fread(rnkUser[total].name, sizeof(char), 202, file) == 202) {
            fread(&rnkUser[total].gameDifficulty, sizeof(char), 1, file);
            fread(&rnkUser[total].trials, sizeof(int), 1, file);

            // check if this player is already in the ranking
            if(strcmp(rnkUser[total].name, U->name) == 0 &&
               rnkUser[total].gameDifficulty == U->gameDifficulty){
                alreadyRanked = 1;
            }

            total++;
        }

        fclose(file);
    }

    // if the player is already in the ranking, do not add again
    if(alreadyRanked)
        return;


    // add a new user to the ranking
    strcpy(rnkUser[total].name, U->name);
    rnkUser[total].gameDifficulty = U->gameDifficulty;
    rnkUser[total].trials = U->trials;
    
    // add the new user to the last position and add one to total cuz we gotta check how the ranking will be
    total++;


    for(int i = 0; i < total - 1; i++) { // 0 to 10 (if its full)
        for(int j = i + 1; j < total; j++) { // i+1 to 11 (if its full)

            int change = 0; // to check if i will need to change the positions because a player was better than the next ones 

            if(rnkUser[i].trials > rnkUser[j].trials)
                change = 1;

            else if(rnkUser[j].trials == rnkUser[i].trials) {

                int gameD = 0, gameD2 = 0;

                if(rnkUser[j].gameDifficulty == 'F')
                    gameD = 1;
                if(rnkUser[j].gameDifficulty == 'M')
                    gameD = 2;
                if(rnkUser[j].gameDifficulty == 'D')
                    gameD = 3;


                if(rnkUser[i].gameDifficulty == 'F') 
                    gameD2 = 1;
                if(rnkUser[i].gameDifficulty == 'M') 
                    gameD2 = 2;
                if(rnkUser[i].gameDifficulty == 'D') 
                    gameD2 = 3;


                if(gameD > gameD2)
                    change = 1;
            }


            if(change) {
                User aux = rnkUser[i];
                rnkUser[i] = rnkUser[j];
                rnkUser[j] = aux;
            }
        }
    }


    // this will remake the file
    file = fopen("ranking/ranking.rmk", "wb");

    if(file == NULL)
        return; // to check if it opened correctly


    int limit = total;

    if(limit > 10)
        limit = 10;


    for(int i = 0; i < limit; i++){
        fwrite(rnkUser[i].name, sizeof(char), 202, file);
        fwrite(&rnkUser[i].gameDifficulty, sizeof(char), 1, file);
        fwrite(&rnkUser[i].trials, sizeof(int), 1, file);
    }


    fclose(file);
}

void showRanking() {
    FILE *file;
    User rnkUser;
    int posicao = 1;

    file = fopen("ranking/ranking.rmk", "rb");

    if(file == NULL){
        system("clear");
        printf("\n============================================\n");
        printf("                 RANKING\n");
        printf("============================================\n");
        printf("\nNao existe nenhum jogador no ranking!\n\n");
        printf("Pressione ENTER para voltar...");
        getchar();
        return;
    }

    system("clear");

    printf("=====================================================\n");
    printf("                    TOP 10 JOGADORES\n");
    printf("=====================================================\n");
    printf("%-4s %-25s %-12s %s\n", "#", "Nome", "Dificuldade", "Tentativas");
    printf("-----------------------------------------------------\n");

    while(fread(rnkUser.name, sizeof(char), 202, file) == 202){
        fread(&rnkUser.gameDifficulty, sizeof(char), 1, file);
        fread(&rnkUser.trials, sizeof(int), 1, file);

        printf("%-4d %-25.25s ", posicao, rnkUser.name);

        switch(rnkUser.gameDifficulty){
            case 'F':
                printf("%-12s", "Facil");
                break;

            case 'M':
                printf("%-12s", "Medio");
                break;

            case 'D':
                printf("%-12s", "Dificil");
                break;

            default:
                printf("%-12s", "-");
        }

        printf("%d\n", rnkUser.trials);

        posicao++;
    }

    printf("=====================================================\n");

    fclose(file);

    printf("\nPressione ENTER para voltar...");
    getchar();
}