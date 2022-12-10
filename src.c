//Library Functions/Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>
#define L 100

typedef struct node
{
    int id;
    char employeefirstname[50];
    char employeelastname[50];
    char gender[10];
    char type[15];
    char age[100];
    float salary;
    struct node *next;
}node;

node *hashtable[25];

//Prototypes
void welcomeScreen(void); //Welcome Screen Function gives a tech icon and an brief introduction of the company
int employeeVerify();     /*Function which allows the user to enter the correct credentials and
                          verifies it to log into the employee menu*/

int adminVerify();        /*Function which allows the user to enter the correct credentials and
                          verifies it to log into the employee menu*/
unsigned int hash(const char *word);
void optionOne(); //Employee Login,This functions calls the function employeeVerify function and the sub-employee menu
int optionTwo(); // Administrator Login,This functions calls the function adminVerify function and the sub-admin menu
int optionThree(); // Exit Program
int genMenu(); //displays the general menu option, allows the user to enter a numeric choice and return that value
void callOptions(void); /*This function calls the generalMenu function and based upon what value is returned from the genMenu,
                        a specific function is called*/
int employeeSalary(char typeofemployee[15]); //Calculating Employees Salary based upon their type of position
int subadminMenu(); //Sub Administrator Menu which entails viewing all employees in the company,adding an employee.
int subadminOptionone(); // This function allows the administrator to view all employee information
int subadminoptionTwo(); // The function allows the administrator to add an employee
float governmentTax(char type[10], float monthlyrevenue); //The function calculates the government Tax for the companies
int addCompany();//This function allows an employee to add a company
int companygeneralReport(); //This function displays all the current registered companies

int subemployeeMenu();
//Displays all the sub-employee options and allows the user to enter a numeric choice which is then returned
void searchCompany();  //This allows the employee to search for a company
void searchEmployee(); //This function allows the administrator to search for an employee

void callingSubadminMenu();
//This function calls a function in the sub-admin Menu based upon what value is returned from the subemployeeMenu

void callingsubemployeeMenu();
//This function calls a function in the sub-employee Menu based upon what value is returned from the subemployeeMenu
node *searchemployeebynumber(int id,node *head);
int totalnodes(node *head);
int middlenumber(node *head,int start,int totalnodes);
node *middlenode(node *head,int start,int totalnodes);
node *findnode(int num,node *head);

//File Pointers Declarations

FILE *fptr, *ptr;

typedef struct nodecompany
{
   char   nameofcompany[100];
   char     yearfounded[100];
   char     yearsregistered[100];
   char     numberofemploy[100];
   char    typeofcompany[10];
   float   monthlyrevenue;
   float   monthlyexpense;
   char    companyaddress[200];
   float yearlyrevenue;
   float yearlyexpenses;
   float GCT;
   struct nodecompany *next;
}nodecompany;
nodecompany *headcompany = NULL;
nodecompany *prevcompany = NULL;
void searchbyposition();
void secondaryswap(nodecompany *l, nodecompany *p)
{
    char tempnameofcompany[50];
    char tempyearfounded[100];
    char tempyearegistered[100];
    char temppnumberofemploy[100];
    char temptypeofcompany[50];
    char tempcompanyaddress[50];
    float tempyearlyrevenue;
    float tempyearlyexpenses;
    float tempyearlyGCT;
    if(toupper(l->nameofcompany[1]) < toupper(p->nameofcompany[1]))
    {
       strcpy(tempnameofcompany,l->nameofcompany);
                    strcpy(tempyearfounded,l->yearfounded);
                    strcpy(tempyearegistered,l->yearsregistered);
                    strcpy(temppnumberofemploy ,l->numberofemploy);
                    strcpy(temptypeofcompany,l->typeofcompany);
                    strcpy(tempcompanyaddress,l->companyaddress);
                    tempyearlyrevenue = l->yearlyrevenue;
                    tempyearlyexpenses = l->yearlyexpenses;
                    tempyearlyGCT = l->GCT;

                    strcpy(l->nameofcompany,p->nameofcompany);
                    strcpy(l->yearfounded,p->yearfounded);
                    strcpy(l->yearsregistered,p->yearsregistered);
                   strcpy(l->numberofemploy ,p->numberofemploy);
                    strcpy(l->typeofcompany,p->typeofcompany);
                    strcpy(l->companyaddress,p->companyaddress);
                    l->yearlyrevenue = p->yearlyrevenue;
                    l->yearlyexpenses = p->yearlyexpenses;
                    l->GCT = p->GCT;

                    strcpy(p->nameofcompany,tempnameofcompany);
                    strcpy(p->yearfounded ,tempyearfounded);
                    strcpy(p->yearsregistered ,tempyearegistered);
                    strcpy(p->numberofemploy,temppnumberofemploy);
                    strcpy(p->typeofcompany,temptypeofcompany);
                    strcpy(p->companyaddress,tempcompanyaddress);
                    p->yearlyrevenue = tempyearlyrevenue;
                    p->yearlyexpenses = tempyearlyexpenses;
                    p->GCT = tempyearlyGCT;

    }
}
//Preprocessors directives
#define _repeat do
#define _until(CONDITION) while (!(CONDITION))

//Global Variable
int countFilelines;


 void welcomeScreen(void)
    {
        printf("-------------------------YELLOW PAGE COMPANY-------------------------");


    printf("\n\n");

   printf("\n\t\t...........  .........   .........   .        .\n");
    printf("\t\t    .        .           .           .        .\n");
    printf("\t\t    .        .           .           .        .\n");
    printf("\t\t    .        .           .           .        .\n");
    printf("\t\t    .        .           .           .        .\n");
    printf("\t\t    .        .........   .           .        .\n");
    printf("\t\t    .        .           .           ..........\n");
    printf("\t\t    .        .           .           .        .\n");
    printf("\t\t    .        .           .           .        .\n");
    printf("\t\t    .        .           .           .        .\n");
    printf("\t\t    .        .........   .........   .        .\n");

    printf("\n\n");

    printf("-------------------------YELLOW PAGE COMPANY-------------------------\n\n");

    printf("Welcome to Yellow Page Company.Chief Operating Officer: Matthew O.Manning\n");
    printf("Brief Introduction: The Yellow Page company is � governmental agency located at 12 King Street,St.Andrew.The agency was founded in 1960 by the Ministry of Industry,Investment and Commerce.The agency contact number is 1876-326-4591.The agency has a staff of 100 employees ranging from junior level to senior management.This agency keeps records of approximately 500 registered businesses in jamaica both profit and non-profit organizations.\n\n\n");
    //Brief Introduction of Yellow Page Company
    printf("CLICK ENTER TO CONTINUE\n"); //Prompting the user to click enter on keyboard to continue
    char enter = 0;
    while (enter != '\r' && enter != '\n')
    {
          enter = getchar();
     }
  }

