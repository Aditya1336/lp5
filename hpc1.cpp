#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

class Node
{
public:
  int data;
  Node *left;
  Node *right;

  Node(int value)
  {
    data = value;
    left = NULL;
    right = NULL;
  }
};

void parallelBFS(Node *root)
{

  if (root == NULL)
  {
    return;
  }

  queue<Node *> q;

  q.push(root);

  cout << "Parallel BFS Traversal: ";

  while (!q.empty())
  {
    int levelSize = q.size();

    vector<Node *> currentLevel;

    for (int i = 0; i < levelSize; i++)
    {
      Node *current = q.front();
      q.pop();
      currentLevel.push_back(current);
    }

#pragma omp parallel for
    for (int i = 0; i < currentLevel.size(); i++)
    {
      Node *current = currentLevel[i];

#pragma omp critical
      {
        cout << current->data << " ";
      }

      if (current->left != NULL)
      {
#pragma omp critical
        {
          q.push(current->left);
        }
      }

      if (current->right != NULL)
      {
#pragma omp critical
        {
          q.push(current->right);
        }
      }
    }
  }

  cout << endl;
};

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

  parallelBFS(root);

  return 0;
}