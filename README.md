# The-sorter
# Jason Holley and Jonathan Boccardi


# Summary

This was the second assignment for my Systems Programming class, a two person assignment that just 
takes an input CSV and sorts based on command line inputs


#PROJECT 0

The purpose of this assignment was to sort movie metadata given a comma separated value file.
We chose to store each row (movie) as a struct of all its data, with all the column headers
as names for each of the properties inside the struct.

The methods inside of sorter.h handle the different possible inputs such as extra whitespace,
commas within an actual set of data, and adding all the data to a Line struct to return to main.

sorter.c includes the main function, which constructs an array of Line structs to then pass to 
mergesort. While the array of Line structs is being built, realloc() is called to resize the array
to be just the proper size for the amount of data sent in.

Mergesort is then called, passing the array of line structs, the size of the array, and the column
to sort by.

Mergesort is implemented recursively, mallocating the right amount of space for the left and right
subarrays to be sorted, then freeing the space once used. Since there were three types of data in
the Line struct, int, double, and char arrays, 3 different comparison methods were necessary to
properly sort all the data.

# Issues

One issue we had with this project was with getting the number of lines in the struct.
We were doing sizeof(Lines) which gave the size of the pointer when we needed to get the size of
the array using an increment.

Another issue was with reallocating the data for the Lines array after each line was added.
Lines = realloc(Lines, sizeof(Lines) + sizeof(Line)) was the code used
But this has the same exact problem.

At the time we had Lines as a double pointer which just made it impossible to use the sizeof 
function.

# PROJECT 1

The purpose of this project was to use fork()ing to accomplish the same task as last time, except 
while traversing the filesystem. Every new directory spawns a new process, and every new .csv file 
spawns a process that sorts the csv file.

If the desired output directory does not exist, this program will create it. It's not perfect
though, since it can only create a directory that is one level deeper than an existing directory.
Essentially, it does not create the in-between directories, although it should, since mkdir should
do that.

# Issues

We ran into a lot of issues when doing the actual sorting for this part of the assignment, and 
all of the problems were memory related. The original implementation in Project 0 realloc()'d the
array of lines that was imported from the csv, but the lines array was the only thing that used
malloc to begin with, so there were no resizing errors.

To avoid this issue, we added a second file descriptor to traverse the file and malloc the correct
amount from the beginning, which is faster anyway, since it doesn't have to realloc the array every
single time a new line is to be added.

Another issue was with creating the output file for the program to output the sorted data. Isolating
the filename from the path was easy, but I ran into issues using fopen on a path that didn't have 
enough space to store the whole path. I had to malloc more space for path to fix it.

# Project 2

This time, instead of making the program multiprocessed, it had to be multithreaded, but perform 
essentially the same task. Instead of outputting the sorted files separately, this time the program 
will compile all sorted .csv files into one file.

All individually sorted files will go in a temporary folder, to then be scanned and merged into one
big AllFiles-sorted-column_name.csv.

This program will also accept any ordering of the argv tags. That was fairly easy to implement.

# Issues

We had an issue where we were using the same lock for everything, and there was a deadlock upon retrieval,
and we didn't know how to fix it other than creating two separate mutex locks and using them to block off
the different parts of memory that were being accessed. It worked much better after making that change.

We also had an issue where after we stored the path to a sorted file into a struct, then passed it to a
merge files function, and unpacked the struct so that the data can be used locally within the function,
the data was corrupted.