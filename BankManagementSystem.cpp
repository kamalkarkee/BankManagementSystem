#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
using namespace std;

#define MinBalance 50
class Insufficient_Funds{ 
};
class customer_Accounts
{
private:
long customer_Accounts_No;
string customer_Fname;
string customer_Lname;
float customer_balance;
static long Other_customer_Accounts_no;

public:
customer_Accounts(){}
customer_Accounts(string fname,string lname,float customer_balance);
long getAccNo(){return customer_Accounts_No;}
string getFName(){return customer_Fname;}
string getLName(){return customer_Lname;}
float getBlnce(){return customer_balance;}
void Deposit(float amount);
void Withdraw(float amount);
static void set_Previous_customer_Accounts_no(long customer_Accounts_No);
static long get_Previous_customer_Accounts_no();

friend ofstream & operator<<(ofstream &ofs,customer_Accounts &acc);
friend ifstream & operator>>(ifstream &ifs,customer_Accounts &acc);
friend ostream & operator<<(ostream &os,customer_Accounts &acc);
};
long customer_Accounts::Other_customer_Accounts_no=0;

class Bank
{
private:
map<long,customer_Accounts> accounts_cl;
public:
Bank();
customer_Accounts Cl_Open_Account(string fname,string lname,float balance);
customer_Accounts Cl_Balance_Enquiry(long Account_no);
customer_Accounts Deposit(long Account_no,float amt);
customer_Accounts Withdraw(long Account_no,float amt);
void CloseAccount(long Account_no);
void ShowAllAccounts();
~Bank();
};

int main()
{
Bank b;
customer_Accounts acc;
int option;
string fname,lname;
long account_no;
float blnced;
float amnts;
cout<<"***Bank Management System***"<<endl;
do
{
cout<<"\n\tSelect From The Options Below ";
cout<<"\n\t1 Open an New Account";
cout<<"\n\t2 Check Balance Enquiry";
cout<<"\n\t3 Deposit";
cout<<"\n\t4 Withdrawal";
cout<<"\n\t5 Close the Account";
cout<<"\n\t6 Show All Accounts";
cout<<"\n\t7 Quit";
cout<<"\nEnter your choice: ";
cin>>option;
switch(option)
{
case 1:
cout<<"Enter First Name: ";
cin>>fname;
cout<<"Enter Last Name: ";
cin>>lname;
cout<<"Enter Initial Balance: ";
cin>>blnced;
acc=b.Cl_Open_Account(fname,lname,blnced);
cout<<endl<<"Congratulations Account is Created"<<endl;
cout<<acc;
break;
case 2:
cout<<"Enter Account Number:";
cin>>account_no;
acc=b.Cl_Balance_Enquiry(account_no);
cout<<endl<<"Your Account Details"<<endl;
cout<<acc;
break;
case 3:
cout<<"Enter Account Number:";
cin>>account_no;
cout<<"Enter Balance:";
cin>>amnts;
acc=b.Deposit(account_no, amnts);
cout<<endl<<"Amount is Deposited in the account"<<endl;
cout<<acc;
break;
case 4:
cout<<"Enter Account Number:";
cin>>account_no;
cout<<"Enter Balance:";
cin>>amnts;
acc=b.Withdraw(account_no, amnts);
cout<<endl<<"Amount is Withdrawn from the account"<<endl;
cout<<acc;
break;
case 5:
cout<<"Enter Account Number:";
cin>>account_no;
b.CloseAccount(account_no);
cout<<endl<<"Account is Closed"<<endl;
cout<<acc;
case 6:
b.ShowAllAccounts();
break;
case 7: break;
default:
cout<<"\nInvalid Choice! Enter correct choice";
exit(0);
}
}while(option!=7);
return 0;
}
customer_Accounts::customer_Accounts(string fname,string lname,float customer_balance)
{
Other_customer_Accounts_no++;
customer_Accounts_No=Other_customer_Accounts_no;
customer_Fname=fname;
customer_Lname=lname;
this->customer_balance=customer_balance;
}

