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
    size_t rows;
    size_t columns;
    size_t starting_row;
    size_t starting_column;
    file >> rows >> columns >> starting_row >> starting_column;
    Board board(rows, columns, starting_row, starting_column);

    string schema;
    getline(file, schema);

    for (size_t i = 0; i < rows; ++i) {
        getline(file, schema);
        if ((i != rows-1 && file.eof()) || schema.size() != columns) {
            throw FileException("invalid board file!");
        }

        board.squares.emplace_back();
        for (size_t j = 0; j < columns; ++j) {
            unsigned int letter_multiplier = 1;
            unsigned int word_multiplier = 1;
            switch (schema[j]) {
            case '.':
                break;
            case '2':
                letter_multiplier = 2;
                break;
            case '3':
                letter_multiplier = 3;
                break;
            case 'd':
                word_multiplier = 2;
                break;
            case 't':
                word_multiplier = 3;
                break;
            default:
                throw FileException("invalid board file!");
            }
            board.squares.at(i).emplace_back(letter_multiplier, word_multiplier);
        }
    }

    return board;
}

size_t Board::get_move_index() const {
    return this->move_index;
}
//Check for out of bounds
PlaceResult Board::test_place(const Move& move) const {
    
    bool start_or_neighboring_tile = false;

    Board::Position cursor(move.row, move.column);

    // Move must be in bounds
    if (!this->is_in_bounds(cursor))
        return PlaceResult("Given starting placement must be in bounds");

    // Can't start on an existing tile.
    if (this->at(cursor).has_tile()) {
        return PlaceResult("cannot start a word on an already-placed tile");
    }

    // Go to start of word
    while (in_bounds_and_has_tile(cursor.translate(move.direction, -1))) {
        cursor = cursor.translate(move.direction, -1);
    }

    string word = "";
    unsigned int total_points = 0;

    vector<string> words;
    unsigned int word_multiplier = 1;
    unsigned int word_points = 0;

    // Check every consequent letter, or remaining letters of word
    for (size_t i = 0; i < move.tiles.size() || in_bounds_and_has_tile(cursor)  ;) {
        // Check in bounds
        if (!this->is_in_bounds(cursor)) {
            return PlaceResult("word placement goes out of bounds");
        }

        const BoardSquare& square = this->at(cursor);
        
        start_or_neighboring_tile = start_or_neighboring_tile || square.has_tile() || cursor == start;

        TileKind tile = square.has_tile() ? square.get_tile_kind() : move.tiles[i++];

        word += tile.letter == TileKind::BLANK_LETTER ? tile.assigned : tile.letter;
        word_points += square.has_tile() ? tile.points : tile.points * square.letter_multiplier;
        word_multiplier *= square.has_tile() ? 1 : square.word_multiplier;

        // Get normal word if tile is newly placed.
        if (!square.has_tile()){
            Board::Position normal_cursor(cursor);
            while (in_bounds_and_has_tile(normal_cursor.translate(!move.direction, -1))) {
                normal_cursor = normal_cursor.translate(!move.direction, -1);
            }
            if (normal_cursor != cursor || in_bounds_and_has_tile(cursor.translate(!move.direction, 1))) { // there is a normal word
                start_or_neighboring_tile = true;
                string normal_word;
                unsigned int normal_word_points = 0;
                unsigned int normal_word_multiplier = 1;

                do {
                    const BoardSquare& normal_square = this->at(normal_cursor);
                    TileKind normal_tile = normal_square.has_tile() ? normal_square.get_tile_kind() : tile;
                    normal_word += normal_tile.letter == TileKind::BLANK_LETTER ? normal_tile.assigned : normal_tile.letter;;
                    normal_word_points += normal_square.has_tile() ? normal_tile.points : normal_tile.points * normal_square.letter_multiplier;
                    normal_word_multiplier *= normal_square.has_tile() ? 1 : normal_square.word_multiplier;
                    normal_cursor = normal_cursor.translate(!move.direction, 1);
                } while (normal_cursor == cursor || in_bounds_and_has_tile(normal_cursor));

                total_points += normal_word_points * normal_word_multiplier;
                words.push_back(normal_word);
            }
        }
        // advance to next square
        cursor = cursor.translate(move.direction);
    }
    if (word.size() > 1){
        words.push_back(word);
        total_points += word_points * word_multiplier;
    }
    if (words.size() == 0){
        return PlaceResult("No words formed.");
    }
    if (!start_or_neighboring_tile)
        return PlaceResult("Words must neighbor placed tile or contain start square.");
    return PlaceResult(words, total_points);
}

PlaceResult Board::place(const Move& move) {
    // TODO: Complete implementation here
    PlaceResult result = this->test_place(move);
    if (result.valid) {
        Board::Position cursor(move.row, move.column);
        for (size_t i = 0; i < move.tiles.size();) {
            if (this->at(cursor).has_tile()) {
            } else {
                this->at(cursor).set_tile_kind(move.tiles[i++]);
            }
            cursor = cursor.translate(move.direction);
        }
    }
    return result;
}

char Board::letter_at(Position p) const
{
    //for blank tile
    if (this->at(p).get_tile_kind().letter=='?')
    {
        return this->at(p).get_tile_kind().assigned;
    }
    //normal
    return this->at(p).get_tile_kind().letter;
}

bool Board::is_anchor_spot(Position p) const
{
    //if it has tile, false
    if (this->in_bounds_and_has_tile(p))
    {
        return false;
    }
    //checks to right, left, top, and bottom of poisition to determine anchor
    //first case is for starting move
    if (this->move_index == 0&& p.row == this->start.row && p.column == this->start.column)
    {
        return true;
    }
    p = p.translate(Direction::DOWN);
    if (this->in_bounds_and_has_tile(p))
    {
        return true;
    }
    p = p.translate(Direction::DOWN,-2);
    if (this->in_bounds_and_has_tile(p))
    {
        return true;
    }
    p = p.translate(Direction::DOWN);
    p = p.translate(Direction::ACROSS);
    if (this->in_bounds_and_has_tile(p))
    {
        return true;
    }
    p = p.translate(Direction::ACROSS,-2);
    if (this->in_bounds_and_has_tile(p))
    {
        return true;
    }
    return false;
}

std::vector<Board::Anchor> Board::get_anchors() const
{
    Board::Position iter = Board::Position(0,0);
    std::vector<Board::Anchor> anchor;
    //go through every square
    for (unsigned int i = 0; i<this->rows;i++)
    {
        for (unsigned int j=0;j<this->columns;j++)
        {
            //if its an anchor spot
            if (this->is_anchor_spot(iter))
            {
                //check for down limit
                size_t l = 0;
                Position temp = iter;
                temp = temp.translate(Direction::DOWN,-1);
                while(this->is_in_bounds(temp) && !this->in_bounds_and_has_tile(temp)&&!this->is_anchor_spot(temp))
                {
                    l++;
                    temp = temp.translate(Direction::DOWN,-1);
                }
                //add down anchor
                anchor.push_back(Anchor(iter,Direction::DOWN,l));
                //check for across limit
                l=0;
                temp = iter;
                temp = temp.translate(Direction::ACROSS,-1);
                while(this->is_in_bounds(temp) && !this->in_bounds_and_has_tile(temp)&&!this->is_anchor_spot(temp))
                {
                    l++;
                    temp = temp.translate(Direction::ACROSS,-1);
                }
                //add across anchor
                anchor.push_back(Anchor(iter,Direction::ACROSS,l));
            }
            //next square
            iter = iter.translate(Direction::ACROSS);
        }
        //next row
        iter = Board::Position(i+1,0);
    }
    return anchor;
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
