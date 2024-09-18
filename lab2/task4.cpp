#include <iostream>
#include <string>

using namespace::std;

class Account {
    protected:
        int account_number;
        double balance;
        string customer_name;

    public:
        Account(int account_num, double balance, string customer_name) {
            this->account_number = account_num;
            this->balance = balance;
            this->customer_name = customer_name;
        }

        virtual void deposit(double amount) = 0;
        virtual double withdraw(double amount) = 0;

        void display_info(){
            cout << "---------------------" << endl << "Account Details:" << endl;
            cout << "Customer Name: " << customer_name << endl;
            cout << "Balance: " << balance << endl;
            cout << "Account Number: " << account_number << endl;
            cout << "---------------------" << endl;
        }

        virtual ~Account() = default;  // Virtual destructor for cleanup of derived classes

        // Operator overloading for comparing classes
        bool operator>(const Account &other) const {
            return balance > other.balance;
        }

        bool operator<(const Account &other) const {
            return balance < other.balance;
        }

        bool operator==(const Account &other) const {
            return balance == other.balance && customer_name == other.customer_name && account_number == other.account_number;
        }

};

class SavingsAccount : public Account {
    private:
        double interest_rate;

    public:
        SavingsAccount(int account_num, double balance, string customer_name, double interest_rate) : 
        Account(account_num, balance, customer_name), interest_rate(interest_rate) {}
        
        void deposit(double amount){
            balance += amount + amount * interest_rate;
        }

        double withdraw(double amount){
            if (amount > 0 && balance >= 1000){
                balance -= amount;
                return amount;
            }
            else {
                cout << "Cannot withdraw. Your account balance is less than one thousad (1000)." << endl;
                return 0;
            }
        }
};

class CheckingAccount : public Account {
    private:
        double overdraft_limit;

    public:
        CheckingAccount(int account_num, double balance, string customer_name, double overdraft_limit) : 
        Account(account_num, balance, customer_name), overdraft_limit(overdraft_limit) {}

        double withdraw(double amount) {
            if (amount > 0 && amount <= balance + overdraft_limit){
                balance -= amount;
                return amount;
            }
            else {
                cerr << "Withdrawal amount exceeds balance and overdraft limit." << endl;
                return 0;
            }
        }

        void deposit(double amount) {
            balance += amount;
        }
};

class InvestmentAccount : public Account {
    private:
        int investment_duration; // years
        double risk_factor;

    public:
        InvestmentAccount(int account_num, double balance, string customer_name, int investment_duration, double risk_factor) : 
        Account(account_num, balance, customer_name), investment_duration(investment_duration), risk_factor(risk_factor) {}

        void deposit(double amount){
            balance += amount + (amount * risk_factor * (investment_duration/12));
        }

        double withdraw(double amount){
            balance -= amount + (amount * risk_factor * (investment_duration/12));
            return amount;
        }
};

int main() {
    // Create objects of each class
    SavingsAccount saving_account = SavingsAccount(1, 0, "Abdullah", 0.2);
    CheckingAccount checking_account = CheckingAccount(1, 0, "Abdullah", 5000);
    InvestmentAccount investment_account = InvestmentAccount(2, 0, "Zain", 2, 0.1);

    // perform deposit operations
    saving_account.deposit(5555);
    checking_account.deposit(5555);
    investment_account.deposit(4444);

    // Display info
    saving_account.display_info();
    checking_account.display_info();
    investment_account.display_info();

    // perform withdraw operations
    saving_account.withdraw(55);
    checking_account.withdraw(55);
    investment_account.withdraw(44);

    // Display info
    saving_account.display_info();
    checking_account.display_info();
    investment_account.display_info();

    cout << "saving_account > investment_account = " << (saving_account > investment_account) << endl;
    cout << "saving_account == checking_account = " << (saving_account == checking_account) << endl;
    cout << "saving_account < investment_account = " << (saving_account < investment_account) << endl;


    cout << "Using polymorphism :" << endl;
    // Using polymorphism with base class pointers
    Account* accounts[3];

    accounts[0] = new SavingsAccount(101, 200.0, "Abdullah", 0.4);  // 3% interest rate
    accounts[1] = new CheckingAccount(102, 400.0, "Gunshot Arshad", 20000); // $10,000 overdraft limit
    accounts[2] = new InvestmentAccount(102, 1030.0, "Abdullah", 20, 0.2); // 12 months, 10% risk factor

    // Deposit money
    accounts[0]->deposit(1000);
    accounts[1]->deposit(500);
    accounts[2]->deposit(2000);

    cout << "Account details after deposits:" << endl;
    for (int i = 0; i < 3; ++i) {
        accounts[i]->display_info();
    }

    // Withdraw money
    accounts[0]->withdraw(200);
    accounts[1]->withdraw(600);
    accounts[2]->withdraw(500);

    cout << "Account details after withdrawals:" << endl;
    for (int i = 0; i < 3; ++i) {
        accounts[i]->display_info();
    }
}
