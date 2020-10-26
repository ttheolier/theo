#include "token_stack.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  TokenStack test;
  test.push(Token(TokenKind::NUMBER, 1));
  test.push(Token(TokenKind::NUMBER, 2));
  test.push(Token(TokenKind::NUMBER, 3));
  test.reverse();
  // test.reverse();
  cout << test << endl;
  cout << test.top() << endl;
  test.pop();
  cout << test << endl;
  test.reverse();
  cout << test << endl;
  return 0;
}
