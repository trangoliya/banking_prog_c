#include <stdio.h>
#include <conio.h>

// Structure to store account details
struct account {
  int accNo;
  char name[30];
  float balance;
};

void create();
void display();
void view();
void del();
void search();

void deposit();
void withdraw();
void checkBalance();
void transfer();

void adminMenu();
void customerMenu();

// Entry point of the program
// Displays main menu and redirects to Admin or Customer menu
void main() {
    int choice;

    while (1) {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Admin\n");
        printf("2. Customer\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: adminMenu(); break;
            case 2: customerMenu(); break;
            case 3: return;
            default: printf("❌ Invalid Choice\n");
        }
    }
}

/* ================= ADMIN ================= */

void adminMenu() {
    int ch;
    while (1) {
        printf("\n--- ADMIN MENU ---\n");
        printf("1. Create Account\n");
        printf("2. Display All Accounts\n");
        printf("3. View Account\n");
        printf("4. Delete Account\n");
        printf("5. Search Account\n");
        printf("6. Back\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: create(); break;
            case 2: display(); break;
            case 3: view(); break;
            case 4: del(); break;
            case 5: search(); break;
            case 6: return;
            default: printf("❌ Invalid Choice\n");
        }
    }
}
// File pointer used to access bank.dat file
void create() {
    struct account a;
    FILE *fp = fopen("bank.dat", "ab");

    printf("Enter Account Number: ");
    scanf("%d", &a.accNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", a.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("✅ Account Created Successfully\n");
}

void display() {
    struct account a;
    FILE *fp = fopen("bank.dat", "rb");

    printf("\n--- ALL ACCOUNTS ---\n");
    while (fread(&a, sizeof(a), 1, fp)) {
        printf("AccNo: %d | Name: %s | Balance: %.2f\n",
               a.accNo, a.name, a.balance);
    }
    fclose(fp);
}

void view() {
    struct account a;
    int acc, found = 0;
    FILE *fp = fopen("bank.dat", "rb");

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc) {
            printf("\nAccount No: %d\nName: %s\nBalance: %.2f\n",
                   a.accNo, a.name, a.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("❌ Invalid Account Number\n");
}

void del() {
    struct account a;
    int acc, found = 0;
    FILE *fp = fopen("bank.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter Account Number to Delete: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo != acc)
            fwrite(&a, sizeof(a), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    // Replaces old file with updated file
    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if (found)
        printf("✅ Account Deleted\n");
    else
        printf("❌ Invalid Account Number\n");
}

void search() {
    struct account a;
    int acc, found = 0;
    FILE *fp = fopen("bank.dat", "rb");

    printf("Enter Account Number to Search: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc) {
            printf("AccNo: %d | Name: %s | Balance: %.2f\n",
                   a.accNo, a.name, a.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("❌ Account Not Found\n");
}

/* ================= CUSTOMER ================= */

void customerMenu() {
    int ch;
    while (1) {
        printf("\n--- CUSTOMER MENU ---\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Check Balance\n");
        printf("4. Transfer Money\n");
        printf("5. Back\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: deposit(); break;
            case 2: withdraw(); break;
            case 3: checkBalance(); break;
            case 4: transfer(); break;
            case 5: return;
            default: printf("❌ Invalid Choice\n");
        }
    }
}

void deposit() {
    struct account a;
    int acc, found = 0;
    float amt;
    FILE *fp = fopen("bank.dat", "rb+");

    printf("Enter Account Number: ");
    scanf("%d", &acc);
    printf("Enter Amount: ");
    scanf("%f", &amt);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc) {
            a.balance += amt;
            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);
            printf("✅ Deposit Successful\n");
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("❌ Invalid Account Number\n");
}

void withdraw() {
    struct account a;
    int acc, found = 0;
    float amt;
    FILE *fp = fopen("bank.dat", "rb+");

    printf("Enter Account Number: ");
    scanf("%d", &acc);
    printf("Enter Amount: ");
    scanf("%f", &amt);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc && a.balance >= amt) {
            a.balance -= amt;
            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);
            printf("✅ Withdrawal Successful\n");
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("❌ Insufficient Balance or Invalid Account\n");
}

void checkBalance() {
    struct account a;
    int acc, found = 0;
    FILE *fp = fopen("bank.dat", "rb");

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc) {
            printf("💰 Balance: %.2f\n", a.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("❌ Invalid Account Number\n");
}

void transfer() {
    struct account a1, a2;
    int from, to, found1 = 0, found2 = 0;
    float amt;
    FILE *fp = fopen("bank.dat", "rb+");

    printf("From Account: ");
    scanf("%d", &from);
    printf("To Account: ");
    scanf("%d", &to);
    printf("Amount: ");
    scanf("%f", &amt);

    while (fread(&a1, sizeof(a1), 1, fp)) {
        if (a1.accNo == from && a1.balance >= amt) {
            found1 = 1;
            break;
        }
    }

    while (fread(&a2, sizeof(a2), 1, fp)) {
        if (a2.accNo == to) {
            found2 = 1;
            break;
        }
    }

    if (found1 && found2) {
        a1.balance -= amt;
        a2.balance += amt;

        fseek(fp, -2 * sizeof(a1), SEEK_CUR);
        fwrite(&a1, sizeof(a1), 1, fp);
        fwrite(&a2, sizeof(a2), 1, fp);

        printf("✅ Transfer Completed\n");
    } else {
        printf("❌ Transfer Failed\n");
    }
    fclose(fp);
}
