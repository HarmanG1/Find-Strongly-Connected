# Find-Strongly-Connected 

The files all come together to find strongly connected components of a digraph built using a linked list

## Files

### FindComponents.c

FindComponents requires two options for an input and output file and finds the strongly connected components using the graph from Graph.c

- <code>input file</code>: specifies the input file to create the graph.
- <code>output file</code>: specifies the output file for the strongly connected components.

### Graph.{c,h}

Contains the source and header files for the Graph ADT implementation

### List.{c,h}

Contains the source and header files for the Linked list ADT implementation

### GraphTest.c

Contains the tests to ensure the function of the Graph ADT from Graph.c

### Makefile

Makefile contains the commands to compile, clean, and leak test the files