int employeeVerify()
{

    printf("\n\n\t\t\t\tEmployee Login\n");
    //Declaration of variable names for username and password
    char user[15]; //Username
    char pass[15]; //Password

    int count = 0;

    typedef struct employeeLogin
    {

        char *username; //declaring username
        char *password; //declaring password


    } employeeLog;     //User defined data type

    employeeLog employee;

    employee.username = "employee@"; //Employee Username
    employee.password = "PAsword@1"; //Employee Password

    printf("\nUsername: "); //Prompting the user for their username
    scanf(" %[^\n]s", user);       //Storing it in the variable name user

    printf("\nPassword:  "); //Prompting the user for their password
    scanf(" %[^\n]s", pass);        //Storing it in the variable name password



    if (strcmp(employee.username, user) == 0 && strcmp(employee.password, pass) == 0)
        //Checking whether the user entered the correct username and password
    {

        return 0;

    }

    else if (strcmp(employee.username, user) != 0 && strcmp(employee.password, pass) != 0)
        //Checking whether the user entered the incorrect username and password
    {

        printf("Error : Invalid username and password\n");
        do          //Re-prompting the user until they have entered correct username and password
        {

            printf("Username: ");
            scanf(" %[^\n]s", user);

            printf("Password: ");
            scanf(" %[^\n]s", pass);

            if (strcmp(employee.username, user) == 0 && strcmp(employee.password, pass) != 0)
            //checking if the user has entered the correct username but incorrect password
            {
                printf("Error : Invalid password\n");
                do                        //Re-prompting the user until they have entered correct password.
                {

                    printf("Password: ");
                    scanf(" %[^\n]s", pass);
                    count++;
                    if (count == 3 &&  strcmp(employee.password, pass) != 0)
                    {
                        printf("%c[%dmAttempt 4: You have no more attempts.", 0x1B, 32);
                        system("color 47");
                        printf("\a");
                        exit(EXIT_FAILURE);
                    }
                }
                while (strcmp(employee.password, pass) != 0);
                //return employeeVerify("Error: Incorrect password");

            }

            else if (strcmp(employee.password, pass) == 0 && strcmp(employee.username, user) != 0)
            //if the user has entered the correct password but incorrect username
            {

                printf("Error : Invalid username\n");
                do                                 //Re-prompting the user until they have entered correct username
                {
                    printf("Username: ");
                    scanf(" %[^\n]s", user);
                    count++;
                    if (count == 3 && strcmp(employee.username, user) != 0)
                    {

                        printf("%c[%dmAttempt 4: You have no more attempts.", 0x1B, 32);
                        /*notifying the user that he/she has no more choices*/

                        system("color 47"); //changing the color of the screen
                        printf("\a");       //making a sound
                        exit(EXIT_FAILURE); //ending the program

                    }

                }
                while (strcmp(employee.username, user) != 0); //repeats until the user has entered a correct username
            }


            count++;
            if (count == 3 && strcmp(employee.username, user) != 0 && strcmp(employee.password, pass) != 0)

            {
                printf("%c[%dmAttempt 4: You have no more attempts.", 0x1B, 32);
                /*nofitying the user they have not more attempts*/
                system("color 47"); //changing the color of the screen
                printf("\a");       //making a sound

                exit(EXIT_FAILURE); //ending the program
            }

        }
        while (strcmp(employee.username, user) != 0 && strcmp(employee.password, pass) != 0);


        return -1;


    }

    else if (strcmp(employee.username, user) == 0 && strcmp(employee.password, pass) != 0)
    //if the user has entered the correct username but incorrect password
    {
        printf("Error : Invalid password\n");
        do                        //Re-prompting the user until they have entered correct password.
        {

            printf("Password: ");
            scanf(" %[^\n]s", pass);
            count++;
            if (count == 3 &&  strcmp(employee.password, pass) != 0)
            {
                printf("%c[%dmAttempt 4: You have no more attempts.", 0x1B, 32);
                /*notifying the user they have no more attempts*/
                system("color 47"); //changing the color of the screen
                printf("\a");       //making a sound
                exit(EXIT_FAILURE); //ending the program
            }
        }
        while (strcmp(employee.password, pass) != 0); //repeats until the password is correct
        return -2;


    }

    else if (strcmp(employee.username, user) != 0 && strcmp(employee.password, pass) == 0)
    {
        //if the username is incorrect but they password is correct

        printf("Error : Invalid username\n");
        do                                 //Re-prompting the user until they have entered correct username
        {
            printf("Username: ");
            scanf(" %[^\n]s", user);
            count++;
            if (count == 3 && strcmp(employee.username, user) != 0)
                //if the user is on attempt three and still haven't entered the correct password
            {

                printf("%c[%dmAttempt 4: You have no more attempts.", 0x1B, 32);
                //Notifying the user that they have no more attempts

                system("color 47"); //Changing the color of the screen to red
                printf("\a");
                exit(EXIT_FAILURE); //Ending the program

            }

        }
        while (strcmp(employee.username, user) != 0); //repeats until the username is correct
        return -3;

    }



    return 1;



}
   int adminVerify()
{
    printf("\n\n\t\t\t\tAdministration Login\n");

    char admin[15]; //declaring a vAariable that will storing the admin username
    char passkey[15]; //declaring a variable that will eb storing the admin password
    int count = 0;

    typedef struct administrativeLogin
    {

        char *administrator;
        char *password;


    } adminLog; //Data Type

    adminLog employee;

    employee.administrator = "admin1"; //Administrator Name
    employee.password      = "passkey1"; //Administrator Password

    printf("\nAdministrator name: "); //Prompting the user for the administrator name
    scanf(" %[^\n]s", admin);               // Storing the input in admin

    printf("\nPassword:  ");//Prompting the user for password
    scanf(" %[^\n]s", passkey);   //Storing the input in passkey



    if (strcmp(employee.administrator, admin) == 0 && strcmp(employee.password, passkey) == 0)
    {

        return 0;

    }

    else if (strcmp(employee.administrator, admin) != 0 && strcmp(employee.password, passkey) != 0)
    //if the admin name and passkeyis  incorrect
    {

        printf("Error : Incorrect administrator name and password\n");
        do
            //Re-prompting the user until they have entered correct password and username
        {

            printf("Administrator Name: ");
            scanf(" %[^\n]s", admin);

            printf("Password: ");
            scanf(" %[^\n]s", passkey);

            if (strcmp(employee.administrator, admin) == 0 && strcmp(employee.password, passkey) != 0)
            //if the user admin name is correct but passkey is incorrect
            {

                printf("Error : Incorrect password\n");
                do                        //Re-prompting the user until they have entered correct password.

                {

                    printf("Password: ");
                    scanf(" %[^\n]s", passkey);
                    count++;
                    if (count == 3 &&  strcmp(employee.password, passkey) != 0)
                    //if the user is on their third attempt and still haven't entered a valid passkey
                    {
                        printf("%c[%dmAttempt 4: You have no more attempts.", 0x1B, 32);
                        system("color 47"); //changes the screen to red
                        printf("\a"); //makes sound
                        exit(EXIT_FAILURE); //exits the program
                    }
                }

                while (strcmp(employee.password, passkey) != 0); //repeats until the passkey is valid

            }

            if (strcmp(employee.password, passkey) == 0 && strcmp(employee.administrator, admin) != 0)
            //if the user has enterd a valid passkey but invalid admin name
            {

                printf("Error : Incorrect administrator name\n");
                do                                 //Re-prompting the  admin  until they have entered correct username

                {
                    printf("Administrator Name: ");
                    scanf(" %[^\n]s", admin);
                    count++;
                    if (count == 3 && strcmp(employee.administrator, admin) != 0)
                    //if the user is on their thirs chance and  still doesn't have the correct admin name
                    {

                        printf("%c[%dmAttempt 4: You have no more attempts.", 0x1B, 32);
                        //notifying the user they have no more attempts

                        system("color 47"); //changes the screen to red
                        printf("\a");       //making a sound
                        exit(EXIT_FAILURE); //exiting the program

                    }

                }
                while (strcmp(employee.administrator, admin) != 0);
            }



            count++;

            if (count == 3 && strcmp(employee.administrator, admin) != 0 && strcmp(employee.password, passkey) != 0)
            //if the user is on their third attempt and still hasn't entered a valid admin name and password
            {
                printf("%c[%dmAttempt 4: You have no more attempts.", 0x1B, 32); //notifying the user they no more attempts
                printf("The program will now end");
                system("color 47"); //changes the screen to red
                printf("\a");       //males a sound

                exit(EXIT_FAILURE); //exit the program
            }

        }
        while (strcmp(employee.administrator, admin) != 0 && strcmp(employee.password, passkey) != 0);


        return 2;


    }

    else if (strcmp(employee.administrator, admin) == 0 && strcmp(employee.password, passkey) != 0)
    {

        printf("Error : Incorrect password\n");
        do                        //Re-prompting the user until they have entered correct password.

        {

            printf("Password: ");
            scanf(" %[^\n]s", passkey);
            count++;
            if (count == 3 &&  strcmp(employee.password, passkey) != 0)
            {
                printf("%c[%dmAttempt 4: You have no more attempts.", 0x1B, 32);
                //Notifying the user they have no more attempts
                system("color 47"); //changes the color of the screen to red
                printf("\a");       //makes a sound
                exit(EXIT_FAILURE); //exits the program
            }
        }

        while (strcmp(employee.password, passkey) != 0); //repeats until the password is correct
        return 3;


    }

    else if (strcmp(employee.administrator, admin) != 0 && strcmp(employee.password, passkey) == 0)
    //if the admin name is incorrect but the password is correct
    {

        printf("Error : Incorrect administrator name\n");
        do                                 //Re-prompting the  admin  until they have entered correct username

        {
            printf("Administrator Name: ");
            scanf(" %[^\n]s", admin);
            count++;
            if (count == 3 && strcmp(employee.administrator, admin) != 0)
                //if the user is on their third chance and they still haven't enter the correct admin name
            {

                printf("%c[%dmAttempt 4: You have no more attempts.", 0x1B, 32);
                //notifying the user they have no more attempts
                system("color 47"); //changes the color to red
                printf("\a");       //making a sound
                exit(EXIT_FAILURE); //exiting the program

            }

        }
        while (strcmp(employee.administrator, admin) != 0); //repeats until the admin name is correct

        return 4;

    }

    return 0;
}



   void optionOne()
{

    int employeVer = employeeVerify(); //calling employee verify
    /* Based on the return value from employee verify an error message is notified*/

    if (employeVer ==  0)
    {
        printf("Sucessfully logged in Empolyee Menu");
    }

    else if (employeVer ==  -1)
    {

        printf("You have now sucessfully entered the correct username and password");

    }

    else if (employeVer ==  -2)

    {

        printf("You have now sucessfully entered the correct password");

    }
    else if (employeVer == -3)

    {

        printf("You have now sucessfully entered the correct username");

    }
    sleep(5); //halting the execution of the program
    system("cls"); //clearing the screen
    callingsubemployeeMenu(); //calling the sub -employee menu

}

