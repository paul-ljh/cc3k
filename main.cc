#include <iostream>
#include <fstream>
#include <string>
#include "game.h"
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){

    int seed = static_cast<int>(time(0));
    srand(seed);

    string MAP_FILE_NAME;

    //commandl line arguments control
    if(argc > 1) {
        MAP_FILE_NAME = argv[1];
    } else {
        cout << "Please give a map file" << endl;
        return 1;
    }

    //prepares to read the map file
    ifstream map_file (MAP_FILE_NAME);
    string line;
    string map_layout = "";


    //reads the map from the specified file
    if (map_file.is_open()) {
        while ( getline(map_file, line) ) {
            map_layout+=line;
        }
        map_file.close();
    }

    //reads the chambers
    ifstream chamber_file ("chamber.txt");
    string chamber_layout = "";


    //reads the map from the specified file
    if (chamber_file.is_open()) {
        while ( getline(chamber_file, line) ) {
            chamber_layout+=line;
        }
        chamber_file.close();
    }


    // START GAME
    string command;
    string direction;
    string race;

    cout << "Please enter a race to continue or 'q' to quit" << endl;
    cout << "Races: 'shade', 'drow', 'vampire', 'troll', 'goblin'" << endl;
    cin >> race;
    if(race == "q") return 1;

    while (true){

        Game g{map_layout, chamber_layout};
        g.init(race);
        int game_status = 1;

        do {
            if (command == "q"){
                return 1;
            } else if (command == "r") {
                //g.restart();
                cout << "restarts the game : to be implemented " << endl;
                //cout << g;
            } else if (command == "a"){
                cin >> direction;
                g.attack(direction);
            } else if (command == "u"){
                cin >> direction;
                g.usePotion(direction);
                game_status = g.nextTurn();
            } else if (command[0] == 'n' || command[0] == 's' || command[0] == 'w' || command[0] == 'e'){
                g.movePlayer(command);
                game_status = g.nextTurn();
            } else if (command == "move"){
                //this is admin move
                cin >> command;
                int x = 0;
                int y = 0;

                if(command == "v") {
                    cin >> x;
                } else if (command == "h") {
                    cin >> y;
                }


                g.movePlayer(-x, y);
                game_status = g.nextTurn();
            } else if (command  == "floor"){
                int win_status = g.changeFloor(1);

                if(win_status != -1) {
                    cout << "Your score is " << win_status << endl;
                    return 1;
                }

            } else {
                game_status = g.nextTurn();
            }

            cout << g;

            //when a player is dead
            if (game_status == 0){
                cout << "Game over" << endl;
                cout << "Enter a race to play again or 'q' to quit" << endl;
                cin >> command;

                if (command == "q") return 1;

                race = command;

                break;
            }
        } while(cin >> command);
    }


};
