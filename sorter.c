#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"sorter.h"
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include"mergesort.c"
#include<dirent.h>
#include"csvsearch.c"

int main(int argc, char *argv[]) {

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
	//error handling for wrong header input still needed?

	//user input handling
	char* output = NULL;	
	char* path = NULL;

	if(argc>3){
		if(strcmp(argv[3],"-d") == 0){
			if(argc>4){
				if(strcmp(argv[4],"-o") != 0){
					path = (char*)malloc((sizeof(char)*strlen(argv[4]) + 64));
					strcpy(path, "./");
					strcat(path, argv[4]);
				}
				if(argc>5){
					if(strcmp(argv[4], "-o")== 0){
						output = (char*)malloc((sizeof(char)*strlen(argv[5]) + 64));
						strcpy(output, "./");
						strcat(output, argv[5]);
					}
					else if(argc>6 && strcmp(argv[5], "-o")== 0){
						output = (char*)malloc((sizeof(char)*strlen(argv[6]) + 64));
						strcpy(output, "./");
						strcat(output, argv[6]);
					}
				}
			}
		}
		if(strcmp(argv[3],"-o") == 0){
			if(argc>4){
				if(strcmp(argv[4],"-d") != 0){
					output = (char*)malloc((sizeof(char)*strlen(argv[4]) + 64));
					strcpy(output, "./");
					strcat(output, argv[4]);
				}
				if(argc>5){
					if(strcmp(argv[4],"-d") == 0){
						path = (char*)malloc((sizeof(char)*strlen(argv[5]) + 64));
						strcpy(path, "./");
						strcat(path, argv[5]);
					}
					else if(argc>6 && strcmp(argv[5],"-d") == 0){
						path = (char*)malloc((sizeof(char)*strlen(argv[6]) + 64));
						strcpy(path, "./");
						strcat(path, argv[6]);
					}
				}
			}
		}
	}

	printf("Initial PID: %d\n", getpid());
	printf("PIDS of all child processes: ");
	fflush(stdout);
	
	int fd[2];
	pipe(fd); 	//write(fd[1], char* data, int length_of_data);
	 		// or read(fd[0], char* buf, int size_of_buf);
	if(path==NULL)
		csvSearch(".", output, argv[2]);
	else
		csvSearch(strcat(path, "."), output, argv[2]);

	fflush(stdout);
	//printf("Total number of processes: %d\n", getpid());
	return 0;
}
