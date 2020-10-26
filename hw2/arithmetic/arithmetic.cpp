#include "token.h"
#include "token_stack.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <cctype>

using namespace std;

// THROW ALL EXCEPTIONS EXACTLY AS GIVEN IN THE COMMENTS
// You need only uncomment them to throw the exceptions
// under the correct conditons
// You can check the conditions using an if statement or
// switch statement
// For any problems with the expression format as well as attempting
// division by zero, throw the exception invalid_argument("Malformed");


TokenStack tokenize(std::string expression) {
    TokenStack stack;
    stringstream stream(expression);

    // Loop while there are still characters in the stream.
    while (stream.rdbuf()->in_avail()) {
        // TODO: push your tokens to the stack.
        stream >> ws;
        int c = stream.peek();
        //checks if character is digit
        if ( isdigit(c) )
        {
            //takes from stream into n, then pushes into stack
            int n;
            stream >> n;
            //if number is negative, pushes minus
            if (n<0)
            {
                n = -n;
                stack.push(Token(TokenKind::MINUS));
                stack.push(Token(TokenKind::NUMBER, n));
            }
            else
            {
                stack.push(Token(TokenKind::NUMBER, n));
            }
        }
        //if char is a parentheses or operator
        else
        {
            char chr;
            chr = stream.get();
            //check kind of char and push to stack accordingly
            if(chr == '(')
            {
                stack.push(Token(TokenKind::LP));
            }

            else if(chr == ')')
            {
                stack.push(Token(TokenKind::RP));           
            }

            else if(chr == '+')
            {
                stack.push(Token(TokenKind::PLUS));
            }

            else if(chr == '-')
            {
                stack.push(Token(TokenKind::MINUS));
            }

            else if(chr == '*')
            {
                stack.push(Token(TokenKind::TIMES));
            }

            else if(chr == '/')
            {
                stack.push(Token(TokenKind::DIVIDE));
            }

            else
            {
                throw invalid_argument("Malformed");
            }
        }
    }
    stack.reverse();
    return stack;
}

