#include "player.h"

using namespace std;

//MAY NEED TILECOLLECTION:: before functions
// TODO: implement member functions
void Player::add_points(size_t points)
{
	this->points += points;
}

void Player::subtract_points(size_t points)
{
	this->points -= points;
}

size_t Player::get_points() const
{
	return this->points;
}

const std::string& Player::get_name() const
{
	return this->name;
}


size_t Player::count_tiles() const
{
	return this->tiles.count_tiles();
}

// Removes tiles from player's hand.
void Player::remove_tiles(const std::vector<TileKind>& tiles)
{
	for (unsigned int i = 0; i<tiles.size();i++)
	{
		this->tiles.remove_tile(tiles[i]);
	}
}

// Adds tiles to player's hand.
void Player::add_tiles(const std::vector<TileKind>& tiles)
{
	for (unsigned int i = 0; i<tiles.size();i++)
	{
		this->tiles.add_tile(tiles[i]);
	}
}

// Checks if player has a matching tile.
bool Player::has_tile(TileKind tile)
{
	try 
	{
		this->tiles.lookup_tile(tile.letter);
		return true;
	}
	catch (out_of_range& e)
	{
		return false;
	}
}

// Returns the total points of all tiles in the players hand.
unsigned int Player::get_hand_value() const
{
	return this->tiles.total_points();
}

size_t Player::get_hand_size() const
{
	return this->hand_size;
}

/*TileBag Player::get_tile_bag() const
{
	return this->lookup;
}

void Player::set_tile_bag(TileBag& tb)
{
	this->lookup = tb;
}*/

