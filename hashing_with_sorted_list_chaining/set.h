/*Brian Jenkins
 *COEN 12, Project #3
 *5/18/06
 *
 *File:		set.h
 *
 *Description:	This file contains the public function and type
 *		declarations for a set abstract data type for strings.  A
 *		set is an unordered collection of unique elements.         
 *
 *
 */

typedef struct set SET;

SET *createSet (int size);

void destroySet (SET *set);

int numElements (SET *set);

int hasElement (SET *set, char *elt);

int insertElement (SET *set, char *elt);

int deleteElement (SET *set, char *elt);

char **sortElements (SET *set);