void customer_Accounts::Deposit(float amt)
{
customer_balance+=amt;
}
void customer_Accounts::Withdraw(float amt)
{
if(customer_balance-amt<MinBalance)
throw Insufficient_Funds();
customer_balance-=amt;
}
void customer_Accounts::set_Previous_customer_Accounts_no(long customer_Accounts_No)
{
Other_customer_Accounts_no=customer_Accounts_No;
}
long customer_Accounts::get_Previous_customer_Accounts_no()
{
return Other_customer_Accounts_no;
}
ofstream & operator<<(ofstream &ofs,customer_Accounts &acc)
{
ofs<<acc.customer_Accounts_No<<endl;
ofs<<acc.customer_Fname<<endl;
ofs<<acc.customer_Lname<<endl;
ofs<<acc.customer_balance<<endl;
return ofs;
}
ifstream & operator>>(ifstream &ifs,customer_Accounts &acc)
{
ifs>>acc.customer_Accounts_No;
ifs>>acc.customer_Fname;
ifs>>acc.customer_Lname;
ifs>>acc.customer_balance;
return ifs;
}
ostream & operator<<(ostream &os,customer_Accounts &acc)
{
os<<"First Name:"<<acc.getFName()<<endl;
os<<"Last Name:"<<acc.getLName()<<endl;
os<<"Account Number:"<<acc.getAccNo()<<endl;
os<<"Balance:"<<acc.getBlnce()<<endl;
return os;
}

Bank::Bank()
{
customer_Accounts acnt;
ifstream infile;
infile.open("Bank.data");
if(!infile)
{
 cout<<"Error in Opening! File Not Found!!"<<endl;
return;
}
while(!infile.eof())
{
infile>>acnt;
accounts_cl.insert(pair<long,customer_Accounts>(acnt.getAccNo(),acnt));
}
customer_Accounts::set_Previous_customer_Accounts_no(acnt.getAccNo());
infile.close();
}
customer_Accounts Bank::Cl_Open_Account(string fname,string lname,float balance)
{
ofstream outfile;
customer_Accounts acnt(fname,lname,balance);
accounts_cl.insert(pair<long,customer_Accounts>(acnt.getAccNo(),acnt));
outfile.open("Bank.data", ios::trunc);
map<long,customer_Accounts>::iterator itr;
for(itr=accounts_cl.begin();itr!=accounts_cl.end();itr++)
{
outfile<<itr->second;
}
outfile.close();
return acnt;
}
customer_Accounts Bank::Cl_Balance_Enquiry(long customer_Accounts_No)
{
map<long,customer_Accounts>::iterator itr=accounts_cl.find(customer_Accounts_No);
return itr->second;
}
customer_Accounts Bank::Deposit(long customer_Accounts_No,float amt)
{
map<long,customer_Accounts>::iterator itr=accounts_cl.find(customer_Accounts_No);
itr->second.Deposit(amt);
return itr->second;
}
customer_Accounts Bank::Withdraw(long customer_Accounts_No,float amt)
{
map<long,customer_Accounts>::iterator itr=accounts_cl.find(customer_Accounts_No);
itr->second.Withdraw(amt);
return itr->second;
}

void Bank::CloseAccount(long customer_Accounts_No)
{
map<long,customer_Accounts>::iterator itr=accounts_cl.find(customer_Accounts_No);
cout<<"Account Deleted"<<itr->second;
accounts_cl.erase(customer_Accounts_No);
}

void Bank::ShowAllAccounts()
{
map<long,customer_Accounts>::iterator itr;
for(itr=accounts_cl.begin();itr!=accounts_cl.end();itr++)
{
cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
}
}

Bank::~Bank()
{
ofstream outfile;
outfile.open("Bank.data", ios::trunc);
map<long,customer_Accounts>::iterator itr;
for(itr=accounts_cl.begin();itr!=accounts_cl.end();itr++)
{
outfile<<itr->second;
}
outfile.close();
}