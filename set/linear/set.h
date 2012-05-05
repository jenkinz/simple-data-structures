/*Brian Jenkins
 *COEN 12, Project #1
 *4/20/06
 *
 *File:		set.h
 *
 *Description:	This file contains the set.h function with all function
 *              prototypedeclarations.
 *
 *
 */

struct set {

	int count;

	int size;

	char **elts;

};

typedef struct set SET;

SET *createSet (int size);

void destroySet (SET *set);

int numElements (SET *set);

int hasElement (SET *set, char *elt);

int insertElement (SET *set, char *elt);

int deleteElement (SET *set, char *elt);

