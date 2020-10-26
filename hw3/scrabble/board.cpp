#include "board.h"
#include "board_square.h"
#include "exceptions.h"
#include "formatting.h"
#include <iomanip>
#include <fstream>

using namespace std;


bool Board::Position::operator==(const Board::Position& other) const {
    return this->row == other.row && this->column == other.column;
}

bool Board::Position::operator!=(const Board::Position& other) const {
    return this->row != other.row || this->column != other.column;
}

Board::Position Board::Position::translate(Direction direction) const {
    return this->translate(direction, 1);
}

Board::Position Board::Position::translate(Direction direction, ssize_t distance) const {
    if (direction == Direction::DOWN) {
        return Board::Position(this->row + distance, this->column);
    } else {
        return Board::Position(this->row, this->column + distance);
    }
}

Board Board::read(const string& file_path) {
    ifstream file(file_path);
    if (!file) {
        throw FileException("cannot open board file!");
    }
    char temp;
    size_t rows;
    size_t columns;
    size_t starting_row;
    size_t starting_column;
    file >> rows >> columns >> starting_row >> starting_column;
    Board board(rows, columns, starting_row, starting_column);
    for (unsigned int i = 0; i < rows;i++)
    {
    	vector<BoardSquare> tempv;
    	//LOOP TO CHECK FOR MULTIPLIERS
    	for (unsigned int j=0;j < columns;j++)
    	{
    		file>>temp;
    		if (temp == '2')
    		{
    			tempv.push_back(BoardSquare(2,1));
    		}
    		if (temp == '3')
    		{
    			tempv.push_back(BoardSquare(3,1));
    		}
    		if (temp == 'd')
    		{
    			tempv.push_back(BoardSquare(1,2));
    		}
    		if (temp == 't')
    		{
    			tempv.push_back(BoardSquare(1,3));
    		}
    		if (temp=='.') 
    		{
    			tempv.push_back(BoardSquare(1,1));
    			continue;
    		}
    	}
    	//PUSH TO BOARD
    	board.squares.push_back(tempv);
    }

    // TODO: complete implementation of reading in board from file here.
    //board.print(cout);
    return board;
}

