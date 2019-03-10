//                   HEADER FILE USED IN PROJECT



#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<stdlib.h>

//                   CLASS USED IN PROJECT


class account
{
	int acno;
	char name[50];
	int deposit;
	char type[10];
   int pin;
public:
	void create_account();	//function to get data from user
   int authen(int);        //function to authenticate user
   void dtype();				//function to dtermine type of account
	void show_account();		//function to show data on screen
	void modify();   			//function to get new data from user
	void dep(int);				//function to accept amount and add to balance amount
	void draw(int);			//function to accept amount and subtract from balance amount
	void report();				//function to show data in tabular format
	int retacno();				//function to return account number
   char* retname();  		//function to return account number
	int retdeposit();			//function to return balance amount
	char* rettype();			//function to return type of account
};         						//class ends here

void account::create_account()
{
	cout<<"\n\n\n\n\t\tEnter The account No.";
	cin>>acno;
	cout<<"\n\tEnter The Name of The account Holder : ";
	gets(name);
   cout<<"\n\tEnter Your PIN ";
   cin>>pin;
	cout<<"\n\tEnter Type of The account (C/S) : ";
	cin>>type;
   dtype();
   A:
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
   if(strcmp(type,"SAVINGS")==0)
   {	if(deposit<500)
     	{
        	cout<<"\n\t\t\t\t INSUFFICIENT AMOUNT ";
         goto A;
      }
   }
   else
   { 	if(deposit<1000)
     	{
        	cout<<"\n\t\t\t\t INSUFFICIENT AMOUNT ";
         goto A;
      }
   }
	cout<<"\n\n\t\t\t\tAccount Created..";
}

int account::authen(int pw)
{
   if(pw==pin)
   	return(1);
   else
      return (0);
}

void account::dtype()
{
	if(strcmpi(type,"s")==0)
   	strcpy(type,"SAVINGS");
   else
		strcpy(type,"CURRENT");
}

void account::show_account()
{
	cout<<"\n\n\n\n\t\t\tAccount No. : "<<acno;
	cout<<"\n\t\t\tAccount Holder Name : "<<name;
	cout<<"\n\t\t\tType of Account : "<<type;
	cout<<"\n\t\t\tBalance amount : "<<deposit;
}


