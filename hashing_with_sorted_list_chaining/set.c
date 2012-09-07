/*Brian Jenkins
 *COEN 12, Project 5
 *6/8/06
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
 *		In addition, a sorting feature has been added.  Utilizing a merge sort algorithm,
 *		it returns an array of all elements in the set in sorted order in O(nlogn) time.
 *
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "list.h"
# include "set.h"

# define ALPHA 10

char **sortElements (SET *set);
static void mergeSort (char **elements, char **temp, int lo, int hi);
static void merge (char **elements, char **temp, int lo1, int hi1, int lo2, int hi2);


/*Definition of "set" datatype: */

struct set {

	int count;		//Number of inserted elements.

	int size;		//Number of slots able to hold a list.

	LIST **lists;		//To be utilized for hashing with chaining
};

/*Function:	sortElements
 *
 *Description:	Preps all elements for sorting by placing all of them into one large dynamically
 *		allocated array. Calls mergeSort () to perform actual sorting.
 *		
 *Complexity:	O(n^2)	
 *
 */

char **sortElements (SET *set) {

	int i, j;
	
	int k = 0;

	char **items;

	char **elements;

	char **temp;

	if ((elements = malloc (sizeof (char *) * set->count)) == NULL)
	
		return NULL;

	if ((temp = malloc (sizeof (char *) * set->count)) == NULL)

		return NULL;
	
	for (i = 0; i < set->size; i++) {

		items = getItems (set->lists[i]);
		
		for (j = 0; j < numItems (set->lists[i]); j++) 
		
			elements[k++] = items[j];

		free (items);
	}
		

	mergeSort (elements, temp, 0, set->count - 1);	
	
	return elements;
}


/* Function:	mergeSort
 * 
 * Description:	Recursively generates many subarrays of each individual string, and calls "merge" 
 *		to combine them all back together in sorted order.
 * 
 * Complexity:	O(nlogn)
 *
 */

static void mergeSort (char **elements, char **temp, int lo, int hi){

	int mid;

	if (lo < hi) {
	
		mid = (lo + hi) / 2;
		
		mergeSort (elements, temp, lo, mid);
		
		mergeSort (elements, temp, mid + 1, hi);
		
		merge (elements, temp, lo, mid, mid + 1, hi);
	}
}


/* Function:	merge
 *
 * Description:	Merges all subarrays together in one large array (in sorted order).
 *
 * Complexity:	O(nlogn)
 *
 */
 
static void merge (char **elements, char **temp, int lo1, int hi1, int lo2, int hi2) {

	int i = lo1;

	int low = lo1;

	int k = 0;

	while ((lo1 <= hi1) && (lo2 <= hi2)) {

		if (strcmp (elements[lo1], elements[lo2]) < 0) 

			temp[i++] = elements[lo1++];

		else

			temp[i++] = elements[lo2++];
	}

	while (lo1 <= hi1)

		temp[i++] = elements[lo1++];            

	while (lo2 <= hi2) 

		temp[i++] = elements[lo2++];
		
	for (k = low; k <= hi2; k++) 

		elements[k] = temp[k];
}


/* Function: 	hashString
 *
 * Description: Performs the given hash function on the element to be inserted, and returns
 *		the result of the hash function so that the calling function can perform 
 *		modulo division, and thus yield the proper index.
 *
 * Complexity: 	O(k), where k is the length of S
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
 *COMPLEXITY:	O(m), where m is the number of chains
 *		
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
 *COMPLEXITY:	O(n)
 *		
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
 *COMPLEXITY:	O(1)
 *		
 */

int numElements (SET *set) {

	return set->count;		
}


/*FUNCTION:	hasElement
 *
 *DESCRIPTION:	Returns 1 if "elt" is a member of "set", otherwise returns 0
 *
 *COMPLEXITY:	Average Case: 	O(1)
 *		Worst Case:	O(n)
 */

int hasElement (SET *set, char *elt) {

	return hasItem (set->lists[(hashString (elt)) % (set->size)], elt);
}


/*FUNCTION:	insertElement
 *
 *DESCRIPTION:	Inserts "elt" into "set", and returns whether the set changed
 *
 *COMPLEXITY:	Average Case:	O(1)
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
 *COMPLEXITY:	Average Case:	O(1)
 *		Worst Case:	O(n)
 */

int deleteElement (SET *set, char *elt) {

	int deleted = deleteItem (set->lists[hashString (elt) % set->size], elt);

	if (!deleted)

		return 0;

	set->count--;

	return 1;
}

