# Systems Programming - Assignment 1
## Gavin Hailey and Giovanni Thompson

### Status
All functions work properly. Original and decoded files are identical. All memory in the heap was freed.

### Usage
- Compile:
  `gcc hcompress.c linkedList.c -o hcompress -Wall`

- Encode:
  `./hcompress -e {filename}.txt`
  (tree generated from "alien.txt")

- Decode:
  `./hcompress -d {filename}.txt.huf`

- Valgrind:
  `valgrind --leak-check=full ./hcompress -e alien.txt`
