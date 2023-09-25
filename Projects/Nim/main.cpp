#include <iostream>
using namespace std;

void print_greetings (void)
{
    cout << "\t\t\tWelcome to game Nim!\n";
    cout << "Available commands:\n";
    cout << "s - Start game\n";
    cout << "r - Print rules\n";
    cout << "q - Exit game\n";
    cout << "Enter command:\n>";
}

void print_rules (void)
{
    cout << "\t\t\tNim game rules:\n";
    cout << "- Num is a turn-based game\n";
    cout << "- Game statement is defined by several rows and ammount of "
            "stones in it\n";
    cout << "- At every turn you(or your opponent) must take N stones from "
            "only one row\n";
    cout
        << "- N is a natural number in section [1; K] where K - ammount of "
           "stones in target row\n";
    cout << "- The person who took the last stone is a winner\n";
    cout
        << "- You should enter your turn in format L M where L - number of "
           "a row, M - ammount of stones you take\n";
    cout << "- You may quit the game at every moment by entering 0 0 \n";
}

void game () { return; }

int main (void)
{
    print_greetings();
    char command;
    cin >> command;
    switch (command)
    {
    case 's':
        game();
        break;
    case 'q':
        cout << "Bye bye\n";
        return 0;
    case 'r':
        print_rules();
        break;
    default:
        cout << "Unknown command!";
        return 1;
    }
    return 0;
}