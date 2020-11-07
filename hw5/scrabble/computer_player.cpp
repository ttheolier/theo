
#include <memory>

#include "computer_player.h"
#include <string>
#include <iostream>



void ComputerPlayer::left_part(Board::Position anchor_pos, 
                               std::string partial_word,
                               Move partial_move, 
                               std::shared_ptr<Dictionary::TrieNode> node, 
                               size_t limit,
                               TileCollection& remaining_tiles,
                               std::vector<Move>& legal_moves,
                               const Board& board) const {
    // HW5: IMPLEMENT THIS
  //dont know if this is an accurate check
  
  //Base Case
  if (limit == 0)
  {
    return;
  }
  else
  {
    //iterate through map
    std::map<char, std::shared_ptr<Dictionary::TrieNode>>::iterator i;
    for (i = node->nexts.begin();i != node->nexts.end();i++)
    {
      //try for adding a regular tile
      try
      {
        TileKind curr = remaining_tiles.lookup_tile(i->first);
        partial_move.tiles.push_back(curr);
        remaining_tiles.remove_tile(curr);
        partial_word += i->first;
        if (partial_move.direction == Direction::DOWN)
        {
          //ind = 1;
          this->extend_right(anchor_pos,partial_word,Move(partial_move.tiles,partial_move.row-partial_word.size(),partial_move.column,Direction::DOWN),
                            i->second,remaining_tiles,legal_moves,board);
        }
        else
        {
          this->extend_right(anchor_pos,partial_word,Move(partial_move.tiles,partial_move.row,partial_move.column-partial_word.size(),Direction::ACROSS),
                            i->second,remaining_tiles,legal_moves,board);
        }
        this->left_part(anchor_pos,partial_word,partial_move,i->second,limit-1,remaining_tiles,legal_moves,board);
        remaining_tiles.add_tile(curr);
        partial_move.tiles.pop_back();
        partial_word.pop_back();
      }
      //catch
      catch (std::out_of_range& e)
      {

      }
      //try for adding a blank tile
      try
      {
        TileKind curr1 = remaining_tiles.lookup_tile('?');
        partial_move.tiles.push_back(TileKind('?',curr1.points,i->first));
        remaining_tiles.remove_tile(curr1);
        partial_word += i->first;
        if (partial_move.direction == Direction::DOWN)
        {
          this->extend_right(anchor_pos,partial_word,Move(partial_move.tiles,partial_move.row-partial_word.size(),partial_move.column,Direction::DOWN),
                            i->second,remaining_tiles,legal_moves,board);
        }
        else
        {
          this->extend_right(anchor_pos,partial_word,Move(partial_move.tiles,partial_move.row,partial_move.column-partial_word.size(),Direction::DOWN),
                            i->second,remaining_tiles,legal_moves,board);
        }
        this->left_part(anchor_pos,partial_word,partial_move,i->second,limit-1,remaining_tiles,legal_moves,board);
        remaining_tiles.add_tile(curr1);
        partial_move.tiles.pop_back();
        partial_word.pop_back();
      }
      //catch
      catch (std::out_of_range& e)
      {
        continue;
      }
    }

  }
}

void ComputerPlayer::extend_right(Board::Position square,
                                  std::string partial_word,
                                  Move partial_move, 
                                  std::shared_ptr<Dictionary::TrieNode> node,
                                  TileCollection& remaining_tiles,
                                  std::vector<Move>& legal_moves,
                                  const Board& board) const {
    // HW5: IMPLEMENT THIS
  //if this square is out of bounds
  if (!board.is_in_bounds(square))
  {
    //if word was made at it
    if (node->is_final)
    {
      legal_moves.push_back(partial_move);
    } 
    return;
  }
  //if current square has a tile
  if (board.in_bounds_and_has_tile(square))
  {
    //find next node
    char let = board.letter_at(square);
    if (node->nexts.find(let)!=node->nexts.end())
    {
      node = node->nexts.find(let)->second;
      square = square.translate(partial_move.direction);
      this->extend_right(square,partial_word+let,partial_move,node,remaining_tiles,legal_moves,board);
      return;
    }
    //esle done
    else
    {
      return;
    }
  }
  //if a full word was made add it
  if (node->is_final)
  {
    legal_moves.push_back(partial_move);
  }
  //iterate through trie
  std::map<char, std::shared_ptr<Dictionary::TrieNode>>::iterator i;
  for (i = node->nexts.begin();i != node->nexts.end();i++)
  {
    //try for adding regular tile
    try
    {
      TileKind curr = remaining_tiles.lookup_tile(i->first);
      partial_move.tiles.push_back(curr);
      remaining_tiles.remove_tile(curr);
      square = square.translate(partial_move.direction);
      this->extend_right(square,partial_word+i->first,partial_move,i->second,remaining_tiles,legal_moves,board);
      remaining_tiles.add_tile(curr);
      partial_move.tiles.pop_back();
      square = square.translate(partial_move.direction,-1);

    }
    //catch
    catch (std::out_of_range& e)
    {

    }
    //try for adding blank tile
    try
    {
      TileKind curr1 = remaining_tiles.lookup_tile('?');
      partial_move.tiles.push_back(TileKind('?',curr1.points,i->first));
      remaining_tiles.remove_tile(curr1);
      square = square.translate(partial_move.direction);
      this->extend_right(square,partial_word+i->first,partial_move,i->second,remaining_tiles,legal_moves,board);
      remaining_tiles.add_tile(curr1);
      partial_move.tiles.pop_back();
      square = square.translate(partial_move.direction,-1);
      
    }
    //catch
    catch (std::out_of_range& e)
    {
      continue;
    }
  }
  
}