void callingsubemployeeMenu()
{

    int employemenu = subemployeeMenu(); //calling the sub employee menu and storing the return value in employeemenu

    switch (employemenu) //based on what value is returned, an option which is a function from the general menu is called
    {


        case 1:
            system("cls");           //clearing the screen
            companygeneralReport();  // Viewing all companies that are currently registered information
            break;

        case 2:
            system("cls");           //clearing the screen
            addCompany();           //Adding a company
            break;

        case 3:
            system("cls");           //clearing the screen
            searchCompany();        //Searching for a registered company
            break;

        case 4:
            system("cls");           //clearing the screen
            callOptions();          //Returning to General Main Menu
    }


}

int subemployeeMenu()
{

    int count = 0;
    /*Displaying the employee menu options */
    printf("\t\tEmployee Menu Options\n\n");

    printf("1 -- View Company's General Report\n");

    printf("2 -- Add a Company\n");

    printf("3 -- Search for an Company\n");

    printf("4 -- Return to General Main Menu\n");

    printf("\nPlease enter a number which corresponds with your option\n");


    int x;
    char chor[100];
    printf("Choice: ");
    scanf(" %[^\n]s", chor); //storing the user input in choice as a string
    x = atoi(chor);         //converting the user input to an integer

    switch (x)   //returning a value based upon what value is entered
    {
        case 1:
            return 1;
            break;

        case 2:
            return 2;
            break;

        case 3:
            return 3;
            break;

        case 4:
            return 4;

    }



    printf("\n\nPlease select option 1 , 2 , 3 , 4\n");
    printf("You have 3 chances before the application ends\n");
    sleep(5); //halting execution for 5 seconds

    for (;;)
    {

        if (count >= 1)
        {
            printf("INVALID CHOICE!\n");
        }

        if (x < 1 || x > 4) //if the user hasn't entered a valid choice
        {
            printf("Choice: ");
            scanf(" %[^\n]s", chor); //storing the user input in choice as a string
            x = atoi(chor);          //converting the user input to an integer
            count++;


            switch (x)              //returning a value based upon what values is entered
            {
                case 1:
                    return 1;

                case 2:
                    return 2;

                case 3:
                    return 3;

                case 4:
                    return 4;
            }

            if (count == 2) //when the user has exceeded thier attempts
            {
                printf("You have exceeded your chances\n");
                sleep(4); //halting the excuetion for four seconds
                system("cls"); //clearing the screen
                printf("The program will end in 10 seconds");
                system("color 47"); //chaning the color to red
                printf("\a");
                sleep(10);  //halting excuetion for 10 seconds
                exit(1);    //exiting the program
            }
        }
    }

    return 0;
}

int optionTwo()
{

    int adminVer = adminVerify(); //calling the function adminverify and storing the return value in adminVer
    /*based upon the return value of adminverify a message is outputted */
    if (adminVer ==  0)
    {

        printf("Sucessfully logged in Administrator Menu\n");
        sleep(3);
        printf("Please wait...........\n");


    }
    else if (adminVer ==  2)

    {

        printf("You have now sucessfully entered the correct administrator name and password\n");
        printf("Logging in the Administrator Menu\n");
        sleep(3);
        printf("Please wait...........\n");

    }

    else if (adminVer ==  3)

    {

        printf("You have now sucessfully entered the correct password\n");
        printf("Logging in the Administrator Menu\n");
        sleep(3);
        printf("Please wait...........\n");

    }

    else if (adminVer == 4)

    {

        printf("You have now sucessfully entered the correct administrator name\n");
        printf("Logging in the Administrator Menu\n");
        sleep(3);
        printf("Please wait...........\n");

    }

    sleep(5); //halting excuetion for 5 seconds
    system("cls"); //clearing the screen
    callingSubadminMenu(); //calling the sub admin menu function
    return 0;

}


void callingSubadminMenu()
{


    int x = subadminMenu();  //calling the sub admin menu and storing the return value in x
    sleep(3);  //halting the program execution for 3 seconds
    printf("Please wait.......");
    sleep(5);  //halting the program execution for 5 seconds
    system("cls"); //clearing the screen


    switch (x)
    {


        case 1:
            subadminOptionone();  // Viewing Employees General Report
            break;

        case 2:
            subadminoptionTwo(); // Adding an Employee
            break;

        case 3:
            searchEmployee();//Searching for an employee
            break;

        case 4:
            searchbyposition();//Returning to Main Screen
            break;

        case 5:
            callOptions();//Returning to Main Screen

    }



}

