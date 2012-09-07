/* Brian Jenkins
*  COEN 12, Project 4
*  6/1/06
*
*  File:		list.c
*
*  Description:	This file contains the public and private function definitions for a list abstract
*               data type in the form of a Binary Search Tree.  Items are stored in sorted order
*               in a BST, and duplicates are allowed.  Location, insertion and deletion are all
*               logarithmic time.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* Datatype declarations: */

typedef struct node {

  char *data;

  struct node *left;

  struct node *right;

} NODE;

struct list {

  int count;

  NODE *root;
};

/* Private function prototypes: */

static int hasNode (NODE *node, char *item);

static NODE *insertNode (NODE *root, NODE *new);

static NODE *deleteNode (NODE *root, char *data, int *success);

static void destroyNode (NODE *node);


/*
 *Function:	createList
 *
 *Description:	Creates, initializes, and returns a list
 *
 *Complexity:	O(1)
 *
 */

LIST *createList (void) {

  LIST *list;

  if ((list = malloc (sizeof(LIST))) == NULL)

    return NULL;

  list->count = 0;

  list->root = NULL;

  return list;
}


/*
 *Function:	destroyNode
 *
 *Description:	Deletes all nodes in the BST, deallocating memory in the process. Recursion
 *		used in postorder sequence.
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

static void destroyNode (NODE *node) {

  if (node != NULL) {	//Non-empty tree

    destroyNode (node->left);

    destroyNode (node->right);

    free (node);
  }

  return;
}


/*
 *Function:	destroyList
 *
 *Description:	Deallocates memory associated with "list"
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

void destroyList (LIST *list) {

  destroyNode (list->root);

  free (list);
}


/*
 *Function:	numItems
 *
 *Description:	Returns the number of items in "list"
 *
 *Complexity:	O(1)
 *
 */

int numItems (LIST *list) {

  return list->count;
}


/*
 *Function:	hasNode
 *
 *Description:	Traverses BST until input node is found, returns one if found and zero otherwise
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

static int hasNode (NODE *node, char *item) {

  if (!node)					//Base case 1

    return 0;

  if (strcmp (node->data, item) == 0)		//Base case 2

    return 1;

  if (strcmp (node->data, item) > 0)

    return hasNode (node->left, item);

  return hasNode (node->right, item);
}


/*
 *Function:	hasItem
 *
 *Description:	Returns one if "item" is present in "list," and zero otherwise
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

int hasItem (LIST *list, char *item) {

  return hasNode (list->root, item);
}


/*
 *Function:	insertNode
 *
 *Description:	Uses recursion to insert a new data node as a leaf in the BST
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

static NODE *insertNode (NODE *root, NODE *new) {

  if (!root)					//NULL tree

    return new;


  if (strcmp (new->data, root->data) < 0) {	//Locate null subtree for insertion

    root->left = insertNode (root->left, new);

    return root;
  }

  else {						//new->data >= cur->data

    root->right = insertNode (root->right, new);

    return root;
  }

  return root;
}


/*
 *Function:	insertItem
 *
 *Description:	Inserts "item" into list, and returns whether list changed
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

int insertItem (LIST *list, char *item) {

  NODE *new;

  if ((new = malloc (sizeof(NODE))) == NULL)

    return 0;

  new->right = NULL;

  new->left = NULL;

  new->data = item;

  if (list->count == 0)

    list->root = new;

  else

    insertNode (list->root, new);

  list->count++;

  return 1;
}


/*
 *Function:	deleteNode
 *
 *Description:	Deletes node from BST and rebalances if needed
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

static NODE *deleteNode (NODE *root, char *data, int *success) {

  NODE *del;
  NODE *exch;
  NODE *newRoot;
  char *temp;

  if (!root)  {

    *success = 0;

    return NULL;			//Base Case 1: Empty tree
  }

  if (strcmp (data, root->data) < 0)

    root->left = deleteNode (root->left, data, success);

  else if (strcmp (data, root->data) > 0)

    root->right = deleteNode (root->right, data, success);

  else {					//Node found: (strcmp (data, root->data) = 0)

    del = root;			//Set "del" Node to the node to be deleted

    if (!root->left) {		//No left child

      free (root->data);	//Empty data memory

      newRoot = root->right;

      free (del);

      *success = 1;

      return newRoot;		//Base case 2
    }

    else

      if (!root->right) {	//Only left child

        newRoot = root->left;

        free (del);

        *success = 1;

        return newRoot; //Base Case 3
      }

      else {			//Delete node has two children

        exch = root->left;

        while (exch->right)	//Find largest node in left subtree

          exch = exch->right;

        temp = root->data;	//Exchange the data

        root->data = exch->data;

        exch->data = temp;

        root->left = deleteNode (root->left, exch->data, success);
      }
  }

  return root;
}

/*
 *Function:	deleteItem
 *
 *Description:	Deletes the first instance of "item" from "list," and returns whether the list changed.
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

int deleteItem (LIST *list, char *item) {

  int success;

  NODE *newRoot;

  newRoot = deleteNode (list->root, item, &success);

  if (success) {

    list->root = newRoot;

    list->count--;

    if (list->count == 0)

      list->root = NULL;

    return 1;
  }

  return 0;
}