void account::modify()
{
   char ch='n';
	cout<<"\n Account No."<<acno;
	cout<<"\n\nDo you want to change the NAME of The account Holder(y/n) ? ";
   cin>>ch;
   if(ch=='y'||ch=='Y')
   {
   cout<<"\n Enter The New Name Of Account Holder : ";
	gets(name);
   }
	cout<<"\n\nDo you want to change the TYPE of The account (y/n) ? ";
   cin>>ch;
   if(ch=='y'||ch=='Y')
   {
   cout<<"\n Enter The New TYPE Of Account (CURRENT(c)/SAVINGS(s) : ";
	cin>>type;
   dtype();
   }
   cout<<"\n\nDo you want to change the PIN (y/n) ? ";
   cin>>ch;
   if(ch=='y'||ch=='Y')
   {
   cout<<"\n Enter The New PIN : ";
	cin>>pin;
   }
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report()
{
	cout<<setw(12)<<acno<<setw(8)<<" | "<<setw(16)<<name<<setw(2)<<" | "<<setw(11)<<type<<setw(7)<<" | "<<setw(13)<<deposit<<endl;
}

int account::retacno()
{
	return acno;
}

char* account::retname()
{
	return name;
}

int account::retdeposit()
{
	return deposit;
}

char* account::rettype()
{
	return type;
}

//    	Variable declaration


int ano;                      //To Store account no entered by User
int upin;                     //To store Customer PIN for authentication
int adpin=1111;               //The Default Adminisatrator PIN
int pos1;                     //To Store Location of Found record of customer
char cname[50];               //To Store Customer Name (temporary)
account ac;



//    	function declaration

void customer1();					//function to Authenticate Customer
int customer2();					//function to Show Customer Menu
void administrator1();  		//function to Authenticate Administrator
int administrator2();   		//function to Show Administrator Menu
void write_account();			//function to write record in binary file
void display_sp();				//function to display account details given by user
void modify_account(int);		//function to modify record of file
void delete_account(int);		//function to delete record of file
void display_all();				//function to display all account details
void deposit_withdraw(int);	//function to desposit/withdraw amount for given account
void intro();						//introductory screen function
void error_msg();					//function to show error in opening file
void wrongpin();					//Function to show error message on wrong PIN;
void no_account();				//function to show error message on no account found;
void get_account();				//function to read ano and upin for authentication



//    	THE MAIN FUNCTION OF PROGRAM


int main()
{
	char ch;
   clrscr();
   intro();
   do
   {
     	clrscr();
      cout<<"\n\n\n";
      cout<<"\n\n\t\t\t WELCOME TO THE PROJECT BANK  ";
      cout<<"\n\t\t\t        ONLINE PORTAL     ";
      cout<<"\n\n\n\t\t\t\t  MAIN MENU";
		cout<<"\n\n\t\t01. CUSTOMER MENU";
		cout<<"\n\n\t\t02. ADMINISTRATOR MENU";
		cout<<"\n\n\t\t03. EXIT";
		cout<<"\n\n\t\t    SELECT YOUR OPTION  ";
      ch=getche();
      clrscr();
 		switch(ch)
		{
		case '1':
			customer1();
			break;
		case '2':
			administrator1();
			break;
		case '3':
         cout<<"\n\n\n\n\n\n\n\n";
			cout<<"\n\t\tTHANKS FOR USING OUR BANK MANAGEMENT SYSTEM";
         getch();
			exit(0);
		 default :cout<<"\a";
		}
   }while(ch!='3');
	return 0;
}


void customer1()
{
	int flag=0;
   ifstream inFile;
	inFile.open("account.dat",ios::binary|ios::in);
	if(!inFile)
	{
   	error_msg();
		return;
	}
   get_account();
	while(!inFile.eof())
	{
      pos1=inFile.tellg();
      inFile.read((char *) &ac, sizeof(account));
      if(ac.retacno()==ano)
		{

			if(ac.authen(upin))
            {
            flag=1;
            strcpy(cname,ac.retname());
         	customer2();
            break;
            }
         else
         {
            wrongpin();
         	return;
         }
		}
   }
	if(flag==0)
	{
   	no_account();
      return;
   }
}

int customer2()
{
	char ch2;
	clrscr();
	do
	{
		clrscr();
      cout<<"\n\n\n\n\t\t\t\t  Welcome "<<cname;
		cout<<"\n\n\n\t\t\t\t  CUSTOMER MENU";
		cout<<"\n\n\n\t\t\t01. DEPOSIT AMOUNT";
		cout<<"\n\n\t\t\t02. WITHDRAW AMOUNT";
		cout<<"\n\n\t\t\t03. BALANCE ENQUIRY";
		cout<<"\n\n\t\t\t04. LOG OUT";
      cout<<"\n\n\t\t\tSelect Your Option (1-4) ";
		ch2=getche();
      clrscr();
		switch(ch2)
		{
		case '1':
			deposit_withdraw(1);
			break;
		case '2':
			deposit_withdraw(2);
			break;
		case '3':
			display_sp();
			break;
		case '4':
			cout<<"\n\n\n\n\n\n\n\n\n\t\t YOU HAVE BEEN SUCCESSFULLY LOGGED OUT";
         getch();
         return 0;
		default :cout<<"\a";
		}
	}while(ch2!='4');
	return 0;
}

void administrator1()
{
	int apin;
   fstream inFile;
	inFile.open("account.dat",ios::binary|ios::app);
	if(!inFile)
	{
		error_msg();
		return;
	}
   cout<<"\n\n\n\n\n\n\n\n\n\t\t Enter Administrator Pin ";
   cin>>apin;
	if(apin==adpin)
         	administrator2();
         else
         {
         	wrongpin();
         	return;
         }
	return;

}

int administrator2()
{
	char ch2;
	clrscr();
	do
	{
		clrscr();
		cout<<"\n\n\n\n\n\t\t\t\t  ADMINISTRATOR MENU";
      cout<<"\n\n\n\t\t\t01. NEW ACCOUNT";
		cout<<"\n\n\t\t\t02. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t\t\t03. CLOSE AN ACCOUNT";
		cout<<"\n\n\t\t\t04. MODIFY AN ACCOUNT";
		cout<<"\n\n\t\t\t05. LOGOUT";
		cout<<"\n\n\t\t\tSelect Your Option (1-8) ";
		ch2=getche();
		clrscr();
		switch(ch2)
		{
		case '1':
			write_account();
			break;
		case '2':
			display_all();
			break;
		case '3':
      	clrscr();
			get_account();
         delete_account(ano);
			break;
		 case '4':
         clrscr();
			get_account();
			modify_account(ano);
			break;
		 case '5':
			cout<<"\n\n\n\n\n\n\n\n\n\t\t YOU HAVE BEEN SUCCESSFULLY LOGGED OUT";
         getch();
			break;
		 default :cout<<"\a";
		}
	}while(ch2!='5');
	return 0;
}



//    	function to write in file


void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(account));
	outFile.close();
   getch();
}


//    	function to read specific record from file


