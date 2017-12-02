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

	mergeTwoFiles("./bboyisverysexy420yoloswag69/", column, "./bboyisverysexy420yoloswag69/data-sorted-movie_title.csv", "./bboyisverysexy420yoloswag69/movie_metadata-sorted-movie_title.csv", 1);
	return 0;

	pthread_t thread;

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
    int x = 1;
    data->threadCount = &x;

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    printf("Initial TID: %lu\n\n", pthread_self());
    printf("TIDs of all child threads: ");
	pthread_create(&thread, NULL, csvSearch, data);
	


	void * pv;
	pthread_join(thread, &pv);


	//q: still need to multithread this?

	//a: no, there's no point because we need to wait for this to return before
	//printing out the number of threads created, and we create more threads in
	//mergeFiles

	//stores file paths into filePaths[][]
	DIR * dir = opendir("./tmp/");
	struct dirent* currentFile;
	char* nameEnd = "abcdefghijk";
	char* sorted = (char*)malloc(sizeof(column) + 13);
	int nameLength = 0;	//length of filename (includes possible "-sorted-<whatever>.csv")
	int endLength = 0;	//length of "-sorted-<whatever>.csv"
	int numFiles = 20; //hope to get this as a global var instead
	int size = sizeof("./bboyisverysexy420yoloswag69/" + 128);
	char filePaths[numFiles][size];
	char * filePath;
	i = 0;

	strcpy(sorted, "-sorted-");
	strcat(sorted, column);
	strcat(sorted, ".csv");

	endLength = strlen(sorted);
	if (dir) {
		while ((currentFile = readdir(dir)) != NULL) {
			if(strcmp(currentFile->d_name,".") == 0 || strcmp(currentFile->d_name,"..") == 0);
			else {
				nameEnd = currentFile->d_name;
				nameLength = strlen(nameEnd);
				if (nameLength > endLength){
					nameEnd = nameEnd + (nameLength - endLength);
					if(strcmp(nameEnd, sorted) == 0){	//sorted, add to array of sorted-file paths
						filePath = filePaths[i * size];
						strcpy(filePath, "./bboyisverysexy420yoloswag69/");
						//printf("just tmp: %s\n", filePath);
						strcat(filePath, currentFile->d_name);
						//printf("filePath: %s\n", filePath);
						//strcpy(filePaths[i],filePath);
						//printf("filepaths[i]: %s\n", filePaths[i*sizeof("./tmp/" + 64)]);
						//memset(filePath, 0, sizeof(filePath));
						//printf("i before increment: %d\n", i);
						i++;

					}
					nameEnd = nameEnd + endLength;
				}
			}
		}
		int j = 0;
		int size = sizeof("./bboyisverysexy420yoloswag69/" + 64);
		
		/*while(j < i){
			printf("FILE IS AT %s\n", filePaths[j * size]);
			j++;
		}*/


		mergeTwoFiles(outpath, column, filePaths[0*size], filePaths[1*size], 1);
		//put your code here; we don't want to call the function if there was never a tmp directory made
		//each filePath in the filePaths array is in format ./tmp/filename-sorted-<column>.csv

	}


	free(sorted);
	//printf("hi from main\n");

	printf("and %lu\n\n", thread);
	pthread_mutex_lock(&mutex);
	(*(data->threadCount))++;
	printf("Total number of threads: %d\n", *(data->threadCount));
	pthread_mutex_unlock(&mutex);
	free(data);
	return 0;
}