int subadminMenu()
{


    int count = 0;


    printf("\t\tAdministrative Menu Options\n\n");

    printf("1 -- View Employees General Report\n");

    printf("2 -- Add an Employee\n");

    printf("3 -- Searching for an employee\n");

     printf("4 -- Searching for an employee by Position\n");


    printf("5 -- Return to General Main Menu\n");

    printf("\nPlease enter a number which corresponds with your option\n");


    int x;
    char chor[100];
    printf("Choice: ");
    scanf(" %[^\n]s", chor); //stroing the user input as a string
    x = atoi(chor); //Converting the user's input into an integer

    switch (x)
    {
        case 1:

            return 1;
            break;

        case 2:

            return 2;
            break;

        case 3:

            return 3;
            break;

        case 4:
            return 4;

        case 5:
            return 5;

    }



    printf("\n\nPlease select option 1 , 2 , 3 , 4\n");
    printf("You have 3 chances before the application ends\n");

    for (;;)
    {
        if (x < 1 || x > 4)
        {
            if (count >= 1) //if the user has entered an invalid choice
            {
                printf("INVALID CHOICE!\n");
            }

            printf("Choice: ");
            scanf(" %[^\n]s", chor); //stroing the user input in chor as a string
            x = atoi(chor);    //converting the user input to integer
            count++; //increment count


            switch (x)
            {
                case 1:
                    return 1;

                case 2:
                    return 2;

                case 3:
                    return 3;

                case 4:
                    return 4;

                case 5:
                    return 5;
            }

            if (count == 3) //if the user has exceeded their attempts
            {
                printf("You have exceeded your chances\n");
                sleep(4); //halting the program exection for four seconds
                system("cls"); //clearing the screen
                printf("The program will end in 10 seconds");
                system("color 47"); //changing the screen color to red
                printf("\a"); //making a sound
                sleep(10);    //halting the program excuetion for 10 seconds
                exit(1);      //exiting the program
            }
        }
    }

    return 0;
}
void searchbyposition()
{
    char position[100];

    printf("Enter the position of the position you want to find?");

    scanf(" %[^\n]s",position); //prompting for the type of employee

    int total = 0;
    float avgsalry = 0.0;
    for(int g = 0; g < 25; g++)
    {
        for(node *r = hashtable[g]; r != NULL; r = r->next)
        {
            if(strcmp(r->type,position)== 0)
            {
                printf("%s  ",r->employeefirstname);
                printf("%s  ",r->employeelastname);
                printf("%s  ",r->type);
                printf("%s  ",r->gender);
                printf("%s  ",r->age);
                printf("%f\n",r->salary);
                total++;
                avgsalry+=r->salary;
            }
        }
    }
    float avd = avgsalry / total;
    printf("There are %d %s with an average salary of %f\n",total,position,avd);

    int ch;
    printf("Do you want to return to administrator menu?\n");
    printf("Enter 1 for YES or 2 for NO\n");
    scanf("%i", &ch);

    if (ch == 1)
    {
        system("color 12"); //changing the background color to blue and text green
        printf("Returning to administrator menu.....\n");
        printf("Please wait....\n");
        sleep(6);      //halting the program excuetion
        system("cls"); //clearing the screen
        system("color 0E");
        callingSubadminMenu(); //calling the subadmin menu options
    }

    else

    {
        system("cls"); //clearing the screen
        system("color 47"); //changes the color of the screen to red
        printf("Goodbye!");
        exit(EXIT_SUCCESS); //exiting the program

    }


}
int subadminOptionone()
{

    printf("---------------------------------YELLOW PAGE LIST OF EMPLOYEES 2021/2022---------------------------------------\n\n");

    printf("\nEmployee ID|Employee First Name |  Employee Last Name    | Employee Gender | Type of Employee   | Employee Age | Employee Salary   \n");

    node *locallist = NULL;
    node *prev = NULL;
    for (int i = 0; i < 25; i++) //printing each employee information
    {
        for(node *emp = hashtable[i]; emp != NULL; emp = emp->next)
        {
             node *each = malloc(sizeof(node));
             each->id = emp->id;
             strcpy(each->employeefirstname, emp->employeefirstname);
             strcpy(each->employeelastname, emp->employeelastname);
             strcpy(each->gender, emp->gender);
             strcpy(each->type, emp->type);
             strcpy(each->age,emp->age);
             each->salary = emp->salary;
             if(locallist == NULL)
             {
                 locallist = each;
             }
             else
             {
                 prev->next = each;
             }
             prev = each;
        }


    }
    //Sort using Bubble Sort
    int tempid;
    char tempemployeefirstname[100];
    char tempemployeelastname[100];
    char temppgender[100];
    char temptype[50];
    char tempage[50];
    float tempsalary;
    for(node *g = locallist; g != NULL; g = g->next)
    {
        for(node *c = locallist; c != NULL; c = c->next)
        {
            if(g->id < c->id)
            {
                tempid = g->id;
                strcpy(tempemployeefirstname,g->employeefirstname);
                strcpy(tempemployeelastname,g->employeelastname);
                strcpy(temppgender,g->gender);
                strcpy(temptype ,g->type);
                strcpy(tempage, g->age);
                tempsalary = g->salary;

                g->id = c->id;
                strcpy(g->employeefirstname ,c->employeefirstname);
                strcpy(g->employeelastname ,c->employeelastname);
                strcpy(g->gender ,c->gender);
                strcpy(g->age ,c->age);
                strcpy(g->type,c->type);
                g->salary = c->salary;

                c->id = tempid;
                strcpy(c->employeefirstname ,tempemployeefirstname);
                strcpy(c->employeelastname ,tempemployeelastname);
                strcpy(c->gender ,temppgender);
                strcpy(c->age ,tempage);
                strcpy(c->type,temptype);
                c->salary = tempsalary;

            }
        }
    }
    for(node *g = locallist; g != NULL; g = g->next)
    {
             printf("%10d",g->id);
             printf("%20s",g->employeefirstname);
             printf("%20s",g->employeelastname);
             printf("%20s",g->gender);
             printf("%20s",g->type);
             printf("%20s",g->age);
             printf("%20f\n",g->salary);
    }
    //prompting to return to the general menu or not
    int ch;
    printf("Do you want to return to administrator menu?\n");
    printf("Enter 1 for YES or 2 for NO\n");
    scanf("%i", &ch);

    if (ch == 1)
    {
        system("color 12"); //changing the background color to blue and text green
        printf("Returning to administrator menu.....\n");
        printf("Please wait....\n");
        sleep(6);      //halting the program excuetion
        system("cls"); //clearing the screen
        system("color 0E");
        callingSubadminMenu(); //calling the subadmin menu options
    }

    else

    {
        system("cls"); //clearing the screen
        system("color 47"); //changes the color of the screen to red
        printf("Goodbye!");
        exit(EXIT_SUCCESS); //exiting the program

    }
    return 0;
}

int subadminoptionTwo()
{

        node *addemployee = malloc(sizeof(node));
        printf("Please enter employees id number? ");
        scanf("%d", &addemployee->id);
        for(int i = 0; i < 25; i++)
        {
            for(node *p = hashtable[i]; p!= NULL; p = p->next)
            {
                if(p->id == addemployee->id)
                {
                    printf("Please enter a valid id number!.This id number is already taken!");
                    return 0;
                }
            }
        }
        printf("Please enter employee's first name? ");
        scanf(" %[^\n]s", addemployee->employeefirstname); //prompting for the employee first name

        printf("Please enter employee's last name? ");
        scanf(" %[^\n]s", addemployee->employeelastname);  //prompting for the employee last name


        printf("Enter M or F\n");
        printf("Please enter employee's gender? ");
        int countgen = 0;
        do
        {
            if (countgen >= 1)
            {
                printf("INVLAID INPUT\n");
                printf("Gender: ");
            }

            scanf(" %[^\n]s", addemployee->gender); //prompting for the employee gender
            countgen++;
        }
        while (strcmp(addemployee->gender, "M") != 0 && strcmp(addemployee->gender, "F") != 0 &&
               strcmp(addemployee->gender, "m") != 0 && strcmp(addemployee->gender, "f") != 0);

        printf("Types of Employees: Manager or Senior or Junior\n");
        printf("Type of Employee: ");
        int counting = 0;
        do
        {
            if (counting >= 1)
            {
                printf("Invalid Input\n");
                printf("Type of Employee: ");
            }
            scanf(" %[^\n]s", addemployee->type); //prompting for the type of employee
            counting++;
        }
        while (strcmp(addemployee->type, "M") != 0 && strcmp(addemployee->type, "Manager") != 0
               && strcmp(addemployee->type, "MANAGER") != 0 && strcmp(addemployee->type, "manager") != 0
               && strcmp(addemployee->type, "m") != 0 && strcmp(addemployee->type, "S") != 0 && strcmp(addemployee->type, "s") != 0
               && strcmp(addemployee->type, "Senior") != 0 &&
               strcmp(addemployee->type, "SENIOR") != 0 && strcmp(addemployee->type, "senior") != 0 && strcmp(addemployee->type, "j") != 0
               && strcmp(addemployee->type, "J") != 0 &&
               strcmp(addemployee->type, "Junior") != 0 && strcmp(addemployee->type, "JUNIOR") != 0 &&
               strcmp(addemployee->type, "junior") != 0);


        printf("Please enter employee age: "); //prompting for the employee age


        scanf(" %[^\n]s", addemployee->age);  //storing the users input as string






        addemployee->salary = employeeSalary(addemployee->type); //calculating the employee salary based upon the type of employee


        addemployee->next = NULL;

        int hashcode = hash(addemployee->employeefirstname);

        if(hashtable[hashcode] ==  NULL)
        {
            hashtable[hashcode] =  addemployee;
        }
        else
        {
            addemployee->next = hashtable[hashcode];
            hashtable[hashcode] = addemployee;
        }




    printf("Employee Information Uploaded Sucessfully\n");
    printf("Please wait....\n");


    int ch;
    printf("Do you want to return to administrator menu?\n");
    printf("Enter 1 for YES or 2 for NO\n");
    scanf("%i", &ch);

    if (ch == 1)
    {
        system("color 12");
        printf("Returning to administrator Menu.....\n");
        printf("Please wait....\n");
        sleep(6);
        system("cls");
        system("color 0E");
        callingSubadminMenu();
    }
    else
    {
        system("cls");
        system("color 47");
        printf("Goodbye!");
        exit(EXIT_SUCCESS);
    }
    return 0;

}


