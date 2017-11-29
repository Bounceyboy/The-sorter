
void *csvSearch(void * data){
	//unpack Data struct
	Data * input = (Data *) data;

	char * path = input->path;
	char * outpath = input->outpath;
	char * column = input->column;

	DIR * dir = opendir(path);
	struct dirent* currentFile;
	char* nameEnd = "abcdefghijk"; 	//changed to 11 chars to check "-sorted.csv"
	char* sorted = (char*)malloc(sizeof(column) + 13); // 13 is size of "-sorted-.csv" + 1 just in case
	int nameLength = 0;	//length of filename (includes possible "-sorted-<whatever>.csv")
	int endLength = 0;	//length of "-sorted-<whatever>.csv"
	char* newpath;
	pthread_t *TID = malloc(sizeof(pthread_t));
	pid_t wpid, child;
	int status = 0;
	Data *newData = malloc(sizeof(Data));

	strcpy(sorted, "-sorted-");
	strcat(sorted, column);
	strcat(sorted, ".csv");

	endLength = strlen(sorted);

	if (dir){
		while((currentFile = readdir(dir)) != NULL){
			nameLength = strlen(currentFile->d_name);
			if(strcmp(currentFile->d_name,".") == 0 || strcmp(currentFile->d_name,"..") == 0);
			else{
				newpath = (char*)malloc((sizeof(char)*strlen(path)) + (sizeof(char)*nameLength) + 16);
				strcpy(newpath, path);
				strcat(newpath, "/");
				strcat(newpath, currentFile->d_name);

				strcpy(newData->path, path);
				strcpy(newData->outpath, outpath);
				strcpy(newData->path, column);

				if((child = fork()) == 0) {
					csvSearch(newData);
					exit(0);
				}
				nameEnd = currentFile->d_name;

				//ignores directory entries less than 4 chars long
				if(nameLength > endLength){ //checks long filenames to see if sorted
					nameEnd = nameEnd + (nameLength - endLength);
					if (strcmp(nameEnd, sorted) == 0)	//skips sorted file
						continue;
					nameEnd = nameEnd + endLength;		//movies pointer to end of filename
				}
				if(nameLength > 4 && nameLength < endLength) //moves nameEnd to last 4 chars
					nameEnd = nameEnd + (nameLength - 4);
				else
					nameEnd = nameEnd - 4;		//moves nameEnd to last 4 chars (case 2)
				if(strcmp(nameEnd, ".csv")==0){
					if ((child = fork()) == 0){
						strcpy(newData->path, path);
						strcpy(newData->outpath, outpath);
						strcpy(newData->path, column);

						csvSort(newData);
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
		free(newData);
		exit(0);		

	}
	// printf("Total number of processes: %d\n", prcsnum);
	// fflush(stdout);
	//return processes;
}

void *csvSort(void * data) {
	//unpack Data struct
	Data *input = data;

	char * pathToFile = input->path;
	char * outpath = input->outpath;
	char * column = input->column;

	FILE * toCount = fopen(pathToFile, "r");
	FILE * toSort = fopen(pathToFile, "r");
	char * filename = (char *)malloc(256 * sizeof(char));
	char * path; 			//directory where file is stored
	FILE * output; 			//path to -sorted file

	path = (char*)malloc(sizeof(strlen(pathToFile)) + 192);
	strcpy(path, pathToFile); 	//path is now direct path to file
	filename = strrchr(pathToFile, '/');
	filename++; 				//file name as "file.csv"

	int endOfPath = (strlen(path) - strlen(filename));
	strncpy(path, path, endOfPath);
	path[endOfPath] = '\0'; //path without filename at end

	int endOfFilename = strlen(filename) - 4;
	strncpy(filename, filename, endOfFilename);
	filename[endOfFilename] = '\0'; //filename without .csv at the end

	strcat(filename, "-sorted-");
	strcat(filename, column);
	strcat(filename, ".csv");

	if (outpath == NULL){
		strcat(path, filename);
		output = fopen(path, "w");
	} else {
		strcat(outpath, "/"); 	//failsafe for input that doesn't add ending slash
		mkdir(outpath, 0755);
		strcat(outpath, filename);
		output = fopen(outpath, "w"); //opens file in path to write to
	}

	int numberOfLines = line_count(toCount);
	fclose(toCount);

	Line *Lines = malloc(sizeof(Line) * (numberOfLines + 1));
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

	strncpy(header, buf, strlen(buf));

	//one manual fgets call to store in first line so that there isn't an extra
	//empty Line in the array "Lines"
	fgets(buf,1024,toSort);
	Lines[0] = *importLine(buf);
	

	//in this loop:
	//increment ArraySize
	//Call importLine to create that line and add it to "Lines"
	while(fgets(buf,1024,toSort)!=NULL){	//for each line (gets stored in string "buf")
		ArraySize++;
		Lines[ArraySize-1] = *importLine(buf);
	}

	Mergesort(Lines, ArraySize, toSortBy);

	int x;
	fprintf(output, "%s", header);
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
}

int line_count(FILE *n) {
	int c; 
	int lines = 0;
	while ((c = fgetc(n)) != EOF) {
		if (c == '\n')
			++lines;
	}
	return lines;
} 