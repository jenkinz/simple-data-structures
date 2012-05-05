/*
 * File:	main.c
 *
 * Description:	This file contains the main function for testing a set
 *		abstract data type for strings.
 *
 *		The program takes two files as command line arguments, the
 *		second of which is optional.  All words in the first file
 *		are inserted into the set and the counts of total words and
 *		total words in the set are printed.  If the second file is
 *		given then all words in the second file are deleted from the
 *		set and the count printed.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"


/* This is sufficient for the test cases in /scratch/coen12. */

# define MAX_SIZE 15000


/*
 * Function:	main
 *
 * Description:	Driver function for the test application.
 */

int main (int argc, char *argv [])
{
    SET *set;
    FILE *fp;
    char buffer [BUFSIZ];
    int words;


    /* Check usage and open the first file. */

    if (argc == 1 || argc > 3) {
	fprintf (stderr, "usage: %s file1 [file2]\n", argv [0]);
	exit (EXIT_FAILURE);
    }

    if ((fp = fopen (argv [1], "r")) == NULL) {
	fprintf (stderr, "%s: cannot open %s\n", argv [0], argv [1]);
	exit (EXIT_FAILURE);
    }


    /* Insert all words into the set. */

    words = 0;

    if ((set = createSet (MAX_SIZE)) == NULL) {
	fprintf (stderr, "%s: failed to create set\n", argv [0]);
	exit (EXIT_FAILURE);
    }

    while (fscanf (fp, "%s", buffer) == 1) {
	words ++;

	if (!hasElement (set, buffer))
	    if (!insertElement (set, strdup (buffer)))
		fprintf (stderr, "set full\n");
    }

    printf ("%d total words\n", words);
    printf ("%d unique words\n", numElements (set));
    fclose (fp);


    /* Try to open the second file. */

    if (argc == 3) {
	if ((fp = fopen (argv [2], "r")) == NULL) {
	    fprintf (stderr, "%s: cannot open %s\n", argv [0], argv [1]);
	    exit (EXIT_FAILURE);
	}


	/* Delete all words in the second file. */

	while (fscanf (fp, "%s", buffer) == 1)
	    deleteElement (set, buffer);

	printf ("%d remaining words\n", numElements (set));
    }

    destroySet (set);
    exit (EXIT_SUCCESS);
}

