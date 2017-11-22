# The-sorter
# Jason Holley and Jonathan Boccardi


# Summary

This was the second assignment for my Systems Programming class, a two person assignment that just takes an input CSV and sorts based on command line inputs


#PROJECT 0

The purpose of this assignment was to sort movie metadata given a comma separated value file.
We chose to store each row (movie) as a struct of all its data, with all the column headers
as names for each of the properties inside the struct.

The methods inside of sorter.h handle the different possible inputs such as extra whitespace,
commas within an actual set of data, and adding all the data to a Line struct to return to main.

sorter.c includes the main function, which constructs an array of Line structs to then pass to mergesort. While the array of Line structs is being built, realloc() is called to resize the array
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

At the time we had Lines as a double pointer which just made it impossible to use the sizeof function.

#PROJECT 1

The purpose of this project was to use fork()ing to accomplish the same task as last time, except while traversing the filesystem.