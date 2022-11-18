/*******************************************************************
                            HEADER FILE USED
*********************************************************************/

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;


/*******************************************************************
                          CLASS USED IN PROJECT
********************************************************************/

class account
{
            int accountNumber;
            char accountName[50];
            int deposit;
            char accountType;
    public:
            void create_account();      //function to get data from user
            void show_account() const;  //function to show data on screen
            void modify();              //function to add new data
            void dep(int);              //function to accept amount and add to balance amount
            void draw(int);             //function to accept amount and subtract from balance amount
            void report() const;        //function to show data in tabular format
            int retaccountNumber() const; // function to return account number
            int retdeposit() const;     //function to return balance amount
            char retaccountType() const;       //function to return type of account

}; //end of class definition

void account::create_account()
{
            cout << "\n Enter The account Number :";
            cin >> accountNumber;
            cout << "\n\n Enter The name of the Account Holder :";
            cin >> accountName;
            cin.ignore();
            cin.getline(accountName,50);
            cout <<"\n Enter type of Account (Current/Savings) :";
            cin >> accountType;
            accountType = toupper(accountType); //converts a given character to upper case
            cout <<"\n Enter the initial amount(>=500 for savings and >=1000 for current) :";
            cin >> deposit;
            cout <<"\n\n\n Account Created successfully...";
}

void account::show_account() const
{
            cout <<"\n Account Number : " << accountNumber;
            cout <<"\n Account Holder Name : " << accountName;
            cout <<"\n Type of Account : " << accountType;
            cout <<"\n Balance Amount : " << deposit;
}

void account::modify()
{
            cout <<"\n Account Number : " <<accountNumber;
            cout <<"\n Modify Account Holder Name : ";
            cin.ignore();
            cin.getline(accountName,50);
            cout <<"\n Modify type of Account : ";
            cin >> accountType;
            accountType = toupper(accountType);
            cout <<"\n Modify Balance amount : ";
            cin >> deposit;    
}

void account::dep(int x)
{
    deposit += x;
}

void account::draw(int x)
{
    deposit -= x;
}

void account::report() const
{
    cout << accountNumber << setw(8) <<" " << accountName << setw(15) <<" " << accountType << setw(8) << deposit << endl;
}

int account::retaccountNumber() const
{
    return accountNumber;
}

int account::retdeposit() const
{
    return deposit;
}

char account::retaccountType() const
{
    return accountType;
}



/***************************************************************************************
 *                  FUNCTION DECLARATIOM
 **************************************************************************************/

void write_account();           //function to write record in binary file
void display_details(int);      //function to display account details given by user
void modify_account(int);       //function to modify record of file
void delete_account(int);       //function to delete record of file
void display_all();             //function to display all account details
void deposit_withdraw(int, int); //function to deposit or withdraw amount for a given account
void intro();                   //introductory screen function


/***************************************************************************************
 *                      THE MAIN FUNCTION OF THE PROGRAM
 *************************************************************************************/

int main()
{
            char ch;
            int num;
            intro();
            do
            {
                        system("cls");
                        cout <<"\n\n\n\t MAIN MENU";
                        cout <<"\n\n\t 01.  NEW ACCOUNT";
                        cout <<"\n\n\t 02.  DEPOSIT AMOUNT";
                        cout <<"\n\n\t 03.  WITHDRAW AMOUNT";
                        cout <<"\n\n\t 04.  BALANCE ENQUIRY";
                        cout <<"\n\n\t 05.  ALL ACCOUNT HOLDER LIST";
                        cout <<"\n\n\t 06.  CLOSE AN ACCOUNT";
                        cout <<"\n\n\t 07.  MODIFY AN ACCOUNT";
                        cout <<"\n\n\t 08.  EXIT";
                        cout <<"\n\n\t Select Your Option(1-8) ";
                        cin >> ch;
                        system("cls");
                        switch(ch)
                        {
                            case '1' :
                                    write_account();
                                    break;
                            case '2' :
                                    cout << "\n\n\t Enter the Account Number : ";
                                    cin >> num;
                                    deposit_withdraw(num, 1);
                                    break;
                            case '3' :
                                    cout << "\n\n\t Enter the Account Number : ";
                                    cin >> num;
                                    deposit_withdraw(num, 2);
                                    break;
                            case '4' :
                                    cout << "\n\n\t Enter the Account Number : ";
                                    cin >> num;
                                    display_details(num);
                                    break;
                            case '5' :
                                    display_all();
                                    break;
                            case '6' :
                                    cout << "\n\n\t Enter the Account Number : ";
                                    cin >> num;
                                    delete_account(num);
                                    break;
                            case '7' :
                                    cout << "\n\n\t Enter the Account Number : ";
                                    cin >> num;
                                    modify_account(num);
                                    break;
                            case '8' :
                                    cout << "\n\n\t Thanks for using Bank Management System";
                                    break;
                            default : cout << "\n\n\n Please select a number between 1 and 8.";
                        }
                        cin.ignore();
                        cin.get();

            }
            while(ch != '8');
            return 0;
}



/********************************************************************
 *              FUNCTION TO WRITE IN FILE
 *******************************************************************/

void write_account()
{
            account ac;
            ofstream outFile;
            outFile.open("account.dat",ios::binary|ios::app);
            ac.create_account();
            outFile.write(reinterpret_cast <char *> (&ac), sizeof(account));
            outFile.close();
}


