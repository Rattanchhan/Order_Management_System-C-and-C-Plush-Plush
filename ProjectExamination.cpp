#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cctype>
#include <conio.h>
using namespace std;
const int MAX_SIZE = 20;
void run(int, struct Order rd[]);
void topping_menu(string st);
void pizza(string st);
void drink_menu(string st);
void size_menu();
void sub_orderMenu();
void food_menu(string st);
int get_option(string, string);
void update_menu();
void sale_typeMenu();
void sub_order_menu(struct Order rd[], int, int&, string);
void sub_menu(struct Order rd[], int, int&, int&, string);
void sub_topping_menu(struct Order rd[], int, int&, int&, string);
void sub_drink_menu(struct Order rd[], int, int&, int&, string);
void main_menu();
void sub_size_menu(struct Order rd[], string, int, int&, int&, string);
void reciept_detail(struct Order rd[], string, float, int, int&, string);
void get_detail(struct Order rd[], string, float, int, int&, string);
void reciept(struct Order rd[], int, int);
void all_order_view(struct Order rd[], int, int);
void get_total_kh(struct Order rd[], int, float);
void get_vat(struct Order rd[], int, float);
void get_net_amt(struct Order rd[], int, float);
void reciept();
float get_amount(int, float);
float get_total(float, float);
int get_numbers(string);
void order_view(struct Order rd[], int, int);
int sub_search(int, int);
void show_message(string);
void display(struct Order rd[], int, int);
void sub_order_update_menu(struct Order rd[], int, int, string, int&);
void sub_delete(struct Order rd[], int, int&, int);
void order_type_menu(struct Order rd[], int);
string getString(string, string);
void get_date(struct Order rd[], int);
void search_order(struct Order rd[], int, int);
void delete_order_menu(struct Order rd[], int&);
void order_update_menu(struct Order rd[], int, float, float, float);
void sort_order(struct Order rd[], int);
void swap(struct Order&, struct Order&);
bool deletes(struct Order rd[], int, int&, char);
void sub_update_menu(struct Order rd[], int, float, float, string);
void update(struct Order rd[], int i, int k, float price);
void get_character(string st);
void payment_update(struct Order rd[], int, float, float);
float check_price(string);
bool validat_option(string);
void repet_show(string, string);
void search_menu();
bool validat_number(string);
bool validat_id(string);
bool validat_staff(string);
bool validat_phoneNumber(string);
void gotoxy(short, short);
void setcolor(int);
void front_display(int, int);
bool check_string(string);
bool check_character(char, int&, int&, int&);
string get_name(int, int);
string get_password(int, int);
bool check_passwordInput(char, int&, int&, int&, int);
void clear_text(int, int);
void intro_changePassword();
void change_password(struct login& account);
void writefile(struct login account);
void to_account(int, struct Order rd[]);
void get_detail(struct Order rd[], float, float, int, int);
void view(struct Order rd[], int, int);
int search(struct Order rd[], int, string, string);
void swap1(struct Order rd[], int, int);
void get_inform(struct Order rd[], int, string);
void intro_reciept_header();
bool verify_newPassword(struct login& account, string, string, string);
bool verify(struct login account, string, string, int, int);
string get_usernameInput(int, int);
string get_passwordInput(int, int, int);
void login_menu();
// Structure Date
struct login
{
    string password;
    string username;
};
login get_account()
{
    login account;
    show_message("\tEnter username: ");
    account.username = get_usernameInput(23, 0);
    show_message("\tEnter password: ");
    account.password = get_passwordInput(24, 2, 24);
    return account;
}
struct Date
{
    int hour;
    int minute;
    int month;
    int year;
    int day;
};
// Structure Inform
struct Inform
{
    string staff;
    int table_numbers;
    string id;
    string address;
    string type_sale;
    string phone_number;
};
// Structure Order
struct Order
{
    float amount[MAX_SIZE];
    float total_usd = 0;
    float total_kh = 0;
    float vat = 0;
    float net_amt = 0;
    int n[MAX_SIZE];
    string name[MAX_SIZE];
    int qty[MAX_SIZE];
    float retail_price[MAX_SIZE];
    // Declaring variablesName of struct Date and struct Inform
    struct Date date;
    struct Inform inform;
};
// Main function
int main()
{
    struct Order rd[MAX_SIZE];
    struct Order get_rd;
    int k = 0;
    int i = 0;
    ifstream loadFile;
    loadFile.open("Customer.bat", ios::in | ios::binary);
    while (loadFile.read((char*)(&get_rd), sizeof(get_rd)))
    {
        rd[k] = get_rd;
        k++;
    }
    loadFile.close();
    //to_account(k, rd);
    run(k, rd);
    return 0;
}
void to_account(int k, struct Order rd[])
{
    int option;
    login account;
    login getAccount;
    enum OPTION
    {
        EXIT = 0,
        LOGIN,
        CHANGE_PASSWORD
    };
    account = get_account();
    writefile(account);
    do
    {
        do {
            system("cls");
            login_menu();
            option = get_option("login", " ");
        } while (option >2);
        switch (option)
        {
        case OPTION::LOGIN:
        {
            string username;
            string password;
            bool result;
            ifstream readFile;
            readFile.open("login.bat", ios::in | ios::binary);
            while (readFile.read((char*)&getAccount, sizeof(getAccount)))
            {
                account = getAccount;
            }
            readFile.close();
            do {
                system("cls");
                front_display(20, 7);
                username = get_name(20, 7);
                password = get_password(20, 7);
                result = verify(account, username, password, 20, 7);
                setcolor(15);
            } while (result!=true);
            run(k, rd);
        }
        break;
        case OPTION::CHANGE_PASSWORD:
        {
            ifstream readFile;
            string username;
            string password;
            bool result;
            readFile.open("login.bat", ios::in | ios::binary);
            while (readFile.read((char*)&getAccount, sizeof(getAccount)))
            {
                account = getAccount;
            }
            readFile.close();
            change_password(account);
            writefile(account);
            do {
                system("cls");
                front_display(20, 7);
                username = get_name(20, 7);
                password = get_password(20, 7);
                result = verify(account, username, password, 20, 7);
                get_character("press any key to continue...");
                setcolor(15);
            } while (result != true);
            setcolor(15);
            run(k, rd);
        }
        break;
        case OPTION::EXIT:
        {
            char ch;
            cout << "\tAare you sure to exit (y/n): ";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                exit(0);
            }
            else {
                option = -1;
                cin.ignore();
            }
        }
        break;
        }
        _getch();
    } while (option != 0);
}
void run(int k, struct Order rd[])
{
    // Declaring Variables
    int i = 0;
    i = k;
    int j;
    //int n[MAX_SIZE];
    const float VAT_PERCENTAGE = 0.1;
    const int VAT = 10;
    const float KH = 4100;
    int option_type;
    enum MAIN_MENU
    {
        EXIT = 0, ORDER, VIEW_ORDER, UPDATE_ORDER, SEARCH_ORDER, DELETE_ORDER, SORT_ORDER, SAVE, LOAD
    };

    do
    {
        system("cls");
        main_menu();
        option_type = get_option("main_menu", "");
        switch (option_type)
        {
        case MAIN_MENU::ORDER:
        {
            j = 0;
            sub_order_menu(rd, i, j, "sub_orderMenu");
            get_detail(rd, KH, VAT_PERCENTAGE, i, j);
            rd[i].n[i] = j;
            i++;
        }break;
        case MAIN_MENU::VIEW_ORDER:
        {
            view(rd, i, VAT);
        }break;
        case MAIN_MENU::SEARCH_ORDER:
        {
            view(rd, i, VAT);
            search_order(rd, i, VAT);
        }break;
        case MAIN_MENU::UPDATE_ORDER:
        {
            view(rd, i, VAT);
            order_update_menu(rd, i, KH, VAT_PERCENTAGE, VAT);
        }break;
        case MAIN_MENU::DELETE_ORDER:
        {
            view(rd, i, VAT);
            delete_order_menu(rd, i);
        }break;
        case MAIN_MENU::SORT_ORDER:
        {
            cout << "\t=======SORT MENU=======" << endl;
            cout << "\tBY TOTAL_AMOUNT" << endl;
            sort_order(rd, i);
            show_message("\tSort successfully!!!\n");
        }break;
        case MAIN_MENU::SAVE:
        {
            ofstream saveFile;
            saveFile.open("Customer.bat", ios::out | ios::binary);
            for (int k = 0; k < i; k++)
            {
                saveFile.write((char*)(&rd[k]), sizeof(rd[k]));
            }
            saveFile.close();
            show_message("\tFile save successfully!!!\n");
        }break;
        case MAIN_MENU::LOAD:
        {
            show_message("\tfile load successfully!!!\n");
        }break;
        case MAIN_MENU::EXIT:
        {
            char st;
            cout << "\tAre you sure to exit (Y/N)? ";
            cin >> st;
            if (st == 'y' || st == 'Y')
            {
                exit(0);
            }
            else
            {
                option_type = -1;
                cin.ignore();
            }
        }break;
        default:
        {
            show_message("\tInvalid!!!\n");
            cin.ignore();
        }break;
        }
        get_character("\tPress any key to counitue...");
    } while (option_type != 0);
}
void sub_order_menu(struct Order rd[], int i, int& j, string st)
{
    enum SUB_ORDER_MENU
    {
        BACK_TO_MAIN_MENU = 0, ORDER, VIEW, UPDATE, SEARCH, DELETES
    };
    int option_order;
    int k;
    do
    {
        system("cls");
        sub_orderMenu();
        option_order = get_option("sub_orderMenu", "");
        switch (option_order)
        {
        case SUB_ORDER_MENU::ORDER:
        {
            sub_menu(rd, i, j, option_order, st);
        }break;
        case SUB_ORDER_MENU::VIEW:
        {
            intro_reciept_header();
            order_view(rd, j, i);
            get_character("\tPress any key to counitue...");
        }break;
        case SUB_ORDER_MENU::SEARCH:
        {
            int neutron;
            intro_reciept_header();
            order_view(rd, j, i);
            neutron = get_numbers("\tPlease input neutron(No): ");
            k = sub_search(neutron, j);
            if (k != -1)
            {
                show_message("\tSearch is found!!!\n");
                intro_reciept_header();
                display(rd, k, i);
            }
            else
            {
                show_message("\tSearch no found!!!\n");
            }
            get_character("\tPress any key to counitue...");
        }break;
        case SUB_ORDER_MENU::UPDATE:
        {
            intro_reciept_header();
            order_view(rd, j, i);
            sub_order_update_menu(rd, i, j, "update", option_order);
            get_character("\tPress any key to counitue...");
        }break;
        case SUB_ORDER_MENU::DELETES:
        {
            int neutron;
            char key;
            intro_reciept_header();
            order_view(rd, j, i);
            neutron = get_numbers("\tPlease input neutron(No): ");
            k = sub_search(neutron, j);
            if (k != -1)
            {
                show_message("\tSearch is found!!!\n");
                show_message("\tAre you sure to delete (Y/N)? ");
                cin >> key;
                if (key == 'y' || key == 'Y')
                {
                    rd[i].total_usd = rd[i].total_usd - rd[i].amount[k];
                    sub_delete(rd, k, j, i);
                    show_message("\tDelete  successfully!!!\n");
                }
            }
            else
            {
                show_message("\tSearch not found!!!\n");
            }
            get_character("\tPress any key to counitue...");
            cin.ignore();
        }break;
        case SUB_ORDER_MENU::BACK_TO_MAIN_MENU: {}break;
        default:
        {
            show_message("\tInvalid!!!\n");
            cin.ignore();
            get_character("\tPress any key to counitue...");
        }
        }
    } while (option_order != 0);
}
void sub_menu(struct Order rd[], int i, int& j, int& option_order, string st)
{
    enum FOOD_MENU
    {
        BACK_TO_SUB_ORDER_MENU = 0, PIZZA, DRINKS, BACK_TO_MAIN_MENU
    };
    int option_menu;
    do
    {
        if (st == "order_update" || st == "update")
        {
            do
            {
                system("cls");
                food_menu(st);
                option_menu = get_option("food_menu", st);
            } while (option_menu > 2);
        }
        else
        {
            do
            {
                system("cls");
                food_menu(st);
                option_menu = get_option("food_menu", st);
            } while (option_menu > 3);
        }
        switch (option_menu)
        {
        case FOOD_MENU::PIZZA:
        {
            sub_topping_menu(rd, i, j, option_menu, st);
        }break;
        case FOOD_MENU::DRINKS:
        {
            sub_drink_menu(rd, i, j, option_menu, st);
        }break;
        case FOOD_MENU::BACK_TO_MAIN_MENU:
        {
            option_order = 0;
            option_menu = 0;
        }break;
        case FOOD_MENU::BACK_TO_SUB_ORDER_MENU:
        {
            if (st == "update")
            {
                option_order = 0;
            }
        }break;
        default:
        {
            show_message("\tInvalid!!!\n");
            get_character("\tPress any key to counitue...");
        }break;
        }
    } while (option_menu != 0);
}
void sub_topping_menu(struct Order rd[], int i, int& j, int& option_menu, string st)
{
    enum TOPPING_MENU
    {
        BACK_TO_FOOD_MENU = 0, CHICKEN, SEAFOOD, SAUSAGE, BACK_TO_SUB_ORDER_MENU
    };
    int option_topping;
    do
    {
        system("cls");
        if (st == "order_update")
        {
            do
            {
                system("cls");
                pizza(st);
                option_topping = get_option("topping_menu", st);
            } while (option_topping > 3);
            st = "update";
        }
        else
        {
            do
            {
                system("cls");
                pizza(st);
                option_topping = get_option("topping_menu", st);
            } while (option_topping > 5);
        }
        switch (option_topping)
        {
        case TOPPING_MENU::CHICKEN:
        {
            sub_size_menu(rd, "Chicken", i, j, option_topping, st);
        }break;
        case TOPPING_MENU::SAUSAGE:
        {
            sub_size_menu(rd, "Sausage", i, j, option_topping, st);
        }break;
        case TOPPING_MENU::SEAFOOD:
        {
            sub_size_menu(rd, "Seafood", i, j, option_topping, st);
        }break;
        case TOPPING_MENU::BACK_TO_FOOD_MENU:
        {
        }break;
        case TOPPING_MENU::BACK_TO_SUB_ORDER_MENU:
        {
            option_menu = 0;
            option_topping = 0;
        }break;
        default:
        {
            show_message("\tInvalid!!!\n");
            get_character("\tPress any key to counitue...");
        }break;
        }
    } while (option_topping != 0);
}
void sub_size_menu(struct Order rd[], string topping_name, int i, int& j, int& option_topping, string st)
{
    enum SIZE_MENU
    {
        BACK_TO_TOPPING_MENU = 0, LARGE, MEDIUM, SMALL, BACK_TO_FOOD_MENU,
    };
    int option_size;
    float price;
    string productName;
    do
    {
        system("cls");
        size_menu();
        option_size = get_option("size_menu", "");
        switch (option_size)
        {
        case SIZE_MENU::LARGE:
        {
            productName = ("L-" + topping_name);
            price = check_price(productName);
            get_detail(rd, productName, price, i, j, st);
        }break;
        case SIZE_MENU::MEDIUM:
        {
            productName = ("M-" + topping_name);
            price = check_price(productName);
            get_detail(rd, productName, price, i, j, st);
        }break;
        case SIZE_MENU::SMALL:
        {
            productName = ("S-" + topping_name);
            price = check_price(productName);
            get_detail(rd, productName, price, i, j, st);
        }break;
        case SIZE_MENU::BACK_TO_FOOD_MENU:
        {
            option_topping = 0;
            option_size = 0;
        }
        break;
        case SIZE_MENU::BACK_TO_TOPPING_MENU: {}break;
        default:
        {
            show_message("\tInvalid!!!\n");
        }break;
        }
        get_character("\tPress any key to counitue...");
    } while (option_size != 0);
}
void sub_drink_menu(struct Order rd[], int i, int& j, int& option_menu, string st)
{
    enum DRINK_MENU
    {
        BACK_TO_FOOD_MENU = 0, STING, COCA_COLA, SPRITE, DRINKING_WATER, BACK_TO_SUB_ORDER_MENU
    };
    int option_drink;
    string productName;
    float price;
    do
    {
        system("cls");
        if (st == "order_update")
        {
            do
            {
                system("cls");
                drink_menu(st);
                option_drink = get_option("drink_menu", st);
            } while (option_drink > 4);
        }
        else
        {
            do
            {
                system("cls");
                drink_menu(st);
                option_drink = get_option("drink_menu", st);
            } while (option_drink > 6);
        }
        switch (option_drink)
        {
        case DRINK_MENU::COCA_COLA:
        {
            productName = "Coca_Cola";
            price = check_price(productName);
            get_detail(rd, productName, price, i, j, st);
        }break;
        case DRINK_MENU::DRINKING_WATER:
        {
            productName = "Drinking_Water";
            price = check_price(productName);
            get_detail(rd, productName, price, i, j, st);
        }break;
        case DRINK_MENU::SPRITE:
        {
            productName = "Sprite";
            price = check_price(productName);
            get_detail(rd, productName, price, i, j, st);
        }break;
        case DRINK_MENU::STING:
        {
            productName = "Sting";
            price = check_price(productName);
            get_detail(rd, productName, price, i, j, st);
        }break;
        case DRINK_MENU::BACK_TO_FOOD_MENU: {}break;
        case DRINK_MENU::BACK_TO_SUB_ORDER_MENU:
        {
            option_drink = 0;
            option_menu = 0;
        }break;
        default:
        {
            show_message("\tInvalid!!!\n");
        }break;
        }
        get_character("\tPress any key to counitue...");
    } while (option_drink != 0);
}
void sub_update_menu(struct Order rd[], int i, float kh, float vat_percentage, string st)
{
    int option;
    int k;
    int j = rd[i].n[i];
    enum UPDATE_MENU
    {
        NAME = 1, QTY, QTY_AND_NAME
    };
    if (st != "order_update")
    {
        system("cls");
    }
    do
    {
        update_menu();
        option = get_option("sub_update_menu", "");
    } while (option > 3 || option == 0);
    switch (option)
    {
    case UPDATE_MENU::NAME:
    {
        int neutron;
        neutron = get_numbers("\tPlease input neutron(No): ");
        k = sub_search(neutron, j);
        if (k != -1)
        {
            show_message("\tSearch is found!!!\n");
            sub_menu(rd, i, k, option, "order_update");
            payment_update(rd, i, kh, vat_percentage);
        }
        else
        {
            show_message("\tSearch not found!!!\n");
        }
    }break;
    case UPDATE_MENU::QTY:
    {
        int neutron;
        float price = 0;
        neutron = get_numbers("\tPlease input neutron(No): ");
        k = sub_search(neutron, j);
        if (k != -1)
        {
            show_message("\tSearch is found!!!");
            price = check_price(rd[i].name[k]);
            update(rd, i, k, price);
            payment_update(rd, i, kh, vat_percentage);
            show_message("\tUpdate successfully!!!\n");
        }
        else
        {
            show_message("\tSearch not found!!!\n");
        }
    }break;
    case UPDATE_MENU::QTY_AND_NAME:
    {
        int neutron;
        float price = 0;
        neutron = get_numbers("\tPlease input neutron(No): ");
        k = sub_search(neutron, j);
        if (k != -1)
        {
            show_message("\tSearch is found!!!\n");
            price = check_price(rd[i].name[k]);
            update(rd, i, k, price);
            sub_menu(rd, i, k, option, "order_update");
            payment_update(rd, i, kh, vat_percentage);
        }
        else
        {
            show_message("\tSearch not found!!!\n");
        }
    }break;
    }
}
void sub_order_update_menu(struct Order rd[], int i, int j, string st, int& option_order)
{
    int option;
    int k;
    enum UPDATE_MENU
    {
        BACK_TO_SUB_ORDER_MENU = 0, UPDATE_NAME, UPDATE_QTY, UPDATE_QTYAND_NAME
    };
    do
    {
        update_menu();
        option = get_option("sub_update_menu", "");
    } while (option > 3);
    switch (option)
    {
    case UPDATE_MENU::UPDATE_NAME:
    {
        int neutron;
        neutron = get_numbers("\tPlease input neutron(No): ");
        k = sub_search(neutron, j);
        if (k != -1)
        {
            show_message("\tSearch is found!!!\n");
            sub_menu(rd, i, k, option, st);
        }
        else
        {
            show_message("\tSearch not found!!!\n");
        }
    }break;
    case UPDATE_MENU::UPDATE_QTY:
    {
        int neutron;
        float price = 0;
        neutron = get_numbers("\tPlease input neutron(No): ");
        k = sub_search(neutron, j);
        if (k != -1)
        {
            show_message("\tSearch is found!!!\n");
            price = check_price(rd[i].name[k]);
            update(rd, i, k, price);
            show_message("\tUpdate successfully!!!\n");
        }
        else
        {
            show_message("\tSearch not found!!!\n");
        }
    }break;
    case UPDATE_MENU::UPDATE_QTYAND_NAME:
    {
        int neutron;
        float price = 0;
        neutron = get_numbers("\tPlease input neutron(No): ");
        k = sub_search(neutron, j);
        if (k != -1)
        {
            show_message("\tSearch is found!!!\n");
            price = check_price(rd[i].name[k]);
            update(rd, i, k, price);
            sub_menu(rd, i, k, option, st);
        }
        else
        {
            show_message("\tSearch not found!!!\n");
        }
    }break;
    case UPDATE_MENU::BACK_TO_SUB_ORDER_MENU: {}break;
    }
}
void order_update_menu(struct Order rd[], int i, float kh, float vat_percentage, float vat)
{
    int updateOption;
    enum UPDATE_BY
    {
        BY_ID = 1, BY_PHONENUMBER = 2
    };
    do
    {
        cout << "\t==========UPDATE MENU==========\n" << endl;
        search_menu();
        updateOption = get_option("update_menu", "");
    } while (updateOption > 2);
    switch (updateOption)
    {
    case UPDATE_BY::BY_ID:
    {
        string id;
        bool found = false;
        id = getString("\tPlease iput id: ", "id");
        for (int k = 0; k < i; k++)
        {
            if (rd[k].inform.id == id)
            {
                system("cls");
                show_message("\tSearch is found!!!\n");
                all_order_view(rd, k, vat);
                sub_update_menu(rd, k, kh, vat_percentage, "order_update");
                found = true;
                break;
            }
        }
        if (found == false)
        {
            show_message("\tSearch not found!!!\n");
        }
    }break;
    case UPDATE_BY::BY_PHONENUMBER:
    {
        string phone;
        bool found = false;
        phone = getString("\tPlease input phone number: ", "phoneNumber");
        for (int k = 0; k < i; k++)
        {
            if (rd[k].inform.phone_number == phone)
            {
                system("cls");
                show_message("\tSearch is found!!!\n");
                all_order_view(rd, k, vat);
                sub_update_menu(rd, k, kh, vat_percentage, "order_update");
                found = true;
                break;
            }
        }
        if (found == false)
        {
            show_message("\tSearch not found!!!\n");
        }
    }break;
    }
}
void order_type_menu(struct Order rd[], int i)
{
    int option_type;
    enum SALTTPYE
    {
        DINE_IN = 1, TAKEAWAY = 2, DELIVERY = 3
    };
    do
    {
        system("cls");
        sale_typeMenu();
        option_type = get_option("sale_typeMenu", "");
    } while (option_type > 3 || option_type == 0);
    switch (option_type)
    {
    case SALTTPYE::DINE_IN:
    {
        get_inform(rd, i, "DINE IN");
    }break;
    case SALTTPYE::TAKEAWAY:
    {
        get_inform(rd, i, "TAKE AWAY");
    }break;
    case SALTTPYE::DELIVERY:
    {
        get_inform(rd, i, "DELIVERY");
    }break;
    }
}
void topping_menu(string st)
{
    cout << "\t=========TOPPING MENU=========" << endl;
    cout << "\t1.Chicken" << endl;
    cout << "\t2.Seafood" << endl;
    cout << "\t3.Sausage" << endl;
    if (st == "order_update")
    {
        cout << "\t0.Back to FOOD MENU" << endl;
        cout << "\tPlease choose one option(1-3):";
    }
    else
    {
        cout << "\t4.Back to  SUB ORDER MENU" << endl;
        cout << "\t0.Back to FOOD MENU" << endl;
        cout << "\tPlease choose one option(1-4):";
    }
}
void size_menu()
{
    cout << "\t===========SIZE MENU===========" << endl;
    cout << "\t1.Large" << endl;
    cout << "\t2.Medium" << endl;
    cout << "\t3.Small" << endl;
    cout << "\t4.Back to FOOD MENU" << endl;
    cout << "\t0.Back to TOPPING MENU" << endl;
    cout << "\tPleae choose one option(1-4):";
}
void drink_menu(string st)
{
    cout << "\t==========DRINKS MENU==========" << endl;
    cout << "\t1.Sting" << endl;
    cout << "\t2.Coca Cola" << endl;
    cout << "\t3.Sprite" << endl;
    cout << "\t4.Drinking Water" << endl;
    if (st == "order_update")
    {
        cout << "\t0.Back to FOOD MENU" << endl;
        cout << "\tPlease choose one option(1-4):";
    }
    else
    {
        cout << "\t5.Back to SUB ORDER MENU" << endl;
        cout << "\t0.Back to FOOD MENU" << endl;
        cout << "\tPlease choose one option(1-5):";
    }
}
void sub_orderMenu()
{
    cout << "\t=======SUB ORDER MENU=======" << endl;
    cout << "\t1.Order" << endl;
    cout << "\t2.View order" << endl;
    cout << "\t3.Update order" << endl;
    cout << "\t4.Search order" << endl;
    cout << "\t5.Delete order" << endl;
    cout << "\t0.Back to MAIN MENU" << endl;
    cout << "\tPlease choose one option(1-5): ";
}
void food_menu(string st)
{
    cout << "\t=====FOOD MENU=====" << endl;
    cout << "\t1.Pizza" << endl;
    cout << "\t2.Drinks" << endl;
    if (st == "order_update")
    {
        cout << "\t0.Back to MAIN MENU" << endl;
        cout << "\tPlease choose one option(1-2):";
    }
    else if (st == "update")
    {
        cout << "\t0.Back to SUB ORDER MENU" << endl;
        cout << "\tPlease choose one option(1-2):";
    }
    else
    {
        cout << "\t3.Back to MAIN MENU" << endl;
        cout << "\t0.Back to SUB ORDER MENU" << endl;
        cout << "\tPlease choose one option(1-3):";
    }
}
void main_menu()
{
    cout << "\t===========MAIN MENU===========" << endl;
    cout << "\t1.Order" << endl;
    cout << "\t2.View order" << endl;
    cout << "\t3.Update order" << endl;
    cout << "\t4.Search order" << endl;
    cout << "\t5.Delete order" << endl;
    cout << "\t6.Sort order" << endl;
    cout << "\t7.Save order to a file" << endl;
    cout << "\t8.Load order from a file" << endl;
    cout << "\t0.Exit" << endl;
    cout << "\tPlease choose one option (1-8): ";
}

