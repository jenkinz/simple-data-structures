/*
 * File:	set.c
 *
 * Description:	This file contains the implementation for a set abstract data type.
 *              The algorithm used to implement the set is a linear array with linear search.
 *
 *              A set is an unordered collection of unique elements.
 *
 * Author:      Brian Jenkins (bj@jenkinz.com)
 * Date:        05/05/2012
 *
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"

/*
 * Function:	locateElement
 *
 * Description: Returns the location of an element `x` in the `set`, or -1 if it could not be found.
 *
 * Complexity:  O(n)
 */
int locateElement (SET *set, char *x)
{
  int i;

  for (i = 0; i < set->count; i++)

    if (strcmp (set->elts[i], x) == 0)

      return i;

  return -1;
}

/*
 * Function:    createSet
 *
 * Description: Initializes and returns a pointer to a set with a maximum capacity of `size` elements.
 *
 * Complexity:  O(1)
 */
SET *createSet (int size)
{
  SET *s;

  s = malloc (sizeof(SET));

  if ( s == NULL )

    return s;

  s->count = 0;

  s->size = size;

  s->elts = malloc (size * sizeof(char *));

  return s;
}

/*
 * Function:	insertElement
 *
 * Description: Insert `elt` into `set`, and return whether the set changed.
 *
 * Complexity:  O(1)
 */

int insertElement (SET *set, char *elt) {

	if (set->count == set->size)

		return 0;

	if (hasElement (set, elt) )

		return 0;

	set->elts[set->count++] = elt;


	return 1;

}



/*
 * Function: numElements
 *
 * Return the number of elements in "set"
 *
 * Algorithmic Complexity: O(1)
 */

int numElements (SET *set) {

	return set->count;

}



/*
 * Function: hasElement
 *
 * Description: Return one if "elt" is a member of "set", and zero otherwise
 *
 * Algorithmic Complexity: O(1)
 */

int hasElement (SET *set, char *elt) {

	return locateElement (set, elt) != -1;

}



/*
 * Function: deleteElement
 *
 * Description: Delete "elt" from "set", and return whether the set changed
 *
 * Algorithmic Complexity: O(1)
 */

int deleteElement (SET *set, char *elt) {

	int loc;

	if ((loc = locateElement(set, elt)) == -1)

		return 0;

	set->elts[loc] = set->elts[--set->count];

	return 1;

}


/*
 * Function: destroySet
 *
 * Description: Deallocate memory associated with "set"
 *
 * Algorithmic Complexity: O(1)
 */

void destroySet (SET *set) {

	free (set->elts);

	free (set);

	return;

}
