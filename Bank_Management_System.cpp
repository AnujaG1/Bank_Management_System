#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

class BankAccount {
public:
string AccountNum;
string Holder;
string AccountType;
float Balance;
vector<string> transactionHistory;

BankAccount(const string& n, const string& holder, const string& t, const float& b) : AccountNum(n), Holder(holder),AccountType(t), Balance(b) {}

BankAccount() : AccountNum(""), Holder(""), AccountType(""), Balance(0.0f) {}

string getAccount() const  { return AccountNum; }
string getHolder() const { return Holder; }
string getType() const { return AccountType; }
float getBalance() const { return Balance; }

void setAccount(const string &n) { AccountNum = n; }
void setHolder(const string &holder) { Holder = holder; }
void setType(const string &t) { AccountType = t;}
void setBalance(const float b) {Balance = b;  }

void deposit(double amount)
{   
 
Balance+=amount;
transactionHistory.push_back("Deposited: "+ to_string(amount));
cout<<"Balance is: "<<Balance<<endl;
cout<<"Amount deposited successfully!"<<endl;

}
void withdraw(double amount)
{
    if(amount>Balance)
    {
        cout<<"Insufficient balance!"<<endl;
        cout<<"Your balance is :"<<Balance<<endl;
    }
    else{
        Balance = Balance -amount;
        transactionHistory.push_back("Withdraw: "+to_string(amount));
        cout<<"Amount left: "<<Balance<<endl;
        cout<<"Amount withdrawn successfully!"<<endl;
    }
}

void compare(const BankAccount &other) {
    if(*this== other){
        cout<<"The two bank account have the same balance."<<endl;
    }
    else if(this->Balance > other.Balance) {
        cout<<this->Holder<<" bank account has a higher balance."<<endl;
    }
    else {
        cout<<other.Holder<<"'s bank account has a higher balance."<<endl;
    }
}

void history()
{
 cout<<"Transaction History for Account: "<<AccountNum<<endl;
 for (const string& record: transactionHistory)
 {
    cout<<record<<endl;
 }
}

void transfer(double amount,  BankAccount &other)
{
 cout<<"Current Balance in "<<this->Holder<<" : "<<  this->Balance<<endl;
 cout<<"Current Balance in "<<other.Holder<<" : "<< other.Balance<<endl; 
 cout<<endl;
 if(amount> Balance)
 {
    cout<<"Insufficient Balance!";
     cout<<" Your Balance"<<" : "<< other.Balance<<endl; 
 
 }
 else{
 other.Balance += amount;
 Balance -= amount;
 transactionHistory.push_back("Transferred: " + to_string(amount)+ " to account "+other.getAccount());
 other.transactionHistory.push_back("Received: "+ to_string(amount)+"from account "+getAccount());
 cout<<"Transferred "<<amount<<" to account "<<other.getAccount()<<endl;
 cout<<other.Holder<<"'s ,new balance is "<<other.Balance<<endl;
 cout<<Holder<<"'s ,new balance is "<<Balance<<endl;
 }
    
}
BankAccount operator+(const BankAccount &other) {
    float new_balance = this->Balance + other.Balance;
    return BankAccount(this->AccountNum, this->Holder, this->AccountType, new_balance);
}

    bool operator==(const BankAccount &other) const {
        return this->Balance == other.Balance;
    }

    virtual double getInterest() const { return 0.0;}
    virtual void displayDetails() const
    {
        cout<<"Account Number: "<<AccountNum<<endl;
        cout<<"Account Holder Name: "<<Holder<<endl;
        cout<<"Account Type: "<<AccountType<<endl;
        cout<<"Balance: "<<Balance<<endl;
    }
    virtual ~BankAccount() {}
};
class SavingsAccount: public BankAccount{
    private:
    double interest;
    int year;
    double cf;
    public:

    SavingsAccount(const string n , const string holder, const string t,const float b, const double i, const int yr, const double c): BankAccount(n,holder,t,b), interest(i), year(yr), cf(c) {}