size_t Board::get_move_index() const {
    return this->move_index;
}
//Check for out of bounds
PlaceResult Board::test_place(const Move& move) const {
    // TODO: complete implementation here, seems hard, later?
    //VARIABLES
    string strcheck;
    vector<vector<BoardSquare>> temp = squares;
    std::vector<TileKind> tiles1 = move.tiles;
    //starting bAse case
    if (this->get_move_index()==0)
    {
    	//COUNTS DOUBLE AND TRIPLES FOR LONGWORD
    	int doub = 0;
    	int trip = 0;
    	//LONG STRING
    	string longword;
    	int start = 0;
    	Position starter = this->start;
    	std::vector<std::string> words;
    	//DOWN
    	if (move.direction == Direction::DOWN)
    	{
    		int tot = 0;
    		Position iter (move.row,move.column);
    		while(tiles1.size()!=0)
    		{
    			//CHECK FOR OUT OF BOUNDS
    			if (!is_in_bounds(iter))
    			{
    				cerr<<"Move went out of bounds"<<endl;;
    				return PlaceResult("Move went out of bounds");
    			}
    			//CHECKS IF START SPOT IS COVERED
    			else if (iter == starter)
    			{
    				start = 1;
    				longword += tiles1[0].letter;
    				if (this->at(iter).word_multiplier == 3)
    				{
    					trip+=1;
    				}
    				else if (this->at(iter).word_multiplier == 2)
    				{
    					doub +=1;
    				}
    				if (this->at(iter).letter_multiplier == 3)
    				{
    					tot += tiles1[0].points*3;
    				}
    				else if (this->at(iter).letter_multiplier == 2)
    				{
    					tot += tiles1[0].points*2;
    				}
    				else
    				{
    					tot += tiles1[0].points;
    				}
    				iter = iter.translate(Direction::DOWN);
    				tiles1.erase(tiles1.begin());

    			}
    			//IF NOT START SPOT
    			else
    			{
    				longword += tiles1[0].letter;
    				if (this->at(iter).word_multiplier == 3)
    				{
    					trip+=1;
    				}
    				else if (this->at(iter).word_multiplier == 2)
    				{
    					doub +=1;
    				}
    				if (this->at(iter).letter_multiplier == 3)
    				{
    					tot += tiles1[0].points*3;
    				}
    				else if (this->at(iter).letter_multiplier == 2)
    				{
    					tot += tiles1[0].points*2;
    				}
    				else
    				{
    					tot += tiles1[0].points;
    				}
    				iter = iter.translate(Direction::DOWN);
    				tiles1.erase(tiles1.begin());
    			}
    		}
    		//ERROR IF START SPOT NOT COVERED
    		words.push_back(longword);
    		if (start ==0)
    		{
    			cerr<<"Move needs to touch start square"<<endl;;
    			return PlaceResult("Move needs to touch start square");
    		}
    		//DOUBLES OR TRIPLES SCORE
    		else
    		{
    			if (trip>0)
    			{
    				tot = tot*trip*3;
    			}
    			if (doub>0)
    			{
    				tot = tot*doub*2;
    			}
    			return PlaceResult(words,tot);
    		}
    	}

    	//if (move.direction == Direction::ACROSS)
    	//ACROSS
    	else
    	{
    		//cerr<<"across"<<endl;
    		int tot = 0;
    		Position iter (move.row,move.column);
    		while(tiles1.size()!=0)
    		{
    			//CHECKS BOUNDS
    			if (!is_in_bounds(iter))
    			{
    				cerr<<"Move went out of bounds"<<endl;
    				return PlaceResult("Move went out of bounds");
    			}
    			//CHECK START SPOT
    			else if (iter == starter)
    			{
    				start = 1;
    				longword += tiles1[0].letter;
    				if (this->at(iter).word_multiplier == 3)
    				{
    					trip+=1;
    				}
    				else if (this->at(iter).word_multiplier == 2)
    				{
    					doub +=1;
    				}
    				if (this->at(iter).letter_multiplier == 3)
    				{
    					tot += tiles1[0].points*3;
    				}
    				else if (this->at(iter).letter_multiplier == 2)
    				{
    					tot += tiles1[0].points*2;
    				}

    				else
    				{
    					tot += tiles1[0].points;
    				}
    				iter = iter.translate(Direction::ACROSS);
    				tiles1.erase(tiles1.begin());

    			}
    			//NOT START SPOT
    			else
    			{
    				longword += tiles1[0].letter;
    				if (this->at(iter).word_multiplier == 3)
    				{
    					trip+=1;
    				}
    				else if (this->at(iter).word_multiplier == 2)
    				{
    					doub +=1;
    				}
    				if (this->at(iter).letter_multiplier == 3)
    				{
    					tot += tiles1[0].points*3;
    				}
    				else if (this->at(iter).letter_multiplier == 2)
    				{
    					tot += tiles1[0].points*2;
    				}
    				else
    				{
    					tot += tiles1[0].points;
    				}
    				iter = iter.translate(Direction::ACROSS);
    				tiles1.erase(tiles1.begin());
    			}
    		}
    		//cerr<<longword<<endl;
    		words.push_back(longword);
    		if (start ==0)
    		{
    			cerr<<"Move needs to touch start square"<<endl;
    			return PlaceResult("Move needs to touch start square");
    		}
    		else
    		{
    			if (trip>0)
    			{
    				tot = tot*trip*3;
    			}
    			if (doub>0)
    			{
    				tot = tot*doub*2;
    			}
    			//cerr<<"HERE"<<endl;
    			//cerr<<words[0]<<" "<<tot<<endl;
    			return PlaceResult(words,tot);
    		}
    	}
    }
    //ALL OTHER MOVES
    else
    {
    	int size1 = tiles1.size();
    	int adjindic = 0;
    	string longword;
    	//Position starter = this->start;
    	std::vector<std::string> words;
    	//DOWN
    	if (move.direction == Direction::DOWN)
    	{
    		int doub = 0;
    		int trip=0;
    		int tot = 0;
    		int tota = 0;
    		Position iter (move.row,move.column);
    		//CHECK OVERLAP
    		if (this->in_bounds_and_has_tile(iter))
    		{
    			cerr<<"Overlap!"<<endl;
    			return PlaceResult("Overlap!");
    		}
    		unsigned int i = move.row-1;
    		unsigned int j = move.column;
    		//EXTEND END
    		while(this->squares[i][j].has_tile() == true)
    		{
    			adjindic = 1;
    			longword.insert(0,1,this->squares[i][j].get_tile_kind().letter);
    			tota += this->squares[i][j].get_tile_kind().points;
    			i--;
    		}
    		//cerr<<tot<<endl;
    		while(tiles1.size()!=0)
    		{
    			//BOUNDS
    			if (!is_in_bounds(iter))
    			{
    				cerr<<"Move went out of bounds"<<endl;;
    				return PlaceResult("Move went out of bounds");
    			}
    			
    			else if(!this->at(iter).has_tile())
    			{
    				//iter = iter.translate(Direction::ACROSS);
    				Position iterl = iter;
    				iterl.column -= 1;
    				Position iterr = iter.translate(Direction::ACROSS);
    				//if tile above
    				//CHECKS FOR TILES TO LEFT
    				if(this->in_bounds_and_has_tile(iterl)==true)
    				{
    					adjindic = 1;
    					int tot1 = 0;
    					int dou = 0;
    					int tri = 0;
    					//cerr<<"in"<<endl;
    					longword += tiles1[0].letter;
    					string tempw;
    					if (this->at(iter).word_multiplier == 3)
    					{
	    					tri+=1;
	    				}
	    				else if (this->at(iter).word_multiplier == 2)
	    				{
	    					dou +=1;
	    				}
	    				if (this->at(iter).letter_multiplier == 3)
	    				{
	    					tot1 += tiles1[0].points*3;
	    				}
	    				else if (this->at(iter).letter_multiplier == 2)
	    				{
	    					tot1 += tiles1[0].points*2;
	    				}
	    				else
	    				{
	    					tot1 += tiles1[0].points;
	    				}
	    				while (this->in_bounds_and_has_tile(iterl)==true)
	    				{
	    					iterl.column -= 1;
	    				}
	    				iterl.column += 1;
	    				while (this->in_bounds_and_has_tile(iterl)==true)
	    				{
	    					if (iterl == iter)
	    					{
			    				iterl = iterl.translate(Direction::ACROSS);
			    				tempw += tiles1[0].letter;
	    					}
	    					else
	    					{
	    						tempw += this->at(iterl).get_tile_kind().letter;
			    				tot1 += this->at(iterl).get_tile_kind().points;
			    				//cerr<<"a"<<this->at(iterl).get_points()<<endl;
			    				iterl = iterl.translate(Direction::ACROSS);
	    					}
	    				}
	    				if (iterl == iter)
    					{
		    				//iterl = iterl.translate(Direction::ACROSS);
		    				tempw += tiles1[0].letter;
    					}
	    				if (tri > 0)
	    				{
	    					tot1 = tot1*3*tri;
	    				}
	    				if( dou >0)
	    				{
	    					tot1 = tot1*2*dou;
	    				}
	    				tot += tot1;
	    				cerr<<tempw<<endl;
	    				words.push_back(tempw);
    				}
    				//CHECKS TILE TO RIGHT
    				else if (this->in_bounds_and_has_tile(iterr)==true)
    				{
    					adjindic = 1;
    					int tot1 = 0;
    					int dou = 0;
    					int tri = 0;
    					string tempw;
    					longword += tiles1[0].letter;
    					if (this->at(iter).word_multiplier == 3)
    					{
	    					tri+=1;
	    				}
	    				else if (this->at(iter).word_multiplier == 2)
	    				{
	    					dou +=1;
	    				}
	    				if (this->at(iter).letter_multiplier == 3)
	    				{
	    					tot1 += tiles1[0].points*3;
	    				}
	    				else if (this->at(iter).letter_multiplier == 2)
	    				{
	    					tot1 += tiles1[0].points*2;
	    				}
	    				else
	    				{
	    					tot1 += tiles1[0].points;
	    				}
	    				while (this->in_bounds_and_has_tile(iterr)==true)
	    				{
	    					tempw += this->at(iterr).get_tile_kind().letter;
		    				tot1 += this->at(iterr).get_tile_kind().points;
		    				iterr = iterr.translate(Direction::ACROSS);
    					}
    					if (tri > 0)
	    				{
	    					tot1 = tot1*3*tri;
	    				}
	    				if( dou >0)
	    				{
	    					tot1 = tot1*2*dou;
	    				}
    					words.push_back(tempw);
    					tot+=tot1;
    				}
    				//cerr<<words.size()<<endl;
					//CONTINUES GOING ACROSS
					//DOES LONGWORD IF SIZE IS GREATER THAN ONE
					if (size1 != 1)
					{
	    				longword += tiles1[0].letter;
	    				if (this->at(iter).word_multiplier == 3)
						{
	    					trip+=1;
	    				}
	    				else if (this->at(iter).word_multiplier == 2)
	    				{
	    					doub +=1;
	    				}
	    				if (this->at(iter).letter_multiplier == 3)
	    				{
	    					tota += tiles1[0].points*3;
	    				}
	    				else if (this->at(iter).letter_multiplier == 2)
	    				{
	    					tota += tiles1[0].points*2;
	    				}
	    				else
	    				{
	    					tota += tiles1[0].points;
	    				}
	    			}
    				tiles1.erase(tiles1.begin());
    				iter = iter.translate(Direction::DOWN);
    			
    			}
    			//if next space haS tile
    			else
    			{
    				adjindic = 1;
    				longword += this->at(iter).get_tile_kind().letter;
    				tota += this->at(iter).get_tile_kind().points;
    				iter = iter.translate(Direction::DOWN);
    			}

    		}
    		//EXTEND FRONT
    		if (this->in_bounds_and_has_tile(iter) == true)
    		{
    			adjindic = 1;
    			while(this->in_bounds_and_has_tile(iter)== true)
    			{
    				longword += this->at(iter).get_tile_kind().letter;
    				tota += this->at(iter).get_tile_kind().points;
    				iter = iter.translate(Direction::DOWN);
    				//cerr<<tot<<endl;
    			}
    		}
    		//CHECKS FOR ADJACENCY
    		if (adjindic == 0)
    		{
    			cerr<<"No adjacent words!"<<endl;
    			return PlaceResult("No adjacent words!");
    		}
    		if (trip > 0)
			{
				tota = tota*3*trip;
			}
			if( doub >0)
			{
				tota = tota*2*doub;
			}
			//if (longword.size()>2)
			//{
    		words.push_back(longword);
			//}
    		tot +=tota;
    		//cerr<<tot<<endl;
    		return PlaceResult(words,tot);
    		
    	}

    	//if (move.direction == Direction::ACROSS)
    	//ACROSS
    	else
    	{
    		//cerr<<"across"<<endl;
    		int doub = 0;
    		int trip=0;
    		int tot = 0;
    		int tota = 0;
    		Position iter (move.row,move.column);
    		//OVERLAP
    		if (this->in_bounds_and_has_tile(iter))
    		{
    			cerr<<"Overlap!"<<endl;
    			return PlaceResult("Overlap!");
    		}
    		unsigned int i = move.row;
    		unsigned int j = move.column-1;
    		//need to check in bounds
    		//EXTEND END
    		while(this->squares[i][j].has_tile() == true)
    		{
    			adjindic = 1;
    			longword.insert(0,1,this->squares[i][j].get_tile_kind().letter);
    			tota += this->squares[i][j].get_tile_kind().points;
    			j--;
    		}
    		//cerr<<longword<<endl;
    		//while there are still tiles to place
    		while(tiles1.size()!=0)
    		{
    			//checks for out of bounds
    			if (!is_in_bounds(iter))
    			{
    				cerr<<"Move went out of bounds"<<endl;;
    				return PlaceResult("Move went out of bounds");
    			}
    			//checks for empty spot case
    			else if(!this->at(iter).has_tile())
    			{
    				//iter = iter.translate(Direction::ACROSS);
    				Position itera = iter;
    				itera.row -= 1;
    				Position iterb = iter.translate(Direction::DOWN);
    				//if tile above
    				if(this->in_bounds_and_has_tile(itera)==true)
    				{
    					int tot1 = 0;
    					int dou = 0;
    					int tri = 0;
    					adjindic = 1;
    					//cerr<<"in"<<endl;
    					longword += tiles1[0].letter;
    					string tempw;
    					if (this->at(iter).word_multiplier == 3)
    					{
	    					tri+=1;
	    				}
	    				else if (this->at(iter).word_multiplier == 2)
	    				{
	    					dou +=1;
	    				}
	    				if (this->at(iter).letter_multiplier == 3)
	    				{
	    					tot1 += tiles1[0].points*3;
	    				}
	    				else if (this->at(iter).letter_multiplier == 2)
	    				{
	    					tot1 += tiles1[0].points*2;
	    				}
	    				else
	    				{
	    					tot1 += tiles1[0].points;
	    				}
	    				while (this->in_bounds_and_has_tile(itera)==true)
	    				{
	    					itera.row -= 1;
	    				}
	    				itera.row += 1;
	    				while (this->in_bounds_and_has_tile(itera)==true)
	    				{
	    					if (itera == iter)
	    					{
			    				itera = itera.translate(Direction::DOWN);
			    				tempw += tiles1[0].letter;
	    					}
	    					else
	    					{
	    						tempw += this->at(itera).get_tile_kind().letter;
			    				tot1 += this->at(itera).get_points();
			    				itera = itera.translate(Direction::DOWN);
	    					}
	    				}
	    				if (itera == iter)
    					{
		    				//iterl = iterl.translate(Direction::ACROSS);
		    				tempw += tiles1[0].letter;
    					}
	    				if (tri > 0)
	    				{
	    					tot1 = tot1*3*tri;
	    				}
	    				if( dou >0)
	    				{
	    					tot1 = tot1*2*dou;
	    				}
	    				tot =+ tot1;
	    				words.push_back(tempw);
    				}
    				//IF TILE BELOW
    				else if (this->in_bounds_and_has_tile(iterb)==true)
    				{
    					int tot1 = 0;
    					int dou = 0;
    					int tri = 0;
    					adjindic = 1;
    					string tempw;
    					longword += tiles1[0].letter;
    					if (this->at(iter).word_multiplier == 3)
    					{
	    					tri+=1;
	    				}
	    				else if (this->at(iter).word_multiplier == 2)
	    				{
	    					dou +=1;
	    				}
	    				if (this->at(iter).letter_multiplier == 3)
	    				{
	    					tot1 += tiles1[0].points*3;
	    				}
	    				else if (this->at(iter).letter_multiplier == 2)
	    				{
	    					tot1 += tiles1[0].points*2;
	    				}
	    				else
	    				{
	    					tot1 += tiles1[0].points;
	    				}
	    				while (this->in_bounds_and_has_tile(iterb)==true)
	    				{
	    					tempw += this->at(iterb).get_tile_kind().letter;
		    				tot1 += this->at(iterb).get_points();
		    				iterb = iterb.translate(Direction::DOWN);
    					}
    					if (tri > 0)
	    				{
	    					tot1 = tot1*3*tri;
	    				}
	    				if( dou >0)
	    				{
	    					tot1 = tot1*2*dou;
	    				}
	    				tot += tot1;
    					words.push_back(tempw);
    				}
					//CONTINUES GOING ACROSS
					if (size1!=1)
					{
						if (this->at(iter).word_multiplier == 3)
						{
	    					trip+=1;
	    				}
	    				else if (this->at(iter).word_multiplier == 2)
	    				{
	    					doub +=1;
	    				}
	    				longword += tiles1[0].letter;
	    				if (this->at(iter).letter_multiplier == 3)
	    				{
	    					tota += tiles1[0].points*3;
	    				}
	    				else if (this->at(iter).letter_multiplier == 2)
	    				{
	    					tota += tiles1[0].points*2;
	    				}
	    				else
	    				{
	    					tota += tiles1[0].points;
	    				}
	    			}
    				tiles1.erase(tiles1.begin());
    				iter = iter.translate(Direction::ACROSS);
    			
    			}
    			//IF NEXT SPACE HAS A TILE
    			else
    			{
    				adjindic = 1;
    				longword += this->at(iter).get_tile_kind().letter;
    				tota += this->at(iter).get_points();
    				iter = iter.translate(Direction::ACROSS);
    			}
    			//cerr<<longword<<endl;

    		}
    		//cerr<<"out"<<endl;
    		//iter = iter.translate(Direction::ACROSS);
    		//LOOKS FOR LETTERS PLACED AFTER(EXTEND)
    		if (this->in_bounds_and_has_tile(iter) == true)
    		{
    			adjindic = 1;
    			while(this->at(iter).has_tile()== true)
    			{
    				longword.insert(0,1,this->at(iter).get_tile_kind().letter);
    				tota += this->at(iter).get_tile_kind().points;
    				iter = iter.translate(Direction::ACROSS);
    				//cerr<<tot<<endl;
    			}
    		}
    		//CHECK ADJACENCY
    		if (adjindic == 0)
    		{
    			cerr<<"No adjacent words!"<<endl;
    			return PlaceResult("No adjacent words!");
    		}
    		if (trip > 0)
			{
				tota = tota*3*trip;
			}
			if( doub >0)
			{
				tota = tota*2*doub;
			}
			tot+= tota;
    		//cerr<<longword<<endl;
    		words.push_back(longword);
    		
    		
			//cerr<<"HERE"<<endl;
			//cerr<<words[0]<<" "<<tot<<endl;
			return PlaceResult(words,tot);
    		
    	}
    }
}

