/* Brian Jenkins
 * COEN 12, Project #3 
 * 5/18/06
 *
 * File: list.h
 *
 * Description: This file contains the public function type declarations for a list
 *		abstract data type for strings.  A list is an ordered collection of
 *		elements.
 *
 */

typedef struct list LIST;

LIST *createList (void);

void destroyList (LIST *list);

int numItems (LIST *list);

int hasItem (LIST *list, char *item);

int insertItem (LIST *list, char *item);

int deleteItem (LIST *list, char *item);
