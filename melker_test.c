#include "melker/melker_example.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct BoardState{
        //int cells[1][30];
        //ints below to be replaced with Vec2 when Pos struct is in place
        int screenWidth;
        int screenHeight;
        int playerPosX;
	    int playerPosY;
    };

int main()
{
    struct BoardState s1;
    //s1.cells[1][30];
    s1.screenHeight = 1;
    s1.screenWidth = 1;
    s1.playerPosX = 1;
    s1.playerPosY = 1;

    char loadCreate;
    
    void askConfig(struct BoardState *state){
        
        loadCreate = '*';
        while(loadCreate != 'L' && loadCreate != 'C'){
            printf("Would you like to load a preset, a previously saved, player-made board configuration or create a new board? (P/L/C)\n");
            scanf(" %c", &loadCreate);

            if(loadCreate == 'P'){
                if(state == NULL){
                    printf("As there are no previously made boards, loading a player-made board will not be possible.\n");
                }
            }else if(loadCreate == 'L'){
                printf("Loading presets.\n");

            }else if(loadCreate == 'C'){
                printf("Time to create yesss!\n");

            }else{
                printf("That doesn't work!! Please try again...\n");
                sleep(1);
                continue;
            }
        }
    }

    askConfig(struct BoardState *s1);

    //doStuffMelker();

    return 0;
}