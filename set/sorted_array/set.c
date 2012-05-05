/* Brian Jenkins
 * COEN 12, Project #2 (Sorted)
 * 5/4/06
 *
 * File:	set.c
 *
 * Description:	This file contains the public and private function and type definitions for
 *		a set abstract data type for strings.  A set is an unordered collection of
 *		unique elements.
 *
 *		This implementation uses a sorted array to store the elements. Therefore,
 *		binary search is utilized and determining membership is logarithmic time.
 *		Insertion is logarithmic if the element is already present, and linear
 *		otherwise. Deletion is logarithmic if the element is not present, and
 *		linear otherwise.
 *
 */
/*
 * File:	set.c
 *
 * Description:	This file contains the implementation for a set abstract data type.
 *              The algorithm used to implement the set is a sorted array with binary search.
 *
 *              A set is an unordered collection of unique elements. Each element is a string.
 *
 * Author:      Brian Jenkins (bj@jenkinz.com)
 * Date:        05/05/2012
 *
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"

static int locateElement (SET *set, char *elt, int *found);

/*
 * Function:	locateElement
 *
 * Description: A private function that returns the location of an element `elt` in an array `set` using binary search.
 *		If element present: return its index, and set `found` pointer to 1. If
 *		element not present, return the index of where it would have been, and
 *		set found pointer to 0.
 *
 * Complexity:  O(logn)
 */
static int locateElement (SET *set, char *elt, int *found)
{
  int low, mid, high, diff;

  low = 0;

  high = set->count - 1;

  while (low <= high) {

    mid = (low + high) / 2;

    diff = (strcmp (elt, set->elts[mid]) );

    if (diff < 0)

      high = mid - 1;

    else if (diff > 0)

      low = mid + 1;

    else {

      *found = 1;
      return mid;
    }
  }

  *found = 0;
  return low;
}

/*
 * Function:	createSet
 *
 * Description: Initializes and returns an empty set with a maximum capacity of `size`.
 *
 * Complexity:  O(1)
 */
SET *createSet (int size)
{
  SET *s;

  s = malloc (sizeof(SET));

  if (s == NULL)
    return NULL;

  s->count = 0;

  s->size = size;

  s->elts = malloc (size * sizeof(char*));

  if (s->elts == NULL)
    return NULL;

  return s;
}

/*
 * Function:	insertElement
 *
 * Description: Inserts `elt` into `set`, and returns whether the set changed.
 *
 * Complexity:  O(logn) - if `elt` is already present
 *		O(n)    - if `elt` not already present
 */
int insertElement (SET *set, char *elt)
{
  int i, locn, found;

  if (set->count == set->size) // Set's capacity has been reached
    return 0;

  locn = locateElement (set, elt, &found);

  if (found)
    return 0;

  /*Ensure that array remains sorted: */

  for (i = set->count; i > locn; i--)
    set->elts[i] = set->elts[i - 1];

  set->elts[locn] = elt;

  set->count++;

  return 1;
}

/*
 * Function:	numElements
 *
 * Description:	Returns the number of elements in `set`.
 *
 * Complexity:  O(1)
 */

int numElements (SET *set)
{
  return set->count;
}

/*
 * Function:    hasElement
 *
 * Description: Returns whether `elt` is a member of `set`.
 *
 * Complexity:  O(logn)
 */
int hasElement (SET *set, char *elt)
{
  int locn, found;

  locn = locateElement (set, elt, &found);

  return found;
}

/*
 * Function:    deleteElement
 *
 * Description: Deletes `elt` from `set`, and returns whether the set changed.
 *
 * Complexity:  O(logn) - if element not present
 *		O(n)    - if element is present
 */
int deleteElement (SET *set, char *elt)
{
  int i, locn, found;

  locn = locateElement (set, elt, &found);

  if (!found)
    return 0;

  for (i = locn + 1; i < set->count; i++)
    set->elts[i - 1] = set->elts[i];

  set->count--;

  return 1;
}

/*
 * Function:    destroySet
 *
 * Description: Deallocates memory associated with `set`.
 *
 * Complexity: O(1)
 */
void destroySet (SET *set)
{
  free (set->elts);

  free (set);

  return;
}