int optionThree() //exiting the program
{
    int count = 0;
    int select;
    char g[100];
    printf("\t\t\t\t\tEXIT PROGRAM\n");
    printf("\n\nAre you sure you want to exit the program?\nEnter 1 for YES and 2 for NO? ");
    scanf(" %[^\n]s", g);
    select = atoi(g);

    switch (select)
    {
        case 1:

            printf("GoodBye! Have a great day.\n");
            printf("The program will end in 10 seconds");
            system("color 12");
            sleep(10);
            exit(EXIT_SUCCESS);
            break;

        case 2:

            printf("Returning to General Main Menu\n");
            printf("Please wait......");
            sleep(10);
            system("cls"); //RETURNING TO THE GENERAL MAIN MENU
            callOptions();



    }

    _repeat
    {
        char x[100];
        printf("Enter 1 for YES or 2 for NO? ");
        scanf(" %[^\n]s", x);
        select = atoi(x);

        if (select == 1)
        {

            printf("GoodBye! Have a great day.\n");
            printf("The program will end in 10 seconds");
            system("color 12");
            sleep(10);//halting exuection for 10 seconds
            exit(0);  //exiting the program

        }
        if (select == 2)
        {
            printf("\nReturning to General Main Menu\n");
            printf("Please wait...........");
            system("cls"); //RETURNING TO THE GENERAL MAIN MENU
            callOptions();
        }
        count++;
        if (count == 2)
        {
            printf("You have now exceeded your chances.The program will now end");
            system("color 47");
            printf("\a");
            return 0;
        }

    }
    _until(select == 1 || select == 2);

    return 0;

}

int genMenu()
{

    int count = 0;
    /*Displaying the general menu options*/
    printf("GENERAL MENU OPTIONS\n\n");

    printf("1 -- Employee Login\n");

    printf("2 -- Admin Login\n");

    printf("3 -- EXIT PROGRAM\n\n");

    printf("Please enter a number which corresponds with your option\n");


    printf("Choice: "); //propmting the user for an input
    char chor[100];
    int x;
    scanf(" %[^\n]s", chor); //stroing the user input as a string
    x = atoi(chor);          //converting the string to integer


    switch (x)       //based on what value is entered a value is returned
    {
        case 1:
            return 1;
            break;

        case 2:
            return 2;
            break;

        case 3:
            return 3;
    }
    printf("Please select option 1 , 2 or 3\n");
    printf("You have 3 chances before the application ends\n");
    sleep(5); //halting excuetion for 5 seconds

    for (;;)
    {

        if (x < 1 || x > 3) //if the user hasn't entered a valid option
        {

            if (count >= 1)
            {
                printf("INVALID CHOICE!\n");
            }

            printf("Choice: "); //prompting fot the input
            scanf(" %[^\n]s", chor); //storing the user input as a string
            x = atoi(chor);          //converting the user input to integer
            count++;

            switch (x)
            {
                case 1:
                    return 1;
                case 2:
                    return 2;
                case 3:
                    return 3;
            }
            if (count == 3)
            {
                printf("You have exceeded your chances\n");
                sleep(4); //halting exuection for 5 seconds
                system("cls"); //clearing the screen
                printf("The program will end in 10 seconds");
                system("color 47"); //changing the color to red
                printf("\a"); //making a sound
                sleep(10);   //halting the program excurtion for 10 seconds
                exit(1);     //ending the program
            }
        }
    }

    return 0;
}

void callOptions()
{
    int x = genMenu(); //callin the general menu function and stroing the return value in x

    system("cls"); //clearing the screen

    if (x == 1)
    {
        optionOne(); //Calling function optionOne: Employee Login
    }
    else if (x == 2)
    {
        optionTwo(); //Calling function optionTwo: Administrative Login
    }
    else if (x == 3)
    {
        optionThree(); //Calling function optionThree: Exit
    }

}

int employeeSalary(char typeofemployee[15])
{
    float salary;
    float managermonthly = 68500.50;
    float seniormonthly  = 38580.70;
    float juniormonthly  = 15785.40;



    if (strcmp(typeofemployee, "M") == 0 || strcmp(typeofemployee, "Manager") == 0 || strcmp(typeofemployee, "MANAGER") == 0
        || strcmp(typeofemployee, "manager") == 0 || strcmp(typeofemployee, "m") == 0)
    {
        return salary = managermonthly * 12;
    }
    else if (strcmp(typeofemployee, "S") == 0 || strcmp(typeofemployee, "s") == 0 || strcmp(typeofemployee, "Senior") == 0 ||
             strcmp(typeofemployee, "SENIOR") == 0 || strcmp(typeofemployee, "senior") == 0)
    {
        return  salary = seniormonthly * 12;
    }
    else if (strcmp(typeofemployee, "j") == 0 || strcmp(typeofemployee, "J") == 0 ||
             strcmp(typeofemployee, "Junior") == 0 || strcmp(typeofemployee, "JUNIOR") == 0
             || strcmp(typeofemployee, "junior") == 0)
    {
        return salary = juniormonthly * 12;
    }
    else
    {
        printf("Report to Manager for wage\n");
    }

    return 0;

}

