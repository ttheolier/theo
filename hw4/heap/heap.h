#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>


template<typename T, typename TComparator = std::less<T> >
class Heap {
public:
    // Constructs an m-ary heap for any m >= 2
    Heap(size_t m, TComparator comparator = TComparator());

    // Destructor as needed
    ~Heap();

    // Adds an item
    void push(const T& item);

    // returns the element at the top of the heap
    //  max (if max-heap) or min (if min-heap)
    const T& top() const;

    // Removes the top element
    void pop();

    // returns true if the heap is empty
    bool empty() const;
    //print function made for debugging commented out
    //void print();

private:
    // Add whatever helper functions and data members you need below
	
    // heapify() helper function
    void heapify(size_t loc);

    // Data
    std::vector<T> store;
    size_t m;
    TComparator comparator;
};
//Constructor
template<class T, class TComparator>
Heap<T,TComparator>::Heap(size_t m, TComparator c) 
{
	//initialize
	this->m = m;
	this->comparator = c;
}
//Destructor, empty
template<class T, class TComparator>
Heap<T,TComparator>::~Heap()
{

}
//heapify function, recursive
template<class T, class TComparator>
void Heap<T,TComparator>::heapify(size_t loc)
{
	//if location is out of bounds or if it doesnt have a left child
	if (loc>store.size()-1 || loc*m+1 >store.size()-1)
	{
		return;
	}
	//intializing varibles for loop
	bool valset = false;
	bool found = false;
	T bestcomp;
	size_t cloc;
	//loop through all children
	for (unsigned int i = 1;i<=m;i++)
	{
		//if child doesnt exist break
		if (loc*m+i >store.size()-1)
		{
			break;
		}
		//if comp of child to parent is true
		if (comparator(store[loc*m+i],store[loc]))
		{
			//if first valid value found
			if (!valset)
			{
				//set bools to true
				found = true;
				valset = true;
				//store value and location of item to swap
				bestcomp = store[loc*m+i];
				cloc = loc*m+i;
			}
			//if another valid value has been found
			else
			{
				//store the lowest/highest, based left to right
				if (comparator(store[loc*m+i],bestcomp))
				{
					bestcomp = store[loc*m+i];
					cloc = loc*m+i;	
				}
			}

		}
	}
	//if no value to swap found return
	if (found == false)
	{
		return;
	}
	//otherwise swap and heapify on where the parent was swapped to
	else
	{
		//std::cerr<<store[loc]<<" "<<store[cloc]<<" "<<store.size()<<std::endl;
		iter_swap(store.begin()+loc,store.begin()+cloc);
		this->heapify(cloc);
	}

}
//Push
template<class T, class TComparator>
void Heap<T,TComparator>::push(const T& item)
{
	//push back item
	this->store.push_back(item);
	//initialize while loop
	bool loop = true;
	//if vector is size 2 or more
	if (store.size()!=1)
	{
		//set index variable
		int curloc = int(store.size())-1;
		//while loop bool true and pushed value not at root node
		while (loop && curloc != 0)
		{
			//if comparator is true when comparing pushed value to its parent, swap and update index, continue loop
			if (comparator(store[curloc],store[(curloc-1)/m]))
			{
				iter_swap(store.begin()+curloc,store.begin()+((curloc-1)/m));
				curloc = (curloc -1)/m;
			}
			//otherwise, brekas out of while loop
			else 
			{
				loop = false;
			}
		}
		
	}
}
//Top 
template<class T, class TComparator>
const T& Heap<T, TComparator>::top() const {
    // If nothing to top:
    // throw std::logic_error("can't top an empty heap");
    if (store.empty())
    {
    	throw std::logic_error("can't top an empty heap");
    }
    else
    {
    	//returns top constant time
    	return store.front();
    }
}
//pop done
template<class T, class TComparator>
void Heap<T, TComparator>::pop() {
    // If nothing to pop
    // throw std::logic_error("can't pop an empty heap");
    if (store.empty())
    {
    	throw std::logic_error("can't pop an empty heap");
    }
    //if vector is size 1 just pop
    else if (store.size()==1)
    {
    	store.pop_back();
    }
    //if vector is size two, just remove first from vector because already in order
    else if (store.size()==2)
    {
    	T temp = store.back();
    	//std::cerr<<store[0]<<store[1]<<std::endl;
    	store.pop_back();
    	store.pop_back();
    	store.push_back(temp);
    }
    //any other size
    else
    {
    	//swap front and back, and pop_back off
    	iter_swap(store.begin(),store.begin()+store.size()-1);
    	store.pop_back();
    	//heapify at root node
    	this->heapify(0);
    }
}
//empty, self explanatory
template<class T, class TComparator>
bool Heap<T, TComparator>::empty() const {
	if (store.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//debbuging print function, commented out for grading
/*template<class T, class TComparator>
void Heap<T, TComparator>::print()
{
	for (unsigned int i = 0;i<store.size();i++)
	{
		std::cerr<<store[i]<<" ";
	}
}*/


#endif
