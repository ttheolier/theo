#include <iostream>
#include <string>

using namespace std;

// Implement below
bool are_paren_balanced(const string& expression);

// We have suggested a helper method, but feel free to write whatever you see fit
bool are_paren_balanced(const string& expression, size_t& i, char expected_closing);

string deleter(string& str,char expected_closing);

// Do not change this method
int main(int argc, char* argv[]) {

    // Check if an expression has been passed to the program
    if (argc != 2) {
        cerr << "error: expected expression to check!" << endl;
        return -1;
    }

    // The second argument is the expression string in the format specified and
    // promised in the assignment page. You do not need to do any error checking
    // except for checking the parentheses.
    string expression(argv[1]);
    if (are_paren_balanced(expression)) {
        cout << "correct" << endl;
    } else {
        cout << "incorrect" << endl;
    }

    return 0;
}

// Some notes:
// - This method must be implemented recursively.
// - When debugging, make sure to output to cerr rather than cout. This will
//   prevent any leftover debug statements from confusing the automated
//   grading and will make sure output is guaranteed to be written to the
//   terminal in case your program crashes.
bool are_paren_balanced(const string& expression) {
    // TODO: your code here
    //sets a temp variable equal to expression
    string temp=expression;
    string &temp1= temp;
    size_t strsize = temp1.size();
    //nothing in string base case
    if (temp1.size()==0)
    {

    	return true;
    }
    //base case for finding a closed parenthese first
    if (expression[0]==']' || expression[0]==')' )
    {
    	return false;
    }
    //case for if open parenthese is found, erases it, recduce size, and passes into helper function
    if (expression[0]=='(')
    {
    	//cerr<<strsize<<endl;
    	temp.erase(0,1);
    	strsize = strsize-1;
    	//cerr<<temp<< " "<<strsize;
        return are_paren_balanced(temp, strsize,')');
    }
    //case for if open bracket is found, erases it, reduce size, and passes into helper function
    if (expression[0]=='[')
    {
    	temp.erase(0,1);
    	strsize = strsize-1;
    	return are_paren_balanced(temp, strsize,']');
    }
    //or else, erases the character, reduces size, and keeps looking
    else
    {
    	temp.erase(0,1);
    	strsize = strsize-1;
    	return are_paren_balanced(temp);
    }
}

// Add any additional function implementations here.
//
// If you want to use the suggested helper method, you'll have to write its
// definition here.
bool are_paren_balanced(const string& expression, size_t& i, char expected_closing)
{
	//declares temp variables
	string temp=expression;
    string &temp1= temp;
    size_t strsize = temp1.size();
    //nothing in string base case
	if (expression.size()==0)
	{
		return false;
	}
	//search for closed parenthese case
	if (expected_closing==')')
    {
    	//searches left to right for closed parenthese
    	if (expression[0]==')')
    	{

            temp.erase(0,1);
            strsize = strsize-1;
    		return are_paren_balanced(temp);
    	}
    	if (expression[0]=='(')
		{
			//cerr<<strsize<<endl;
			temp.erase(0,1);
			strsize = strsize-1;
			//cerr<<temp<< " "<<strsize;
		    return are_paren_balanced(temp, strsize,')');
		}
		//case for if open bracket is found, erases it, reduce size, and passes into helper function
		if (expression[0]=='[')
		{
			temp.erase(0,1);
			strsize = strsize-1;
			return are_paren_balanced(temp, strsize,']');
		}
    	//if not found search next character
    	else
    	{
            temp.erase(0,1);
            strsize = strsize-1;
    		return are_paren_balanced(temp,strsize,')');
    	}
        
    }
    //search for closed bracket case
    if (expected_closing==']')
    {
    	//cerr<<"a";
    	//searches left to right for closed parenthese
    	if (expression[0]==']')
    	{
            temp.erase(0,1);
            strsize = strsize-1;
    		return are_paren_balanced(temp);
    	}
    	if (expression[0]=='(')
		{
			//cerr<<strsize<<endl;
			temp.erase(0,1);
			strsize = strsize-1;
			//cerr<<temp<< " "<<strsize;
			if (are_paren_balanced(temp, strsize,')'))
			{
				cerr<<"a";
				temp = deleter(temp,')');
				strsize = strsize-temp.size();
		    return are_paren_balanced(temp, strsize,']');
			}
			else
			{
				return false;
			}
		}
		//case for if open bracket is found, erases it, reduce size, and passes into helper function
		if (expression[0]=='[')
		{
			temp.erase(0,1);
			strsize = strsize-1;
			return are_paren_balanced(temp, strsize,']');
		}
    	//if not found search next character
    	else
    	{
            temp.erase(0,1);
            strsize = strsize-1;
    		return are_paren_balanced(temp,strsize,']');
    	}
        
    }
    //avoids warning
    else
    {
    	return false;
    }
}

string deleter(string& str,char expected_closing)
{
	if (expected_closing == ')')
	{
		size_t spot = str.find_first_of(')');
		
		cerr<<str;
		str.erase(0,spot);
		cerr<<str;
        return str;

	}
	if (expected_closing == ']')
	{
		size_t spot = str.find_first_of(')');
		
		cerr<<str;
		str.erase(0,spot);
		cerr<<str;
        return str;

	}
}