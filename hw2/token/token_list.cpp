#include "token_list.h"
#include <stdexcept>


size_t TokenList::size() const {
    return this->_size;
}

// TODO: implement the TokenList methods.

Token& TokenList::at(size_t index) {
    if (this->size() == 0) {
        throw std::out_of_range("no items");
    }

    // TODO: complete this function here
    //Ensures no wrap around
    size_t position = index % this->_size;
    //Iterates until speified index, returns reference 
    std::shared_ptr<Item> current = head;
    if (position ==this->_size-1)
    {
        Token& val = this->head->previous->value;
        return val;
    }
    else
    {
        for (unsigned int i = 0; i <=position;i++)
        {
            if (i==position)
            {
                //does this work
                Token& val = current->value;
                return val;
            }
            else
            {
                current = current->next;

            }
        }
        //prevents non void warning
        throw std::invalid_argument("Malformed");
    }

}

const Token& TokenList::at(size_t index) const {
    if (this->size() == 0) {
        throw std::out_of_range("error");
    }
    //Ensures no wrap around
    size_t position = index % this->_size;
    //Iterates until speified index, returns reference
    std::shared_ptr<Item> current = head;
    if (position ==this->_size-1)
    {
        Token& val = this->head->previous->value;
        return val;
    }
    else
    {
        for (unsigned int i = 0; i <=position;i++)
        {
            if (i==position)
            {
                //does this work
                Token& val = current->value;
                return val;
            }
            else
            {
                current = current->next;

            }
        }
        //prevents non void warning
        throw std::invalid_argument("Malformed");
    }
}

//Not implemeneted by me
std::ostream& operator<<(std::ostream& out, const TokenList& list)  {
    out << "{";
    std::shared_ptr<TokenList::Item> cursor = list.head;
    if (cursor != nullptr) {
        for (size_t i = 0; i < list.size() - 1; i++) {
            out << cursor->value << ", ";
            cursor = cursor->next;
        }
        out << cursor->value;
    }
    return out << "}";
}
//Copy assignment operator
TokenList& TokenList::operator=(TokenList const& other)
{
    //Case where lists are same size
    if (this->_size == other.size())
    {
        //copying nothing
        if (other.size() == 0)
        {
            this->head = nullptr;
            this->_size= 0;

        }
        //copies elements by element
        else
        {
            std::shared_ptr<Item> iter;
            std::shared_ptr<Item> itero = other.head;
            iter = std::make_shared<Item> (*itero);
            for (unsigned int i=0;i<this->_size;i++)
            {
                iter->next = std::make_shared<Item> (*itero->next);
                iter->next->previous = std::make_shared<Item> (*itero->next->previous);
                iter = iter->next;
                itero = itero->next;


            }
        }
        TokenList& val = *this;
        return val;
    }
    //Case where this is size 0, push back
    else if (this->_size == 0)
    {
        for( unsigned int j=0;j<other.size();j++)
        {
            this->push_back(other.at(j));
        }
        return *this;
    }
    //case where this is smaller list but not size 0
    else if (this->_size < other.size())
    {
        //element by element copy and then push back
        unsigned int i=0;
        std::shared_ptr<Item> iter;
        std::shared_ptr<Item> itero = other.head;
        iter = std::make_shared<Item> (*itero);
        for (i=0;i<this->_size;i++)
        {
            iter->next = std::make_shared<Item> (*itero->next);
            iter->next->previous = std::make_shared<Item> (*itero->next->previous);
            iter = iter->next;
            itero = itero->next;


        }
        for( unsigned int j=i;j<other.size();j++)
        {
            this->push_back(other.at(j));
            
        }
        return *this;
    }
    //Case where this is larger list
    else if (this->_size > other.size())
    {
        //if copying empty list
        if (other.size() == 0)
        {
            for (unsigned int j=0;j<this->_size;j++)
            {
                this->remove(j);
            }
            this->head = nullptr;
            this->_size= 0;

        }
        //element by element copy and then remove
        unsigned int i=0;
        std::shared_ptr<Item> iter;
        std::shared_ptr<Item> itero = other.head;
        iter = std::make_shared<Item> (*itero);
        for (i=0;i<other.size();i++)
        {
            iter->next = std::make_shared<Item> (*itero->next);
            iter->next->previous = std::make_shared<Item> (*itero->next->previous);
            iter = iter->next;
            itero = itero->next;


        }
        for (unsigned int j=i;j<this->_size;j++)
        {
            this->remove(j);
        }
        return *this;
    }
    //shouldnt occur
    else
    {
        //cerr something wrong, return this
        std::cerr<<"Somethings wrong"<<std::endl;
        return *this;
    }
    
}
//copy constructor
TokenList::TokenList(TokenList const& other)
{
    //if list is empty
    if (other.size() == 0)
    {
        this->head = nullptr;
        this->_size= 0;

    }
    //else push back
    else
    {
        this->_size = 0;
        this->head = other.head;
        std::shared_ptr<Item> iter = this->head;
        for (unsigned int i =0; i<other.size(); i++)
        {
            this->push_back(other.at(i));
        }
    }
}
//Destructor 
TokenList::~TokenList()
{
    //removes all items
    size_t a = this->_size;
    for (unsigned int i =0; i<a; i++)
    {
         this->remove(0);
    }

}
//push to end of list
void TokenList::push_back(Token value)
{
    //if this size is 0,update head and pointers to new item
    if (this->_size==0)
    {
        std::shared_ptr<Item> create = std::make_shared<Item>(Item(value));
        this->head = create;
        this->head->next = create;
        this->head->previous = create;
        this->_size += 1;
        return;
    }
    //otherwise, get the first and last item, and link them to new item
    else
    {
        std::shared_ptr<Item> create = std::make_shared<Item>(Item(value));
        std::shared_ptr<Item> before = (this->find(this->_size-1));
        this->link(before,create);
        this->link(create,this->head);
        this->_size += 1;
        before.reset();
        create.reset();
        return; 
    }

}