float governmentTax(char type[10], float monthlyrevenue) //function to calculate the governemnt tax
{
    float GCT = 0.0; //Government Corporation Tax

    /*Profit Organizations are taxed 13% of theirs annual income.
     Non - Profit Organizations are taxed % 7 of theirs annually income.*/

    float yearlyrevenue;
    if (strcmp(type, "Profit") == 0 || strcmp(type, "profit") == 0 ||  strcmp(type, "PROFIT") == 0)
    {
        yearlyrevenue = monthlyrevenue * 12;
        GCT = yearlyrevenue - (yearlyrevenue * 0.13);
    }
    else if (strcmp(type, "Non-Profit") == 0 || strcmp(type, "non-profit") == 0 || strcmp(type, "NON-PROFIT") == 0
             || strcmp(type, "nonprofit") == 0 || strcmp(type, "Nonprofit") == 0 || strcmp(type, "NONPROFIT") == 0
             || strcmp(type, "Non-PROFIT") == 0)
    {
        yearlyrevenue = monthlyrevenue * 12;
        GCT = yearlyrevenue - (yearlyrevenue * 0.07);
    }
    return GCT;
}
int addCompany() //function to add a company
{

    int ch;
    int counter = 0;
    int counter2 = 0;
    countFilelines = 1;
    int countf = 0;
    int companyyearsregistered;
    int numberofemployees;


    nodecompany *addnewcompany = malloc(sizeof(nodecompany));
    char namep[100];
    printf("What is the full name of your company? ");
    scanf(" %[^\n]s",namep);
    for(int i = 0, len = strlen(namep); i < len; i++)
    {
        if(i == 0)
        {
            namep[i] = toupper(namep[i]);
        }
    }
    strcpy(addnewcompany->nameofcompany,namep);



            printf("What year was your company founded? ");
            scanf(" %[^\n]s", addnewcompany->yearfounded);




        do
        {
            if (countf >= 1)
            {
                printf("\nError: Input Invalid");
                printf("\nPlease enter a number between 1 and 25 (both inclusive)\n");
                printf("Please note to enter 1 if your are new\n");


            }

            printf("How many years your company has been registered? ");
            scanf(" %[^\n]s", addnewcompany->yearsregistered);
            companyyearsregistered = atoi(addnewcompany->yearsregistered);

            countf++;

        }
        while (companyyearsregistered > 25 || companyyearsregistered < 1);



        do
        {


            printf("What is the exact number of employees in your company? ");
            scanf(" %[^\n]s", addnewcompany->numberofemploy);
            numberofemployees = atoi(addnewcompany->numberofemploy);
        }
        while (numberofemployees < 1);






        printf("Please enter Profit or Non-profit\n");
        do
        {

            printf("State the type of company: ");
            scanf(" %[^\n]s", addnewcompany->typeofcompany);



        }
        while (strcmp(addnewcompany->typeofcompany, "Profit") != 0 && strcmp(addnewcompany->typeofcompany, "Non-Profit")
               != 0 && strcmp(addnewcompany->typeofcompany, "profit") != 0 && strcmp(addnewcompany->typeofcompany, "non-profit") != 0
               && strcmp(addnewcompany->typeofcompany, "PROFIT") != 0 && strcmp(addnewcompany->typeofcompany, "NON-PROFIT") != 0
               && strcmp(addnewcompany->typeofcompany, "nonprofit") != 0 && strcmp(addnewcompany->typeofcompany, "Nonprofit") != 0
               && strcmp(addnewcompany->typeofcompany, "NONPROFIT") != 0);


        printf("Minimum monthly expenses that can be registered for one company:  5497.35\n");
        printf("Maximum monthly expenses that can be registered for one company: 181412.54\n");


        char monthlyrev[100];
        do
        {



                if (counter >= 1)
                {
                    printf("Error: INVALID AMOUNT\n");
                }
                printf("State your company average monthly revenue? ");
                scanf(" %[^\n]s", monthlyrev);
               addnewcompany->monthlyrevenue = atoi(monthlyrev);

                counter++;
        }

        while (addnewcompany->monthlyrevenue <= 5497.35 || addnewcompany->monthlyrevenue >= 181412.54);



        printf("Minimum monthly expenses that can be registered for one company: 5000\n");
        printf("Maximum monthly expenses that can be registered for one company: 155000\n");

         //prompting the user for the company monthly expenses
        char monthlyex[100];
        do
        {

            if (counter2 >= 1)
            {
                printf("Error: INVALID AMOUNT\n");

            }
             printf("State your company average monthly expenses? ");
             scanf(" %[^\n]s", monthlyex);
            //storing the monthly exepenses


            addnewcompany->monthlyexpense = atoi(monthlyex);
            counter2++;
        }
        while (addnewcompany->monthlyexpense <= 5000.00 || addnewcompany->monthlyexpense >= 155000.00);
        printf("Where is your company located? ");
        scanf(" %99[^\n]s", addnewcompany->companyaddress);

        addnewcompany->yearlyexpenses = addnewcompany->monthlyexpense * 12;
        addnewcompany->yearlyrevenue = addnewcompany->monthlyrevenue * 12;
        addnewcompany->GCT = governmentTax(addnewcompany->typeofcompany,addnewcompany->monthlyrevenue);
        addnewcompany->next = NULL;

        if(headcompany == NULL)
        {
            headcompany = addnewcompany;
        }
        else
        {
            addnewcompany->next = headcompany;
            headcompany = addnewcompany;
        }



    //displaying a receipt for future use

    printf("----------------PROOF OF PAYMENT---------------------\n\n");
    printf("Take a screenshot for future purposes\n\n");

    printf("Company Name: %s\n", addnewcompany->nameofcompany);
    printf("Year Founded:  %s\n",addnewcompany->yearfounded);
    printf("Address:%s\n", addnewcompany->companyaddress);
    printf("Number of Employees: %s\n", addnewcompany->numberofemploy);

    printf("Type: %s\n", addnewcompany->typeofcompany);
    printf("Monthly Revenue: %.2f\n", addnewcompany->monthlyrevenue);
    printf("Monthly Expenses: %.2f\n", addnewcompany->monthlyexpense);
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("Today's Date: ");
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    assert(strftime(s, sizeof(s), "%c", tm));
    printf("%s\n", s);




    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    printf("Thank you registering your business with the government\n");
    printf("Its the right thing to do\n");




    printf("Do you want to return to employee main menu?\n");
    printf("Enter 1 for YES or 2 for NO\n");
    scanf("%i", &ch);

    if (ch == 1)
    {
        system("color 12");
        printf("Returning to employee menu.....\n");
        printf("Please wait....\n");
        sleep(6);
        system("cls");
        system("color 0E");
        callingsubemployeeMenu();
    }
    else
    {
        system("cls");
        system("color 47");
        printf("Goodbye!");
        exit(EXIT_SUCCESS);
    }
    return 0;
}

int companygeneralReport() //Function to display all registered companies
{
    char tempnameofcompany[50];
    char tempyearfounded[100];
    char tempyearegistered[100];
    char temppnumberofemploy[100];
    char temptypeofcompany[50];
    char tempcompanyaddress[50];
    float tempyearlyrevenue;
    float tempyearlyexpenses;
    float tempyearlyGCT;
    int f = 0;
    char tempr;
    char tempq;

    for(nodecompany *l = headcompany; l != NULL; l = l->next)
    {
        for(nodecompany *p = headcompany; p != NULL; p = p->next)
        {
                tempr = toupper(l->nameofcompany[f]);
                tempq = toupper(p->nameofcompany[f]);
                if(tempr < tempq )
                {
                    strcpy(tempnameofcompany,l->nameofcompany);
                    strcpy(tempyearfounded,l->yearfounded);
                    strcpy(tempyearegistered,l->yearsregistered);
                    strcpy(temppnumberofemploy,l->numberofemploy);
                    strcpy(temptypeofcompany,l->typeofcompany);
                    strcpy(tempcompanyaddress,l->companyaddress);
                    tempyearlyrevenue = l->yearlyrevenue;
                    tempyearlyexpenses = l->yearlyexpenses;
                    tempyearlyGCT = l->GCT;

                    strcpy(l->nameofcompany,p->nameofcompany);
                    strcpy(l->yearfounded,p->yearfounded);
                    strcpy(l->yearsregistered,p->yearsregistered);
                    strcpy(l->numberofemploy ,p->numberofemploy);
                    strcpy(l->typeofcompany,p->typeofcompany);
                    strcpy(l->companyaddress,p->companyaddress);
                    l->yearlyrevenue = p->yearlyrevenue;
                    l->yearlyexpenses = p->yearlyexpenses;
                    l->GCT = p->GCT;

                    strcpy(p->nameofcompany,tempnameofcompany);
                    strcpy(p->yearfounded,tempyearfounded);
                    strcpy(p->yearsregistered,tempyearegistered);
                    strcpy(p->numberofemploy,temppnumberofemploy);
                    strcpy(p->typeofcompany,temptypeofcompany);
                    strcpy(p->companyaddress,tempcompanyaddress);
                    p->yearlyrevenue = tempyearlyrevenue;
                    p->yearlyexpenses = tempyearlyexpenses;
                    p->GCT = tempyearlyGCT;
                }
                else if(l->nameofcompany[f] == p->nameofcompany[f])
                {
                    secondaryswap(l,p);
                }
        }
    }
    int ch;


    printf("-----------------------------------Registered Companies 2021/2022--------------------------------------\n\n");
    printf("\nCompany Name |Year Founded|Years Registered | Number of Employee/s|  Type of Company| Company Address | Yearly Revenue | Yearly Expenses   |    Yearly Tax       \n");

    for (nodecompany *p = headcompany; p != NULL;  p = p->next)
    {
        printf("%-12s", p->nameofcompany);
        printf("%12s",  p->yearfounded);
        printf("%15s", p->yearsregistered);
        printf("%15s", p->numberofemploy);
        printf("%22s",p->typeofcompany);
        printf("%22s", p->companyaddress);
        printf("%20.2f", p->yearlyrevenue);
        printf("%20.2f", p->yearlyexpenses);
        printf("%20.2f\n", p->GCT);


    }

    printf("\n\n\n-----------------------------ANALYSIS OF ALL REVENUES AND TAXES--------------------------------\n");
    //Finding the maximum revenue
    //TODO SORT THE DATA USING SELECTION SORT
    char temp2nameofcompany[50];
    char temp2yearfounded[100];
    char temp2yearegistered[100];
    char temp2numberofemploy[100];
    char temp2typeofcompany[50];
    char temp2companyaddress[50];
    float temp2yearlyrevenue;
    float temp2yearlyexpenses;
    float temp2yearlyGCT;
    nodecompany *min;
    for(nodecompany *p = headcompany; p != NULL; p = p->next)
    {
        //set the current element
        min = p;
        for(nodecompany *h = headcompany; h != NULL; h = h->next)
        {
            if(h->yearlyrevenue < min->yearlyrevenue)
            {
                    strcpy(temp2nameofcompany,min->nameofcompany);
                    strcpy(temp2yearfounded,min->yearfounded);
                    strcpy(temp2yearegistered,min->yearsregistered);
                    strcpy(temp2numberofemploy,min->numberofemploy);
                    strcpy(temp2typeofcompany,min->typeofcompany);
                    strcpy(temp2companyaddress,min->companyaddress);
                    temp2yearlyrevenue = min->yearlyrevenue;
                    temp2yearlyexpenses = min->yearlyexpenses;
                    temp2yearlyGCT = min->GCT;

                    strcpy(min->nameofcompany,h->nameofcompany);
                    strcpy(min->yearfounded,h->yearfounded);
                    strcpy(min->yearsregistered,h->yearsregistered);
                    strcpy(min->numberofemploy ,h->numberofemploy);
                    strcpy(min->typeofcompany,h->typeofcompany);
                    strcpy(min->companyaddress,h->companyaddress);
                    min->yearlyrevenue = h->yearlyrevenue;
                    min->yearlyexpenses = h->yearlyexpenses;
                    min->GCT = h->GCT;

                    strcpy(h->nameofcompany,temp2nameofcompany);
                    strcpy(h->yearfounded,temp2yearfounded);
                    strcpy(h->yearsregistered,temp2yearegistered);
                    strcpy(h->numberofemploy,temp2numberofemploy);
                    strcpy(h->typeofcompany,temp2typeofcompany);
                    strcpy(h->companyaddress,temp2companyaddress);
                    h->yearlyrevenue = temp2yearlyrevenue;
                    h->yearlyexpenses = temp2yearlyexpenses;
                    h->GCT = temp2yearlyGCT;
            }
        }
    }
    //TODO FINDING THE MAXIMUM REVENUE USING BINARY SEARCH
    nodecompany *maximumrevenue = headcompany;
    for(nodecompany *c = headcompany; c != NULL; c = c->next)
    {
        if(c->yearlyrevenue > maximumrevenue->yearlyrevenue)
        {
            maximumrevenue->yearlyrevenue = c->yearlyrevenue;
        }
    }




    nodecompany *maximumgct = headcompany;
    for(nodecompany *c = headcompany; c != NULL; c = c->next)
    {
        if(c->GCT > maximumgct->GCT)
        {
            maximumgct->GCT = c->GCT;

        }
    }




    printf("Company with the yearly maximum revenue: %s\n",maximumrevenue->nameofcompany);
    printf("The %s Company has a yearly maximum revenue of %f\n",maximumrevenue->nameofcompany,maximumrevenue->yearlyrevenue);

    printf("The %s Company pay with most tax, their annual tax is %f\n",maximumgct->nameofcompany,maximumgct->GCT);

    printf("Do you want to return to employee menu?\n");
    printf("Enter 1 for YES or 2 for NO\n");
    scanf("%i", &ch); //Storing the user choice in a variable name 'ch'

    if (ch == 1)
    {
        system("color 12");          //changing the background-color of the screen to blue
        printf("Returning to employee  Menu............\n");
        printf("Please wait....\n");
        sleep(6);                   //Halting execution for 6 seconds
        system("cls");             //Clearing the screen
        system("color 0E");       //changing the background-color of the screen to black and text yellow
        callingsubemployeeMenu(); //Returning to sub-employee Menu
    }
    else
    {
        system("cls");      //Clearing the screen
        system("color 47"); //changing the color of the screen to red
        printf("Goodbye!");
        exit(EXIT_SUCCESS); //Exiting the program
    }
    return 0;
}

