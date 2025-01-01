#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <limits>

using namespace std;

const int BOARD_SIZE = 8;

// Chess board setup
vector<vector<string>> board = {
    {"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
    {"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
    {"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}
};

// Display the chess board
void displayBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].empty()) {
                cout << "-- ";
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Get the position from the user
pair<int, int> getPosition(const string& prompt) {
    int row, col;
    cout << prompt;
    cin >> row >> col;

    if (cin.fail() || row < 1 || row > BOARD_SIZE || col < 1 || col > BOARD_SIZE) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Invalid input. Please enter row and column between 1 and 8.");
    }

    return {row - 1, col - 1}; // Convert to 0-based index
}

// Move a piece
bool movePiece(pair<int, int> start, pair<int, int> end) {
    int startRow = start.first;
    int startCol = start.second;
    int endRow = end.first;
    int endCol = end.second;

    if (startRow < 0 || startRow >= BOARD_SIZE || startCol < 0 || startCol >= BOARD_SIZE ||
        endRow < 0 || endRow >= BOARD_SIZE || endCol < 0 || endCol >= BOARD_SIZE) {
        cout << "Invalid move: Out of bounds." << endl;
        return false;
    }

    if (board[startRow][startCol].empty()) {
        cout << "Invalid move: No piece at the starting position." << endl;
        return false;
    }

    if (!board[endRow][endCol].empty() && board[startRow][startCol][0] == board[endRow][endCol][0]) {
        cout << "Invalid move: Cannot capture your own piece." << endl;
        return false;
    }

    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol].clear();
    return true;
}

int main() {
    cout << "Welcome to the Chess Game!" << endl;

    while (true) {
        try {
            displayBoard();

            auto start = getPosition("Enter the starting position (row and column): ");
            auto end = getPosition("Enter the ending position (row and column): ");

            if (movePiece(start, end)) {
                cout << "Move successful." << endl;
            } else {
                cout << "Move failed. Try again." << endl;
            }

        } catch (const exception& e) {
            cout << e.what() << endl;
            continue;
        }

        char choice;
        cout << "Do you want to continue? (y/n): ";
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            break;
        }
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}
