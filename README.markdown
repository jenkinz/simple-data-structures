# Simple Data Structures

This project contains simple data type implementations of sets and lists using various algorithms. These are primarily for learning and fun, so feel free to use/modify or whatever.

## Usage

Set implementations are in `set/`; lists in `list/`. In addition to the source and header, each implementation contains a `main.c` which provides a test function for the corresponding implementation. The test function takes two files as command line arguments, the second of which is optional. See each `main.c` for further information on the test function's output.

For example, to run the test for `set/linear_array`:

- `cd set/linear_array`
- `gcc *.c`
- `./a.out file1.txt file2.txt`

The output of this particular test lists the total number of words in `file1.txt`, the total number of unique words in `file1.txt`, and the total number of remaining words in `file1.txt` after removing every occurrence of every world in `file2.txt` from `file1.txt`.

## Credit

I implemented these back in my college years for Darrent Atkinson's COEN 12 data structures class at Santa Clara University in 2006.