// Reduce is called when we encounter closing parentheses. If the expression
// is validly formed, we can expect there to be either a binary operation on
// the work stack. This method should pop the tokens in that operation,
// compute the result, and push it back onto the work stack as a new token.
void reduce(TokenStack& work) {
    TokenStack immediate;
    //Loop to pop from work into immediate
    while (work.top().kind != TokenKind::LP)
    {
        //if nothing in loop malformed
        if (work.size()==0)
        {
            throw invalid_argument("Malformed");
        }
        else
        {
            //checks token kind and pushes into immediate
            Token temp = work.top();
            work.pop();
            if(temp.kind == TokenKind::RP)
            {
                immediate.push(Token(TokenKind::RP));           
            }

            else if(temp.kind == TokenKind::PLUS)
            {
                immediate.push(Token(TokenKind::PLUS));
            }

            else if(temp.kind == TokenKind::MINUS)
            {
                immediate.push(Token(TokenKind::MINUS));
            }

            else if(temp.kind == TokenKind::TIMES)
            {
                immediate.push(Token(TokenKind::TIMES));
            }

            else if (temp.kind ==TokenKind::NUMBER)
            {
                immediate.push(Token(TokenKind::NUMBER,temp.value));
            }

            else
            {
                immediate.push(Token(TokenKind::DIVIDE));
            }

        }

    }
    work.pop();
    //if immediate is empty throw error
    if (immediate.empty())
    {
        throw invalid_argument("Malformed");   
    }
    //check for -p case
    else if (immediate.top().kind == TokenKind::MINUS)
    {
        immediate.pop();
        if (immediate.top().kind != TokenKind::NUMBER)
        {
            throw invalid_argument("Malformed");
        }
        else
        {
            Token tempT = immediate.top();
            int temp = immediate.top().value;
            temp = -temp;
            immediate.pop();
            if (!immediate.empty())
            {
                throw invalid_argument("Malformed");
            }
            else
            {
                tempT.value = temp;
                work.push(tempT);
                return;
            }
        }
    }
    //all other cases
    else
    {
        //checks the first tokens
        Token oper(TokenKind::PLUS);
        int temp;
        Token tempT = immediate.top();
        if (immediate.top().kind != TokenKind::NUMBER)
        {
            throw invalid_argument("Malformed");
        }
        else
        {
            immediate.pop();
        }
        //if size of immediate is now zero, push to work 
        if (immediate.size()== 0 )
        {
            work.push(tempT);
            return;
        }
        //ensures operator is correct
        if (immediate.top().kind != TokenKind::PLUS && immediate.top().kind != TokenKind::MINUS && immediate.top().kind != TokenKind::TIMES 
        && immediate.top().kind != TokenKind::DIVIDE)//edit
        {
            throw invalid_argument("Malformed");
        }
        //sets oper.kind so that only correct chains will work in future loop
        else
        {
            oper.kind = immediate.top().kind;
            immediate.pop();
        }
        if (immediate.top().kind != TokenKind::NUMBER)
        {
            throw invalid_argument("Malformed");
        }
        else
        {
            //does operation based on operator kind
            if (oper.kind == TokenKind::PLUS)
            {
                temp = tempT.value + immediate.top().value;
                immediate.pop();
                tempT.value = temp;
                immediate.push(tempT);
            }
            else if(oper.kind == TokenKind::MINUS)
            {
                temp = tempT.value - immediate.top().value;
                immediate.pop();
                if (temp<0)
                {
                    temp = -temp;
                    tempT.value=temp;
                    immediate.push(tempT);
                    immediate.push(TokenKind::MINUS);
                }
                else
                {
                    tempT.value = temp;
                    immediate.push(tempT);
                }
            }
            else if(oper.kind == TokenKind::TIMES)
            {
                temp = tempT.value * immediate.top().value;
                immediate.pop();
                tempT.value = temp;
                immediate.push(tempT);
                cerr<<"after times"<<immediate<<endl;
            }
            //division, checks division by zero
            else
            {
                if (immediate.top().value == 0)
                {
                    throw invalid_argument("Malformed");
                }
                else
                {
                    temp = tempT.value / immediate.top().value;
                    immediate.pop();
                    tempT.value = temp;
                    immediate.push(tempT);
                }
            }
            //if only one number in immediate, push to work
            if (immediate.size() == 1)
            {
                cerr<<immediate<<endl;
                work.push(tempT);
                cerr<<"work in reduce"<<work<<endl;
                return;

            }
        }
        //while loop for chains
        while (immediate.top().kind != TokenKind::RP)
        {
            //checks for minus case again
            if (immediate.top().kind == TokenKind::MINUS)
            {
                immediate.pop();
                if (immediate.top().kind != TokenKind::NUMBER)
                {
                    throw invalid_argument("Malformed");
                }
                else
                {
                    Token tempT = immediate.top();
                    temp = immediate.top().value;
                    temp = -temp;
                    immediate.pop();
                    if (!immediate.empty())
                    {
                        throw invalid_argument("Malformed");
                    }
                    else
                    {
                        tempT.value = temp;
                        work.push(tempT);
                        return;
                    }
                }
            }
            Token tempT = immediate.top();
            if (immediate.top().kind != TokenKind::NUMBER)
            {
                throw invalid_argument("Malformed");
            }
            else
            {
                immediate.pop();
            }
            //if immediate empty pop to work
            if (immediate.size()== 0 )
            {
                work.push(tempT);
                return;
            }
            //make sure chained operations use same operator
            if (immediate.top().kind != oper.kind)
            {
                throw invalid_argument("Malformed");
            }
            else
            {
                immediate.pop();
            }
            if (immediate.top().kind != TokenKind::NUMBER)
            {
                throw invalid_argument("Malformed");
            }
            //does operations and pushes, same as before while loop
            else
            {
                if (oper.kind == TokenKind::PLUS)
                {
                    temp = tempT.value + immediate.top().value;
                    immediate.pop();
                    tempT.value = temp;
                    immediate.push(tempT);
                }
                else if(oper.kind == TokenKind::MINUS)
                {
                    temp = tempT.value - immediate.top().value;
                    immediate.pop();
                    if (temp<0)
                    {
                        temp = -temp;
                        //Token temptT(TokenKind::NUMBER,temp);
                        tempT.value = temp;
                        immediate.push(tempT);
                        immediate.push(TokenKind::MINUS);
                    }
                    else
                    {
                        tempT.value = temp;
                        immediate.push(tempT);
                    }
                }
                else if(oper.kind == TokenKind::TIMES)
                {
                    temp = tempT.value * immediate.top().value;
                    immediate.pop();
                    tempT.value = temp;
                    immediate.push(tempT);
                }
                else
                {
                    if (immediate.top().value == 0)
                    {
                        throw invalid_argument("Malformed");
                    }
                    else
                    {
                        temp = tempT.value % immediate.top().value;
                        immediate.pop();
                        tempT.value = temp;
                        immediate.push(tempT);
                    }
                }
            }
        }
    }
}
    


//evaluates the expression
int evaluate(std::string expression) {
    TokenStack tokens = tokenize(expression);
    TokenStack work;
    //if the token kind is RP, throw malformed
    if (tokens.top().kind == TokenKind::RP)
    {
        throw invalid_argument("Malformed");
    }
    //while tokens isnt empty
    while (!tokens.empty())
    {
        Token thing = tokens.top();
        //if top is RP, pop and reduce
        if (thing.kind == TokenKind::RP)
        {
            tokens.pop();
            reduce(work);
        }
        //else pop and push to work
        else
        {
            tokens.pop();
            work.push(thing);
        }

    }
    //if work is exactly one number, return it
    if (work.size()==1 && work.top().kind == TokenKind::NUMBER)
    {
        return work.top().value;
    }
    else
    {
        throw invalid_argument("Malformed");
    }
}



// Please DO NOT CHANGE MAIN
int main(int argc, char** argv) {
    if (argc <= 1) {
        cerr << "Expect an expression..." << endl;
        return -1;
    }

    try {
        cout << evaluate(argv[1]) << endl;
    } catch (invalid_argument &e) {
        cerr << "error: " << e.what() << endl;
    }
    return 0;
}


// If you're interested in extending your parser to support things like order
// of operations, unary operators, and single values, feel free to ping me
// on Discord (noahbkim) once you've finished the assignment as is. This will
// not give you any extra credit or improve your score in any way; it's just
// something fun and cool.
