#include <cstdlib>
#include <string>
#include <iostream>
#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>
#include <curses.h>
using namespace std;

/////////////////////////////////
void initialize() {
	initscr();
	raw();
	noecho();
	nonl();
	intrflush( stdscr, FALSE );
	keypad( stdscr, TRUE );
}

void finalize() { 
	endwin();
}
void delscreen(SCREEN *screen);

int x = 10, y= 20;
bool a = true;





///////////////////////////////////
int playerNum =0;
int gameNum=0;
main(int argc, char **) {

    if (argc-1 > 0) {
        cerr << "This program has no arguments" << endl;
        exit(1);
    }

    try {


        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        string const serverUrl("http://localhost:8080/RPC2");
        string const methodName("server.joinGame");
        myClient.call(serverUrl, methodName, "ii", &result, 5, 7);
        
        xmlrpc_c::value_array array1(result);
        vector<xmlrpc_c::value> const param1Value(array1.vectorValueValue());
        int const player_value = xmlrpc_c::value_int(param1Value[0]);
	int const game_value = xmlrpc_c::value_double(param1Value[1]);  
	playerNum=player_value;
	gameNum= game_value;
	cout << "The game number is " << player_value << " the playerNumber is " << game_value <<  endl;

int ch;
	initialize();

	while (a) {
		
		curs_set(0);
		wclear( stdscr );
		wmove( stdscr, x, y );
		waddch( stdscr, ACS_DIAMOND );

		wrefresh( stdscr );

		ch = wgetch( stdscr);
		switch (ch) {
			case KEY_UP: 
				x -= 1;
				break;
			case KEY_DOWN:
				x += 1;

				break;
			case KEY_LEFT:
				y -= 1;

				break;			
			case KEY_RIGHT:
				y += 1;

				break;
			case KEY_BACKSPACE:
				a = false;
				wrefresh( stdscr );
				finalize();
				break;
			default:
				break;
				
		}
xmlrpc_c::value result1;
 	 myClient.call(serverUrl, "server.getLocations", "iiii", &result1, x, y,playerNum,gameNum);	
			
		if(!a) {
			endwin();
			break;
		}
	}
	
	finalize();




    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }

    return 0;
}
