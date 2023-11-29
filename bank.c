#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CUSTOMERS 100
#define ADMIN_USERNAME "mosad"
#define ADMIN_PASSWORD 1111

typedef struct Customer
{
    int id;
    int password;
    int account_number;
    float balance;
} Customer;

int num_customers = 0;
Customer customers[MAX_CUSTOMERS];


void admin();
void add_customer();
void staff();
void exit_program();
void check_balance(Customer*);
void transfer(Customer*);
void deposit(Customer*);
void withdraw(Customer*);


int main() {
    int choice;
    while (1)
    {
        printf("\n\t\t\t*********\n\t\t\t*   Main Menu for BMS   *\n\t\t\t*********\n\t\t\t*"
               "      1. Admin Panel.  *\n\t\t\t*   "
               "   2. Staff Panel.  *\n\t\t\t*      3. Exit.    "
               "     *\n\t\t\t*********\n\t\t\tEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                admin();
                break;
            case 2:
                staff();
                break;
            case 3:
                exit_program();
                break;
            default:
                printf("\nInvalid choice, please enter a valid choice.\n");
        }
    }

    return 0;
}
void admin()
{
    char user_name[100];
    int password;
    while (1)
    {
        printf("\n\t\tEnter user_name: ");
        scanf("%s", user_name);
        printf("\t\tEnter password: ");
        scanf("%d", &password);
        if (strcmp(user_name, ADMIN_USERNAME) == 0 && password == ADMIN_PASSWORD)
        {
            int x;
            while (1)
            {
                printf("\n\t\tLogin successfully, welcome MR/MS:%s\n", user_name);
                printf("\n\n\t\t\t*********\n\t\t\t*      Admin Panel      *\n\t\t\t*********\n\t\t\t*  1. Add Customer.     *\n\t\t\t*  2. Delete Customer.  *\n\t\t\t*  3. Search Customer.  *\n\t\t\t*  4. Return to Main menu*\n\t\t\t*********\n\t\t\tEnter Your Choice: ");
                scanf("%d", &x);
                switch (x)
                {
                case 1:
                    add_customer();
                    break;
                // case 2:
                //     delete_customer();
                //     break;
                // case 3:
                //     search_customer();
                //     break;
                case 4:
                    return;
                    break;
                default:
                    printf("\nInvalid choice, please enter a valid choice.\n");
                }
            }
        }
        else
        {
            char l;
            printf("\n\t\tSorry, your user name or password is incorrect. Do you want to try again (y/n)? ");
            scanf(" %c", &l);
            if (l == 'n' || l == 'N')
            {
                return;
            }
        }
    }
}
void add_customer()
{
    if (num_customers >= MAX_CUSTOMERS)
    {
        printf("\nCannot add more customers, the database is full.\n");
        return;
    }
    printf("\n\t\t\t**** Add Customer *****\n\n");
    Customer new_customer;
    printf("\t\tEnter User ID : ");
    scanf("%d", &new_customer.id);
    for (int i = 0; i < num_customers; i++)
    {
        if (new_customer.id == customers[i].id)
        {
            printf("\t\tUser ID already exists, please try again.\n");
            return;
        }
    }
    printf("\t\tEnter password: ");
    scanf("%d", &new_customer.password);
    printf("\t\tEnter account number: ");
    scanf("%d", &new_customer.account_number);
    printf("\t\tEnter initial balance: ");
    scanf("%f", &new_customer.balance);
    customers[num_customers] = new_customer;
    num_customers++;
    printf("\n\t\tNew customer added successfully.\n");
}

void staff()
{
    int id, password;
    printf("\n\t\tEnter user ID: ");
    scanf("%d", &id);
    printf("\t\tEnter password: ");
    scanf("%d", &password);
    for (int i = 0; i < num_customers; i++)
    {
        if (customers[i].id == id && customers[i].password == password)
        {
            int choice;
            while (1)
            {
                printf("\n\t\tLogin successfully, welcome, MR/MS. %d\n", id);
                printf("\n\n\t\t\t*********\n\t\t\t*      Staff Panel       *\n\t\t\t*********\n\t\t\t*  1. Deposit.           *\n\t\t\t*  2. Withdraw.          *\n\t\t\t*  3. Check Balance.     *\n\t\t\t*  4.transfer.           *\n\t\t\t*  5. Return to Main menu*\n\t\t\t*********\n\t\t\tEnter Your Choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    deposit(&customers[i]);
                    break;
                case 2:
                    withdraw(&customers[i]);
                    break;
                case 3:
                    check_balance(&customers[i]);
                    break;
                case 4:
                    transfer(&customers[i]);
                    break;
                case 5:
                    return;
                    break;
                default:
                    printf("\nInvalid choice, please enter a valid choice.\n");
                }
            }
        }
    }
    printf("\n\t\tUser ID or password is incorrect.\n");
}
void check_balance(Customer *customer)
{
    printf("\n\t\tAccount balance is %.2f.\n", customer->balance);
}
void exit_program()
{
    printf("\n\t\t*Thank you for using our Banking Management System.*\n\n\t\t\t\t *THE MOON*\n");
    exit(0);
}
void transfer(Customer *sender)
{
    int receiver_id;
    float amount;
    printf("\n\t\tEnter the user ID of the receiver: ");
    scanf("%d", &receiver_id);
    Customer *receiver = 0;
    for (int i = 0; i < num_customers; i++)
    {
        if (customers[i].id == receiver_id)
        {
            receiver = &customers[i];
            break;
        }
    }
    if (receiver == 0)
    {
        printf("\n\t\tReceiver with ID %d not found.\n", receiver_id);
        return;
    }
    printf("\n\t\tEnter the amount to transfer: ");
    scanf("%f", &amount);
    if (amount > sender->balance)
    {
        printf("\n\t\tInsufficient balance.\n");
        return;
    }
    sender->balance -= amount;
    receiver->balance += amount;
    printf("\n\t\tTransfer of %.2f from account %d to account %d is successful.\n", amount, sender->account_number, receiver->account_number);
}
void deposit(Customer *customer)
{
    float amount;
    printf("\n\t\tEnter amount to deposit: ");
    scanf("%f", &amount);
    customer->balance += amount;
    printf("\n\t\tDeposit of %.2f successful, new balance is %.2f.\n", amount, customer->balance);
}
void withdraw(Customer *customer)
{
    float amount;
    printf("\n\t\tEnter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount > customer->balance)
    {
        printf("\n\t\tInsufficient balance.\n");
        return;
    }
    customer->balance -= amount;
    printf("\n\t\tWithdrawal of %.2f successful, new balance is %.2f.\n", amount, customer->balance);
}