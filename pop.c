#include <stdio.h>
#include <stdlib.h>

// Global Constants
#define POPMAX 105
#define POPMIN 30
#define POPMULTIPLE 5
#define NICKELVAL 5
#define DIMEVAL 10
#define QUARTERVAL 25

// Declaring functions
void vendingMachine(int popPrice);
void addFunds(int* moneyInMachine, int* running);
void returnChange(int* moneyInMachine);
void balanceDue(int moneyInMachine, int popPrice);
void printInput(int moneyInMachine);

// Takes stdin at runtime and uses it to set price of pop
// if price is over 105 or under 30 program will tell user to enter a valid number
// if price is not a multipe of 5 program will tell user to enter a valid number
int main(int argc, char* argv[]) {
	int popPrice;

	if(argc == 2) {
		popPrice = atoi (argv[1]);
		if(popPrice > POPMAX || popPrice < POPMIN) {
			printf("The price must be between %d and %d\n", POPMIN, POPMAX);
		} else if (popPrice % POPMULTIPLE != 0) {
			printf("The price must be a multiple of %d\n", POPMULTIPLE);
		} else {
			vendingMachine(popPrice);
		}
	} else if (argc == 1) {
		printf("Please specify selling price as command line argument.\n");
		printf("Usage: pop [price]\n");
	} else {
		printf("Too many arguments inserted\n");
	}

	

	return (0);
}

// Runs the vending machine
// if running == 0 continue running vending machine
// if running != 0 return funds and exit program
// if moneyInMachine is greater than popPrice vend 1 pop and refund remainder
void vendingMachine(int popPrice) {
	printf("Welcome to the AMcTagga vending machine.\n\nThe price of pop is %d.\nPlease insert any combination of Nickels [N or n], Dimes [D or d], Quarter [Q or q].\n", popPrice);
	int running;
	int moneyInMachine;

	running = 0;
	moneyInMachine = 0;

	while(running == 0) {
		printf("Enter coin (NDQR):\n");
		addFunds(&moneyInMachine, &running);
		if(moneyInMachine >= popPrice) {
			printf("/tPop is dispensed. Thank you for your business! Please come again.\n");
			moneyInMachine -= popPrice;
			returnChange(&moneyInMachine);
		} else if (moneyInMachine > 0 && moneyInMachine < popPrice) {
			balanceDue(moneyInMachine, popPrice);
		}
	}

	if(running != 0) {
		returnChange(&moneyInMachine);
	}

	printf("Shutting down. Goodbye.\n");
	
}

// adds funds to machine (inserts coins)
// If R will refund money to client
// If E will refund money to client, then exit program
void addFunds(int *moneyInMachine, int *running) {
	char coinUsed;
	scanf(" %c", &coinUsed);

	switch(coinUsed) {
		case 'n' : case 'N' :
			printf("\tNickel Detected\n");
			*moneyInMachine += NICKELVAL;
			printInput(*moneyInMachine);
			break;

		case 'd' : case 'D' :
			printf("\tDime Detected\n");
			*moneyInMachine += DIMEVAL;
			printInput(*moneyInMachine);
			break;

		case 'q' : case 'Q' :
			printf("\tQuarter Detected\n");
			*moneyInMachine += QUARTERVAL;
			printInput(*moneyInMachine);
			break;

		case 'e' : case 'E' :
			*running = 1;
			break;

		case 'r' : case 'R' :
			returnChange(&*moneyInMachine);
			break;

		default :
			printf("\tUnknown coin rejected\n");
	}
}

// Refunds remaining money in machine to user in nickels and dimes
void returnChange(int *moneyInMachine) {
	int nickels, dimes;
	dimes = *moneyInMachine / DIMEVAL;
	nickels = (*moneyInMachine - (dimes * DIMEVAL)) / NICKELVAL;

	printf("\t\tChange given: %d cents as %d dime(s) and %d nickel(s).\n", *moneyInMachine, dimes, nickels);
	*moneyInMachine = 0;
}

// Prints the amount of money needed to purchase next can of pop
void balanceDue(int moneyInMachine, int popPrice) {
	printf("\t\tPlease insert %d more cents.\n", (popPrice-moneyInMachine));
}

// Prints the amount of money the user has inputted so far (before most recent vend)
void printInput(int moneyInMachine) {
	printf("\t\tYou have inserted a total of %d cents.\n", moneyInMachine);
}