void searchCompany()  //Searching for an company
{
    char name[100];

    printf("Please enter the name of the company you would like to find: ");
    //Prompting the user for the name of the company they would like to find in the system
    scanf(" %[^\n]s", name); //Storing the name of the company in a variable
    for(int i = 0,len = strlen(name); i < len; i++)
    {
        if(i == 0)
        {
            name[i] = toupper(name[i]);
            break;
        }
    }
    int found = 0;
    for(nodecompany *c = headcompany; c != NULL; c =c->next)
    {
        if(strcmp(c->nameofcompany , name) == 0)
        {
            printf("The company you are searching for has been found\n");
            printf("Please wait to view this company information\n");
            sleep(5);
            system("cls");
            printf("Company Information: \n");
            printf("Name of Company: %s\n", c->nameofcompany);
            //Printig the name of the company
            printf("Founding Year: %s\n", c->yearfounded);
            //Printig the year the company was founded
            printf("Number of years registered: %s\n", c->yearsregistered);
            //Printing how long it was registered
            printf("Number of employees: %s\n", c->numberofemploy);
            //Printing the number of employees in the company
            printf("Type of Company: %s\n", c->typeofcompany);
            //Printing the type of company
            printf("Company Address: %s\n", c->companyaddress);
             //Printing the address in the company



            printf("Company's Yearly Revenue %.2f\n", c->yearlyrevenue); //Printing the company yearly revenue


            //Calculating the company yearly expenses based upon montlhy expenses
            printf("Company Yearly Expense: %.2f\n", c->yearlyexpenses); //Printing the company yearly expenses

            //Calculating the company yearly government tax

            printf("Company Government Tax Yearly: %.2f\n\n\n", c->GCT);
            found = 1;
        }
    }
    if(found == 0)
    {
        printf("Company not registered!");
    }
    sleep(2); //Halting execution for 2 seconds
    printf("Do you want to return to employee menu?\n"); //Prompting the user to return to employee menu
    printf("Enter 1 for YES or 2 for NO\n");
    char choice[100];
    scanf(" %[^\n]s", choice); //Storing choice
    int c = atoi(choice); //converting choice to an integer and storing it in the variable c



    if (c == 1)
    {
        system("color 12"); //changing the background screen to blue and text to green
        printf("Returning to employee menu.....\n");
        printf("Please wait....\n");
        sleep(6); //Halting execution for 6 seconds
        system("cls");  //Clearing the screen
        system("color 0E");
        callingsubemployeeMenu(); //Returning to employee menu
    }
    else
    {
        system("cls");      //Clearing the screen
        system("color 47"); // Changing the color to red
        printf("Goodbye!");
        exit(EXIT_SUCCESS); //Exiting the program
    }

}

void searchEmployee() //Searching for an employee
{
    node *locallinkedlist = NULL;
    node *prev = NULL;
    //Reading Data From the global hashtable into a local linked list to find data using binary search
    for(int p = 0; p < 25; p++)
    {
        for(node *c = hashtable[p]; c != NULL; c = c->next)
        {
            node *liste = malloc(sizeof(node));
            liste->id = c->id;
            strcpy(liste->employeefirstname,c->employeefirstname);
            strcpy(liste->employeelastname,c->employeelastname);

            strcpy(liste->gender,c->gender);
            strcpy(liste->type,c->type);
            strcpy(liste->age,c->age);
            liste->salary = c->salary;
            liste->next = NULL;
            if(locallinkedlist == NULL)
            {
                locallinkedlist = liste;
            }
            else
            {
                prev->next = liste;
            }
            prev = liste;

        }
    }

    int tempid;
    char tempemployeefirstname[100];
    char tempemployeelastname[100];
    char temppgender[100];
    char temptype[50];
    char tempage[50];
    float tempsalary;

    for(node *g = locallinkedlist; g != NULL; g = g->next)
    {
        for(node *c = locallinkedlist; c != NULL; c = c->next)
        {
            if(g->id < c->id)
            {
                tempid = g->id;
                strcpy(tempemployeefirstname,g->employeefirstname);
                strcpy(tempemployeelastname,g->employeelastname);
                strcpy(temppgender,g->gender);
                strcpy(temptype ,g->type);
                strcpy(tempage, g->age);
                tempsalary = g->salary;

                g->id = c->id;
                strcpy(g->employeefirstname ,c->employeefirstname);
                strcpy(g->employeelastname ,c->employeelastname);
                strcpy(g->gender ,c->gender);
                strcpy(g->age ,c->age);
                strcpy(g->type,c->type);
                g->salary = c->salary;

                c->id = tempid;
                strcpy(c->employeefirstname ,tempemployeefirstname);
                strcpy(c->employeelastname ,tempemployeelastname);
                strcpy(c->gender ,temppgender);
                strcpy(c->age ,tempage);
                strcpy(c->type,temptype);
                c->salary = tempsalary;
            }
        }
    }


    int id;
    printf("What is the id of the employee information you are searching for? ");
    //Prompting the user for an employee they would like to find in the system

    scanf("%d", &id); //Storing the input in the variable name
    if(isalpha(id))
    {
        printf("Enter a valid string!");
        return;
    }

    node *found = searchemployeebynumber(id,locallinkedlist);

    if(found == NULL)
    {
        printf("Employee Not Found!");
        return;
    }

    printf("First Name:  %s\n",found->employeefirstname);
    printf("Last Name:   %s\n",found->employeelastname);
    printf("Gender:      %s\n",found->gender);
    printf("Position:    %s\n",found->type);
    printf("Age:         %s\n",found->age);
    printf("Salary:      %f\n",found->salary);


    sleep(2); //Halting execution for 2 seconds
    printf("Do you want to return to employee menu?\n"); //Prompting the user to return to employee menu
    printf("Enter 1 for YES or 2 for NO\n");
    char choice[100];
    scanf(" %[^\n]s", choice); //Storing choice
    int c = atoi(choice); //converting choice to an integer and storing it in the variable c



    if (c == 1)
    {
        system("color 12"); //changing the background screen to blue and text to green
        printf("Returning to employee menu.....\n");
        printf("Please wait....\n");
        sleep(6); //Halting execution for 6 seconds
        system("cls");  //Clearing the screen
        system("color 0E");
        callingSubadminMenu(); //Returning to employee menu
    }
    else
    {
        system("cls");      //Clearing the screen
        system("color 47"); // Changing the color to red
        printf("Goodbye!");
        exit(EXIT_SUCCESS); //Exiting the program
    }


}
node *searchemployeebynumber(int id,node *head)
{

    int last = totalnodes(head);

    int start = 0;
    int m;
    for(node *empy = head; empy != NULL; empy = empy->next)
    {

        m = (start + last) / 2;
        node *middle = findnode(m , head);
        if(middle->id == id)
        {
            return middle;
        }
        else if(middle->id > id)
        {
            last = m - 1;
        }
        else if(middle->id < id)
        {
            start = m + 1;
        }
    }
    return NULL;
}
node *findnode(int num,node *head)
{
    int t = 0;
    for(node *c = head; c != NULL; c = c->next)
    {
        if(t == num)
        {
            return c;
        }
        t++;
    }
    return NULL;
}
int totalnodes(node *head)
{
    int total = 0;
    for(node *h = head; h != NULL; h=h->next)
    {
        total += 1;
    }
    return total;
}

