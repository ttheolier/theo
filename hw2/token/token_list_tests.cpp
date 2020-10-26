#include "token_list.h"
#include <iostream>
#include <string>

using namespace std;
// getting rid of copy assign takes one away
// other is from first pushback

int main() {
  TokenList test;
  // cerr<<"hi";
  test.push_back(Token(TokenKind::NUMBER, 1));
  // cerr<<"wow"<<endl;
  test.push_back(Token(TokenKind::NUMBER, 2));
  // cerr<<"dude"<<endl;
  test.push_back(Token(TokenKind::NUMBER, 3));
  cout << "After push back: " << test << endl;
  // cerr<<"whoa"<<endl;

  test.reverse();
  cout << "After reverse: " << test << endl;

  TokenList test2 = test;
  cout << "Original after copy: " << test << endl;
  cout << "Copy after copy: " << test2 << endl;

  test.remove(0);
  // test.remove(0);
  // test.remove(0);
  // cerr<<"whoa"<<endl;
  cout << "Original after removing 1: " << test << endl;
  cout << "Copy after removing 1 from original: " << test2 << endl;

  test.at(1) = Token(TokenKind::NUMBER, 2);
  cout << "After replace 3 with 3: " << test << endl;

  // size_t i = 1;
  // test.insert(i,Token(TokenKind::NUMBER, 4));
  // cout<<"After insert: "<< test<<endl;

  return 0;
}