Move ComputerPlayer::get_move(const Board& board, const Dictionary& dictionary) const {
	std::vector<Move> legal_moves;
    std::vector<Board::Anchor> anchors = board.get_anchors();
    // HW5: IMPLEMENT THIS
    //iterate through anchors
    for (unsigned int i = 0;i<anchors.size();i++)
    {
      //0 anchor limit case
      if (anchors[i].limit == 0)
      {
        //add characters to partial word
        std::string partial_word;
        Board::Position iter = anchors[i].position;
        iter = iter.translate(anchors[i].direction,-1);
        while (board.in_bounds_and_has_tile(iter))
        {
          iter = iter.translate(anchors[i].direction,-1);
        }
        //optimize
        iter = iter.translate(anchors[i].direction);
        while (board.in_bounds_and_has_tile(iter))
        {
          partial_word += board.letter_at(iter);
          iter = iter.translate(anchors[i].direction);
        }
        //call extend right
        TileCollection remaining_tiles = this->tiles;
        std::vector<TileKind> tiles;
        std::shared_ptr<Dictionary::TrieNode> node = dictionary.find_prefix(partial_word);
        Move partial_move = Move(tiles, anchors[i].position.row,anchors[i].position.column,anchors[i].direction);
        this->extend_right(anchors[i].position,partial_word,partial_move,node ,remaining_tiles ,legal_moves,board);

      }
      //positive limit size
      else
      {
        //call extend right on blank prefix then call left part
        TileCollection remaining_tiles = this->tiles;
        std::vector<TileKind> tiles;
        std::string partial_word;
        std::shared_ptr<Dictionary::TrieNode> node = dictionary.get_root();
        Move partial_move = Move(tiles, anchors[i].position.row,anchors[i].position.column,anchors[i].direction);
        this->extend_right(anchors[i].position,partial_word,partial_move,node,remaining_tiles,legal_moves,board);
        this->left_part(anchors[i].position,partial_word,partial_move,node,anchors[i].limit,remaining_tiles,legal_moves,board);
      }
    }

	return get_best_move(legal_moves, board, dictionary);
}

Move ComputerPlayer::get_best_move(std::vector<Move> legal_moves, const Board& board, const Dictionary& dictionary) const {
    Move best_move = Move(); // Pass if no move found	
	// HW5: IMPLEMENT THIS
    //keep track of highest point
    unsigned int points = 0;
    for (unsigned int i = 0;i<legal_moves.size();i++)
    {
      //index to keep track of illegal move
      int ind = 0;
      //get placeresult and make sure it's valid
      PlaceResult R = board.test_place(legal_moves[i]);
      if (!R.valid)
      {
        continue;
      }
      //make sure every word is in dict.
      for (unsigned int i = 0;i<R.words.size();i++)
      {
        if (!dictionary.is_word(R.words[i]))
        {
          ind = 1;
          break;
        }
      }
      //if word wasnt in dictionary, back to top of loop
      if (ind ==1)
      {
        continue;
      }
      //check for 50 pt bonus
      if (legal_moves[i].tiles.size() == this->get_hand_size())
      {
        if (R.points +50>points)
        {
          points = R.points + 50;
          best_move = legal_moves[i];
        }
        else
        {
          continue;
        }
      }
      //non 50 point bonus
      else
      {
        if (R.points >points)
        {
          points = R.points;
          best_move = legal_moves[i];
        }
        else
        {
          continue;
        }
      }
    }
	
	return best_move;	
}


