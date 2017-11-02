
void csvSearch(char* path, char* outpath, char* toSortBy){
	DIR * dir = opendir(path);
	struct dirent* currentFile;
	char* nameEnd = "abcdefghijk"; //changed to 11 chars to check "-sorted.csv"
	int length=0;
	int status=0;
	char* newpath;
	pid_t PID, child, wpid;

	if (dir){
		while((currentFile = readdir(dir)) != NULL){
			length = strlen(currentFile->d_name);
			if(strcmp(currentFile->d_name,".") == 0 || strcmp(currentFile->d_name,"..") == 0);
			else{
				newpath = (char*)malloc((sizeof(char)*strlen(path)) + (sizeof(char)*length) + 16);
				strcpy(newpath, path);
				strcat(newpath, "/");
				strcat(newpath, currentFile->d_name);
				if((child = fork()) == 0){
					csvSearch(newpath, outpath, toSortBy);
					exit(0);
				}
				nameEnd = currentFile->d_name;
				if(length > 11){
					nameEnd = nameEnd + (length - 11);
					if (strcmp(nameEnd, "-sorted.csv") == 0)
						continue;
					nameEnd = nameEnd + 11;
				}
				if(length > 4 && length < 11)
					nameEnd = nameEnd + (length - 4);
				else
					nameEnd = nameEnd - 4;
				if(strcmp(nameEnd, ".csv")==0){
					if ((child = fork()) == 0){
						csvSort(newpath, outpath, toSortBy);
						exit(0);
					}
				}
			}
		}
		if(newpath != NULL)
			free(newpath);
		while((wpid = wait(&status)) > 0){
			printf("%d, ", wpid);
		}

		exit(0);		

	}
	// printf("Total number of processes: %d\n", prcsnum);
	// fflush(stdout);
	//return processes;
}

void csvSort(char* pathToFile, char* outpath, char* column) {
	FILE * toSort = fopen(pathToFile, "r");
	char * filename;
	char * path; 			//directory where file is stored
	FILE * output; 			//path to -sorted file

	path = (char*)malloc(sizeof(strlen(pathToFile)));
	strcpy(path, pathToFile); 	//path is now direct path to file
								//(not yet just path to dir where file is held)
	filename = strrchr(pathToFile, '/');
	filename++; 				//file name as "file.csv"
	strtok(path, filename);		//path is now "./dir/somewhere/" (where file is held)
	strtok(filename, "."); 		//file name as "file"
	strcat(filename, "-sorted.csv"); //"file-sorted.csv"

	if (outpath == NULL){
		strcat(path, filename);
		output = fopen(path, "w");
	} else {
		strcat(outpath, "/"); 	//failsafe for input that doesn't add ending slash
		mkdir(outpath, S_IRWXU);
		strcat(outpath, filename);
		output = fopen(outpath, "w"); //opens file in path to write to
	}

	Line *Lines = malloc(sizeof(Line*));
	char buf[1024];
	char header[1024];
	
	int ArraySize = 1;
	char toSortBy[64];
	int i;
	for (i = 0; i < 64; ++i)
		toSortBy[i] = 0;
	strncpy(toSortBy, column, strlen(column));

	//store header line of csv
	fgets(buf,1024,toSort);

	//printf("\n\nbuf is: %s\n\n\n", buf);

	// if(buf == NULL || buf == "\0" || !isalnum(buf) || buf == "" || buf == " "){
	// 	fprintf(output, "EMPTY FILE\n");
	// 	fflush(output);
	// 	fclose(output);
	// 	exit(0);
	// }
	//fprintf(output, "i hate myself so much\n");
	//fflush(output);
	//fclose(output);
	//exit(0);

	strncpy(header, buf, strlen(buf));

	//one manual fgets call to store in first line so that there isn't an extra
	//empty Line in the array "Lines"
	fgets(buf,1024,toSort);
	Lines[0] = *importLine(buf);
	

	//in this loop:
	//increment ArraySize
	//Reallocate memory to allow for an additional Line in "Lines"
	//Call importLine to create that line and add it to "Lines"
	
	while(fgets(buf,1024,toSort)!=NULL){	//for each line (gets stored in string "buf")
		ArraySize++;
		Lines = realloc(Lines, ((ArraySize + 1)*sizeof(Line*)));
		Lines[ArraySize-1] = *importLine(buf);
	}

	Mergesort(Lines, ArraySize, toSortBy);

	int x;
	fprintf(output, "%s\n", header);
	for(x=0;x<ArraySize;x++){

		if(strcmp((&Lines[x])->color,"lack and Whitee"))
			fprintf(output, "Black and White,");
		else
			fprintf(output, "%s,",(&Lines[x])->color);
		fprintf(output, "%s,",(&Lines[x])->director_name);
		fprintf(output, "%d,",(&Lines[x])->num_critic_for_reviews);
		fprintf(output, "%d,",(&Lines[x])->duration);
		fprintf(output, "%d,",(&Lines[x])->director_facebook_likes);
		fprintf(output, "%d,",(&Lines[x])->actor_3_facebook_likes);
		fprintf(output, "%s,",(&Lines[x])->actor_2_name);
		fprintf(output, "%d,",(&Lines[x])->actor_1_facebook_likes);
		fprintf(output, "%d,",(&Lines[x])->gross);
		fprintf(output, "%s,",(&Lines[x])->genres);
		fprintf(output, "%s,",(&Lines[x])->actor_1_name);		
		char *y = strchr((&Lines[x])->movie_title,',');
		if(y==NULL)
			fprintf(output, "%s,",(&Lines[x])->movie_title);
		else
			fprintf(output, "\"%s \",",(&Lines[x])->movie_title);
		fprintf(output, "%d,",(&Lines[x])->num_voted_users);
		fprintf(output, "%d,",(&Lines[x])->cast_total_facebook_likes);
		fprintf(output, "%s,",(&Lines[x])->actor_3_name);
		fprintf(output, "%d,",(&Lines[x])->facenumber_in_poster);
		fprintf(output, "%s,",(&Lines[x])->plot_keywords);
		fprintf(output, "%s,",(&Lines[x])->movie_imdb_link);
		fprintf(output, "%d,",(&Lines[x])->num_user_for_reviews);
		fprintf(output, "%s,",(&Lines[x])->language);
		fprintf(output, "%s,",(&Lines[x])->country);
		fprintf(output, "%s,",(&Lines[x])->content_rating);
		fprintf(output, "%d,",(&Lines[x])->budget);
		fprintf(output, "%d,",(&Lines[x])->title_year);
		fprintf(output, "%d,",(&Lines[x])->actor_2_facebook_likes);
		fprintf(output, "%f,",(&Lines[x])->imdb_score);
		fprintf(output, "%f,",(&Lines[x])->aspect_ratio);
		fprintf(output, "%d\n",(&Lines[x])->movie_facebook_likes);
	}

	free(Lines);
	free(path);
	fclose(output);
	fclose(toSort);
	return;
	exit(0);
}