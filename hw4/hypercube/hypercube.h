#ifndef HYPER_CUBE_H
#define HYPER_CUBE_H

#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>

struct Node {
	std::string word;
	std::string pred;
	int g;
	int h;

	Node(const std::string& word, const std::string pred, int g) : word(word), pred(pred), g(g), h(0) {
        // TODO: calculate h given the word.
        int value = 0;
        //iterate through string to calc h value and set it
        for (unsigned int i =0; i<word.size();i++)
        {
            if (word[i]== '0')
            {
                value+=1;
            }
        }
        this->h = value;
	}
};

struct NodePriority {
	bool operator()(const Node& lhs, const Node& rhs) {
        // TODO: implement priority for nodes.
        //calculates f value
        int left = lhs.g + lhs.h;
        int right = rhs.g + rhs.h;
        //if tie
        if(left == right)
        {
            //if h is tied
            if (lhs.h == rhs.h)
            {
                //iterate through each string, comparing values
                for (unsigned int i=0;i<lhs.word.size();i++)
                {
                    if (lhs.word[i]=='1' && rhs.word[i]=='0')
                    {
                        return true;
                    }
                    else if (lhs.word[i] == rhs.word[i])
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                //if somehow strings are same and all else tied, compare value of pred (saw on piazza)
                for (unsigned int i=0;i<lhs.word.size();i++)
                {
                    if (lhs.pred[i]=='1' && rhs.pred[i]=='0')
                    {
                        return true;
                    }
                    else if (lhs.pred[i] == rhs.pred[i])
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                //avoids warning for reaching end of non void.
                throw std::logic_error("Provided empty strings somehow");
            }
            //otherwise return bool
            else 
            {
                return lhs.h>rhs.h;
            }
        }
        //otherwise return bool
        else
        {
            return left>right;
        }
	}
};

struct SearchResult {
    // Whether or not there is a path.
    bool found;

    // The node labels on the path.
    std::vector<std::string> path;

    // The number of expansions made during search.
    size_t expansions;

    // Convenience for if found.
    SearchResult(std::vector<std::string> path, size_t expansions) : found(true), path(path), expansions(expansions) {}

    // Convenience for if not found.
    SearchResult(bool found, size_t expansions) : found(found), expansions(expansions) {}
};

class HyperCube {
public:
    // TODO: take an input file stream containing the permitted nodes for the
    // n-hypercube and populate the hypercube permitted node labels with the
    // set of nodes it lists. Do not change the signature.
    void read(std::istream& input);

    // TODO: take the starting node label string and return a vector of strings
    // containing the node labels on the optimal path from the starting node to
    // the ending node. If not path is found, the returned vector should
    // contain the string "no path". The last string in the returned vector
    // should otherwise be the number of expansions.
    SearchResult search(const std::string& start) const;

private:
   std::set<std::string> permitted;

   // TODO: optionally add any helper methods.
   //helper function that calculates valid neighbors for a node and returns them in a vector
   std::vector<Node> neighbors(const Node& current, const std::map<std::string,std::string>& explored) const;
};

#endif
