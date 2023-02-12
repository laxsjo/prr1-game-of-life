#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "../rasmus/ansi_term.h"

//Source: https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html

//Useful ASCII table: https://www.asciitable.com/

//makes Gunther say X for Y amount of itterations, he can either be shocked or not
void speakGen(int dialogueLen, char *msg, bool isShocked){
    for (int i = 0; i < dialogueLen + 1; i++){

        if(!isShocked){
            printf("   _______   \r\n");
            printf("  /       \\  \r\n");
            printf(" |  ~   ~  | \r\n");
            printf(" |    O    | \r\n");
            printf("  \\_______/  \r\n");
            printf("\r\n");
            printf("%s", msg);
            usleep(200000);
            system("clear");

            printf("   _______   \r\n");
            printf("  /       \\  \r\n");
            printf(" |  ~   ~  | \r\n");
            printf(" |    _    | \r\n");
            printf("  \\_______/  \r\n");
            printf("\r\n");
            printf("%s", msg);
            usleep(200000);
            system("clear");
        }
        else{
            printf("   _______   \r\n");
            printf("  /       \\  \r\n");
            printf(" |  O   O  | \r\n");
            printf(" |    O    | \r\n");
            printf("  \\_______/  \r\n");
            printf("\r\n");
            printf("%s", msg);
            usleep(200000);
            system("clear");

            printf("   _______   \r\n");
            printf("  /       \\  \r\n");
            printf(" |  O   O  | \r\n");
            printf(" |    _    | \r\n");
            printf("  \\_______/  \r\n");
            printf("\r\n");
            printf("%s", msg);
            usleep(200000);
            system("clear");
        }  
    }
}

//prints Gunther's shocked or normal face
void printFace(bool isShocked){
    if(!isShocked){
        printf("   _______   \r\n");
        printf("  /       \\  \r\n");
        printf(" |  ~   ~  | \r\n");
        printf(" |  \\___/  | \r\n");
        printf("  \\_______/  \r\n");
        printf("\r\n");
    }
    else{
        printf("   _______   \r\n");
        printf("  /       \\  \r\n");
        printf(" |  O   O  | \r\n");
        printf(" |    O    | \r\n");
        printf("  \\_______/  \r\n");
        printf("\r\n");
    }
}

//intro sequence for the game
void runIntro(){
    enterNonCanonicalMode();

    system("clear");

    printFace(false);
    sleep(1);
    system("clear");

    int usleep(useconds_t usec);

    speakGen(8, "Hello, little human! Would you like to play my game?\r\n", false);

    printf("   _______   \r\n");
    printf("  /       \\  \r\n");
    printf(" |  ~   ~  | \r\n");
    printf(" |  \\___/  | \r\n");
    printf("  \\_______/  \r\n");
    printf("\r\n");

    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        usleep(500000);
    }
    printf("\r\n");
    
    printf("(Press 'y'...)\r\n");

    //loop until player inputs 'y'
    while (1) {

        char c = '\0';
        read(STDIN_FILENO, &c, 1);

        /*
        if(iscntrl(c)) {
            printf("%d\r\n", c);
        }else{
            printf("%d ('%c')\r\n", c, c);
        }
        */
        if(c == 'y') break;
    }

    //he's happy, he won't be if you play... the forbidden board...
    system("clear");
    printf("   _______   \r\n");
    printf("  /       \\  \r\n");
    printf(" |  O   O  | \r\n");
    printf(" |  \\___/  | \r\n");
    printf("  \\_______/  \r\n");
    printf("\r\n");

    char *yay;
    yay = "YAY!";
    for (int i = 0; i < 4; i++)
    {
        printf("%c", yay[i]);
        fflush(stdout);
        usleep(500000);
    }
    printf("\r\n");
    usleep(500000);
    system("clear");

    speakGen(10, "This is the game of life, white cells are alive, black cells are dead! You will watch them go.\r\n", false);

    printf("   _______   \r\n");
    printf("  /       \\  \r\n");
    printf(" |  O   O  | \r\n");
    printf(" |    O    | \r\n");
    printf("  \\_______/  \r\n");
    printf("\r\n");
    usleep(800000);
    system("clear");

    printf("   _______   \r\n");
    printf("  /       \\  \r\n");
    printf(" |  O   ~  | \r\n");
    printf(" |  \\___/  | \r\n");
    printf("  \\_______/  \r\n");
    printf("\r\n");
    usleep(1500000);
    system("clear");

    speakGen(8, "Are you ready to start the game?\r\n", false);

    printf("   _______   \r\n");
    printf("  /       \\  \r\n");
    printf(" |  ~   ~  | \r\n");
    printf(" |  \\___/  | \r\n");
    printf("  \\_______/  \r\n");
    printf("\r\n");

    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        usleep(500000);
    }
    printf("\r\n");
    
    printf("(Press 's'...)\r\n");

    //loop until player inputs 's'
    while (1) {

        char c = '\0';
        read(STDIN_FILENO, &c, 1);

        /*
        if(iscntrl(c)) {
            printf("%d\r\n", c);
        }else{
            printf("%d ('%c')\r\n", c, c);
        }
        */
        if(c == 's'){
            system("clear");
            break;
        }
    }
    exitNonCanonicalMode();
}