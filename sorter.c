#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<pthread.h>
#include<unistd.h>
#include<dirent.h>
#include"sorter.h"
#include"mergesort.c"
#include"csvsearch.c"

int main(int argc, char *argv[]) {
	char* path = NULL;
	char* outpath = NULL;	
	char* column = NULL;
	int i = 1;

	//user input handling
	while ((i + 1)< argc) {
		if (strcmp(argv[i], "-c") == 0 && ((strcmp(argv[i+1],"-o") != 0) && (strcmp(argv[i+1],"-d") != 0))){
			column = (char*)malloc((sizeof(char)*strlen(argv[i+1]) + 32));
			column = argv[i+1];
		} else if (strcmp(argv[i], "-d") == 0 && ((strcmp(argv[i+1],"-c") != 0) && (strcmp(argv[i+1],"-o") != 0))){
			path = (char*)malloc((sizeof(char)*strlen(argv[i+1]) + 192));
			strcpy(path, "./");
			strcat(path, argv[i+1]);
		} else if (strcmp(argv[i], "-o") == 0 && ((strcmp(argv[i+1],"-d") != 0) && (strcmp(argv[i+1],"-c") != 0))) {
			outpath = (char*)malloc((sizeof(char)*strlen(argv[i+1]) + 64));
			strcpy(outpath, "./");
			strcat(outpath, argv[i+1]);
		}
		i++;
	}

	//checks for wrong header input

	if (column == NULL || !(!strcmp(column, "num_critic_for_reviews") || !strcmp(column, "duration")
		|| !strcmp(column, "director_facebook_likes") || !strcmp(column, "actor_3_facebook_likes")
		|| !strcmp(column, "actor_1_facebook_likes") || !strcmp(column, "gross") || !strcmp(column, "num_voted_users")
		|| !strcmp(column, "cast_total_facebook_likes") || !strcmp(column, "facenumber_in_poster")
		|| !strcmp(column, "num_user_for_reviews") || !strcmp(column, "budget") || !strcmp(column, "title_year")
		|| !strcmp(column, "actor_2_facebook_likes") || !strcmp(column, "movie_facebook_likes")
		|| !strcmp(column, "imdb_score") || !strcmp(column, "aspect_ratio")
		|| !strcmp(column, "color") || !strcmp(column, "director_name")
		|| !strcmp(column, "actor_2_name") || !strcmp(column, "genres") || !strcmp(column, "actor_1_name")
		|| !strcmp(column, "movie_title") || !strcmp(column, "actor_3_name")
		|| !strcmp(column, "plot_keywords") || !strcmp(column, "movie_imdb_link") || !strcmp(column, "language")
		|| !strcmp(column, "country") || !strcmp(column, "content_rating"))) {

		printf("Header does not exist.\n");
		return 0;
	}

	pthread_t * threads = (pthread_t *)malloc(sizeof(pthread_t)*20); //assume 20 threads to start, can reallocate +10 when necessary
	int maxThread = 20;
	int threadCount = 0;

	if (path==NULL)
		path = ".";
	else
		strcat(path, ".");

	if (outpath==NULL)
		outpath = ".";
	else
		strcat(outpath, ".");

	Data *data = malloc(sizeof(Data));

    strcpy(data->path, path);
    strcpy(data->column, column);


	if (pthread_create(&threads[threadCount], NULL, csvSearch, data) == 0)
		threadCount++;

	printf("Thread ID's %lu and %lu\n", pthread_self(), threads[0]);
	

	void * pv;
	pthread_join(threads[0], &pv);
	printf("hi from main\n");

	mergeFiles(outpath, column);

	free(data);
	return 0;
}