void display_sp()
{
	ifstream inFile;
	inFile.open("account.dat",ios::binary|ios::in);
	if(!inFile)
	{
		error_msg();
		return;
	}
	cout<<"\n\n\n\t\t\t\tBALANCE DETAILS\n";
	inFile.seekg(pos1,ios::beg);
	inFile.read((char *) &ac, sizeof(account));
	ac.show_account();
	inFile.close();
   getch();
}



//    	function to modify record of file


void modify_account(int n)
{
   clrscr();
   cout<<"\n\t\t\t\t MODIFY ACCOUNT ";
	int found=0;
   fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		error_msg();
		return;
	}
   while(!File.eof() && found==0)
   {
   File.read((char *) &ac, sizeof(account));
		if(ac.retacno()==n)
		{
         if(ac.authen(upin))
         {
         	ac.show_account();
				cout<<"\n\nEnter The New Details of account"<<endl;
				ac.modify();
				int pos=(-1)*sizeof(account);
				File.seekp(pos,ios::cur);
				File.write((char *) &ac, sizeof(account));
				cout<<"\n\n\t Record Updated";
            getch();
				found=1;
         }
         else
         {
         	wrongpin();
         	return;
         }

		}
	}
	File.close();
	if(found==0)
		no_account();
}


//    	function to delete record of file



void delete_account(int n)
{
	ifstream inFile;
	inFile.open("account.dat",ios::binary|ios::in);
	if(!inFile)
	{
		error_msg();
		return;
	}
	ofstream outFile;
   outFile.open("Temp.dat",ios::binary|ios::out);
	inFile.seekg(0,ios::beg);
   while(!inFile.eof())
   {
	inFile.read((char *) &ac, sizeof(account));
		if(ac.retacno()==n)
		{
         if(ac.authen(upin))
         {
         cout<<"\n Cash Withdrawed After Closing Account ="<<ac.retdeposit();
         cout<<"\n Account Closed ";
			continue;
         }
         else
         {
            wrongpin();
         	remove("Temp.dat");
            return;
         }
		}

      else
      	outFile.write((char *) &ac, sizeof(account));
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
   getch();
}


//    	function to display all accounts deposit list


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary|ios::in);
	if(!inFile)
	{
		error_msg();
		return;
	}
	cout<<"\n\n\t\t\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"===============================================================================\n";
	cout<<"      A/c no.     |      NAME        |      Type        |      Balance\n";
	cout<<"===============================================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
   getch();
}


//    	function to deposit and withdraw amounts


void deposit_withdraw(int option)
{
	int amt;
 	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		error_msg();
		return;
	}
	File.seekg(pos1,ios::beg);
	File.read((char*) &ac,sizeof(ac));
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\n\n\t\t\t\tTO DEPOSITE AMOUNT ";
				cout<<"\n\n\t\tEnter The amount to be deposited ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\n\t\t\t\tTO WITHDRAW AMOUNT ";
				cout<<"\n\n\t\tEnter The amount to be withdrawn ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
            if((bal<500 && strcmp(ac.rettype(),"SAVINGS")==0) || (bal<1000 && strcmp(ac.rettype(),"CURRENT")==0))
				cout<<"\n\t\t\tInsufficience balance";
				else
					ac.draw(amt);
			}
			File.seekp(pos1,ios::beg);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t\t\t\t Record Updated";
			File.close();
   getch();
}



//     Function To Show Error In File Opening


void error_msg()
{
		cout<<"\n\n\n\n\n\n\n\n";
		cout<<"\n\n\t\t File could not be opened !! Press any Key...";
      getch();
}



//     Function To Show Warning Wrong Password


void wrongpin()
{
            clrscr();
				cout<<"\n\n\n\n\n\n\n\n";
         	cout<<"\n\t\t\t\t Incorrect PIN ";
            cout<<"\n\t\t\tPress Any Key to Go To The Previous Menu ";
            getch();
}



//     Function To Show No Account No Exists


void no_account()
{
            clrscr();
				cout<<"\n\n\n\n\n\n\n\n";
         	cout<<"\n\t\t\t No Record Found !!! ";
            cout<<"\n\t\tPress Any Key to Go To The Previous Menu ";
            getch();
}

void get_account()
{
				cout<<"\n\n\n\n\t\t\t\t CUSTOMER LOGIN ";
            cout<<"\n\n\n\n\n\t\t\t Enter The Account Number ";
            cin>>ano;
            cout<<"\n\t\t\t\t Enter PIN ";
            cin>>upin;
}


//    	INTRODUCTION FUNCTION


void intro()
{
	cout<<"\n\n\n\n\t\t\t  BANK MANAGEMENT SYSTEM";
	cout<<"\n\n\n\t\t\t  ";
	cout<<"\n\n\n\t\t MADE BY : ARCHIT GOYAL        ";
	getch();
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************