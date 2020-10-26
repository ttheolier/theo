#include <sstream>
#include <stdexcept>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "place_result.h"
#include "move.h"
#include "exceptions.h"
#include "human_player.h"
#include "tile_kind.h"
#include "formatting.h"
#include "rang.h"

using namespace std;


// This method is fully implemented.
inline string& to_upper(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

Move HumanPlayer::get_move(const Board& board, const Dictionary& dictionary) const {
	// TODO: begin your implementation here.
    string temp;
    cin>>temp;
    cout<<endl;
    temp = to_upper(temp);
    this->print_hand(cout);
    //FOR PLACE MOVE
    if (temp=="PLACE")
    {
        string dir;
        cin>>dir;
        //FOR ACROSS
        if (dir == "-")
        {
            unsigned int row;
            unsigned int col;
            string str;
            cin>>row>>col>>to_upper(str);
            //ENSURE VALID WORD LENGTH
            if (str.size()>board.rows||str.size()>board.columns)
            {
                cerr<<"Invalid Move, word too big, enter another"<<endl;
                throw CommandException("invalid Move");
            }
            row = row-1;
            col -=1;
            //ENSURE VALID PLACEMENT START
            if (row>board.rows||col>board.columns)
            {
                cerr<<"Invalid, row or column doesnt exist"<<endl;
                throw CommandException("invalid Move");
            }
            //IMPROPER FORMATTING
            /*if (cin.fail())
            {

            }*/
            vector<TileKind> parsed = parse_tiles(1,str);
            //IF PLAYER DOESNT HAVE CORRECT TILES
            for (unsigned int i=0;i<parsed.size();i++)
            {
                try 
                {
                    tiles.lookup_tile(parsed[i].letter);
                }
                catch (out_of_range e)
                {
                    cerr<<"invalid Move, enter another"<<endl;
                    throw CommandException("invalid Move");
                }
            }
            Move tempm(parsed,row,col,Direction::ACROSS);
            //ATTEMPTS PLACE, CHECK IF VALID
            PlaceResult result = board.test_place(tempm);
            if (!result.valid)
            {
                cerr<<"Invalid Move, enter another"<<endl;
                throw CommandException("invalid Move");
            }
            //IF WORD ISNT IN DICTIONARY
            //THIS LINE AVOIDS WARNING BECAUSE DIDNT FIGURE OUT THIS ERROR CHECK
            if (!dictionary.is_word("a"))
            {

            }
            /*for (unsigned int i=0;i<result.words.size();i++)
            {
                if (!dictionary.is_word(result.words[i]))
                {
                    cerr<<"Invalid word created, enter another"<<endl;
                    throw CommandException("invalid Move");
                }
            }*/
            //also need to check that words from test_place are valid
            return tempm;
        }
        //DOWNWARD
        if (dir == "|")
        {
            unsigned int row;
            unsigned int col;
            string str;
            cin>>row>>col>>to_upper(str);
            //CHECK WORD SIZE
            if (str.size()>board.rows||str.size()>board.columns)
            {
                cerr<<"Invalid Move, word too big, enter another"<<endl;
                throw CommandException("invalid Move");
            }
            row = row-1;
            col-=1;
            //CHECK INIT PLACEMENT
            if (row>board.rows||col>board.columns)
            {
                cerr<<"Invalid, row or column doesnt exist"<<endl;
                throw CommandException("invalid Move");
            }
            //IMPROPER FORMATTING
            if (cin.fail())
            {

            }
            vector<TileKind> parsed = parse_tiles(1,str);
            //SEE IF PLAYER HAS TILES
            for (unsigned int i=0;i<parsed.size();i++)
            {
                try 
                {
                    tiles.lookup_tile(parsed[i].letter);
                }
                catch (out_of_range e)
                {
                    cerr<<"invalid Move, enter another"<<endl;
                    throw CommandException("invalid Move");
                }
            }
            Move tempm(parsed,row,col,Direction::DOWN);
            //ATTEMPT PLACE, CHECK IF VALID
            PlaceResult result = board.test_place(tempm);
            if (!result.valid)
            {
                cerr<<"Invalid Move, enter another"<<endl;
                throw CommandException("invalid Move");
            }
            /*for (unsigned int i=0;i<result.words.size();i++)
            {
                //cerr<<boolalpha<<dictionary.is_word("dims")<<endl;
                if (!dictionary.is_word(result.words[i]))
                {
                    cerr<<"Invalid word created, enter another"<<endl;
                    throw CommandException("invalid Move");
                }
            }*/
            return tempm;
        }
    }   
    //PASS
    if (temp=="PASS")
    {
        return Move();
    }
    //EXCHANGE
    if (temp=="EXCHANGE")
    {
        string temp2;
        cin>>to_upper(temp2);
        vector<TileKind> parsed = parse_tiles(0,temp2);
        Move tempm(parsed);
        //THROW EXCEPTION IF NOT TILES CORRECT
        for (unsigned int i=0;i<parsed.size();i++)
        {
            try 
            {
                tiles.lookup_tile(parsed[i].letter);
            }
            catch (out_of_range e)
            {
                cerr<<"Invalid Move"<<endl;
            }
        }
        return tempm;
    }
    //EXCEPTION
    else
    {
        throw CommandException("Incorrect command format");
    }
}
//0 for exchange, 1 for place
vector<TileKind> HumanPlayer::parse_tiles(int movetype, string& letters) const{
    // TODO: begin implementation here.
    vector<TileKind> parsed;
    //PARSES TILES BASE ON MOVETYPE, ACCT. FOR WILDCARD
    if (movetype == 0)
    {
        for (unsigned int i = 0;i<letters.size();i++)
        {
            if (letters[i] == '?')
            {
                parsed.push_back(TileKind('?',0));
            }
            else
            {
                parsed.push_back(tiles.lookup_tile(letters[i]));
            }
        }
        return parsed;
    }
    else 
    {
        for (unsigned int i = 0;i<letters.size();i++)
        {
            //cerr<<letters.size()<<endl;
            //cerr<<i<<endl;
            if (letters[i] == '?')
            {
                parsed.push_back(TileKind('?',0,(letters[i+1])));
                i++;
            }
            else
            {
                //cerr<<letters<<endl;
                parsed.push_back(tiles.lookup_tile(letters[i]));
            }
        }
        //cerr<<333<<endl;
        //cerr<<parsed.size()<<endl;
        return parsed;
    }
}
//DIDNT USE
//implement in get_move?
//Move HumanPlayer::parse_move(int movetype, string& move_string) const {
	// TODO: begin implementation here.
    
//}


// This function is fully implemented.
void HumanPlayer::print_hand(ostream& out) const {
	const size_t tile_count = tiles.count_tiles();
	const size_t empty_tile_count = this->get_hand_size() - tile_count;
	const size_t empty_tile_width = empty_tile_count * (SQUARE_OUTER_WIDTH - 1);

	for(size_t i = 0; i < HAND_TOP_MARGIN - 2; ++i) {
		out << endl;
	}

	out << repeat(SPACE, HAND_LEFT_MARGIN) << FG_COLOR_HEADING << "Your Hand: " << endl << endl;

    // Draw top line
    out << repeat(SPACE, HAND_LEFT_MARGIN) << FG_COLOR_LINE << BG_COLOR_NORMAL_SQUARE;
    print_horizontal(tile_count, L_TOP_LEFT, T_DOWN, L_TOP_RIGHT, out);
    out << repeat(SPACE, empty_tile_width) << BG_COLOR_OUTSIDE_BOARD << endl;

    // Draw middle 3 lines
    for (size_t line = 0; line < SQUARE_INNER_HEIGHT; ++line) {
        out << FG_COLOR_LABEL << BG_COLOR_OUTSIDE_BOARD << repeat(SPACE, HAND_LEFT_MARGIN);
        for (auto it = tiles.cbegin(); it != tiles.cend(); ++it) {
            out << FG_COLOR_LINE << BG_COLOR_NORMAL_SQUARE << I_VERTICAL << BG_COLOR_PLAYER_HAND;

            // Print letter
            if (line == 1) {
                out << repeat(SPACE, 2) << FG_COLOR_LETTER << (char)toupper(it->letter) << repeat(SPACE, 2);

            // Print score in bottom right
            } else if (line == SQUARE_INNER_HEIGHT - 1) {
                out << FG_COLOR_SCORE << repeat(SPACE, SQUARE_INNER_WIDTH - 2) << setw(2) << it->points;

            } else {
                out << repeat(SPACE, SQUARE_INNER_WIDTH);
            }
        }
        if (tiles.count_tiles() > 0) {
            out << FG_COLOR_LINE << BG_COLOR_NORMAL_SQUARE << I_VERTICAL;
            out << repeat(SPACE, empty_tile_width) << BG_COLOR_OUTSIDE_BOARD << endl;
        }
    }

    // Draw bottom line
    out << repeat(SPACE, HAND_LEFT_MARGIN) << FG_COLOR_LINE << BG_COLOR_NORMAL_SQUARE;
    print_horizontal(tile_count, L_BOTTOM_LEFT, T_UP, L_BOTTOM_RIGHT, out);
    out << repeat(SPACE, empty_tile_width) << rang::style::reset << endl;
}
