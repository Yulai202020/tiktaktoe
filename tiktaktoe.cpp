#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <list>

#include <iostream>
#include <list>

struct Coords {
    int row;
    int column;
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

Coords player1(){
    std::cout << "Player 1 : write row's id (1-3) ";
    int row;
    std::cin >> row;

    std::cout << "Player 1 : write column's id (1-3) ";
    int column;
    std::cin >> column;

    row--;
    column--;

    if (row > 3 || column > 3) {
        std::cout << "Sorry invalid input" << "\n";
    }

    Coords coords;
    coords.row = row;
    coords.column = column;
    return coords;
}

Coords player2(){
    std::cout << "Player 2 : write row's id (1-3) ";
    int row;
    std::cin >> row;

    std::cout << "Player 2 : write column's id (1-3) ";
    int column;
    std::cin >> column;

    row--;
    column--;

    if (row > 3 || column > 3) {
        std::cout << "Sorry invalid input" << "\n";
        return {4,4};
    }

    Coords coords;
    coords.row = row;
    coords.column = column;
    return coords;
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
    Coords coords;

    Stat station;
    station.game_on = true;
    station.winner = "";

    clearScreen();

    std::string table[3][3];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            table[i][j] = " ";
        }
    }

    while (station.game_on) {
        // player 1
        clearScreen();
        printScreen(table);

        coords = player1();
        table[coords.row][coords.column] = "o";

        // check winner
        station = check_winner(table);

        // check draw
        station.game_on = !check_draw(table);

        if (station.game_on == false) {
            clearScreen();
            printScreen(table);
            break;
        }

        // player 2 
        clearScreen();
        printScreen(table);

        coords = player2();
        table[coords.row][coords.column] = "x";

        // check winner
        station = check_winner(table);

        // check draw
        station.game_on = !check_draw(table);
        std::cout << station.game_on;
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
