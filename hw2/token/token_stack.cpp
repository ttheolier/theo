#include "token_stack.h"
#include <stdexcept>


// TODO: return the top value on the stack.
const Token& TokenStack::top() const{
    if (this->empty()) {
        throw std::out_of_range("empty stack");
    }

    // TODO: complete function here
    else
    {
    	return this->list.at(0);
	}
}

// TODO: implement the TokenStack methods.
//uses list size
size_t TokenStack::size() const
{
	return this->list.size();
}
//checks size, true if empty, false otherwise
bool TokenStack::empty() const
{
	if (this->list.size()==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//uses insert at the head
void TokenStack::push(const Token& t)
{
	this->list.insert(0,t);
}
//uses remove on head
void TokenStack::pop()
{
	this->list.remove(0);
	return;
}
//uses list reverse
void TokenStack::reverse()
{
	this->list.reverse();
}
//just makes the os using << operator from list
std::ostream& operator<<(std::ostream& out, const TokenStack& stack)
{
	out<<stack.list;
	return out;
}