void TokenList::insert(size_t index, Token value)
{
    //if size is zero just push back
    if (this->_size==0)
    {
        this->push_back(value);
        return;
    }
    //prevents wrap around
    int position = index% this->_size;
    //if index zero, get first and last item and link to new in correct order
    if (position == 0)
    {
        std::shared_ptr<Item> beg = (this->find(0));
        std::shared_ptr<Item> end = (this->find(this->_size-1));
        this->head = std::make_shared<Item> (Item(value));
        this->link(end,this->head);
        this->link(this->head,beg);
        this->_size += 1;

    }
    //otherwise link the old index and old index-1 with new item at index
    else
    {
        std::shared_ptr<Item> create = std::make_shared<Item> (Item(value));
        std::shared_ptr<Item> before = (this->find(index-1));
        std::shared_ptr<Item> after = (this->find(index));
        this->link(before,create);
        this->link(create, after);
        this->_size += 1;
        before.reset();
        after.reset();
    }
}

void TokenList::remove(size_t index)
{
    //If empty list
    if (this->_size == 0)
    {
        return;
    }
    else
    {
        std::shared_ptr<Item> del (this->find(index));
        //if removing head of size one list, make sure pointers reset
        if (this->_size == 1)
        {
            del->next.reset();
            del->previous.reset();
            head.reset();
            this->_size -= 1;
        }
        //otherwise, link items to left and right of removed item
        else
        {
            link(del->previous,del->next);
            //if removing head, set head correctly
            if (this->head== del)
            {
                this->head= del->next;
            }
            del->next.reset();
            del->previous.reset();
            this->_size -= 1;
        }
        return;
    }
    
}

void TokenList::reverse()
{
    //uses iterating pointer to swap previous and next for each item
    std::shared_ptr<Item> iter = this->head;
    for (unsigned int i = 0;i<this->_size;i++)
    {
        (iter->next).swap(iter->previous);
        iter = iter->previous;
        //std::cerr<<iter->value<<std::endl;
    }
    iter.reset();
    //updates the head
    this->head = this->head->next;
}
//helper functio to return sharedptr to Item at desired index
std::shared_ptr<TokenList::Item> TokenList::find(size_t index)
{
    //case for no items
    if (this->_size == 0) {
        throw std::out_of_range("no items");
    }
    //prevent wrap around
    size_t position = index % this->_size;
    //iterate until correct position and return
    std::shared_ptr<Item> current = this->head;
    for (unsigned int i = 0; i <=position;i++)
    {
        if (i==position)
        {
            return current;
        }
        else
        {
            current = current->next;
            
        }
    }
    //prevents non-void warning
    return nullptr;

}
//link helper function, very simple, links two nodes unidirectionally,
//called once for remove, twice when adding item
void TokenList::link(std::shared_ptr<Item> ind1, std::shared_ptr<Item> ind2)
{
    ind1->next = ind2;
    ind2->previous = ind1;
    return;

}