PlaceResult Board::place(const Move& move) {
    // TODO: Complete implementation here
    PlaceResult tempo = test_place(move);
    //CHECKS IF MOVE IS VALID
    if (tempo.valid)
    {
    	//DOWN
    	if (move.direction == Direction::DOWN)
    	{
    		int j = 0;
    		//LOOP PLACES LETTERS
    		for (unsigned int i = 0;i<move.tiles.size();)
    		{
    			if (squares[move.row+j][move.column].has_tile()==false)
    			{
    				squares[move.row+j][move.column].set_tile_kind(move.tiles[i]);
    				i++;
    				j++;
    			}
    			else
    			{
    				j++;
    			}
    		}
    	}
    	//ACROSS
    	if (move.direction == Direction::ACROSS)
    	{
    		//cerr<<"here"<<endl;
    		int j = 0;
    		//LOOP PLACES LETTERS
    		for (unsigned int i = 0;i<move.tiles.size();)
    		{
    			//cerr<<move.column<<endl;
    			if(squares[move.row][move.column+j].has_tile() == false)
    			{
    				squares[move.row][move.column+j].set_tile_kind(move.tiles[i]);
    				i++;
    				j++;
    			}
    			else
    			{
    				j++;
    			}
    		}
    		//cerr<<"loop"<<endl;
    	}
    	if (this->get_move_index()==0)
    	{
    		this->move_index = 1;
    	}
    	//this->print(cout);
    	return tempo;
    }
    //OTHERWISE
    else
    {
    	return tempo;
    }
}

