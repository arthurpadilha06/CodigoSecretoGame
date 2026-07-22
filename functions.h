// developed by Arthur Padilha de Oliveira 26.1.4014
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    char name[202];
    char gameDifficulty;
    int *colorsSecretSequency;
    int trials;
    int **plays;
} User;

// functions protoype

void invalidOption();
void createNewGame(User *U, char userName[], int difficulty);
void savePlay(User *U, int try[], int difficulty, int w);
void printColor(int c);
int tryResult(User *U, int try[], int difficulty, int *w, int *v);
void saveGame(User *U, char fileName[]);
void loadGame(User *U, char fileName[]);
void playGame(User *U, int d, int maxTrials, int *w, int *t2, int *try, int *v, char op);

void showStringWithEffect(char name[], int sizeName);
void freeUser(User *U, int *try, int *v);
void createARandomShowSequence(int v[], int d);

void ranking(User *U);
void showRanking();

#endif