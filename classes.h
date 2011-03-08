// ache; Cheng, Allan
#include <string.h>

template<class K, class E>
class AVL;

template <class K, class E>
class AvlNode
{
  friend class AVL<K, E>;
  public:
  AvlNode(){}
  AvlNode(const K& k, const E& e)
  {
    key = k; element = e; bf=0; leftChild = rightChild = 0,
    freq = 1;
  }
  private:
    K key;
    E element;
    int bf;
    unsigned int freq; 
    AvlNode<K, E> *leftChild, * rightChild;
};

template <class K, class E>
class AVL
{
  public:
    AVL(){root = NULL;}
    E& Search(const K&) const;
    void Insert(const K&, const E&);
    void Delete(const K&);
    void print(AvlNode<K, E>* node) //inorder
    {
      if (node->leftChild != 0)
        print(node->leftChild);

      cout << "<entry word=\"" << node->element << "\" frequency=\""
           << node->freq << "\" bf=\"";
      if (node->bf == 1)
        cout << "+";
      cout << node->bf << "\" />" << endl;

      if (node->rightChild != 0)
        print(node->rightChild);
    }
    AvlNode<K,E>* getRoot(){return root;}
    void printRoot(){cout << root->element << endl;}
  private:
    AvlNode<K,E> *root;
};

template <class K, class E>
void AVL <K, E>::Insert(const K& k, const E& e)
{
  if (!root) // special case: empty tree
  {
    root = new AvlNode<K, E>(k, e);
    return;
  }
  
  // Phase 1: Locate insertion point for e.
  AvlNode<K,E> *a = 0, //most recent node with bf = +/- 1
               *pa = 0, //parent of a
               *p = root, //p moves through the tree
               *pp = 0; // parent of p
  while (p)
  {
    if (p->bf)
    {
      a = p;
      pa = pp;
    }

    if (strcasecmp(k.c_str(), (p->key).c_str()) < 0)
    {
      pp = p;
      p = p->leftChild;
    }
    else 
      if (strcasecmp(k.c_str(), (p->key).c_str()) > 0)
      {
        pp = p;
        p = p->rightChild;
      }
      else
      {
        (p->freq)++;
        p->element = e;
        return; //k already in tree
      }  
  } //while

  //Phase 2: Insert and rebalance.
  AvlNode<K, E> *y = new AvlNode<K, E>(k, e);
  //y = new node to be inserted

  if (strcasecmp(k.c_str(), (pp->key).c_str()) < 0)
    pp->leftChild = y; // insert as left child
  else
    pp->rightChild = y; // insert as right child

  //Adjust balance factors of nodes on path from a to pp
  int d;
  AvlNode<K, E> *b, // child of a
                *c; // child of b

  if (a == 0) //entire bf was 0
    a = root;

  if (strcasecmp(k.c_str(), (a->key).c_str()) > 0)
  {
    b = p = a->rightChild;
    d = -1;
  }
  else
  {
    b = p = a->leftChild;
    d = 1;
  }

  while (p && p != y)
  {
    if (strcasecmp(k.c_str(), (p->key).c_str()) > 0)
    {
      p->bf = -1;
      p = p->rightChild;
    }
    else //height of left increases by 1
    {
      p->bf = 1;
      p = p->leftChild;
    }
  }
  //Is tree unbalanced?

  if (!(a->bf) || !(a->bf+d)) //height of right increases by 1
  {
    a->bf+=d;
    return;
  }

  if (d==1) //left imbalance
  {
    if (b->bf == 1) //Rotation type LL
    {
      a->leftChild = b->rightChild;
      b->rightChild = a;
      a->bf = 0;
      b->bf = 0;
    }
    else //rotation type LR
    {
      c = b->rightChild;
      b->rightChild = c->leftChild;
      a->leftChild = c->rightChild;
      c->leftChild = b;
      c->rightChild = a;
      switch(c->bf)
      {
        case 1:
          a->bf = -1;
          b->bf = 0;
          break;
        case -1:
          b->bf = 1;
          a->bf = 0;
          break;
        case 0:
          b->bf = 0;
          a->bf = 0;
          break;
      }

      c->bf = 0;
      b = c; //b is the new root
    } //end of LR
  } //end of imbalance
  else if (d==-1)//right inbalance
  {
    if (b->bf == -1) //Rotation type RR
    {
      a->rightChild = b->leftChild;
      b->leftChild = a;
      a->bf = 0;
      b->bf = 0;
    }
    else //rotation type RL
    {
      c = b->leftChild;
      b->leftChild = c->rightChild;
      a->rightChild = c->leftChild;
      c->rightChild = b;
      c->leftChild = a;
      switch(c->bf)
      {
        case -1:
          a->bf = 1;
          b->bf = 0;
          break;
        case 1:
          b->bf = 1;
          a->bf = 0;
          break;
        case 0:
          b->bf = 0;
          a->bf = 0;
          break;
      }
      c->bf = 0;
      b = c; //b is the new root
    } //end of LR
  } //end of imbalance

  if (!pa)
    root = b;
  else
    if (a==pa->leftChild)
      pa->leftChild = b;
    else
      pa->rightChild = b;
  return;
} //AVL::Insert
