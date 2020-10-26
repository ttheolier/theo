#include "flexible.h"
#include <iostream>

using namespace std;                         //DELETE IOSTREAM


// The constructor creates a unique_ptr to a dynamically allocated array of two
// CharacterBlocks using the initialization list syntax. No need to change this
// unless you add fields to the FlexibleCharacterManager.
FlexibleCharacterManager::FlexibleCharacterManager() : blocks(new CharacterBlock[2] {}) {}

char* FlexibleCharacterManager::alloc_chars(size_t n) {
	// TODO: your implementation here
	//cerr<<"start";
	//Initializes variables
	int found;
	char* loc;
	//For first added word
	if (blocks_in_use==0)
	{
		loc = buffer;
		blocks[0].address = buffer;
	    blocks[0].size = n;
	    blocks_in_use += 1;
	    return loc;
	}

	else
	{
		//Checks if theres room between start of buffer and first block
		if (((buffer)+n) <= (blocks[0].address))
		{
			found =1;
			loc = buffer;
		}
		else
		{
			//Checks for space in between blocks
			for (unsigned int i = 0; i<blocks_in_use-1;i++)
			{
				if (((blocks[i].address+blocks[i].size) + n )< blocks[i+1].address)
				{
					found = 1;
					loc = &buffer[i] + 1;
				}
			}
			//Checks between last block and end of buffer
			if ((blocks[blocks_in_use-1].address + blocks[blocks_in_use-1].size + n) < (&buffer[BUFFER_SIZE-1]))
			{
				found = 1;
				loc = blocks[blocks_in_use-1].address + blocks[blocks_in_use-1].size;
			}
			//Sets found to -1 for future use
			if (found != 1)
			{
				found = -1;
			}
		}
			//}
		/*for (int i=0;i<BUFFER_SIZE;i++)
		{
			for (int j=0;j<n;j++)
			{
				for(int t=0;t<blocks_in_use;t++) //check if any blocks in use
				{
					if ((&buffer[i]+j >= blocks[t].address) && ((&buffer[i]+j) <= ((blocks[t].address) + (blocks[t].size))))
					{
						if(i==BUFFER_SIZE-n)//t==blocks_in_use-1 //could be seg fault prob here
						{
							found = -1;
							break;
						}
						else
						{
							break;
						}
					}
					else if(t==blocks_in_use-1 && j==n-1)
					{
						loc = &buffer[i];
						found = 1;
						break;
					}
				}
				if (found==-1 || found==1)
				{
					break;
				}
			}
			if (found==-1|| found==1)
			{
				break;
			}
		}*/
		//If no room returns null pointer
		if (found == -1)
		{
			return nullptr;
		}
		else
		{
			//makes new character block
		    blocks[blocks_in_use].address = loc;
		    blocks[blocks_in_use].size = n;
		    blocks_in_use += 1;
		    //Reorders the character blocks
		    for (unsigned int i =0;i<blocks_in_use;i++)
		    {
		    	if (blocks[blocks_in_use-1].address < blocks[i].address)
		    	{
		    		CharacterBlock temp= blocks[i];
		    		blocks[i]= blocks[blocks_in_use-1];
		    		for(unsigned int j = blocks_in_use-1;j>i;j--)
		    		{
		    			blocks[j] = blocks[j-1];

		    		}
		    		blocks[i+1] = temp;
		    	}
		    }
		    //Makes array bigger if necessary
		    if (blocks_in_use==blocks_size)
		    {
				size_t nextsize = blocks_size*2;
				unique_ptr<CharacterBlock[]> grown = make_unique<CharacterBlock[]>(nextsize);
				for (unsigned int i = 0; i<blocks_in_use;i++)
				{
					grown[i] = blocks[i];
				}
				blocks = move(grown);
				blocks_size = nextsize;
			}
		    return loc;
			
		}
	}
}
void FlexibleCharacterManager::free_chars(char* p) {
	// TODO: your implementation here
	//searches for correct block and fills it
	//moves all the blcoks over on
	for (unsigned int i = 0; i<blocks_in_use;i++)
	{
		if (p==blocks[i].address)
		{
			fill(p,p+blocks[i].size,'\0');
			for (;i<blocks_in_use-1;i++)
			{
				blocks[i] = blocks[i+1];
			}
			//makes last block equal to end of buffer
			blocks[blocks_in_use-1].address = &buffer[BUFFER_SIZE-1];
			blocks[blocks_in_use-1].size = 0;
			blocks_in_use -=1;
			//Halves the array if needed
			if (((double(blocks_in_use)/blocks_size)<.5) && blocks_size !=2)
			{
				size_t nextsize = blocks_size/2;
				unique_ptr<CharacterBlock[]> grown = make_unique<CharacterBlock[]>(nextsize);
				grown = move(blocks);
				blocks = move(grown);
				blocks_size = nextsize;
			}
			return;
		}
		else
		{
			continue;
		}
	}
	return;
}
