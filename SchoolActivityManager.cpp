#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <fstream.h>

class act
{
    char act_name[30];
    char act_location[30];
    char teacher_name[30];
    char stu_name[30];
    char month[30];
    int day;

public:
    char *aname()
    {
        return act_name;
    }

    void act_getdata()
    {
        cout << "Enter activity name : ";
        gets(act_name);
        cout << "Enter activity location : ";
        gets(act_location);
        cout << "Enter name of teacher in charge : ";
        gets(teacher_name);
        cout << "Enter name of student in charge : ";
        gets(stu_name);
        cout << "Enter date of activity :\n  Enter month : ";
        gets(month);
        cout << "  Enter day : ";
        cin >> day;
    }

    void act_putdata()
    {
        cout << "\nActivity name : " << act_name;
        cout << "\nActivity location : " << act_location;
        cout << "\nName of teacher in charge : " << teacher_name;
        cout << "\nName of student in charge : " << stu_name;
        cout << "\nDate of activity :\n  Month : " << month;
        cout << "  Day : " << day;
    }

} act_obj;

void act_add();
void act_del();
void act_search();
void act_display();
void act_modify();

int actnamecheck(char str[]);

void res_add();
void res_display();

struct res
{
    char act_name[30];
    char res_name[30];
    int res_amt;
    int res_budget;
};

class resources
{
    int r;
    res reso[30];

public:
    void res_getdata()
    {
        char warnch;
        r = 0;
        int check;
        char morech;
    again:
        cout << "Enter activity name : ";
        gets(reso[r].act_name);
        check = actnamecheck(reso[r].act_name);
        if (check == 1)
            goto data;
        if (check != 1)
        {
            cout << "\nWarning : You have entered an activity name that has no reccord !\n Do you want to continue (Y) or enter again (A) ? : ";
            cin >> warnch;
            if (warnch == 'y' || warnch == 'Y')
                goto data;
            else
                goto again;
        }
        else
            goto again;
    data:
        cout << "Enter budget for activity : ";
        cin >> reso[r].res_budget;
        do
        {
            cout << "Enter resource name : ";
            gets(reso[r].res_name);
            cout << "Enter resource amount : ";
            cin >> reso[r].res_amt;
            cout << "Enter more resources for the activity (Y/N)? ";
            cin >> morech;
            r++;
        } while (morech == 'y' || morech == 'Y');
    }
    void res_putdata()
    {
        int re = 0;
        ;
        cout << "Activity name : " << reso[re].act_name << endl;
        cout << "Activity budget : " << reso[re].res_budget << endl;
        for (re = 0; re <= r - 1; re++)
        {
            cout << "Resource name : " << reso[re].res_name << endl;
            cout << "Resource amount : " << reso[re].res_amt << endl;
        }
    }
} res_obj;

void main()
{
    int ch;
    int input;
    char inputch;
    char password[30];
    cout << "\n\t ***** WELCOME TO SCHOOL ACTIVITY MANAGER CONSOLE *****\n";
    do
    {
    re:
        cout << "\nMain Menu\n";
        cout << "\n Choose account to login :\n";
        cout << "\n  1. Teacher login\n  2. Admin login\n  3. Exit\n";
        cin >> input;
        if (input == 1)
        {
            cout << "\nEnter password\n";
            gets(password);
            if (strcmp(password, "@T101") == 0)
            {
                cout << "\nLogged in\n";
                do
                {
                actmenu:
                    cout << "\nActivity Menu\n";
                    cout << "\nChoose an option (1-6)\n";
                    cout << "\n1. Enter new activity details\n2. Delete an activity\n3. Search an activity\n4. Modify activity details\n5. Display details of all activities\n6. Log out\n";
                    cin >> ch;
                    if (ch == 1)
                        act_add();
                    if (ch == 2)
                        act_del();
                    if (ch == 3)
                        act_search();
                    if (ch == 4)
                        act_modify();
                    if (ch == 5)
                        act_display();
                    if (ch == 6)
                        break;
                } while (ch != 6);
            }
            else
            {
                cout << "\nWrong password !\n";
                goto re;
            }
        }
        else if (input == 2)
        {
            int ch1;
            cout << "\nEnter password : ";
            gets(password);
            if (strcmp(password, "@A909") == 0)
            {
                cout << "\nLogged in\n";
                do
                {
                remenu:
                    cout << "\nResource Menu\n";
                    cout << "\nChoose an option (1-3)\n";
                    cout << "\n1. Add resource(s) for an activity\n2. Display resource details of all activities\n3. Log out\n";
                    cin >> ch1;
                    if (ch1 == 1)
                        res_add();
                    if (ch1 == 2)
                        res_display();
                    if (ch1 == 3)
                        break;
                } while (ch1 != 3);
            }
            else
            {
                cout << "\nWrong password !\n";
                goto re;
            }
        }
        if (input == 3)
        {
            cout << "\n\t ***** THANK YOU FOR USING SCHOOL ACTIVITY MANAGER CONSOLE *****\n";
            break;
        }
        if (input != 1 && input != 2 && input != 3)
        {
            cout << "\nWrong choice\n";
            goto re;
        }
        cout << "\nAre you sure you want to log out ? Y / N : ";
        cin >> inputch;
        if (inputch == 'n' || inputch == 'N')
        {
            if (input == 1)
                goto actmenu;
            if (input == 2)
                goto remenu;
        }
    } while (inputch == 'y' || inputch == 'Y');
    getch();
}

