// ache; Cheng, Allan

#include <string>
#include <fstream>
#include <iostream>
using namespace std;
#include "classes.h"
#include <ctype.h>

void buildAVL(string input);

int main()
{
  unsigned int length, i, pos;
  char letter;
  string input;
  AVL<string, string>* tree = new AVL<string, string>;
  AvlNode<string, string>* root = new AvlNode<string, string>;  

  cin.seekg(0, ios::end);
  length = cin.tellg();
  cin.seekg(0, ios::beg);

  for (i = 0; i < length; i++)
  {
    cin.get(letter);

    while ( i < length && isalnum(letter))
    {
      if (isupper(letter))
        letter = tolower(letter);
      input.insert(input.end(), letter);
      if (input.size() > 256)
        break;
      i++;
      cin.get(letter);
    }
    if (input.size() != 0)
    {
      tree->Insert(input, input);
      input.clear();
    }
  }
  cout << "<?xml version=\"1.0\"?>\n" << "<dictionary>\n";
  root = tree->getRoot();
  tree->print(root);
  cout << "</dictionary>\n";
}