    SavingsAccount() : BankAccount(), interest(0.0) {}

    double getInterestRate() const{ return interest; }
    void setInterestRate(double i) { interest = i; }
    void setYear(int yr) { year = yr; }
    void setFrequency(float c) { cf = c;}
     void displayDetails() const {
     BankAccount::displayDetails();
     cout<<"Interest Rate: "<<interest<<"%"<<endl;
     cout<<"Time interval: "<<year<<" years"<<endl;
     cout<<"Compounding frequency: "<<cf<<endl;
     float r = interest/100;
     float ca = Balance * pow((1+r/cf),cf*year);
     cout<<"The compound iterest amount is Rs."<<ca<<endl;
    }
};

class CheckingAccount: public BankAccount{
    private:
    double interest;
    public: 
    CheckingAccount(const string n, const string holder, const string t, const float b, const double i ):BankAccount(n,holder,t,b),interest(i) {}
    CheckingAccount() : BankAccount(), interest(0.0) {}

    double getInterestRate() const { return interest; }
    void setInterestRate(double i) { interest = i; }
    void displayDetails() const {
     BankAccount::displayDetails();
     cout<<"Interest Rate: "<<interest<<"%"<<endl;
    }
};
class CreditAccount: public BankAccount{
    private:
    float borrow;
    float rate;
    public:
    CreditAccount( const string n, const string holder, const string t, const float b, const float bor, const float r ):BankAccount(n,holder,t,b),borrow(bor), rate(r) {}
     CreditAccount() : BankAccount(), borrow(0.0), rate(0.0) {}

     float getBorrow() const { return borrow; }
     float getRate() const{ return rate; }
     void setBorrow(float bor, float r) { 
        borrow = bor; 
         rate = r;
         }
     void displayDetails() const {
     BankAccount :: displayDetails();
     cout<<"Amount Borrowed: Rs."<<borrow<<endl;
     float charge = (rate/100)*borrow;
     cout<<"Charge on borrowed amount is "<<charge<<endl;


     }

};

class JointAccount: public BankAccount{
    private:
    vector<string> accountHolders;
    public:
    JointAccount(const string n, const vector<string>& holders, const string& t, const float &b ):BankAccount(n, holders[0], t,b), accountHolders(holders) {}

    JointAccount() : BankAccount() {}

    void addAccountHolder(const string& holder) {
     accountHolders.push_back(holder);
    }
    void removeAccountHolder(const string & holder) {
         accountHolders.erase(remove(accountHolders.begin(), accountHolders.end(), holder), accountHolders.end());
    }
    void displayDetails() const override {
        BankAccount::displayDetails();
        cout<<"Account Holders: ";
        for(const auto& holder: accountHolders)
        {
            cout<<holder<<" ";
        }
        cout<<endl;
    }
};

void getBankDetails(BankAccount &account)
{
    string accountnum, holder, accounttype;
    float balance;
    cout<<"Enter Account Number: ";
    cin>>accountnum;
    cout<<"Enter Holder name: ";
    cin>>holder;
    cout<<"Enter account type: ";
    cin>>accounttype;
    cout<<"Enter balance:";
    cin>>balance;

    account.setAccount(accountnum);
    account.setHolder(holder);
    account.setType(accounttype);
    account.setBalance(balance);
}

void setInterestRate(CheckingAccount& c) {
    double interest;
    cout << "Enter interest rate for checking account: ";
    cin >> interest;
    c.setInterestRate(interest);
}
void setInterestRate(SavingsAccount& s) {
    double interest ;
    cout << "Enter interest rate for savings account: ";
    cin >> interest;
    s.setInterestRate(interest);
}
void setYear(SavingsAccount & s)
{
    int year;
    cout<<"Enter time interval: ";
    cin>>year;
    s.setYear(year);
}
void setFrequency(SavingsAccount &s)
{
    float cf;
    cout<<"Enter compounding frequency: ";
    cin>>cf;
    s.setFrequency(cf);

}
void setBorrow(CreditAccount & cr)
{
    float borrow, rate;
    cout<<"Enter amount to be borrowed: "<<endl;
    cin>>borrow;
    cout<<"Enter interest charge: ";
    cin>>rate;
    cr.setBorrow(borrow, rate);
}

