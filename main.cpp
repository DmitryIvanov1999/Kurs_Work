#include <iostream>
#include <string>
#include <graphics.h>
#include "Sapper.h"
using namespace std;
bool is_number(string param)
{
    for (int i = 0; i < param.length(); i++)
    {
        if (param[i] != 45)
        {
            if ((param[i] < 48) || (param[i] > 57))
                return false;
        }
    }
    return true;
}
int main()
{
    string answer;
    int param;
    int rows, cols, seconds, mines;
    One_Sapper &Game_Object = One_Sapper::Instance();//The instance of main game object
    while(1)
    {
        while(1)
        {
            system("cls");
            cout << "1 - Play\n2 - Exit\n";
            cin >> answer;
            if(is_number(answer) == false)
            {
                cout << "Incorrect!\n";
                system("pause");
                continue;
            }
            else
                param = atoi(answer.c_str());
            if(param > 2 || param < 1)
            {
                cout << "Incorrect!\n";
                system("pause");
                continue;
            }
            else
                break;
        }
        if(param == 2)
           break;
        else
        {
            while(1)
            {
                system("cls");
                cout << "Enter the number of lines:\n";
                cin >> answer;
                if(is_number(answer) == false)
                {
                    cout << "Incorrect!\n";
                    system("pause");
                    continue;
                }
                else
                    rows = atoi(answer.c_str());
                if(rows <= 0)
                {
                    cout << "Incorrect!\n";
                    system("pause");
                    continue;
                }
                else
                {
                    Game_Object.set_rows(rows);
                    break;
                }
            }
            while(1)
            {
                system("cls");
                cout << "Enter the number of columns:\n";
                cin >> answer;
                if(is_number(answer) == false)
                {
                    cout << "Incorrect!\n";
                    system("pause");
                    continue;
                }
                else
                    cols = atoi(answer.c_str());
                if(cols <= 0)
                {
                    cout << "Incorrect!\n";
                    system("pause");
                    continue;
                }
                else
                {
                    Game_Object.set_cols(cols);
                    break;
                }
            }
            while(1)
            {
                system("cls");
                cout << "Enter the number of mines:\n";
                cin >> answer;
                if(is_number(answer) == false)
                {
                    cout << "Incorrect!\n";
                    system("pause");
                    continue;
                }
                else
                    mines = atoi(answer.c_str());
                if(mines >= (Game_Object.get_cols() * Game_Object.get_rows()))
                {
                    cout << "Incorrect!\n";
                    system("pause");
                    continue;
                }
                else
                {
                    Game_Object.set_mines(mines);
                    break;
                }
            }
            while(1)
            {
                system("cls");
                cout << "Do you need time limit?\n";
                cout << "y - YES\n";
                cout << "n - NO\n";
                cin >> answer;
                if(answer != "y" && answer != "n")
                {
                    cout << "Incorrect!\n";
                    system("pause");
                    continue;
                }
                if(answer == "n")
                {
                    Game_Object.set_timer_mode(false);
                    Game_Object.set_seconds(0);
                }
                else
                {
                    Game_Object.set_timer_mode(true);
                    while(1)
                    {
                        system("cls");
                        cout << "Enter the number of seconds:\n";
                        cin >> answer;
                        if(is_number(answer) == false)
                        {
                            cout << "Incorrect!\n";
                            system("pause");
                            continue;
                        }
                        else
                            seconds = atoi(answer.c_str());
                        if(seconds <= 0)
                        {
                            cout << "Incorrect!\n";
                            system("pause");
                            continue;
                        }
                        else
                        {
                            Game_Object.set_seconds(seconds);
                            break;
                        }
                    }
                }
                break;
            }
            Game_Object.set_matrix();
        }
    }
    cout << "Goodbye!\n";
    return 0;
}
