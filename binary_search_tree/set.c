/* Brian Jenkins
 * COEN 12, Project #4
 * 6/1/06
 *
 * File:		set.c
 *
 * Description:	This file contains the function definitions for a set abstract datatype for strings.
 *
 *              This implemenation relies on a list abstract datatype (which happens to be in the form of a
 *              binary search tree) to store elements.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "set.h"

/*Datatype declaration(s): */

struct set {

  LIST *list;
};

/*
 *Function:	createSet
 *
 *Description:	Creates, initializes and returns a set with a maximum capacity of "size"
 *
 *Complexity:	O(1)
 *
 */

SET *createSet (int size) {

  SET *set;

  if ((set = malloc (sizeof(SET))) == NULL)

    return NULL;

  if ((set->list = createList()) == NULL)

    return NULL;

  return set;
}


/*
 *Function:	destroySet
 *
 *Description:	Deallocates memory associated with "set"
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

void destroySet (SET *set) {

  destroyList (set->list);

  free (set);
}


/*
 *Function:	numElements
 *
 *Description:	Returns the number of elements in "set"
 *
 *Complexity:	O(1)
 *
 */

int numElements (SET *set) {

  return numItems (set->list);
}


/*
 *Function:	hasElement
 *
 *Description:	Returns 1 if "elt" is present in "set," and zero otherwise
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

int hasElement (SET *set, char *elt) {

  return hasItem (set->list, elt);
}


/*
 *Function:	insertElement
 *
 *Description:	Inserts "elt" into "set," and returns whether the set changed
 *
 *Complexity:	Average: O(logn)
 *		Worst:   O(n)
 */

int insertElement (SET *set, char *elt) {

  if (hasItem (set->list, elt))

    return 0;

  if (insertItem (set->list, elt))

    return 1;

  return 0;
}


/*
 *Function:	deleteElement
 *
 *Description:	Removes "elt" from "set," and returns whether the set changed
 *
 *Complexity:	O(logn)
 *		O(n)
 */

int deleteElement (SET *set, char *elt) {

  return deleteItem (set->list, elt);
}
