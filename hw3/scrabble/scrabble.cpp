#include "scrabble.h"
#include "formatting.h"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;


// Given to you. this does not need to be changed
Scrabble::Scrabble(const ScrabbleConfig& config)
    : hand_size(config.hand_size)
    , minimum_word_length(config.minimum_word_length)
    , tile_bag(TileBag::read(config.tile_bag_file_path, config.seed))
    , board(Board::read(config.board_file_path))
    , dictionary(Dictionary::read(config.dictionary_file_path)) {}

void Scrabble::add_players()
{
    cout<<"Enter the number of players, between 1-8, then press enter key."<<endl;
    unsigned int numplay;
    cin>>numplay;
    if (cin.fail())
    {
        throw FileException("Invalid value entered");
    }
    //ENSURE CORRECT NUMBER OF PLAYERS
    if (numplay<1||numplay>8)
    {
        throw FileException("Invalid number of players");
    }
    //LOOP ADDS IN PLAYERS AND GETS THEIR HANDS
    for (unsigned int i=0;i<numplay;i++)
    {
        cout<<"Enter Player "<<i<<" name, then press enter key"<<endl;
        string player;
        cin>>player;
        if (cin.fail())
        {
            throw FileException("Invalid value entered");
        }
        players.push_back(make_shared<HumanPlayer>(HumanPlayer(player,7)));
        vector<TileKind> draw = tile_bag.remove_random_tiles(7);
        players.back()->add_tiles(draw);
        //players.back()->set_tile_bag(this->tile_bag);
        //players.back()->print_hand(cout);
    }
    cout<<endl;
}

// Game Loop should cycle through players and get and execute that players move
// until the game is over.
void Scrabble::game_loop() {
    // TODO: implement this.
    //INITIATES LOOP
    int game = 0;
    //KEEPS TRACK OF ALL PASS ENDGAME
    unsigned int allpass = 0;
    //board.print(cout);
    while(game == 0)
    {
        for (unsigned int i = 0; i<players.size();i++)
        {
            cout<<players[i]->get_name()<<" enter your move, then press enter key"<<endl;
            board.print(cout);
            int loopy = 0;
            Move move;
            //LOOP TO GET A VALID MOVE
            while (loopy == 0)
            {
                try 
                {
                    move = players[i]->get_move(board,dictionary);
                    loopy = 1;
                }
                catch(CommandException e)
                {
                    continue;
                }
            }
            //PLACE
            if (move.kind == MoveKind::PLACE)
            {
                //cerr<<"place"<<endl;
                //PLACE AND POINTS
                PlaceResult result = board.place(move);
                players[i] -> add_points(result.points);
                //RESET ALLPASS
                allpass = 0;
                //GET NEW TILES IN HAND
                players[i]->remove_tiles(move.tiles);
                vector<TileKind> draw = tile_bag.remove_random_tiles(move.tiles.size());
                players[i]->add_tiles(draw);
                cout << "You gained " << SCORE_COLOR << result.points << rang::style::reset << " points!" << endl;
                cout << "Your current score: " << SCORE_COLOR << players[i]->get_points() << rang::style::reset << endl;
                cout << endl << "Press [enter] to continue."<<endl;
                cin.ignore();
            }
            //EXCHANGE
            else if(move.kind== MoveKind::EXCHANGE)
            {
                allpass = 0;
                //REMOVE FROM HAND, ADD TO BAG, DRAW NEW
                players[i]->remove_tiles(move.tiles);
                for (unsigned int i =0;i<move.tiles.size();i++)
                {
                    this->tile_bag.add_tile(move.tiles[i]);

                }
                vector<TileKind> draw = tile_bag.remove_random_tiles(move.tiles.size());
                players[i]->add_tiles(draw);
            }
            //PASS
            else
            {
                allpass += 1;
                //continue;
            }

            //cerr<<"hhh"<<allpass<<endl;
            //CHECKS FOR ALL PASS ENDGAME
            if (allpass == players.size())
            {
                game =1;
                break;
            }

        }
        
        
    }
    // Useful cout expressions with fancy colors. Expressions in curly braces, indicate values you supply.
    // cout << "You gained " << SCORE_COLOR << {points} << rang::style::reset << " points!" << endl;
    // cout << "Your current score: " << SCORE_COLOR << {points} << rang::style::reset << endl;
    // cout << endl << "Press [enter] to continue.";
}

// Performs final score subtraction. Players lose points for each tile in their
// hand. The player who cleared their hand receives all the points lost by the
// other players.
void Scrabble::final_subtraction(vector<shared_ptr<Player>> & plrs) {
    // TODO: implement this method.
    // Do not change the method signature.
    //indicates type of endgame
    int indicator =1;
    unsigned int empty;
    //check for empty hand
    for (unsigned int i = 0; i <plrs.size();i++)
    {
        if (plrs[i]->get_hand_size()==0)
        {
            indicator =0;
            empty = i;
            break;
        }

    }
    //EMPTY HAND ENDGAME
    if (indicator == 0)
    {
        unsigned int tot = 0;
        //GET ALL PLAYERS HAND POINTS
        for (unsigned int i = 0; i <plrs.size();i++)
        {
            if (i==empty)
            {
                continue;
            }
            else
            {
                tot+= plrs[i]->get_hand_value();
            }

        }
        //ADD TO EMPTY PLAYER, THEN SUBTRACT OTHERS
        plrs[empty]->add_points(tot);
        for (unsigned int i = 0; i <plrs.size();i++)
        {
            if (plrs[i]->get_hand_value()>plrs[i]->get_points())
            {
                plrs[i]->subtract_points(plrs[i]->get_points());
            }
            else
            {
                plrs[i]->subtract_points(plrs[i]->get_hand_value());
            }

        }
    }
    //PASS ENDGAME
    else
    {
        //SUBTRACT POINTS
        for (unsigned int i = 0; i <plrs.size();i++)
        {
            if (plrs[i]->get_hand_value()>plrs[i]->get_points())
            {
                plrs[i]->subtract_points(plrs[i]->get_points());
            }
            else
            {
                plrs[i]->subtract_points(plrs[i]->get_hand_value());
            }

        }
    }
}

// You should not need to change this function.
void Scrabble::print_result() {
	// Determine highest score
    size_t max_points = 0;
	for (auto player : this->players) {
		if (player->get_points() > max_points) {
			max_points = player->get_points();
        }
	}

	// Determine the winner(s) indexes
	vector<shared_ptr<Player>> winners;
	for (auto player : this->players) {
		if (player->get_points() >= max_points) {
			winners.push_back(player);
        }
	}

    cout << (winners.size() == 1 ? "Winner:" : "Winners: ");
	for (auto player : winners) {
		cout << SPACE << PLAYER_NAME_COLOR << player->get_name();
	}
	cout << rang::style::reset << endl;

	// now print score table
    cout << "Scores: " << endl;
    cout << "---------------------------------" << endl;

	// Justify all integers printed to have the same amount of character as the high score, left-padding with spaces
    cout << setw(static_cast<uint32_t>(floor(log10(max_points) + 1)));

	for (auto player : this->players) {
		cout << SCORE_COLOR << player->get_points() << rang::style::reset << " | " << PLAYER_NAME_COLOR << player->get_name() << rang::style::reset << endl;
	}
}

// You should not need to change this.
void Scrabble::main() {
    add_players();
    game_loop();
    final_subtraction(this->players);
    print_result();
}
