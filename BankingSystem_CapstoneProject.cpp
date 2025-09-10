#include <iostream>
#include <fstream>
using namespace std;

//Classes
class Account{
    public:
        int accountnum;
        string accountholdername;
        string acctype;
        double balance;
        Account() {
            accountnum = 0;
            accountholdername = "";
            acctype = "";
            balance = 0.0;
        }
};


//Functions
void savefile(Account obj[], int index) {
    fstream file;
    file.open("Account_details.txt", ios::app);
    file<<"Account Number: "<<obj[index].accountnum<<endl;
    file<<"Account holder's name: "<<obj[index].accountholdername<<endl;
    file<<"Account type: "<<obj[index].acctype<<endl;
    file<<"Account holder's balance: "<<obj[index].balance<<endl;
    file<<"-----------------------------------------------------------"<<endl;
    file.close();
}

int loadfile(Account obj[]) {
    ifstream file("Account_details.txt");
    int index = 0;
    while (file) {
        string line;
        getline(file, line);
        if (line.find("Account Number:") != string::npos) {
            obj[index].accountnum = stoi(line.substr(16));
            getline(file, line);
            obj[index].accountholdername = line.substr(21);
            getline(file, line);
            obj[index].acctype = line.substr(14);
            getline(file, line);
            obj[index].balance = stod(line.substr(17));
            // Skip separator
            getline(file, line);
            index++;
        }
    }
    return index;
}

void modifyfile(Account obj[], int totalCustomers) {
    ofstream file("Account_details.txt");
    for (int i = 0; i < totalCustomers; ++i) {
        if (obj[i].accountnum == 0) continue;
        file << "Account Number: " << obj[i].accountnum << endl;
        file << "Account Holder Name: " << obj[i].accountholdername << endl;
        file << "Account Type: " << obj[i].acctype << endl;
        file << "Account Balance: " << obj[i].balance << endl;
        file << "---------------------------" << endl;
    }
    file.close();
}


void login(){
    string username;
    string password;
    cout<<"User Name: ";
    cin>>username;
    cout<<"Password: ";
    cin>>password;
    if(username == "Admin" && password == "12345678") {
        cout<<"Access Granted"<<endl;
    }
    else {
        cout<<"Access denied \nTerminating program";
        exit(0);
    }
}

int option() {
    int optnum;
    cout<<"\n\n\nPlease select an option from below [Enter option number as mentioned below]"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"1. Add a new customer"<<endl<<"2. Delete an existing customer's account"<<endl<<"3. Look the details of an existing customer"<<endl<<"4. Deposit Money"<<endl<<"5. Log-out"<<endl;
    cin>>optnum;
    return optnum;
}

int deleteCustomer(int acNum, Account obj[]) {
    for(int i = 0; i < 30; i++){
        if (obj[i].accountnum == acNum) {
            obj[i].accountnum = 0;
            obj[i].accountholdername = "";
            obj[i].acctype = "";
            obj[i].balance = 0.0;
            return 1;
        }
    }
    return 0;
}

void fetchDetails(Account obj[]){
    int acNum, found = 0;
    cin>>acNum;
    for(int i = 0; i < 30; i++){
        if (obj[i].accountnum == acNum) {
            cout<<"\n\nCustomer's Account Number: "<<obj[i].accountnum<<endl;
            cout<<"Account holder's name: "<<obj[i].accountholdername<<endl;
            cout<<"Account holder's account type: "<<obj[i].acctype<<endl;
            cout<<"Available balance in account: "<<obj[i].balance<<endl;
            found = 1;
            break;
        }
    }
    if(found == 0) {
        cout<<"No account exists under the provided account number."<<endl;
    }
}

void deposit(Account obj[]) {
    int acNum, found = 0, amt;
    cout<<"Enter Account Number: ";
    cin>>acNum;
    for(int i = 0; i < 30; i++){
        if (obj[i].accountnum == acNum) {
            cout<<"Enter Amount to be deposited: ";
            cin>>amt;
            obj[i].balance += amt;
            cout<<"\n\nMoney Deposited successfully!!!";
            cout<<"\n\nCustomer's Account Number: "<<obj[i].accountnum<<endl;
            cout<<"Account holder's name: "<<obj[i].accountholdername<<endl;
            cout<<"Account holder's account type: "<<obj[i].acctype<<endl;
            cout<<"Balance in account after depositing " <<amt<<": "<<obj[i].balance<<endl;
            found = 1;
            break;
        }
    }
    if(found == 0) {
        cout<<"No account exists under the provided account number."<<endl;
        cout<<"Please re-check your account details and reselect deposit from main menu to deposit an amount into your account.";
    }
}


int main() {
    int optnum;
    Account acc[100];
    int customer = 0;
    int accountnum = 100000000;
    customer = loadfile(acc);
    if (customer > 0) {
        accountnum = acc[customer - 1].accountnum + 1;
    }

    cout<<"-----------------------Welcome to my Bank-------------------------"<<endl;
    cout<<"                *** Connecting lives Globally ***"<<endl;
    cout<<endl<<"Welcome Admin - Please enter your credentials"<<endl;
    
    //Asking user to login using their credentials
    login();
    
    //Condition to check, input from user regarding their choice
    while(1) {
        //If entered credentials are valid then proceeding with entering option
        optnum = option();

        if(optnum == 1) {
            
            cout<<"\nAdd new customer:"<<endl;

            acc[customer].accountnum = accountnum++;

            cout<<"Enter account Holder's Name: ";
            cin>>acc[customer].accountholdername;

            cout<<"Enter the account type (current/saving/other): ";
            cin>>acc[customer].acctype;

            cout<<"How much is the initial balance: ";
            cin>>acc[customer].balance;

            cout<<endl<<"Customer added successfully!!!"<<endl<<endl;

            cout<<"Your account number is: "<<acc[customer].accountnum;

            savefile(acc, customer);

            customer++;
        }

        else if(optnum == 2) {
            int acNum, work;
            cout<<"\nDelete existing account"<<endl;

            cout<<"Enter account number: ";
            cin>>acNum;

            work = deleteCustomer(acNum, acc);
            if(work == 0) {
                cout<<"Customer's Data was not found"<<endl;
            }
            else if(work == 1) {
                cout<<"Customer deleted successfully"<<endl;
                modifyfile(acc, customer);
            }
        }

        else if(optnum == 3) {
            cout<<"\nLooking at details of existing customer"<<endl;
            cout<<"Enter account number: ";
            fetchDetails(acc);
        }

        else if(optnum == 4) {
            cout<<"\nDeposit money"<<endl;
            deposit(acc);
            modifyfile(acc, customer);
        }

        else if(optnum == 5) {
            cout<<"\nLoggging out"<<endl;
            exit(0);
        }
    }
}