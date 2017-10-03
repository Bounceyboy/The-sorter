#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"sorter.h"
#include <time.h>
#include"mergesort.c"

int main(int argc, char *argv[]){
	FILE *input;
	input = stdin;				//the File "input" is now the csv
//	input = fopen("movie_metadata.csv", "r"); 		//for debugging

	// if (!feof(input)){
	// 	printf("%s\n", "No data.");
	// 	return 0;
	// }

	//error handling for wrong header input

	if (!(!strcmp(argv[2], "num_critic_for_reviews") || !strcmp(argv[2], "duration")
		|| !strcmp(argv[2], "director_facebook_likes") || !strcmp(argv[2], "actor_3_facebook_likes")
		|| !strcmp(argv[2], "actor_1_facebook_likes") || !strcmp(argv[2], "gross") || !strcmp(argv[2], "num_voted_users")
		|| !strcmp(argv[2], "cast_total_facebook_likes") || !strcmp(argv[2], "facenumber_in_poster")
		|| !strcmp(argv[2], "num_user_for_reviews") || !strcmp(argv[2], "budget") || !strcmp(argv[2], "title_year")
		|| !strcmp(argv[2], "actor_2_facebook_likes") || !strcmp(argv[2], "movie_facebook_likes")
		|| !strcmp(argv[2], "imdb_score") || !strcmp(argv[2], "aspect_ratio")
		|| !strcmp(argv[2], "color") || !strcmp(argv[2], "director_name")
		|| !strcmp(argv[2], "actor_2_name") || !strcmp(argv[2], "genres") || !strcmp(argv[2], "actor_1_name")
		|| !strcmp(argv[2], "movie_title") || !strcmp(argv[2], "actor_3_name")
		|| !strcmp(argv[2], "plot_keywords") || !strcmp(argv[2], "movie_imdb_link") || !strcmp(argv[2], "language")
		|| !strcmp(argv[2], "country") || !strcmp(argv[2], "content_rating"))) {

		printf("%s\n", "Header does not exist.");
		return 0;
	}


	
	Line *Lines = malloc(sizeof(Line));
	char buf[1024];
	
	int ArraySize = 1;
	char toSortBy[64];
	int i;
	for (i = 0; i < 64; ++i)
	{
		toSortBy[i] = 0;
	}
	strncpy(toSortBy, argv[2], strlen(argv[2]));

	printf("%s\n", toSortBy);
	//one extra fgets call to skip header line of csv
	fgets(buf,1024,input);

	//one manual fgets call to store in first line so that there isn't an extra
	//empty Line in the array "Lines"
	fgets(buf,1024,input);
	Lines[0] = *importLine(buf);
	

	//in this loop:
	//increment ArraySize (might remove, just figured it'd be good to have just in case)
	//Reallocate memory to allow for an additional Line in "Lines"
	//Call importLine to create that line and add it to "Lines"
	
	while(fgets(buf,1024,input)!=NULL){	//for each line (gets stored in string "buf")
		ArraySize++;
		Lines = realloc(Lines, (ArraySize*sizeof(Line)));
		Lines[ArraySize-1] = *importLine(buf);
	}


/*TODO mergesort function with following properties
 *Takes a "Lines" input (pointer to array of "Line" structs), and a string (character array) containing
 *the title of the column to sort by
 *
 *a prototype of the function would look like this:
 *	Line* Mergesort(Line* inputArray, char* column);
 *
 *This will be in a separate file called Mergesort.c
 *Let me know if you need help!
 */

	//Mergesort(Lines, ArraySize, "duration");
	Mergesort(Lines, ArraySize, toSortBy);

	int x;
	printf("color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");
	for(x=0;x<ArraySize;x++){

	printf("%s,",(&Lines[x])->color);
	printf("%s,",(&Lines[x])->director_name);
	printf("%d,",(&Lines[x])->num_critic_for_reviews);
	printf("%d,",(&Lines[x])->duration);
	printf("%d,",(&Lines[x])->director_facebook_likes);
	printf("%d,",(&Lines[x])->actor_3_facebook_likes);
	printf("%s,",(&Lines[x])->actor_2_name);
	printf("%d,",(&Lines[x])->actor_1_facebook_likes);
	printf("%d,",(&Lines[x])->gross);
	printf("%s,",(&Lines[x])->genres);
	printf("%s,",(&Lines[x])->actor_1_name);
		
	char *y = strchr((&Lines[x])->movie_title,',');
	if(y==NULL)
		printf("%s,",(&Lines[x])->movie_title);
	else
		printf("\"%s \",",(&Lines[x])->movie_title);
	printf("%d,",(&Lines[x])->num_voted_users);
	printf("%d,",(&Lines[x])->cast_total_facebook_likes);
	printf("%s,",(&Lines[x])->actor_3_name);
	printf("%d,",(&Lines[x])->facenumber_in_poster);
	printf("%s,",(&Lines[x])->plot_keywords);
	printf("%s,",(&Lines[x])->movie_imdb_link);
	printf("%d,",(&Lines[x])->num_user_for_reviews);
	printf("%s,",(&Lines[x])->language);
	printf("%s,",(&Lines[x])->country);
	printf("%s,",(&Lines[x])->content_rating);
	printf("%d,",(&Lines[x])->budget);
	printf("%d,",(&Lines[x])->title_year);
	printf("%d,",(&Lines[x])->actor_2_facebook_likes);
	printf("%f,",(&Lines[x])->imdb_score);
	printf("%f,",(&Lines[x])->aspect_ratio);
	printf("%d\n",(&Lines[x])->movie_facebook_likes);
	}

	free(Lines);
	return 0;
}
