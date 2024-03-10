// Program: Tic-Tac-Toe with numbers: Player 1 can place odd numbers and player 2 can place even ones, the first player that creates a line with numbers that add up to 15 is the winner.
// Game 2 - Tic-Tac-Toe with Numbers
// Author:  Hassan Ali Hassan Ali Ismail - 20230588
// Version: 4.0
// Date:    01/03/2024

#include <bits/stdc++.h>
#define el '\n'
#define space ' '
using namespace std;

// displays the initial screen
void initialScreen() {
    cout << "Tic-Tac-Toe with numbers! Player 1 can place odd numbers and player 2 can place even ones, the first player that creates a line with numbers that add up to 15 is the winner (lines can be comprised of both even and odd numbers)" << el;
}

// displays the first menu, takes the input from the user, and validates it
char firstMenu() {
    cout << "A) Start Game\nB) Exit Game\n";
    char choice;
    cin >> choice;
    choice = toupper(choice);
    if (choice == 'A' || choice == 'B') {
        return choice;
    } else {
        cout << "Invalid input1213...\n";
        return firstMenu();
    }
}

// prototypes
int playerNumberInput(int player, vector<vector<char>> board, vector<vector<int>> playerNumbers, int i = 0);

vector<int> playerPositionInput(int player, vector<vector<char>> board, int i = 0);

bool isNumeric(string input);

bool validNumber(int player, vector<vector<int>> playerNumbers, string input);

bool validPosition(vector<vector<char>> board, int hPosition, int vPosition);

void updateBoard(int player, vector<vector<char>> &board, int hPosition, int vPosition, int number);

int winnerCheck(vector<vector<char>> board);

void updatePlayerNumbers(int player, vector<vector<int>> &playerNumbers, int number);

void displayBoard(vector<vector<char>> board);

int main() {
    initialScreen();
    while (true) {
        vector<vector<int>> players = {{1, 3, 5, 7, 9}, // arrays storing the numbers that the players are allowed to use, they will be modified after each turn
                                       {0, 2, 4, 6, 8}};
        vector<vector<char>> board = {{' ', '1', '2', '3'}, // array storing the board
                                      {'1', '#', '#', '#'},
                                      {'2', '#', '#', '#'},
                                      {'3', '#', '#', '#'}};
        int player = 2; // player tracker
        if (firstMenu() == 'B') { // exiting the game if user chooses b in first menu
            cout << "Exiting the game..." << el;
            return 0;
        }
        cout << "Note: vacant positions are denoted by \"#\"\n";
        while (true) {
            player = (player == 1) ? 2 : 1; // player tracker logic
            displayBoard(board);
            int number = playerNumberInput(player, board, players); // takes the number from user
            vector<int> position = playerPositionInput(player, board); // array containing the row and column the user chose
            updateBoard(player, board, position[0], position[1], number); // updates board
            updatePlayerNumbers(player, players, number); // updates the numbers the players are allowed to use
            int winStatus = winnerCheck(board); // checks for a win or tie
            if (winStatus == 1) { // if player won
                cout << "Player " << player << " is the winner!" << el;
                break;
            } else if (winStatus == -1) { // if tie
                cout << "Tie..." << el;
                break;
            }
        }
    }
}

// a function that takes the number from the player and validates it
int playerNumberInput(int player, vector<vector<char>> board, vector<vector<int>> playerNumbers, int i) {
    if (i == 0) { // displays the turn status on first call only
        cout << "Player " << player << "'s turn" << el;
    }
    cout << "Please choose a number to place from the following:" << el;
    for (auto number: playerNumbers[player - 1]) { // displays available numbers to use
        cout << number << space;
    }
    cout << el;
    string input;
    cin >> input; // takes input as a string
    if (isNumeric(input)) { // validates the input is numeric
        if (validNumber(player, playerNumbers, input)) { // validates the input is from the allowed numbers
            return stoi(input);
        }
    }
    cout << "Invalid Input, please try again..." << el;
    return playerNumberInput(player, board, playerNumbers, 1); // repeats the function if input is invalid
}