void setJointAccountDetails(JointAccount &j)
{
    string accountnum, holder, accounttype;
    float balance;
    int numHolders;
    vector<string> holders;

    cout<<"Enter Account number: ";
    cin>>accountnum;
    cout << "Enter number of account holders: ";
    cin >> numHolders;
    for(int i =0; i<numHolders;++i)
    {
        cout<<"Enter holder name:";
        cin>>holder;
        holders.push_back(holder);
    }
    cout<<"Enter account type: ";
    cin>>accounttype;
    cout<<"Enter balance: ";
    cin>> balance;

    if(!holders.empty()){ j.setHolder(holders[0]); }

    j.setAccount(accountnum);
    j.setType(accounttype);
    j.setBalance(balance);
    
    for (const auto& h : holders) {
        j.addAccountHolder(h);
    }
    cout<<endl;

}
int main()
{
   BankAccount b, b1;
   CheckingAccount c;
   SavingsAccount s;
   CreditAccount cr;
   JointAccount j;
   double amount;
    bool running = true;
    int ch;
    
    cout<<"Bank Management System!"<<endl;
    cout<<"Enter details of the first bank account:"<<endl;
    getBankDetails(b);
    cout<<endl;
    // getBankDetails(b1);

    c.setAccount(b.getAccount());
    c.setHolder(b.getHolder());
    c.setType(b.getType());
    c.setBalance(b.getBalance());

    s.setAccount(b.getAccount());
    s.setHolder(b.getHolder());
    s.setType(b.getType());
    s.setBalance(b.getBalance());

    cr.setAccount(b.getAccount());
    cr.setHolder(b.getHolder());
    cr.setType(b.getType());
    cr.setBalance(b.getBalance());

   
    while(running)
    {
        cout<<"Menu:"<<endl;
        cout<<"1. Deposit"<<endl;
        cout<<"2. Withdraw"<<endl;
        cout<<"3. Compare"<<endl;
        cout<<"4. Transaction History"<<endl;
        cout<<"5. Transfer fund"<<endl;
        cout<<"6. Display Interest Rate"<<endl;
        cout<<"7. Display Bank Details"<<endl;
        cout<<"8. Borrow "<<endl;
        cout<<"9. Joint Account"<<endl;
        cout<<"10. Exit"<<endl;
        cout<<"Enter choice: ";
        cin >>ch;
        switch(ch)
        {
            case 1:
            cout<<"Amount : ";
            cin>>amount;
            b.deposit(amount);
            
            break;

             case 2:
             cout<<"Withdraw Amount: ";
             cin>>amount;
            b.withdraw(amount);
            break;

             case 3:
             b.compare(b1);
            break;

            case 4:
           b.history();
            break;

            case 5:
            cout<<"Transfer Amount: ";
            cin>>amount;
            b.transfer(amount, b1);
            break;

            case 6:
             cout << "Checking Account Details:" << endl;
            setInterestRate(c);
            c.displayDetails();
            
            cout<<endl;
            cout << "Savings Account Details:" << endl; 
            setInterestRate(s);
            setYear(s);
            setFrequency(s);
                s.displayDetails();
                break;
            
            case 7:
            b.displayDetails();
            break;
            
            case 8:
            setBorrow(cr);
            cr.displayDetails();
            break;

            case 9:
            setJointAccountDetails(j);
            j.displayDetails();
            break;

             case 10:
             running = false;
             cout<<"Exiting the program"<<endl;
             break;

             default:
             cout<<"Enter valid choice (1-4): "<<endl;
             break;
        }
    }
    return 0;
}