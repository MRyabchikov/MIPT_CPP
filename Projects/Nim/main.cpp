#include <iostream>
#include <vector>
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

vector<int> init_field ()
{
    vector<int> field{3, 4, 5};
    return field;
}

bool game_is_end (const vector<int>& field)
{
    for (auto x : field)
        if (x)
            return false;
    return true;
}

const int player_turn = 1;
const int bot_turn = 0;

void change_turn (int& current_turn)
{
    if (current_turn == player_turn)
        current_turn = bot_turn;
    else
        current_turn = player_turn;
}

void print_n_char (char c, int n)
{
    for (int i = 0; i < n; i++)
        cout << c;
}

void print_field_condition (const vector<int>& field)
{
    cout << "\t\t\tCurrent field condition: \n";
    for (int i = 0; i < static_cast<int>(field.size()); i++)
    {
        print_n_char('*', field[i]);
        printf("    (%d stones)\n", field[i]);
    }
}

bool is_valid_value (const vector<int>& field, int row, int ammount)
{
    return row > 0 && row <= static_cast<int>(field.size()) &&
           ammount <= field[row - 1] && ammount > 0;
}

int handle_player_turn (vector<int>& field)
{
    while (true)
    {
        cout << "Enter your turn: ";
        int row, ammount;
        cin >> row >> ammount;
        if (!cin)
        {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        if (row == 0 && ammount == 0)
            return 0;
        if (is_valid_value(field, row, ammount))
        {
            field[row - 1] -= ammount;
            return 1;
        }
    }
}

int calculate_nim_sum (const vector<int>& field)
{
    int res = field[0];
    for (int i = 1; i < static_cast<int>(field.size()); i++)
        res ^= field[i];
    return res;
}

void make_random_turn (vector<int>& field)
{
    int row = rand() % field.size();
    int ammount = rand() % field[row];
    field[row] -= ammount;
}

void handle_bot_turn (vector<int>& field)
{
    if (calculate_nim_sum(field) == 0)
        make_random_turn(field);
    else
        for (int i = 0; i < static_cast<int>(field.size()); i++)
            for (int j = 1; j < field[i]; j++)
            {
                field[i] -= j;
                if (calculate_nim_sum(field) == 0)
                    return;
                else
                    field[i] += j;
            }
}

void game ()
{
    vector<int> field = init_field();
    int current_turn = rand() % 2 ? player_turn : bot_turn;
    while (!game_is_end(field))
    {
        print_field_condition(field);
        if (current_turn == player_turn)
        {
            if (handle_player_turn(field) == 0)
            {
                cout << "Game over with your capitulation\n";
                return;
            }
            else
                handle_bot_turn(field);
        }
        change_turn(current_turn);
    }
    if (current_turn == bot_turn)
        cout << "Congratulations! You beat the machine!\n";
    else
        cout << "Unfortunately you lose. Try again!\n";
    return;
}

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