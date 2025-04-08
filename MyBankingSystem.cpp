#include <iostream>
#include <string>


using namespace std;

class BankAccount {
    private:
    string ownerName;
    string accountNumber;
    double balance;
    int pin;
    bool locked=false;

    public:
    BankAccount(string ownerName, string accountNumber, double balance,int pin);
    bool verifyPin();
    void deposit(double amount);
    bool withdraw(double amount);
    void displayBalance() const;
    bool isLocked() const;
    void CheckLowBalance(double minBalance = 50.0) const;
    bool TransferMoney(double amount, BankAccount& targetAccount);
    void changePIN();
};
BankAccount::BankAccount(string owner, string accNum, double initialbalance, int Enteredpin) {
    ownerName = owner;
    accountNumber = accNum;
    balance = initialbalance;
    pin = Enteredpin;
}
bool BankAccount::verifyPin() {
    if (locked) {
        std::cout<< "Account is locked due to many incorrent PIN attempts" << std::endl;
    }
    int attempts = 0;
    int Enteredpin;
    while (attempts <3) {
        std::cout<< "Enter account PIN" << std::endl;
        std::cin >> Enteredpin;
        if (Enteredpin == pin) {
            return true;
        } else {
            std::cout <<"Incorrect PIN" << std::endl;
            attempts++;
        }
    }
    std::cout << "Too many incorrected attempts. Account is locked" << std::endl;
    locked = true;
    return false;
}
bool BankAccount::isLocked() const{
        return locked;
}
void BankAccount::deposit(double amount) {
    if (isLocked()) {
        std::cout << "Account is locked. Cannot perform deposit" << std::endl;
        return;
    }
    if (amount > 0) {
        balance+= amount;
        std::cout << "Deposit " << amount << " euro. New balance: " << balance << std::endl;
    } else {
        std::cout << "Please enter a positive amount." << std::endl;
    }
}
bool BankAccount::withdraw(double amount) {
    if (isLocked()) {
        std::cout << "Account is locked. Cannot perform withdraw" << std::endl;
        return false;
    }
    if (amount > 0 && amount <=balance) {
        balance-= amount;
        std::cout << "Withdraw " << amount << " euro. New balance: " << balance << std::endl;
        CheckLowBalance();
        return true;
    } else {
        std::cout << "Not enough balance." << std::endl;
        return false;
    }
}
void BankAccount::displayBalance() const{
    std::cout << "The account " << accountNumber << " has " << balance << " euro." << std::endl;
}
void BankAccount::CheckLowBalance(double minBalance) const {
    if (balance < minBalance) {
        std::cout << "Warning: Your balance is low. Current balance: " << balance << std::endl;
    }
}
bool BankAccount::TransferMoney(double amount, BankAccount& targetAccount) {
    if (amount<=0) {
        std::cout << "Please enter a positive amount for transfer" << std::endl;
        return false;
    }
    if (amount> balance) {
        std::cout << "Insufficient funds to transfer" << std::endl;
        return false;
    }
    balance-= amount;
    targetAccount.balance += amount;
    std::cout << "Transferred " << amount << " euro to " << targetAccount.accountNumber << ". " << targetAccount.ownerName << "'s new balance: " << targetAccount.balance << " euro.\n";
    return true;
}
void BankAccount::changePIN() {
    if (locked) {
        std::cout << "Account is locked. Cannot change PIN." << std::endl;
        return;
    }
    int OldPin, NewPin, confirmPin;
    std::cout << "Enter current pin: " << std::endl;
    std::cin >> OldPin;
    if (OldPin != pin) {
        std::cout << "Incorrect PIN.Returning to menu.\n";
        return;
    }
    std::cout << "Enter new PIN: " << std::endl;
    std::cin >> NewPin;
    std::cout << "Confirm PIN: " << std::endl;
    std::cin >> confirmPin;
    if (NewPin != confirmPin) {
        std::cout << "PINs dont match. Try again\n";
        return;
    }
    pin=NewPin;
    std::cout << "Pin changed succesfully.\n" << std::endl;
}
int main() {
    BankAccount account1("Vasilis Grigoriadis", "GR04112003",1000.0, 2003);
    BankAccount account2("Giannis Papadopoulos", "GR09872001", 1000.0, 1234);
    BankAccount account3("Dimitris Terzis", "GR12345678", 1000.0, 1234);
    BankAccount* currentAccount = nullptr;
    int choice,accountChoice;
    double amount;
    while (true) {
        std::cout << "\nBANK SYSTEM BY VASILISGR\n" << std::endl;
        std::cout << "\nChoose an account:\n";
        std::cout << "1. Vasilis Grigoriadis (GR04112003)\n";
        std::cout << "2. Giannis Papadopoulos (GR09872001)\n";
        std::cout << "3. Dimitris Terzis (GR12345678)\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> accountChoice;

        if (accountChoice == 0) break;

        switch (accountChoice) {
            case 1:
                currentAccount = &account1;
                break;
            case 2:
                currentAccount = &account2;
                break;
            case 3:
                currentAccount = &account3;
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                continue;
        }
        if (currentAccount->isLocked()) {
            std::cout << "Account is locked. Returning to main menu." << std::endl;
            continue;
        }
        if (!currentAccount->verifyPin()) {
            continue;
        }

        while (true) {
            std::cout << "\nAccount: " << (accountChoice == 1 ? "Vasilis Grigoriadis" : (accountChoice == 2 ? "Giannis Papadopoulos": "Dimitris Terzis" )) << "\n";
            std::cout << "\n1. Deposit\n2. Withdraw\n3. Balance\n4. Transfer money\n5. Change PIN\n0. Exit\nChoice: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    std::cout << "Enter deposit amount: ";
                std::cin >> amount;
                currentAccount->deposit(amount);
                break;
                case 2:
                    std::cout << "Enter withdrawal amount: ";
                std::cin >> amount;
                currentAccount->withdraw(amount);
                break;
                case 3:
                    currentAccount->displayBalance();
                break;
                case 4: {
                    int targetChoice;
                    BankAccount* targetAccount = nullptr;
                    std::cout << "Choose target account to transfer:\n" <<std::endl;
                    std::cout << "1. Vasilis Grigoriadis\n";
                    std::cout << "2. Giannis Papadopoulos\n";
                    std::cout << "3. Dimitris Terzis\n";
                    std::cout << "Choice: ";
                    std::cin >> targetChoice;
                    if (targetChoice == 1) {
                        targetAccount = &account1;
                    } else if (targetChoice == 2) {
                        targetAccount = &account2;
                    } else if (targetChoice == 3) {
                        targetAccount = &account3;
                    } else {
                        std::cout << "Invalid choice. Try again.\n";
                        continue;
                    }
                    std::cout << "Enter transfer amount" << std::endl;
                    std::cin >> amount;
                    if (currentAccount->TransferMoney(amount, *targetAccount)) {
                        std::cout << "Transfer successful." << std::endl;
                    } else {
                        std::cout << "Transfer failed." << std::endl;
                    }
                    break;
                }
                case 5:
                    currentAccount->changePIN();
                    break;
                case 0:
                    std::cout << "Returning to account selection...\n";
                    goto select_account;
                default:
                    std::cout << "Incorrect choice. Try again.\n";
            }
        }

    select_account:
        continue;
    }

    std::cout << "Exiting Banking System.\n";
    return 0;
}