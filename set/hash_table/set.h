/*
 * File:	set.h
 *
 * Description:	This file contains the specification of the structure and function prototypes
 *              for a set abstract data type.
 *
 *              A set is an unordered collection of unique elements. Each element is a string.
 *
 * Author:      Brian Jenkins (bj@jenkinz.com)
 * Date:        05/05/2012
 *
 */

typedef struct set SET;

SET *createSet (int size);

void destroySet (SET *set);

int numElements (SET *set);

int hasElement (SET *set, char *elt);

int insertElement (SET *set, char *elt);

int deleteElement (SET *set, char *elt);
