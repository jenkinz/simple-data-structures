/*Brian Jenkins
 *COEN 12, Project 5
 *6/8/06
 *
 *FILE:		list.c
 *
 *DESCRIPTION:	This file contains the public and private function and type
 *		definitions for a list abstract data type for strings.
 *
 *		This implementation utilizes a singly linked list model, where
 *		traversal, insertion, and deletion are all linear time.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "list.h"


/*Definition of "set" datatype: */

typedef struct node {

	char *data;

	struct node *next;

} NODE;

struct list {

	int count;

	struct node *head;
};

/*FUNCTION:	getItems
 *
 *DESCRIPTION:	Returns an pointer to an array of all items in a singly linked list.
 *
 *COMPLEXITY:	O(n)
 *
 */
 
char **getItems (LIST *list) {

	int i = 0;
	
	NODE *curr;
	
	char **items;
	
	if ((items = malloc (sizeof (char *) * list->count)) == NULL)
	
		return NULL;
	
	for (curr = list->head->next; curr != NULL; curr = curr->next)
	
		items[i++] = curr->data;
	
	return items;
}
 
 
 
/*FUNCTION: 	locateItem
 *
 *DESCRIPTION:	Traverses the list; always returns the previous node pointer of where the item is/should be; sets flag pointer to 0 if not found and 1 if found.
 *
 *COMPLEXITY:	O(n)
 *
 */

static NODE *locateItem (LIST *list, char *item, int *flag) {

	NODE *pre, *loc;

	pre = list->head;

	loc = pre->next;

	while (loc != NULL) {

		if (strcmp (item, loc->data) == 0) {

			*flag = 1;

			return pre;
		}

		if (strcmp (item, loc->data) > 0) {

			*flag = 0;

			return pre;
		}

		pre = loc;

		loc = loc->next;
	}

	*flag = 0;

	return pre;
}

/*
 *FUNCTION: 	createList
 *
 *DESCRIPTION:	Creates, initializes, and returns a list
 *
 *COMPLEXITY;	O(1)
 */


LIST *createList (void) {

	LIST *list;

	if ((list = malloc (sizeof(LIST))) == NULL)

		return NULL;

	if ((list->head = malloc (sizeof(NODE))) == NULL)

		return NULL;

	list->count = 0;

	list->head->data = NULL;

	list->head->next = NULL;

	return list;
}


/*FUNCTION: 	destroyList
 *
 *DESCRIPTION:	Deallocates memory associated with "list"
 *
 *COMPLEXITY:	O(n)
 *
 */

void destroyList (LIST *list) {

	NODE *pre, *loc;

	pre = list->head;

	do {

		loc = pre->next;

		free (pre);

		pre = loc;
	
	} while (loc != NULL);

	free (list);
}

/*
 *FUNCTION: 	insertItem
 *
 *DESCRIPTION:	Inserts "item" into "list" in sorted order, and returns whether the list changed
 * 
 *COMPLEXITY:	O(n)
 *
 */

int insertItem (LIST *list, char *item) {

	int found;

	NODE *pre, *new;

	if ((new = malloc (sizeof(NODE))) == NULL)

		return 0;

	pre = locateItem (list, item, &found);

	new->data = item;

	new->next = pre->next;

	pre->next = new;

	list->count++;

	return 1;
}

/*
 *FUNCTION: 	deleteItem
 *
 *DESCRIPTION:	Deletes the first instance of "item" from "list", and returns whether the list changed
 *
 *COMPLEXITY:	O(n)
 *
 */

int deleteItem (LIST *list, char *item) {

	int found;

	NODE *pre, *loc;

	pre = locateItem (list, item, &found);

	if (!found)

		return 0;

	loc = pre->next;

	pre->next = loc->next;

	list->count--;

	return 1;
}

/*FUNCTION:	hasItem
 *
 *DESCRIPTION:  Returns 1 if "item" is present in "list", otherwise returns 0
 *
 *COMPLEXITY:	O(n)
 *
 */

int hasItem (LIST *list, char *item) {

	int found;

	NODE *pre;

	pre = locateItem (list, item, &found);

	if (found)

		return 1;
	
	return 0;
}

/*FUNCTION: 	numItems
 *
 *DESCRIPTION:	Returns the number of items in "list"
 *
 *COMPLEXITY:	O(1)
 *
 */

int numItems (LIST *list) {

	return list->count;
}
	



