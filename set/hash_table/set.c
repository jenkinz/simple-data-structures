/*
 * File:	set.c
 *
 * Description:	This file contains the implementation for a set abstract data type.
 *              The algorithm used to implement the set is a hash table with linear
 *              probing to resolve collisions. The hash function used has time
 *              relative to the size of the input array. Determining membership,
 *              insertion and deletion have constant time for the average case when
 *              all keys map to different locations, and linear time for the worst
 *              case when linear probing is required for each key.
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

# define EMPTY 0
# define FILLED 1
# define DEL 2

/* Definition of the `set` data type */
struct set
{
  int count; /* The number of elements currently in `elts` */

  int size; /* The maximum size of `elts` */

  char **elts; /* The array of element strings */

  char *flag; /* Keeps track of whether the slot in the array is empty, full, or deleted */
};

/* Private function prototypes */
static unsigned hashIt (char *s, SET *set);
static int locateElement (SET *set, char *elt, int *found);

/*
 * Function:	hashIt
 *
 * Description: Performs the hash function on the element `elt`, and returns
 *		the index in `set` where it should be inserted.
 *
 * Complexity:  O(x) - x is the length of the `elt` string
 */
static unsigned hashIt (char *elt, SET* set)
{
  unsigned hash = 0;

  while (*elt != '\0') /* while the end of the string has not yet been reached */
    hash = (31 * hash + *elt ++); /* revise the `hash` with the current character, and proceed to the next char */

  return hash % set->size;
}

/*
 * Function:	locateElement
 *
 * Description: Returns the location of an element in the `set` using the hash function.
 *              If element present: return its index, and set `found` pointer to 1. If
 *		element not present, return the index of where it would have been, and
 *		set found pointer to 0.
 *
 * Complexity:  O(1) - average case, where all keys map to different locations
 *		O(n) - worst case, where linear probing is required for each key
 */
static int locateElement (SET *set, char *elt, int *found)
{
  int first, locn, i, actual = -1, actcount = 0;

  first = hashIt (elt, set);

  for (i = 0; i < set->size; i++) {

    locn = (first + i) % set->size;

    /* Case if it's empty: */

    if (set->flag[locn] == EMPTY) {
      *found = 0;
      return locn;
    }

    /* If it's deleted: */

    else if (set->flag[locn] == DEL) {
      actual = locn;
      actcount++;	/* We need a counter to keep track of the FIRST deleted slot encountered */
    }

    /* If it's filled: */

    else if (strcmp (set->elts[locn], elt) == 0) {
      *found = 1;
      return locn;
    }
  }

  *found = 0;
  return (actual - actcount);     /* Make sure we return the FIRST deleted slot encountered */
}

/*
 * Function:	createSet
 *
 * Description: Initializes and returns a set with a maximum capacity of `size`.
 *
 * Complexity:  O(n)
 */
SET *createSet (int size)
{
  int i;

  SET *s;

  s = malloc (sizeof(SET));

  if ( s == NULL )
    return NULL;

  s->elts = malloc (size * sizeof(char *));

  if (s->elts == NULL)
    return NULL;

  s->flag = malloc (size * sizeof(char));

  if (s->flag == NULL)
    return NULL;

  s->count = 0;

  s->size = size;

  for (i = 0; i < size; i++)
    s->flag[i] = EMPTY;

  return s;
}

/*
 * Function:	insertElement
 *
 * Description: Inserts `elt` into `set`, and returns whether the set changed.
 *
 * Complexity:  O(1) - average case, where all keys map to different locations
 *		O(n) - worst case, where linear probing is required for each key
 */
int insertElement (SET *set, char *elt)
{
  int locn, found;

  if (set->count == set->size)
    return 0;

  locn = locateElement (set, elt, &found);

  if (found)
    return 0;

  set->elts[locn] = elt;

  set->flag[locn] = FILLED;

  set->count++;

  return 1;
}

/*
 * Function:	numElements
 *
 * Description:	Returns the number of elements in `set`
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
 * Description: Returns if `elt` is a member of `set`.
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
 * Complexity:  O(1) - average case, where all keys map to different locations
 *		O(n) - worst case, where linear probing required for each key
 */
int deleteElement (SET *set, char *elt)
{

  int locn, found;

  locn = locateElement (set, elt, &found);

  if (!found)
    return 0;

  set->flag[locn] = DEL;

  set->count--;

  return 1;
}

/*
 * Function:    destroySet
 *
 * Description: Deallocates memory associated with `set`.
 *
 * Complexity:  O(1)
 */
void destroySet (SET *set)
{
  free (set->flag);

  free (set->elts);

  free (set);

  return;
}
