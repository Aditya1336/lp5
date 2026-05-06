#include <iostream>
#include <omp.h>

using namespace std;

class Node
{
public:
  int data;
  Node *left;
  Node *right;

  Node(int data)
  {
    this->data = data;
    left = NULL;
    right = NULL;
  }
};

void dfsTraversal(Node *root)
{
  if (root == NULL)
  {
    return;
  }

#pragma omp critical
  {
    cout << root->data << " ";
  }

#pragma omp parallel sections
  {
#pragma omp section
    {
      dfsTraversal(root->left);
    }

#pragma omp section
    {
      dfsTraversal(root->right);
    }
  }
}

int main()
{
  Node *root = new Node(0);

  root->left = new Node(1);
  root->right = new Node(2);

  root->left->left = new Node(3);
  root->left->right = new Node(4);

  root->right->left = new Node(5);
  root->right->right = new Node(6);

  root->left->left->left = new Node(7);

  dfsTraversal(root);

  return 0;
}