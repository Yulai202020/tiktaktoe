#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <list>
#include <cstring>

#include <iostream>
#include <list>

struct Coords {
    int row;
    int column;
    std::string table[3][3];
};

struct Stat {
    bool game_on;
    std::string winner; // if game_on is true winner is "" or null
};

bool check_draw(std::string table[3][3]) {
    int count = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (table[i][j] == " ") { count++; }
        }
    }
    if (count == 0) {
        return true;
    }
    else {
        return false;
    }
}

Coords player(int id, std::string table[][3]){
    while (true){
    std::cout << "Player " << id << ": enter row's id (1-3) ";
    int row;
    std::cin >> row;

    std::cout << "Player " << id << ": enter column's id (1-3) ";
    int column;
    std::cin >> column;

    row--;
    column--;

    if (row > 3 || column > 3) {
        std::cout << "Sorry invalid input" << "\n";
        continue;
    } else if (table[row][column] != " ") {
        std::cout << "This cell is not empty" << "\n";
        continue;
    } else {
        std::string players_char = "";
        if (id == 1){
            players_char = "o";
        } else {
            players_char = "x";
        }
        table[row][column] = players_char;
        // break;
    }

    Coords coords;
    coords.row = row;
    coords.column = column;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            coords.table[i][j] = table[i][j];
        }
    }

    return coords;
    }

}

void clearScreen() {
    system("clear");
}

void printScreen(std::string table[3][3]) {
    std::cout << "-------" << "\n";

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << "|" << table[i][j];
        }
        std::cout << "|" << std::endl;
        std::cout << "-------" << "\n";
    }
}

Stat check_winner(std::string table[3][3]){
    int game_on = true;
    std::string winner;

    // vertical
    if (table[0][0] == table[0][1] && table[0][0] == table[0][2] && table[0][0] != " ") {
        game_on = false;
        winner = table[0][0];
    } else if (table[1][0] == table[1][1] && table[1][0] == table[1][2] && table[1][0] != " ") {
        game_on = false;
        winner = table[1][0];
    } else if (table[2][0] == table[2][1] && table[2][0] == table[2][2] && table[2][0] != " ") {
        game_on = false;
        winner = table[2][0];
    }

    // horizontal
    else if (table[0][0]== table[1][0] && table[0][0] == table[2][0] && table[0][0] != " ") {
        game_on = false;
        winner = table[0][0];
    } else if (table[0][1]== table[1][1] && table[0][1] == table[2][1] && table[0][1] != " ") {
        game_on = false;
        winner = table[0][1];
    } else if (table[0][2]== table[1][2] && table[0][2] == table[2][2] && table[0][2] != " ") {
        game_on = false;
        winner = table[0][2];
    }

    // like bishop in chess (idk how its on eng)

    else if (table[0][0]== table[1][1] && table[0][0] == table[2][2] && table[0][0] != " ") {
        game_on = false;
        winner = table[0][0];
    } else if (table[0][2]== table[1][1] && table[0][2] == table[2][0] && table[0][2] != " ") {
        game_on = false;
        winner = table[0][2];
    }

    Stat station;

    station.game_on = game_on;
    station.winner = winner;

    return station;
}


int main() {

    std::string table[3][3];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            table[i][j] = " ";
        }
    }

    Coords coords;

    // copy table to coords
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            coords.table[i][j] = table[i][j];
        }
    }

    Stat station;
    station.game_on = true;
    station.winner = "";

    clearScreen();

    while (station.game_on) {
        // player 1
        printScreen(coords.table);

        coords = player(1, coords.table);
       
        // check winner
        station = check_winner(coords.table);

        // check draw
        station.game_on = !check_draw(coords.table);

        if (station.game_on == false) {
            clearScreen();
            printScreen(coords.table);
            break;
        }
        
        clearScreen();

        /// player 2
        printScreen(coords.table);

        coords = player(2, coords.table);

        // check winner
        station = check_winner(coords.table);

        // check draw
        station.game_on = !check_draw(coords.table);

        // clear screen
        clearScreen();
    }

    if (station.winner == "o") {
        std::cout << "Player 1 WON !!!" << "\n";
    } else if (station.winner == "x") {
        std::cout << "Player 2 WON !!!" << "\n";
    } else {
        std::cout << "FREINDSHIP won !!!" << "\n";
    }

    return 0;
}
