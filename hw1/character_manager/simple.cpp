#include "simple.h"
#include<algorithm>
using namespace std;


char* SimpleCharacterManager::alloc_chars(size_t size) {
	// TODO: your implementation here
	//sets location as the first avavilable and updates the first available location
	char* loc = first_available_address;
	first_available_address = (first_available_address+size);
	return loc;
	/*int loc;
	for (int i=0;i<BUFFER_SIZE;i++)
	{
		if (&buffer[i]== nullptr)
		{
			loc = i;
			break;
		}
		else
		{
			loc= -1;
			break;
		}
	}
	if (loc == -1 || (unsigned int)(BUFFER_SIZE-loc)<size +1)
	{
		return nullptr;
	}
	else
	{
		return &buffer[loc];
	}*/
}

void SimpleCharacterManager::free_chars(char* address) {
	// TODO: your implementation here
	//fills with null pointer and resets first available
	fill(address,&buffer[BUFFER_SIZE-1],'\0');
	first_available_address = address;
}
