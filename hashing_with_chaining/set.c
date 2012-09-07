/*Brian Jenkins
 *COEN 12, Project 3
 *5/18/06
 *
 *FILE:		set.c
 *
 *DESCRIPTION:	This file contains the public and private function and type
 *		definitions for a set abstract data type for strings.  A
 *		set is an unordered collection of unique elements.
 *
 *		This implementation utilizes hashing with chaining to store elements,
 *		and to resolve collisions. To do this, it uses a list ADT for each "chain"
 *		of the hash table. Therefore, insertion and deletion are linear time.
 *
 *
 *
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "list.h"
# include "set.h"

# define ALPHA 10

/*Definition of "set" datatype: */

struct set {

	int count;		//Number of inserted elements.

	int size;		//Number of slots able to hold a list.

	LIST **lists;		//To be utilized for hashing with chaining
};




/* Function: 	hashString
 *
 * Description: Performs the given hash function on the element to be inserted, and returns
 *		the result of the hash function so that the calling function can perform 
 *		modulo division, and thus yield the proper index.
 *
 * Complexity: 	O(k) - k is the length "s", the input string
 *
 */

static unsigned hashString  (char *s) {

	unsigned hash = 0;

	while (*s != '\0') 
	
		hash = (31 * hash + *s ++);

	return hash;
}


/*FUNCTION:	createSet
 *
 *DESCRIPTION:	Creates, initializes, and returns a set with a maximum capacity of "size"
 *
 *COMPLEXITY:	Average Case:	O(n)
 *		Worst Case:	O(n)
 */

SET *createSet (int size) {

	SET *set;

	int i;

	if ((set = malloc (sizeof(SET))) == NULL)

		return NULL;

	set->size = (size + ALPHA - 1) / ALPHA;		//Set initial size to input parameter.

	if ((set->lists = malloc(set->size * sizeof(LIST*))) == NULL)

		return NULL;

	set->count = 0;					//Set initial count to 0.
	
	for (i = 0; i < set->size; i++) {

		if ((set->lists[i] = createList ()) == NULL)	//Create size/ALPHA lists
		
			return NULL;
	}

	return set;
}


/*FUNCTION:	destroySet
 *
 *DESCRIPTION:	Deallocates memory associated with "set"
 *
 *COMPLEXITY:	Average Case:	O(n)
 *		Worst Case:	O(n)
 */

void destroySet (SET *set) {

	int i;

	for (i = 0; i < set->size; i++) 
	
		destroyList(set->lists[i]);

	free (set);
}


/*FUNCTION:	numElements
 *
 *DESCRIPTION:	Returns the number of elements in "set"
 *
 *COMPLEXITY:	Average Case:	O(n)
 *		Worst Case:	O(n)
 */

int numElements (SET *set) {

	int i, listcnt;

	int num = 0;

	for (i = 0; i < set->size; i++) {

		listcnt = numItems (set->lists[i]);

		num += listcnt;
	}

	return num;		
}


/*FUNCTION:	hasElement
 *
 *DESCRIPTION:	Returns 1 if "elt" is a member of "set", otherwise returns 0
 *
 *COMPLEXITY:	Average Case: 	O(n)
 *		Worst Case:	O(n)
 */

int hasElement (SET *set, char *elt) {

	return hasItem (set->lists[(hashString (elt)) % (set->size)], elt);
}


/*FUNCTION:	insertElement
 *
 *DESCRIPTION:	Inserts "elt" into "set", and returns whether the set changed
 *
 *COMPLEXITY:	Average Case:	O(n)
 *		Worst Case:	O(n)
 */

int insertElement (SET *set, char *elt) {

	int found, inserted;

	found = hasItem (set->lists[(hashString (elt)) % (set->size)], elt);

	if (found)

		return 0;

	else {

		inserted = insertItem (set->lists[(hashString (elt)) % (set->size)], elt);

		if (inserted) {

			set->count++;

			return 1;	
		}
	}

	return 0;
}


/*FUNCTION:	deleteElement
 *
 *DESCRIPTION:	Deletes "elt" from "set", and returns whether the set changed
 *
 *COMPLEXITY:	Average Case:	O(n)
 *		Worst Case:	O(n)
 */

int deleteElement (SET *set, char *elt) {

	int deleted = deleteItem (set->lists[hashString (elt) % set->size], elt);

	if (!deleted)

		return 0;

	set->count--;

	return 1;
}