// a function that takes the position from the player and validates it
vector<int> playerPositionInput(int player, vector<vector<char>> board, int i) {
    if (i == 0) { // displays the message on first call only
        cout << "Player " << player << ", choose a vacant position to place your number at." << el;
    }
    string hPosition, vPosition;
    cout << "Input the row and column separated by a space ";
    cin >> hPosition >> vPosition; // takes horizontal and vertical positions as strings
    if (isNumeric(hPosition) && isNumeric(vPosition) && isNumeric(hPosition)) { // validates that both positions are numbers
        if (validPosition(board, stoi(hPosition), stoi(vPosition))) { // validates that both positions are vacant and available
            return {stoi(hPosition), stoi(vPosition)};
        }
    }
    cout << "Invalid input, please try again..." << el;
    return playerPositionInput(player, board, 1); // repeats the function if input is invalid
}

// checks if input is numeric
bool isNumeric(string input) {
    for (char i: input) { // checks if each digit in the string is a number
        if (!isdigit(i)) {
            return false;
        }
    }
    return true;
}

// checks if the chosen number is valid
bool validNumber(int player, vector<vector<int>> playerNumbers, string input) {
    for (auto i: playerNumbers[player - 1]) { // checks if the chosen number is one of the allowed numbers from the current player
        if (stoi(input) == i) {
            return true;
        }
    }
    return false;
}

// checks if the chosen position is valid
bool validPosition(vector<vector<char>> board, int hPosition, int vPosition) {
    if (hPosition > 0 && hPosition < 4 && vPosition > 0 && vPosition < 4) { // checks if the positions are inside the board
        return (board[hPosition][vPosition] == '#'); // checks if the position is vacant
    }
    return false;
}

// displays the board
void displayBoard(vector<vector<char>> board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) { // loops over each cell and prints it
            cout << board[i][j] << space;
        }
        cout << el;
    }
}

// updates the board
void updateBoard(int player, vector<vector<char>> &board, int hPosition, int vPosition, int number) {
    board[hPosition][vPosition] = (char) number + '0';
}

// updates the allowed numbers for the current player
void updatePlayerNumbers(int player, vector<vector<int>> &playerNumbers, int number) {
    playerNumbers[player - 1].erase(find(playerNumbers[player - 1].begin(), playerNumbers[player - 1].end(), number));
}

// checks if the player won or if it is a tie
int winnerCheck(vector<vector<char>> board) {
    int cnt = 0;
    /* the following if block checks a certain line is not vacant in any of its cells
     * if not vacant, it increments the counter and checks if the sum of its cells is 15
     * if equal to 15, it returns that the player has won
     * if not equal to 15, it moves onto the next line and does the same
     * the number of probable lines is 8, and the counter is incremented with each non-vacant line
     * meaning that if the counter reaches 8, then every line is not vacant and none of them is 15, so it's a tie
     */
    if (board[1][1] != '#' && board[2][1] != '#' && board[3][1] != '#') {
        int V1 = board[1][1] + board[2][1] + board[3][1];
        cnt++;
        if (V1 == 159) return 1;
    }
    if (board[1][2] != '#' && board[2][2] != '#' && board[3][2] != '#') {
        int V2 = board[1][2] + board[2][2] + board[3][2];
        cnt++;
        if (V2 == 159) return 1;
    }
    if (board[1][3] != '#' && board[2][3] != '#' && board[3][3] != '#') {
        int V3 = board[1][3] + board[2][3] + board[3][3];
        cnt++;
        if (V3 == 159) return 1;
    }
    if (board[1][1] != '#' && board[1][2] != '#' && board[1][3] != '#') {
        int H1 = board[1][1] + board[1][2] + board[1][3];
        cnt++;
        if (H1 == 159) return 1;
    }
    if (board[2][1] != '#' && board[2][2] != '#' && board[2][3] != '#') {
        int H2 = board[2][1] + board[2][2] + board[2][3];
        cnt++;
        if (H2 == 159) return 1;
    }
    if (board[3][1] != '#' && board[3][2] != '#' && board[3][3] != '#') {
        int H3 = board[3][1] + board[3][2] + board[3][3];
        cnt++;
        if (H3 == 159) return 1;
    }
    if (board[1][1] != '#' && board[2][2] != '#' && board[3][3] != '#') {
        int D1 = board[1][1] + board[2][2] + board[3][3];
        cnt++;
        if (D1 == 159) return 1;
    }
    if (board[1][3] != '#' && board[2][2] != '#' && board[3][1] != '#') {
        int D2 = board[1][3] + board[2][2] + board[3][1];
        cnt++;
        if (D2 == 159) return 1;
    }
    if (cnt == 8) return -1;
    else return 0;
}
