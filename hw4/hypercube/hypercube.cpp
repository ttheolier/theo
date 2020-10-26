#include "hypercube.h"
#include <iostream>
using namespace std;


void HyperCube::read(istream& input) {
    // TODO: implement
    
    size_t numr;
    string word;
    //gets rows
    input>>numr;
    //fail check
    if (input.fail())
    {
        throw std::logic_error("Malformed input");
    }
    //gets empty end
    getline(input,word);
    //for each row, get value and insert into permitted
    for (unsigned int i = 0;i<numr;i++)
    {
        getline(input,word);
        //fail check
        if (input.fail())
        {
            throw std::logic_error("can't pop an empty heap");
        }
        this->permitted.emplace(word);
    }
}

std::vector<Node> HyperCube::neighbors(const Node& current,const map<string,string>& explored) const
{
    std::vector<Node> neighbor;
    //iterate through strings
    for (unsigned int i = 0;i<current.word.size();i++)
    {
        string temp = current.word;
        //flips temp based on value of string at i
        if (current.word[i]=='1')
        {
            temp[i] = '0';
        }
        else
        {
            temp[i] = '1';
        }
        //ensures node is in permitted and not explored
        if ((this->permitted.find(temp)!= this->permitted.end())&&(explored.find(temp)==explored.end()))
        {
            //cerr<<"put in vector"<<endl;
            neighbor.push_back(Node(temp,current.word,current.g+1));
        }
    }
    return neighbor;
}

SearchResult HyperCube::search(const string& start) const {
    // TODO: implement

    // Initialize ending node of all 1's.
    std::string end(start.size(), '1');

    // Instantiate priority queue to use for A* algorithm.
    std::priority_queue<Node, std::vector<Node>, NodePriority> unvisited;

    // Initialize the number of expansions used by the algorithm and path.
    size_t expansions = 0;
    std::vector<std::string> path;

    // Add any variables needed for A* algorithm
    //map with string for word and for pred
    std::map<std::string,std::string> explored;

    // Implement A* algorithm. Remember to add node label strings on the path
    // to the results vector. Order of the strings in the vector matters. Make
    // sure to return a SearchResult object.
    //push start node with specific pred value
    unvisited.push(Node(start,"hi",0));
    //while the top is not the target and the queue isnt empty
    while (unvisited.top().word != end && (!unvisited.empty()))
    {
        //remove top node
        Node temp = unvisited.top();
        unvisited.pop();
        //if already explored, continue without updating expansions
        if (explored.find(temp.word)!= explored.end())
        {
            continue;
        }
        //emplace into explored map with pred
        explored.emplace(temp.word,temp.pred);
        //get vector of neighbors
        std::vector<Node> neighbor = this->neighbors(temp,explored);
        //while vector not empty push neighbors to stack
        while(!neighbor.empty())
        {
            unvisited.push(neighbor.back());
            neighbor.pop_back();
        }
        expansions++;
    }
    //temporary path vector in reverse order
    std::vector<std::string> temppath;
    //if top isnt target then return false
    if (unvisited.top().word != end)
    {
        return SearchResult(false,expansions);
    }
    //if target found
    else
    {
        //make trace variable
        std::string trace = unvisited.top().word;
        //push it
        temppath.push_back(trace);
        //set to pred
        trace = unvisited.top().pred;
        //while trace is not at start value
        while (explored.find(trace)->second!="hi" )
        {
            //push trace and set to pred
            temppath.push_back(trace);
            trace = explored.find(trace)->second;

        }
        //push start value
        temppath.push_back(trace);
        //reverse order into path
        while(!temppath.empty())
        {
            path.push_back(temppath.back());
            temppath.pop_back();
        }
        //return SearchResult
        return SearchResult(path,expansions);
    }
}