void act_add()
{
    ofstream fout;
    fout.open("act.dat", ios::app);
    act_obj.act_getdata();
    fout.write((char *)&act_obj, sizeof(act));
    fout.close();
    cout << "\nNew activity added\n";
}
void act_display()
{
    int flag = 0;
    ifstream fin;
    fin.open("act.dat", ios::in);
    while (!fin.eof())
    {
        fin.read((char *)&act_obj, sizeof(act));
        if (fin.eof() && flag == 0)
        {
            cout << "\nNo activity data exists\n";
            break;
        }
        if (fin.eof())
            break;
        act_obj.act_putdata();
        flag++;
    }
    fin.close();
    getch();
}
void act_search()
{
    char ana[30];
    int flag = 0;
    cout << "\nEnter activity name to be searched ";
    gets(ana);
    ifstream fin;
    fin.open("act.dat");
    do
    {
        fin.read((char *)&act_obj, sizeof(act));
        if (strcmpi(act_obj.aname(), ana) == 0)
        {
            flag = 1;
            break;
        }
    } while (!fin.eof());
    if (flag == 1)
    {
        cout << "\nActivity found\n";
        act_obj.act_putdata();
    }
    if (flag == 0)
    {
        cout << "Not found";
    }
    fin.close();
    getch();
}
void act_modify()
{
    char ana[30];
    cout << "\nEnter activity name to be modfied ";
    gets(ana);
    fstream fio;
    fio.open("act.dat", ios::in | ios::out);
    while (fio.read((char *)&act_obj, sizeof(act_obj)))
    {
        int pos = fio.tellg();
        fio.read((char *)&act_obj, sizeof(act_obj));
        if (strcmpi(act_obj.aname(), ana) == 0)
        {
            cout << "\nEnter new activity details\n";
            act_obj.act_getdata();
            fio.seekg(pos);
            fio.write((char *)&act_obj, sizeof(act_obj));
            cout << "Records updated\n";
        }
    }
    getch();
}
void act_del()
{
    ifstream fin;
    ofstream fout;
    fin.open("act.dat", ios::nocreate);
    fout.open("file.dat", ios::out);
    char ana[30];
    cout << "Enter the activity name of the record you wish to delete\n";
    gets(ana);
    while (fin.read((char *)&act_obj, sizeof(act)))
    {
        fin.read((char *)&act_obj, sizeof(act));
        if (fin.eof())
            break;
        if (strcmpi(act_obj.aname(), ana) == 1)
        {
            fout.write((char *)&act_obj, sizeof(act));
        }
    }
    fin.close();
    fout.close();
    remove("act.dat");
    rename("file.dat", "act.dat");
    cout << "Records updated\n";
}

void res_add()
{
    ofstream fout;
    fout.open("res.dat", ios::app);
    res_obj.res_getdata();
    fout.write((char *)&res_obj, sizeof(resources));
    fout.close();
    cout << "\nNew resources added\n";
}
void res_display()
{
    int flag = 0;
    ifstream fin;
    fin.open("res.dat", ios::in);
    while (!fin.eof())
    {
        fin.read((char *)&res_obj, sizeof(resources));
        if (fin.eof() && flag == 0)
        {
            cout << "\nNo resource data exists\n";
            break;
        }
        if (fin.eof())
            break;
        res_obj.res_putdata();
        flag++;
    }
    fin.close();
    getch();
}
int actnamecheck(char ana[])
{
    int flag = 0;
    ifstream fin;
    fin.open("act.dat");
    do
    {
        fin.read((char *)&act_obj, sizeof(act));
        if (strcmpi(act_obj.aname(), ana) == 0)
        {
            flag = 1;
            break;
        }
    } while (!fin.eof());
    fin.close();
    if (flag == 1)
    {
        cout << "\nActivity found\n";
        return 1;
    }
    else
    {
        cout << "\nActvity not found";
        return 0;
    }
}