// The rest of this file is provided for you. No need to make changes.

BoardSquare& Board::at(const Board::Position& position) {
    return this->squares.at(position.row).at(position.column);
}

const BoardSquare& Board::at(const Board::Position& position) const {
    return this->squares.at(position.row).at(position.column);
}

bool Board::is_in_bounds(const Board::Position& position) const {
    return position.row < this->rows && position.column < this->columns;
}

bool Board::in_bounds_and_has_tile(const Position& position) const{
    return is_in_bounds(position) && at(position).has_tile();
}

void Board::print(ostream& out) const {
	// Draw horizontal number labels
	for (size_t i = 0; i < BOARD_TOP_MARGIN - 2; ++i) {
		out << std::endl;
	}
	out << FG_COLOR_LABEL << repeat(SPACE, BOARD_LEFT_MARGIN);
	const size_t right_number_space = (SQUARE_OUTER_WIDTH - 3) / 2;
	const size_t left_number_space = (SQUARE_OUTER_WIDTH - 3) - right_number_space;
	for (size_t column = 0; column < this->columns; ++column) {
		out << repeat(SPACE, left_number_space) << std::setw(2) << column + 1 << repeat(SPACE, right_number_space);
	}
	out << std::endl;

	// Draw top line
	out << repeat(SPACE, BOARD_LEFT_MARGIN);
    print_horizontal(this->columns, L_TOP_LEFT, T_DOWN, L_TOP_RIGHT, out);
    out << endl;

	// Draw inner board
	for (size_t row = 0; row < this->rows; ++row) {
        if (row > 0) {
            out << repeat(SPACE, BOARD_LEFT_MARGIN);
			print_horizontal(this->columns, T_RIGHT, PLUS, T_LEFT, out);
			out << endl;
		}

		// Draw insides of squares
		for (size_t line = 0; line < SQUARE_INNER_HEIGHT; ++line) {
			out << FG_COLOR_LABEL << BG_COLOR_OUTSIDE_BOARD;

			// Output column number of left padding
			if (line == 1) {
				out << repeat(SPACE, BOARD_LEFT_MARGIN - 3);
				out << std::setw(2) << row + 1;
				out << SPACE;
			} else {
				out << repeat(SPACE, BOARD_LEFT_MARGIN);
			}

            // Iterate columns
			for (size_t column = 0; column < this->columns; ++column) {
				out << FG_COLOR_LINE << BG_COLOR_NORMAL_SQUARE << I_VERTICAL;
				const BoardSquare& square = this->squares.at(row).at(column);
				bool is_start = this->start.row == row && this->start.column == column;

				// Figure out background color
				if (square.word_multiplier == 2) {
					out << BG_COLOR_WORD_MULTIPLIER_2X;
				} else if (square.word_multiplier == 3) {
					out << BG_COLOR_WORD_MULTIPLIER_3X;
				} else if (square.letter_multiplier == 2) {
					out << BG_COLOR_LETTER_MULTIPLIER_2X;
				} else if (square.letter_multiplier == 3) {
					out << BG_COLOR_LETTER_MULTIPLIER_3X;
				} else if (is_start) {
					out << BG_COLOR_START_SQUARE;
                }

				// Text
                if (line == 0 && is_start) {
                    out << "  \u2605  ";
                } else if (line == 0 && square.word_multiplier > 1) {
                    out << FG_COLOR_MULTIPLIER << repeat(SPACE, SQUARE_INNER_WIDTH - 2) << 'W' << std::setw(1) << square.word_multiplier;
                } else if (line == 0 && square.letter_multiplier > 1) {
                    out << FG_COLOR_MULTIPLIER << repeat(SPACE, SQUARE_INNER_WIDTH - 2) << 'L' << std::setw(1) << square.letter_multiplier;
				} else if (line == 1 && square.has_tile()) {
                    char l = square.get_tile_kind().letter == TileKind::BLANK_LETTER ? square.get_tile_kind().assigned : ' ';
                    out << repeat(SPACE, 2) << FG_COLOR_LETTER << square.get_tile_kind().letter << l << repeat(SPACE, 1);
				} else if (line == SQUARE_INNER_HEIGHT - 1 && square.has_tile()) {
					out << repeat(SPACE, SQUARE_INNER_WIDTH - 1) << FG_COLOR_SCORE << square.get_points();
				} else {
					out << repeat(SPACE, SQUARE_INNER_WIDTH);
				}
			}

			// Add vertical line
			out << FG_COLOR_LINE << BG_COLOR_NORMAL_SQUARE << I_VERTICAL << BG_COLOR_OUTSIDE_BOARD << std::endl;
		}
	}

	// Draw bottom line
	out << repeat(SPACE, BOARD_LEFT_MARGIN);
	print_horizontal(this->columns, L_BOTTOM_LEFT, T_UP, L_BOTTOM_RIGHT, out);
	out << endl << rang::style::reset << std::endl;
}
