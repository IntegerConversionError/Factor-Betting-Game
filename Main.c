//Esad Kaya
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// STANDARD DEFINITIONS TO PROVIDE CROSS PLATFORM clear screen and pause commands
#if defined(_WIN32) || defined(_WIN64)
    #define clrscr() system("cls")
    #define pause() system("pause")
#else
    #define clrscr() printf("\x1B[1;1H\x1B[2J")
    #define pause() system("read -r -p \"Press any key to continue...\" key")
#endif

// Factor betting game

int  aNumber, targetNum, x, remaind, factorCounter, y, z, rollTotal, prob, roll1, roll2, roll;

float probability, grp, factorRollProbability, money = 100, winAmount, bet = 0, divideNum = 100;

char ch;

int rollDie(void) { //Finds a random number between 1 and 6
	aNumber = rand() % (6 - 1 + 1) + 1;
	return aNumber;
}

int menu(void) {//Prints a nice, well formatted welcome message to the user at startup
	printf("--------------------------------------------------------------------\n");
    printf("| Hello, welcome to the Lusital Casino!                            |\n");
	printf("| In this game, the objective is to win as much money as possible! |\n");
	printf("| But watch out, don't lose all your money, or else you lose!      |\n");
	printf("| Also, you have 15 tries to win, and then the game finishes       |\n");
	printf("| Have fun!                                                        |\n");
    printf("--------------------------------------------------------------------\n\n");
           return 0;
}

int probabilityFinder(int targetNum) {
	for (x = 1; x <= targetNum; x++) {//loops through all the numbers from 0 to the number inputted
		remaind = targetNum % x;
		if (remaind == 0 && x <= 12) {//finds the factors only if they are less than or equal to 12
                                    //counts how many different combinations can roll the factor being currently checked
            if (x == 2||x == 12){
                grp ++ ;
            }
            else if (x == 3||x == 11){
                grp += 2;
            }
            else if (x == 4||x == 10){
                grp += 3;
            }
            else if (x == 5||x == 9){
                grp += 4;
            }
            else if (x == 6||x == 8){
                grp += 5;
            }
            else if (x == 7){
                grp += 6;
            }
		}
	}
	return grp;//returns value out of 36
}
int endMessage(float money){//Gives the user a message at the end of the game depending on how much money they finished with
    if (money<=1000 && money>100){
        printf("Good job! You finished with $%.2f",money);
    }
    else if (money<=2000 && money>1000){
        printf("Great job! You finished with $%.2f",money);
    }
    else if (money<=3000 && money>2000){
        printf("Wow! You finished with $%.2f",money);
    }
    else if (money<=0.019){
        printf(" You finished with $0");
    }
    else if (money<=100){
        printf("Eh, not bad, at least you didn't lose all your money. You finished with $%.2f", money);
    }
    else if (money>3000){
        printf("WOW. THAT is INSANE! You finished with $%.2f????? You have to have been cheating. No way. Maybe owning a regular casino was the better option.",money);
    }
    sleep(5);
}
int main(void) {
    printf("\033[1;35m");//Sets the console colour to purple
	//Makes sure that random numbers are truly random
    menu();
    while (z < 15 && money>0.019){//Runs through the loop 15 times, because the counter variable Z starts at 0. Also cancells if the user doesn't have more than 1.9 cents
        z++;

        printf("---------------------------\nTry #%i\nYou currently have: $%.2f \n---------------------------\n\n",z, (float)money);//Outputs user's balance
        printf("Please enter the number you will be betting on: ");
        scanf("%d", &targetNum);//Gets the target number from user 
        factorRollProbability = probabilityFinder(targetNum)/(float)36;//Finds percentage of rolling a factor on any roll
        printf("\nYou have a %.2f %% chance of rolling a factor on any given diceroll. \n", factorRollProbability*(float)100);
        printf("\nPlease enter the amount of money you are going to risk: ");
        while (bet>money || bet<=0){//Makes sure a proper amount is inputted for the bet amount
            scanf("%f",&bet);
            if (bet>money+0.01 || bet<=0){
                printf("\nPlease enter a valid amount: ");
            }
        }
        money -= bet;//Subtracts the bet from the user's money
        winAmount = (float)bet/(float)factorRollProbability;//Finds how much the user can win if they roll a factor
        for (y = 1; y <=3; y++){//Rolls 3 "dice" via the function rollDie()
            roll1 = rollDie();
            roll2 = rollDie();
            roll = roll1 + roll2;
            printf("\nRoll #%i is %i and %i, which adds up to: %i\n\n",y,roll1,roll2,roll);
            sleep(1);
            for (x = 1; x <= targetNum; x++) {//Rolls "dice" and outputs a "win message" if they won
                remaind = targetNum % x;
                if (remaind == 0 && x <= 12 && x == roll) {
                    money = money + winAmount;
                    printf("Congrats! You rolled your factor, and got $%.2f, which brings your total balance to $%.2f\n\n\n",winAmount,(float)money);
                    sleep(5);
                    y = 10;
                    break;
                }
                

            }

        }
        if (y<5){// Outputs a "loss message" if the user lost their bet, and may output a "full loss" message if the user has no more money left.
            printf("Oh no! You lost your bet!\n");
            if (money <= 0.019){ 
                printf("You lost all your money! ");
                z = 20;
            }
            sleep(5);
        } 
        system("clear");
        grp = 0;//Resets the factor rolling probability counter back to 0 for the next try
        bet = 0;//Resets the betting amount
    }
    system("clear");

    endMessage(money); //Calls the end message function

}
