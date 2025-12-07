#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h> 

#define ACCOUNT_FILE "slot_account.txt"
#define STARTING_BALANCE 100.00
#define COST_PER_SPIN 10.00
#define MAX_USERNAME_LENGTH 50

struct User {
    char username[MAX_USERNAME_LENGTH];
    double balance;
};

struct User currentUser;

void initialize_game();
void login_user();
void display_menu();
void deposit();
void withdraw();
void play_slot();
void cash_out();
char* get_symbol_name(int symbol_value);
double calculate_payout(int s1, int s2, int s3, double bet);

int load_user_data();
void save_user_data();

int main() {
    initialize_game();
    login_user();

    int choice;

    do {
        display_menu();
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\n--==[ Invalid input. Please enter a number (1-4). ]==--\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: deposit(); break;
            case 2: withdraw(); break;
            case 3: play_slot(); break;
            case 4: cash_out(); break;
            default:
                printf("\n!!! Invalid option. Please choose from 1 to 4. !!!\n");
                break;
        }

    } while (choice != 4);

    return 0;
}

void save_user_data() {
    FILE *file = fopen(ACCOUNT_FILE, "w");

    if (file == NULL) {
        printf("Warning: Could not save data to %s.\n", ACCOUNT_FILE);
        return;
    }

    fprintf(file, "%s\n%.2f", currentUser.username, currentUser.balance);
    fclose(file);

    printf("Successfully saved account data to %s.\n", ACCOUNT_FILE);
}

int load_user_data() {
    FILE *file = fopen(ACCOUNT_FILE, "r");

    if (file == NULL) {
        return 0;
    }

    if (fscanf(file, "%49[^\n]\n%lf", currentUser.username, &currentUser.balance) == 2) {
        fclose(file);
        return 1;
    } else {
        fclose(file);
        return 0;
    }
}

void initialize_game() {
    srand((unsigned int)time(NULL));
}

void login_user() {
    printf("============================================\n");
    printf("         WELCOME TO THE C SLOT MACHINE      \n");
    printf("============================================\n");

    if (load_user_data()) {
        printf("Welcome back, %s! Loaded balance: $%.2f.\n",
               currentUser.username, currentUser.balance);
    } else {
        printf("Input Your Name [Max %d]: ", MAX_USERNAME_LENGTH - 1);
        getchar(); // clear leftover newline

        if (fgets(currentUser.username, MAX_USERNAME_LENGTH, stdin)) {
            currentUser.username[strcspn(currentUser.username, "\n")] = 0;
        } else {
            strcpy(currentUser.username, "Guest");
        }

        currentUser.balance = STARTING_BALANCE;
        printf("\nHello, %s! Your starting balance is $%.2f.\n",
               currentUser.username, currentUser.balance);
    }
}


void display_menu() {
    printf("\n\t\t\t[$$$] ATM [$$$]\n");
    printf("User: %s | Balance: $%.2f\n", currentUser.username, currentUser.balance);
    printf("--------------------------\n");
    printf("1. Deposit Money\n");
    printf("2. Withdraw Money\n");
    printf("3. Spin the Slot Machine (Cost: $%.2f)\n", COST_PER_SPIN);
    printf("4. Exit\n");
    printf("--------------------------\n");
}







void deposit() {
    double amount;
    printf("\nEnter deposit amount: $");

    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        printf("\n--==[ Invalid deposit amount. Please enter a positive number. ]==--\n");
        while (getchar() != '\n');
        return;
    }

    currentUser.balance += amount;
    printf("\nDeposit successful. New balance: $%.2f\n", currentUser.balance);
}















void withdraw() {
   double amount;
    printf("\ Enter withdrawal amount");

    if (scanf("%lf", &amount) != 1 || <= 0 ){
        printf("Invalid withdrawal amount);

    }

    if (amount > currentUser.balance) {
            printf(" Insufficient funds" );







}
   






















char* get_symbol_name(int symbol_value) {
    switch (symbol_value) {
        case 0: return "CHERRY";
        case 1: return "LEMON";
        case 2: return "BAR";
        case 3: return "SEVEN";
        case 4: return "JACKPOT!";
        default: return "ERROR";
    }
}

double calculate_payout(int s1, int s2, int s3, double bet) {
    if (s1 == s2 && s2 == s3) {
        if (s1 == 4) return bet * 50.0;
        if (s1 == 3) return bet * 25.0;
        if (s1 == 2) return bet * 10.0;
        if (s1 == 0 || s1 == 1) return bet * 5.0;
    }

    if (s1 == s2) {
        if (s1 == 4) return bet * 4.0;
        if (s1 == 3) return bet * 3.0;
        return bet * 2.0;
    }

    if (s1 == 0) return bet * 1.5;

    return 0.00;
}

void play_slot() {
    if (currentUser.balance < COST_PER_SPIN) {
        printf("\n--==[ You do not have enough money to spin. Deposit more! ]==--\n");
        return;
    }

    currentUser.balance -= COST_PER_SPIN;
    printf("\n--==[ Spinning the reels! Cost: $%.2f ]==--\n\n", COST_PER_SPIN);

    printf("Spinning");
    Sleep(400); printf(".");
    Sleep(400); printf(".");
    Sleep(400); printf(".\n");
    Sleep(400);

    int reel1 = rand() % 5;
    Sleep(350);
    int reel2 = rand() % 5;
    Sleep(350);
    int reel3 = rand() % 5;
    Sleep(350);

    printf("\n------------------------------\n");
    printf("| %8s | %8s | %8s |\n",
           get_symbol_name(reel1),
           get_symbol_name(reel2),
           get_symbol_name(reel3));
    printf("------------------------------\n");

    double winnings = calculate_payout(reel1, reel2, reel3, COST_PER_SPIN);

    if (winnings > 0) {
        currentUser.balance += winnings;
        printf("\n! CONGRATULATIONS !\n");
        printf("You won $%.2f!\n", winnings);
    } else {
        printf("\nSorry, better luck next time.\n");
    }

    printf("New Balance: $%.2f!\n", currentUser.balance);
}
void cash_out() {
    printf("\nInitiating Exit Process\n");
    printf("\n=====[ Final Summary ]=====\n");
    printf("\nUser: %s\n", currentUser.username);
    printf("\nBalance to Cash Out: %.2f\n", currentUser.balance);
    currentUser.balance = 0;
    save_user_data();
}