void delete_order_menu(struct Order rd[], int& i)
{
    int deleteOption;
    enum DELETED
    {
        BY_ID = 1, BY_PHONENUMBER = 2
    };
    do
    {
        cout << "\t=========DELETE MENU=========\n" << endl;
        search_menu();
        deleteOption = get_option("delete_menu", "");
    } while (deleteOption > 2);
    switch (deleteOption)
    {
    case DELETED::BY_ID:
    {
        string id;
        int k;
        char ch;
        id = getString("\tPlease input id to delete: ", "id");
        k = search(rd, i, "id", id);
        if (k > -1) {
            show_message("\tSearch is found!!!\n");
            show_message("\tAre you sure to delete (Y/N)? ");
            cin >> ch;
            if (deletes(rd, k, i, ch)) {
                show_message("\tDelete successfully!!!\n");
            }
        }
        else show_message("\tSearch not found!!!\n");
    }
    break;
    case DELETED::BY_PHONENUMBER:
    {
        string phoneNumber;
        int k;
        char ch;
        phoneNumber = getString("\tPlease input id to delete: ", "phoneNumber");
        k = search(rd, i, "phoneNumber", phoneNumber);
        if (k > -1) {
            show_message("\tSearch is found!!!\n");
            show_message("\tAre you sure to delete (Y/N)?");
            cin >> ch;
            if (deletes(rd, k, i, ch)) {
                show_message("\tDelete successfully!!!\n");
            }
        }
        else show_message("\tSearch not found!!!\n");
    }break;
    }
}
void search_order(struct Order rd[], int i, int vat)
{
    enum SEARCH
    {
        BY_ID = 1, BY_PHONENUMBER = 2
    };
    int searchOption;
    do
    {
        show_message("\t=========SEARCH MENU=========\n");
        search_menu();
        searchOption = get_option("search_menu", "");
    } while (searchOption > 2);
    switch (searchOption)
    {
    case SEARCH::BY_ID:
    {
        string id;
        int k;
        id = getString("\tPlease input id: ", "id");
        k = search(rd, i, "id", id);
        if (k > -1) {
            show_message("\tSearch is found!!!\n");
            all_order_view(rd, k, vat);
        }
        else show_message("\tSearch not found!!!\n");
    }break;
    case SEARCH::BY_PHONENUMBER:
    {
        string phoneNumber;
        int k;
        phoneNumber = getString("\tPlease input phone number: ", "phoneNumber");
        k = search(rd, i, "phoneNumber", phoneNumber);
        if (k > -1) {
            show_message("\tSearch is found!!!\n");
            all_order_view(rd, k, vat);
        }
        else show_message("\tSearch not found!!!\n");
    }break;
    }
}
void reciept()
{
    cout << endl;
    cout << right << setw(76) << "The pizza resturant: #107, Phoum 4 ANZ Road" << endl;
    cout << right << setw(67) << "Sangkat Boeung Kakti 2," << endl;
    cout << right << setw(72) << "Khan Toul Kork Phnom Penh, 120408" << endl;
    cout << right << setw(71) << "Call & Pick up  : 088 50 60 697" << endl;
    cout << right << setw(80) << "-------------------------------------------------" << endl;
}
void reciept(struct Order rd[], int i, int vat)
{

    cout << right << setw(61) << "Receiption " << endl;
    cout << right << setw(80) << "-------------------------------------------------" << endl;
    cout << right << setw(38) << "Slip:  "
        << "000000000C92000000" << i << endl;
    cout << right << setw(38) << "Staff: " << rd[i].inform.staff << endl;
    if (rd[i].inform.type_sale == "TAKE AWAY")
    {
        cout << right << setw(38) << "ID:    " << rd[i].inform.id << endl;
        cout << right << setw(47) << "PHONE NUMBER:   " << rd[i].inform.phone_number << endl;
    }
    else if (rd[i].inform.type_sale == "DELIVERY")
    {
        cout << right << setw(38) << "ID:    " << rd[i].inform.id << endl;
        cout << right << setw(47) << "PHONE NUMBER:   " << rd[i].inform.phone_number << endl;
        cout << right << setw(41) << "Adderess: " << rd[i].inform.address << endl;
    }
    else
    {
        cout << right << setw(35) << "ID: " << rd[i].inform.id << endl;
        cout << right << setw(38) << "Table: " << rd[i].inform.table_numbers << endl;
    }
    cout << right << setw(43) << "Sales Type: " << left << setw(7) << rd[i].inform.type_sale << endl;
    cout << right << setw(80) << "-------------------------------------------------" << endl;
    cout << right << setw(64) << "** PRINT BILL ** " << endl;
    cout << right << setw(80) << "-------------------------------------------------" << endl;
    cout << right << setw(80) << "No.      Description                    Amount   " << endl;
    cout << endl;
    for (int l = 0; l < rd[i].n[i]; l++)
    {
        if (l < 10)
        {
            cout << right << setw(32) << "0" << l + 1;
            cout << right << setw(7 + rd[i].name[l].length()) << rd[i].name[l] << endl;
            cout << right << setw(38) << rd[i].qty[l] << " pcs * " << left << setw(15) << rd[i].retail_price[l];
            cout << right << setw(15) << rd[i].amount[l] << " $" << left << setw(10) << endl;
        }
        else
        {
            cout << right << setw(32) << l + 1;
            cout << right << setw(7 + rd[i].name[l].length()) << rd[i].name[l] << endl;
            cout << right << setw(38) << rd[i].qty[l] << " pcs * " << left << setw(15) << rd[i].retail_price[l];
            cout << right << setw(15) << rd[i].amount[l] << " $" << left << setw(10) << endl;
        }
    }
    cout << endl;
    cout << right << setw(80) << "-------------------------------------------------" << endl;
    cout << right << setw(80) << "-------------------------------------------------" << endl;
    cout << right << setw(40) << "Total USD" << left << setw(20) << right << setw(35) << rd[i].total_usd << " $" << left << setw(12) << endl;
    cout << right << setw(40) << "Total KHR" << left << setw(20) << right << setw(35) << fixed << setprecision(2) << rd[i].total_kh << " R" << left << setw(12) << endl;
    cout << right << setw(80) << "-------------------------------------------------" << endl;
    cout << right << setw(80) << "   VAT%     Net.Amt         VAT            Amount" << endl;
    cout << right << setw(32) << "$" << left << setw(2) << " " << vat;
    cout << left << setw(7) << " " << left << setw(8) << rd[i].net_amt << left << setw(8) << " " << left << setw(8) << rd[i].vat << right << setw(13) << rd[i].total_usd << endl;
    cout << right << setw(80) << "-------------------------------------------------" << endl;
    cout << right << setw(71) << "Thank you,  See you again soon!" << endl;
}
void reciept_detail(struct Order rd[], string product_name, float price, int i, int& j, string st)
{
    if (st == "update")
    {
        rd[i].name[j] = product_name;
        rd[i].retail_price[j] = price;
        rd[i].total_usd = rd[i].total_usd - rd[i].amount[j];
        rd[i].amount[j] = get_amount(rd[i].qty[j], price);
        rd[i].total_usd = get_total(rd[i].total_usd, rd[i].amount[j]);
    }
    else
    {
        rd[i].name[j] = product_name;
        rd[i].retail_price[j] = price;
        rd[i].qty[j] = get_numbers(st);
        rd[i].amount[j] = get_amount(rd[i].qty[j], price);
        rd[i].total_usd = get_total(rd[i].total_usd, rd[i].amount[j]);
        j++;
    }
}
void update_menu()
{
    show_message("\t=========UPDATE MENU=========\n");
    cout << "\t1.Update name" << endl;
    cout << "\t2.Update qty" << endl;
    cout << "\t3.Update name and qty" << endl;
    cout << "\t0.Back" << endl;
    cout << "\tPlease choose one option(1-3): ";
}
void sale_typeMenu()
{
    cout << "\t========SALE TYPE MENU========" << endl;
    cout << "\t1.DINE IN" << endl;
    cout << "\t2.Take Away" << endl;
    cout << "\t3.Delivery" << endl;
    cout << "\tPlease choose one option(1-3): ";
}
void search_menu()
{
    cout << "\t1.BY ID" << endl;
    cout << "\t2.By PhoneNumber" << endl;
    cout << "\t0.Back" << endl;
    cout << "\tPlease choose one option(1-2): ";
}
void writefile(struct login account)
{
    ofstream writeFile;
    writeFile.open("login.bat", ios::out | ios::binary);
    writeFile.write(reinterpret_cast<char*>(&account), sizeof(account));
    writeFile.close();
}
void change_password(struct login& account)
{
    bool flag;
    string currentPassword;
    string newPassword;
    string confirmPassword;
    do
    {
        system("cls");
        intro_changePassword();
        gotoxy(20, 9);
        clear_text(28, 9);
        currentPassword = get_passwordInput(20, 10, 20);
        gotoxy(20, 12);
        clear_text(28, 12);
        newPassword = get_passwordInput(20, 13, 20);
        gotoxy(20, 15);
        clear_text(26, 15);
        confirmPassword = get_passwordInput(20, 16, 20);
        flag = verify_newPassword(account, currentPassword, newPassword, confirmPassword);
        _getch();
    } while (flag != true);
}
void gotoxy(short x, short y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setcolor(int Color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}
bool verify(struct login account, string username, string password, int x, int y)
{
    if (password[0] == 0)
    {
        gotoxy(x, y + 6);
        setcolor(12);
        show_message("Please input your password...\n");
        _getch();
    }
    if (username == account.username && password == account.password)
    {
        gotoxy(x, y + 6);
        setcolor(2);
        show_message("Successfully!!!\n");
        _getch();
        return true;
    }
    else
    {
        gotoxy(x, y + 6);
        setcolor(12);
        show_message("Sorry,please try again!!!\n");
        _getch();
        return false;
    }
}
string get_name(int x, int y)
{
    string name;
    bool flag;
    do
    {
        clear_text(x + 13, y + 1);
        gotoxy(x, y + 1);
        getline(cin, name);
        if (check_string(name))
        {
            flag = true;
        }
        else
        {
            gotoxy(x, y + 8);
            setcolor(12);
            show_message("Please input your name...");
            flag = false;
            _getch();
            system("cls");
            front_display(x, y);
        }
    } while (!flag);
    return name;
} 
bool check_string(string name)
{
    if (name[0] == NULL)
    {
        return false;
    }
    return true;
}
string get_password(int x, int y)
{
    char password[20] = { 0 };
    char str;
    bool flag;
    int i = 0;
    gotoxy(x, y + 5);
    clear_text(x + 13, y + 5);
    do
    {
        if ((str = _getch()))
        {
            if (str == 13)
            {
                break;
            }
            else if (check_character(str, x, y, i))
            {
                password[i] = str;
                i++;
                flag = true;
            }
            else
            {
                flag = true;
            }
        }
    } while (flag);
    password[i] = '\0';
    return password;
}
void front_display(int x, int y)
{
    setcolor(15);
    setcolor(3);
    gotoxy(x, 5);
    cout << ("LOGIN");
    setcolor(15);
    gotoxy(x, y);
    cout << ("Username");
    gotoxy(x, y + 1);
    setcolor(8);
    cout << ("Enter username");
    setcolor(15);
    gotoxy(x, y + 3);
    cout << ("Password");
    gotoxy(x, y + 5);
    setcolor(8);
    cout << ("Enter Password");
    gotoxy(x, y + 1);
}
void clear_text(int x, int y)
{
    if (_getch() || _getch() == 8)
    {
        for (int i = 20; i < 34; i++)
        {
            gotoxy(x--, y);
            show_message(" ");
        }
    }
}
bool check_character(char str, int& x, int& y, int& i)
{
    if (str == 8)
    {
        if (x > 20)
        {
            gotoxy(x--, y + 5);
            show_message(" ");
            i--;
        }
        else if (x == 20)
        {
            gotoxy(x--, y + 5);
            show_message(" ");
            x++;
            i--;
        }
        return false;
    }
    else
    {
        gotoxy(x, y + 5);
        show_message("*");
        x++;
        return true;
    }
}
bool check_passwordInput(char str, int& x, int& y, int& i, int x1)
{
    if (str == 8)
    {
        if (x > x1)
        {
            gotoxy(x--, y - 1);
            show_message(" ");
            i--;
        }
        else if (x == x1)
        {
            gotoxy(x--, y - 1);
            show_message(" ");
            x++;
            i--;
        }
        return false;
    }
    else
    {
        gotoxy(x, y - 1);
        show_message("*");
        x++;
        return true;
    }
}
void intro_changePassword()
{
    setcolor(15);
    setcolor(3);
    gotoxy(20, 5);
    cout << ("Change password");
    setcolor(15);
    gotoxy(20, 8);
    cout << ("Current password");
    setcolor(8);
    gotoxy(20, 9);
    cout << "Password";
    setcolor(15);
    gotoxy(20, 11);
    cout << ("New password");
    setcolor(8);
    gotoxy(20, 12);
    cout << "Password";
    setcolor(15);
    gotoxy(20, 14);
    cout << ("Confirm new password");
    setcolor(8);
    gotoxy(20, 15);
    cout << "Cofirm";
}
void get_detail(struct Order rd[], float kh, float vat_percentage, int i, int j) {
    order_type_menu(rd, i);
    get_total_kh(rd, i, kh);
    get_net_amt(rd, i, vat_percentage);
    get_vat(rd, i, vat_percentage);
}
void view(struct Order rd[], int i, int vat) {
    for (int k = 0; k < i; k++)
    {
        all_order_view(rd, k, vat);
        cout << endl;
        cout << endl;
    }
}
int search(struct Order rd[], int i, string str, string st) {
    if (str == "id") {
        for (int k = 0; k < i; k++)
        {
            if (rd[k].inform.id == st)
            {
                return k;
            }
        }
    }
    else {
        for (int k = 0; k < i; k++)
        {
            if (rd[k].inform.phone_number == st)
            {
                return k;
            }
        }
    }
    return -1;
}
float check_price(string topping)
{
    // Pizza
    // Small Prices
    const float S_CHICKEN_PRICE = 8.99;
    const float S_SEAFOOD_PRICE = 8.99;
    const float S_SAUSAGE_PRICE = 8.99;
    // Large Prices
    const float L_CHICKEN_PRICE = 19.99;
    const float L_SEAFOOD_PRICE = 19.99;
    const float L_SAUSAGE_PRICE = 17.85;
    // Medium Prices
    const float M_CHICKEN_PRICE = 13.99;
    const float M_SEAFOOD_PRICE = 13.99;
    const float M_SAUSAGE_PRICE = 12.28;
    //  Drinks Prices
    const float STING_PRICE = 1.99;
    const float COCA_COLA_PRICE = 2.00;
    const float SPRITE_PRICE = 1.50;
    const float DRINKING_WATER_PRICE = 1.20;
    if (topping == "L-Chicken")
    {
        return L_CHICKEN_PRICE;
    }
    else if (topping == "M-Chicken")
    {
        return M_CHICKEN_PRICE;
    }
    else if (topping == "S-Chicken")
    {
        return S_CHICKEN_PRICE;
    }
    else if (topping == "L-Sausage")
    {
        return L_SAUSAGE_PRICE;
    }
    else if (topping == "M-Sausage")
    {
        return M_SAUSAGE_PRICE;
    }
    else if (topping == "S-Sausage")
    {
        return S_SAUSAGE_PRICE;
    }
    else if (topping == "L-Seafood")
    {
        return L_SEAFOOD_PRICE;
    }
    else if (topping == "M-Seafood")
    {
        return M_SEAFOOD_PRICE;
    }
    else if (topping == "S-Seafood")
    {
        return S_SEAFOOD_PRICE;
    }
    else if (topping == "Coca_Cola") {
        return COCA_COLA_PRICE;
    }
    else if (topping == "Drinking_Water") {
        return DRINKING_WATER_PRICE;
    }
    else if (topping == "Sprite") {
        return SPRITE_PRICE;
    }
    else if (topping == "Sting") {
        return STING_PRICE;
    }
}
void repet_show(string option_type, string str)
{
    show_message("\tError input,please try again\n");
    get_character("\tpress any key to continue...\n");
    if (option_type == "main_menu")
    {
        system("cls");
        main_menu();
    }
    else if (option_type == "food_menu")
    {
        system("cls");
        food_menu(str);
    }
    else if (option_type == "sub_orderMenu")
    {
        system("cls");
        sub_orderMenu();
    }
    else if (option_type == "topping_menu")
    {
        system("cls");
        pizza(str);
    }
    else if (option_type == "size_menu")
    {
        system("cls");
        size_menu();
    }
    else if (option_type == "drink_menu")
    {
        system("cls");
        drink_menu(str);
    }
    else if (option_type == "sub_update_menu")
    {
        cout << endl;
        update_menu();
    }
    else if (option_type == "sale_typeMenu")
    {
        system("cls");
        sale_typeMenu();
    }
    else if (option_type == "search_menu")
    {
        cout << endl;
        show_message("\t=========SEARCH MENU=========\n");
        search_menu();
    }
    else if (option_type == "delete_menu")
    {
        cout << endl;
        show_message("\t=========DELETE MENU=========\n");
        search_menu();
    }
    else if (option_type == "update_menu")
    {
        cout << endl;
        show_message("\t==========UPDATE MENU==========\n");
        search_menu();
    }
    else {
        system("cls");
        login_menu();
    }
}
void update(struct Order rd[], int i, int k, float price)
{
    rd[i].qty[k] = get_numbers("\tEnter qty: ");
    rd[i].total_usd = rd[i].total_usd - rd[i].amount[k];
    rd[i].amount[k] = get_amount(rd[i].qty[k], price);
    rd[i].total_usd = get_total(rd[i].total_usd, rd[i].amount[k]);
}
void sub_delete(struct Order rd[], int k, int& j, int i)
{
    for (int l = k; l < j; l++)
    {
        swap1(rd, i, l);
    }
    j = j - 1;
}
void swap1(struct Order rd[], int i, int l) {
    rd[i].name[l] = rd[i].name[l + 1];
    rd[i].qty[l] = rd[i].qty[l + 1];
    rd[i].retail_price[l] = rd[i].retail_price[l + 1];
    rd[i].amount[l] = rd[i].amount[l + 1];
}
string getString(string st, string str)
{
    string get;
    bool found = false;
    do
    {
        cout << st;
        cin.sync();
        getline(cin, get);
        if (str == "staffName") {
            found = validat_staff(get);
            if (!found)
            {
                show_message("\tstaff name must be 3 character contain letter and latin,Please try again!!!\n");
                get_character("\tPress any key to continue...\n");
                system("cls");
            }
        }
        else if (str == "phoneNumber") {
            found = validat_phoneNumber(get);
            if (!found)
            {
                show_message("\tphone number must be 8 character contain number ,Please try again!!!\n");
                get_character("\tPress any key to continue...\n");
            }
        }
        else if (str == "address") {
            found = true;
        }
        else if (str == "id") {
            found = validat_id(get);
            if (!found)
            {
                show_message("\tID must be 6 character contain number,Please try again!!!\n");
                get_character("\tPress any key to continue...\n");
            }
        }
    } while (!found);
    return get;
}
bool validat_id(string st)
{
    if (st[0] == NULL)
    {
        return false;
    }
    else if (st.length() < 6)
    {
        return false;
    }
    for (int i = 0; i < st.length(); i++)
    {
        if ((st[i] >= '0' && st[i] <= '9'))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
bool validat_staff(string st)
{
    if ((st[0] == NULL) || (!(st[0] >= 'A' && st[0] <= 'Z')))
    {
        return false;
    }
    else if (st.length() < 3)
    {
        return false;
    }
    for (int i = 0; i < st.length(); i++)
    {
        if ((st[i] >= 65 && st[i] <= 122) || st[i] == ' ')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
bool validat_phoneNumber(string st)
{
    if (st[0] == NULL)
    {
        return false;
    }
    else if (st.length() < 8)
    {
        return false;
    }
    for (int i = 0; i < st.length(); i++)
    {
        if ((st[i] >= '0' && st[i] <= '9'))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
void order_view(struct Order rd[], int n, int i)
{
    for (int k = 0; k < n; k++)
    {
        display(rd, k, i);
    }
    cout << endl;
}
void display(struct Order rd[], int k, int i)
{
    if (k < 10)
    {
        cout << right << setw(32) << "0" << k + 1 << left << setw(16) << " ";
        cout << left << setw(18) << rd[i].name[k];
        cout << right << setw(7) << rd[i].qty[k] << " * pcs" << endl;
    }
    else
    {
        cout << right << setw(32) << k + 1 << left << setw(16) << " ";
        cout << left << setw(18) << rd[i].name[k];
        cout << right << setw(7) << rd[i].qty[k] << " * pcs" << endl;
    }
    cout << endl;
}
void show_message(string st)
{
    cout << st;
}
int sub_search(int neutron, int j)
{
    for (int k = 0; k < j; k++)
    {
        if (neutron - 1 == k)
        {
            return k;
        }
    }
    return -1;
}
int get_numbers(string st)
{
    int number;
    string str;
    bool found;
    do
    {
        show_message(st);
        cin.sync();
        getline(cin, str);
        found = validat_number(str);
        if (found)
        {
            number = stoi(str);
        }
        else
        {
            show_message("\tError input,please try again\n");
            get_character("\tpress any key to continue...\n");
            cout << endl;
        }
    } while (!found);
    return number;
}
bool validat_number(string st)
{
    if (st[0] == NULL)
    {
        return false;
    }
    for (int i = 0; i < st.length(); i++)
    {
        if ((st[i] >= '0' && st[i] <= '9'))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
void get_total_kh(struct Order rd[], int i, float kh)
{
    rd[i].total_kh = rd[i].total_usd * kh;
}
void get_vat(struct Order rd[], int i, float percentage)
{
    rd[i].vat = rd[i].total_usd * percentage;
}
void get_net_amt(struct Order rd[], int i, float percentage)
{
    rd[i].net_amt = rd[i].total_usd - (percentage * rd[i].total_usd);
}
int get_option(string option_type, string str)
{
    int opTion;
    string st;
    bool found;
    do
    {
        cin.sync();
        getline(cin, st);
        found = validat_option(st);
        if (found)
        {
            opTion = stoi(st);
        }
        else
        {
            repet_show(option_type, str);
        }
    } while (!found);
    return opTion;
}
bool validat_option(string st)
{
    if (st[0] == NULL)
    {
        return false;
    }
    for (int i = 0; i < st.length(); i++)
    {
        if (st[i] >= '0' && st[i] <= '9')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
float get_amount(int qty, float price)
{
    return qty * price;
}
float get_total(float total, float amount)
{
    return total + amount;
}

void pizza(string st)
{
    topping_menu(st);
}
void all_order_view(struct Order rd[], int i, int vat)
{
    cout << endl;
    reciept();
    reciept(rd, i, vat);
}
void swap(struct Order& rd1, struct Order& rd2)
{
    struct Order temp;
    temp = rd1;
    rd1 = rd2;
    rd2 = temp;
}
void sort_order(struct Order rd[], int i)
{
    for (int k = 0; k < i - 1; k++)
    {
        for (int l = k; l < i; l++)
        {
            if (rd[k].total_usd < rd[l].total_usd)
            {
                swap(rd[k], rd[l]);
            }
        }
    }
}
bool deletes(struct Order rd[], int k, int& i, char ch)
{
    if (ch == 'y' || ch == 'Y')
    {
        for (int l = k; l < i; l++)
        {
            swap(rd[l], rd[l + 1]);
        }
        i = i - 1;
        return true;
    }
    else
    {
        return false;
    }
}
void get_date(struct Order rd[], int i)
{
    time_t now = time(NULL);
    tm* ltm = localtime(&now);
    rd[i].date.hour = (1 + ltm->tm_hour) - 1;
    rd[i].date.minute = (1 + ltm->tm_min) - 1;
    rd[i].date.month = (1 + ltm->tm_mon);
    rd[i].date.year = (1 + ltm->tm_year + 1900) - 1;
    rd[i].date.day = (1 + ltm->tm_mday) - 1;
}
void get_character(string st)
{
    show_message(st);
    _getch();
}
void payment_update(struct Order rd[], int i, float kh, float vat_percentage)
{
    get_total_kh(rd, i, kh);
    get_net_amt(rd, i, vat_percentage);
    get_vat(rd, i, vat_percentage);
}
string get_usernameInput(int x, int y)
{
    string name;
    bool flag;
    do
    {
        gotoxy(x, y - 1);
        getline(cin, name);
        if (check_string(name))
        {
            flag = true;
        }
        else
        {
            gotoxy(x, y + 2);
            setcolor(12);
            show_message("Please input your name...");
            flag = false;
            _getch();
            system("cls");
        }
    } while (!flag);
    return name;
}
string get_passwordInput(int x, int y, int x1)
{
    char password[20] = { 0 };
    char str;
    bool flag;
    int i = 0;
    gotoxy(x, y - 1);
    do
    {
        if ((str = _getch()))
        {
            if (str == 13)
            {
                break;
            }
            else if (check_passwordInput(str, x, y, i, x1))
            {
                password[i] = str;
                i++;
                flag = true;
            }
            else
                flag = true;
        }
    } while (flag);
    password[i] = '\0';
    return password;
}
void get_inform(struct Order rd[], int i, string type) {
    rd[i].inform.type_sale = type;
    rd[i].inform.staff = getString("\tInput staff name: ", "staffName");
    rd[i].inform.id = getString("\tInput id: ", "id");
    if (type == "DINE IN") {
        rd[i].inform.table_numbers = get_numbers("\tInput table: ");
    }
    else if (type == "TAKE AWAY") {
        rd[i].inform.phone_number = getString("\tInput phone number: ", "phoneNumber");
    }
    else {
        rd[i].inform.phone_number = getString("\tInput phone number: ", "phoneNumber");
        rd[i].inform.address = getString("\tInput address: ", "address");
    }
    get_date(rd, i);
    system("cls");
}
void intro_reciept_header() {
    reciept();
    cout << right << setw(80) << "No.               Description                 Qty" << endl;
}
void get_detail(struct Order rd[], string productName, float price, int i, int& j, string st) {
    if (st == "update")
    {
        reciept_detail(rd, productName, price, i, j, st);
        show_message("\tUpdate successfully!!!\n");
    }
    else if (st == "order_update")
    {
        reciept_detail(rd, productName, price, i, j, "update");
        show_message("\tUpdate successfully!!!\n");
        st = "order_update";
    }
    else
    {
        reciept_detail(rd, productName, price, i, j, "\tEnter qty: ");
    }
}
bool verify_newPassword(struct login& account, string currentPassword, string newPassword, string confirmPassword) {
    if (currentPassword != account.password)
    {
        return false;
        setcolor(12);
        gotoxy(20, 16);
        show_message("Currentpassword incorrect!!!");
    }
    else if (newPassword != confirmPassword)
    {
        return false;
        setcolor(12);
        gotoxy(20, 16);
        show_message("Password not match!!!");
    }
    else if ((currentPassword == account.password) && (newPassword == confirmPassword))
    {
        return true;
        setcolor(2);
        gotoxy(20, 16);
        show_message("Password updated!!!");
        account.password = newPassword;
        account.username = "Admin";
    }
    else
    {
        return false;
        setcolor(12);
        gotoxy(20, 16);
        show_message("Invalid!!!");
    }
}
void login_menu() {
    cout << "\t=====  WELCOME TO THE PIZZA RESTRAURANT  =====\n" << endl;
    cout << "\t1.LOGIN" << endl;
    cout << "\t2.CHANGE PASSWORD" << endl;
    cout << "\t0.EXIT" << endl;
    cout << "\tPlease choice one option:";
}
