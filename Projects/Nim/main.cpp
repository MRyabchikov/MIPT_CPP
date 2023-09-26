#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

vector<int> heaps_data{3, 4, 5};

vector<int> init_field (const vector<int>& heaps_data)
{
    vector<int> field;
    for (int i = 0; i < static_cast<int>(heaps_data.size()); i++)
        field.push_back(heaps_data[i]);
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

void print_turn_state (int current_turn)  // FIXME: rename, use state
{
    if (current_turn == player_turn)
        cout << "Your turn\n";
    else
        cout << "Machine turn\n";
}

void print_game_state (const vector<int>& field, int current_turn)  // FIXME: rename, use state
{
    cout << "\t\t\tCurrent field condition: \n";
    print_turn_state(current_turn);
    for (int i = 0; i < static_cast<int>(field.size()); i++)
    {
        print_n_char('*', field[i]);
        printf_s("    (%d field, %d stones)\n", i + 1, field[i]);
    }
}

bool is_valid_value (const vector<int>& field, int row, int ammount)
{
    return row > 0 && row <= static_cast<int>(field.size()) && ammount <= field[row - 1] && ammount > 0;
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
    int row, ammount;
    do
    {
        row = rand() % field.size();
        ammount = rand() % (field[row] + 1);
    }
    while (!is_valid_value(field, row + 1, ammount));
    field[row] -= ammount;
}

void handle_bot_turn (vector<int>& field)
{
    if (calculate_nim_sum(field) == 0)
        make_random_turn(field);
    else
        for (int i = 0; i < static_cast<int>(field.size()); i++)
            for (int j = 1; j <= field[i]; j++)
            {
                field[i] -= j;
                if (calculate_nim_sum(field) == 0)
                    return;
                else
                    field[i] += j;
            }
}

void game (const vector<int>& heaps_data)
{
    vector<int> field = init_field(heaps_data);
    int current_turn = rand() % 2 ? player_turn : bot_turn;
    while (!game_is_end(field))
    {
        print_game_state(field, current_turn);
        if (current_turn == player_turn)
        {
            if (handle_player_turn(field) == 0)
            {
                cout << "Game over with your capitulation\n";
                return;
            }
        }
        else
            handle_bot_turn(field);
        change_turn(current_turn);
    }
    if (current_turn == bot_turn)
        cout << "Congratulations! You beat the machine!\n";
    else
        cout << "Unfortunately you lose. Try again!\n";
    return;
}

const char start_command = 's';
const char exit_command = 'q';
const char rules_command = 'r';
const char settings_command = 'c';

void print_menu (void)
{
    cout << "Available commands:\n";
    cout << start_command << " - Start game\n";
    cout << rules_command << " - Print rules\n";
    cout << exit_command << " - Exit game\n";
    // cout << settings_command << " - Change game settings\n"
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
    cout << "- N is a natural number in section [1; K] where K - ammount of "
            "stones in target row\n";
    cout << "- The person who took the last stone is a winner\n";
    cout << "- You should enter your turn in format L M where L - number of "
            "a row, M - ammount of stones you take\n";
    cout << "- You may quit the game at every moment by entering 0 0\n";
}

// void print_current_settings (const vector<int> heaps_data)
// {
//     cout << "Current stones distrubution: \n";
//     for (int i = 0; i < heaps_data.size(); i++)
//         cout << "Heap " << i << ": " << heaps_data[i] << "\n";
// }

// void clear_heaps_data (vector<int> heaps_data)
// {
//     while (heaps_data.size())
//         heaps_data.pop_back();
// }

// void change_settings_mode (vector<int>& heaps_data)
// {
//     print_current_settings(heaps_data);
//     clear_heaps_data(heaps_data);
//     while (true)
//     {
//         cout << "Enter ammount of heaps: ";
//         int heaps_ammount = 0;
//         cin >> heaps_ammount;
//         if (cin)
//         {
//             for (int i = 0; i < heaps_ammount; i++){

//             }
//         }
//     }
// }

int main (void)
{
    srand(time(NULL));
    cout << "\t\t\tWelcome to game Nim!\n";
    while (true)
    {
        print_menu();
        char command;
        cin >> command;
        switch (command)
        {
        case start_command:
            game(heaps_data);
            break;
        case exit_command:
            cout << "Bye bye\n";
            return 0;
        case rules_command:
            print_rules();
            break;
            // case settings_command:
            //     change_settings_mode();

        default:
            cout << "Unknown command! Try again\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    return 0;
}