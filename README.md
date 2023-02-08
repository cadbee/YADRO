The Tape storage device is designed to write and read data sequentially. The read/write magnetic head is stationary during reading and writing, while the tape has the ability to move in both directions. It is possible to write and read information to the cell of the tape where the magnetic head is at the moment. Moving the tape is a time-consuming operation - the tape is not intended for random access. 

There is an input tape of length N (where N is great), containing elements of type integer (2 32). There is an output tape of the same length. It is necessary to write elements from the input tape sorted in ascending order to the output tape. There is a RAM usage limitation - no more than M bytes (M may be < N, i.e. it is impossible to load all data from the tape into RAM). To implement the algorithm, you can use a reasonable number of temporary tapes, i.e. tapes on which you can store some temporary information needed during the algorithm's work. 

You must create a C++ console application, which implements the algorithm for sorting data from the input tape to the output one. You need to do the following:
 - Define an interface to work with the tape type device. 
- Write a class that implements this interface and emulates working with the tape through an ordinary file. It must be possible to configure (without recompiling - for example, through an external configuration file to be read at the start of the application) delays for writing/reading an item from the tape, rewinding the tape, and shifting the tape by one position. 
- Temporary tape files can be saved in the tmp directory. 
- Write a class implementing an algorithm to sort data from the input to the output tape. 
- The console application must accept the input and output file names and perform sorting.