unsigned int hash(const char *word)
{
    // TODO:
    int p = strlen(word);
    char word2[p];
    strcpy(word2, word);
    unsigned int h = 0;
    for (int i = 0; i < p; i++)
    {
        word2[i] = toupper(word2[i]);

        if (isalpha(word2[i]))
        {
            h += word2[i];
        }

    }
    unsigned int hashnumber = h % 25;
    return hashnumber;
}

int main() //Main Function
{

    system("color 0E"); /*This changes the color of the text color and the background color outputted to the user
    This changes the color to black text and a light yellow background*/

    /*

    0 = Black  8 = Gray
    1 = Blue   9 = Light Blue
    2 = Green  A = Light Green
    3 = Aqua   B = Light Aqua
    4 = Red    C = Light Red
    5 = Purple D = Light Purple
    6 = Yellow E = Light Yellow
    7 = White  F = Bright White

    */


    int i = 0;
    int size =  0;

    fptr = fopen("employeedata.txt", "r"); //opening the file for reading

    if (fptr == NULL) //if the file doesn't exists
    {
        printf("“Error: File doesn't exist");
        callingSubadminMenu();
    }


    node *currentemployee = NULL;
    int hashcode;
    while (!feof(fptr)) //reading from the file until it reaches the end of the file
    {

        currentemployee = malloc(sizeof(node));
        fscanf(fptr, "%d", &currentemployee->id);
        fscanf(fptr, "%s", currentemployee->employeefirstname);
        fscanf(fptr, "%s", currentemployee->employeelastname);
        fscanf(fptr, "%s",  currentemployee->gender);
        fscanf(fptr, "%s",  currentemployee->type);
        fscanf(fptr, "%s",  currentemployee->age);
        fscanf(fptr, "%f", &currentemployee->salary);
        currentemployee->next = NULL;

        hashcode = hash(currentemployee->employeefirstname);

        if(hashtable[hashcode] ==  NULL)
        {
            hashtable[hashcode] =  currentemployee;
        }
        else
        {
            currentemployee->next = hashtable[hashcode];
            hashtable[hashcode] = currentemployee;
        }

        i++;
        size++;
    }
    fclose(fptr);

    FILE *pts = fopen("company50.txt", "r");  //Opening the file for reading

    if (pts == NULL) //If the file doesn't exists or its empty
    {
        printf("Error: File doesn't exists");
        callingsubemployeeMenu(); //Returning to the sub employee menu
    }


    while (!feof(pts))
        /*reading the data from the file and storing it*/
    {
        nodecompany *list = malloc(sizeof(nodecompany));
        fscanf(pts, "%s", list->nameofcompany);
        fscanf(pts, "%s",list->yearfounded);
        fscanf(pts, "%s", list->yearsregistered);
        fscanf(pts, "%s", list->numberofemploy);
        fscanf(pts, "%s", list->typeofcompany);
        fscanf(pts, "%f", &list->monthlyrevenue);

        fscanf(pts, "%f", &list->monthlyexpense);
        fscanf(pts, "%s",  list->companyaddress);

        list->yearlyrevenue = list->monthlyrevenue * 12;
        list->yearlyexpenses = list->monthlyexpense * 12;
        list->GCT = governmentTax(list->typeofcompany, list->monthlyrevenue);

        list->next = NULL;
        if (headcompany == NULL)
        {
            headcompany = list;
        }
        else
        {
            list->next = headcompany;
            headcompany  = list;
        }



    }

    fclose(pts);

    char tempnameofcompany[50];
    char tempyearfounded[100];
    char tempyearegistered[100];
    char temppnumberofemploy[100];
    char temptypeofcompany[50];
    char tempcompanyaddress[50];
    float tempyearlyrevenue;
    float tempyearlyexpenses;
    float tempyearlyGCT;
    int f = 0;
    char tempr;
    char tempq;
    //Sort using Bubble Sort
    for(nodecompany *l = headcompany; l != NULL; l = l->next)
    {
        for(nodecompany *p = headcompany; p != NULL; p = p->next)
        {
                tempr = toupper(l->nameofcompany[f]);
                tempq = toupper(p->nameofcompany[f]);
                if(tempr < tempq )
                {
                    strcpy(tempnameofcompany,l->nameofcompany);
                    strcpy(tempyearfounded,l->yearfounded);
                    strcpy(tempyearegistered,l->yearsregistered);
                    strcpy(temppnumberofemploy,l->numberofemploy);
                    strcpy(temptypeofcompany,l->typeofcompany);
                    strcpy(tempcompanyaddress,l->companyaddress);
                    tempyearlyrevenue = l->yearlyrevenue;
                    tempyearlyexpenses = l->yearlyexpenses;
                    tempyearlyGCT = l->GCT;

                    strcpy(l->nameofcompany,p->nameofcompany);
                    strcpy(l->yearfounded,p->yearfounded);
                    strcpy(l->yearsregistered,p->yearsregistered);
                    strcpy(l->numberofemploy ,p->numberofemploy);
                    strcpy(l->typeofcompany,p->typeofcompany);
                    strcpy(l->companyaddress,p->companyaddress);
                    l->yearlyrevenue = p->yearlyrevenue;
                    l->yearlyexpenses = p->yearlyexpenses;
                    l->GCT = p->GCT;

                    strcpy(p->nameofcompany,tempnameofcompany);
                    strcpy(p->yearfounded,tempyearfounded);
                    strcpy(p->yearsregistered,tempyearegistered);
                    strcpy(p->numberofemploy,temppnumberofemploy);
                    strcpy(p->typeofcompany,temptypeofcompany);
                    strcpy(p->companyaddress,tempcompanyaddress);
                    p->yearlyrevenue = tempyearlyrevenue;
                    p->yearlyexpenses = tempyearlyexpenses;
                    p->GCT = tempyearlyGCT;
                }
                else if(l->nameofcompany[f] == p->nameofcompany[f])
                {
                    secondaryswap(l,p);
                }
        }

    }

    welcomeScreen(); //Welcome Screen function
    system("cls"); //Clearing the screen

    printf("\t\t\t\tWelcome to Yellow Page Company\n\n\n");



    callOptions(); //Calling the General Main Menu

    return 0;
}