/*************************************************************************
 *              FUNCTION TO READ SPECIFIC RECORD FROM FILE
 ************************************************************************/

void display_details(int n)
{
            account ac;
            bool flag = false;
            ifstream inFile;
            inFile.open("account.dat",ios::binary);
            if(!inFile)
            {
                    cout << "File could not be opened!! Press any key.....";
                    return;
            } 
            cout <<"\n BALANCE DETAILS\n";

            while(inFile.read(reinterpret_cast <char *> (&ac), sizeof(account)))
            {
                    if(ac.retaccountNumber() == n)
                    {
                                ac.show_account();
                                flag = true;
                    }
            }
            inFile.close();
            if(flag == false)
                    cout <<"\n\n Account Number does not exist";
}


/*******************************************************************************
 *              FUNCTION TO MODIFY RECORD OF FILE
 ***************************************************************************/

void modify_account(int n)
{
            bool found = false;
            account ac;
            fstream File;
            File.open("account.dat", ios::binary|ios::in|ios::out);
            if(!File)
            {
                        cout <<"File could not be open !!! Press any key to continue........";
                        return;
            }
            while(!File.eof() && found == false)
            {
                        File.read(reinterpret_cast <char *> (&ac), sizeof(account));
                        if(ac.retaccountNumber() == n)
                        {
                                ac.show_account();
                                cout <<"\n\n Enter The new details of Account \n";
                                ac.modify();
                                int pos = (-1)*static_cast<int>(sizeof(account));
                                File.seekp(pos,ios::cur);
                                File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                                cout <<"\n\n\t Record Updated";
                                found = true;
                        }
            }
            File.close();
            if(found == false)
                    cout <<"\n\n Record not found ";
}

/***********************************************************************
 *              FUNCTION TO DELETE RECORD OF FILE
 ***********************************************************************************/

void delete_account(int n)
{
                account ac;
                ifstream inFile;
                ofstream outFile;
                inFile.open("account.dat", ios::binary);
                if(!inFile)
                {
                            cout <<"File could not be opened!!! Press any key to continue............";
                            return;
                }
                outFile.open("Temp.dat",ios::binary);
                inFile.seekg(0,ios::beg);
                while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
                {
                            if(ac.retaccountNumber()!= n)
                            {
                                outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
                            }
                }
                inFile.close();
                outFile.close();
                remove("account.dat");
                rename("Temp.dat", "account.dat");
                cout <<"\n\n\t Record Deleted ...";

}

/**************************************************************************
 *      FUNCTION TO DISPLAY ALL ACCOUNT DEPOSIT LIST
 **************************************************************************/

void display_all()
{
                account ac;
                ifstream inFile;
                inFile.open("account.dat", ios::binary);
                if(!inFile)
                {
                            cout <<"File could not be open !!! Press any key ........";
                            return;
                }
                cout <<"\n\n\t\t ACCOUNT HOLDER LIST\n\n";
                cout <<"===================================================================\n";
                cout <<"A/c no.         NAME            Type         Balance\n";
                cout <<"===================================================================\n";
                while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
                {
                            ac.report();
                }
                inFile.close();
}

/*********************************************************************************
 *              FUNCTION TO DEPOSIT AND WITHDRAW AMMOUNTS
 ********************************************************************************/

void deposit_withdraw(int n, int option)
{
            int amount;
            bool found = false;
            account ac;
            fstream File;
            File.open("account.dat", ios::binary|ios::in|ios::out);
            if(!File)
            {
                        cout <<"File could not be opened !!! Press any key......";
                        return;
            }
            while(!File.eof() && found == false)
            {
                File.read(reinterpret_cast<char *> (&ac), sizeof(account));
                if(ac.retaccountNumber() == n)
                {
                            ac.show_account();
                            if(option == 1)
                            {
                                        cout <<"\n\n\t TO DEPOSIT AMMOUNT ";
                                        cout <<"\n\n Enter amount to be deposited";
                                        cin >> amount;
                                        ac.dep(amount);
                            }
                            if(option == 2)
                            {
                                        cout <<"\n\n\t TO WITHDRAW AMOUNT ";
                                        cout <<"\n\n Enter amount to be withdrawn";
                                        cin >> amount;
                                        int bal = ac.retdeposit() - amount;
                                        if((bal < 500 && ac.retaccountType() == 'S') || (bal < 1000 && ac.retaccountType() == 'C'))
                                                        cout <<"Insufficient funds";
                                        else
                                        {
                                                        ac.draw(amount);
                                        }
                            }
                            int pos = (-1)*static_cast<int>(sizeof(ac));
                            File.seekp(pos,ios::cur);
                            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                            cout <<"\n\n\t Record Updated";
                            found = true;         
                }
            }
            File.close();
            if(found == false);
                    cout <<"\n\n Record not Found";
}


/*************************************************************************************************
 *                          INTRODUCTORY FUNCTION PART
 *********************************************************************************************************/


void intro()
{
                cout <<"\n\n\t   BANK";
                cout <<"\n\t MANAGEMENT";
                cout <<"\n\t   SYSTEM";
                cout <<"\n\n\n MADE BY  :   BABALOLA FEMI";
                cout <<"\n SCHOOL   :   UNIVERSITY OF LAGOS";
                cin.get();
}

/*************************************************************************************
 *                          END OF PROJECT
 * **********************************************************************************/