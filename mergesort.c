
void Mergesort(Line* movies, int size, char* col) {

	int mid, i;
	Line *L, *R;

	if (size < 2) return;

	mid = size/2;

	L = (Line*)malloc(mid*sizeof(Line));
	R = (Line*)malloc((size - mid)*sizeof(Line));

	for(i = 0; i < mid; i++)
		L[i] = movies[i];
	for(i = mid; i < size; i++)
		R[i - mid] = movies[i];

	Mergesort(L, mid, col);
	Mergesort(R, size - mid, col);
	merge(movies, L, mid, R, size - mid, col);
	free(L);
	free(R);

	return;
}

void merge(Line* movies, Line* L, int l, Line* R, int r, char* col) {
	int i, j, k;
	i = 0; j = 0; k = 0;

	while(i < l && j < r) {

		if (!strcmp(col, "num_critic_for_reviews") || !strcmp(col, "duration") //all int types
			|| !strcmp(col, "director_facebook_likes") || !strcmp(col, "actor_3_facebook_likes")
			|| !strcmp(col, "actor_1_facebook_likes") || !strcmp(col, "gross") || !strcmp(col, "num_voted_users")
			|| !strcmp(col, "cast_total_facebook_likes") || !strcmp(col, "facenumber_in_poster")
			|| !strcmp(col, "num_user_for_reviews") || !strcmp(col, "budget") || !strcmp(col, "title_year")
			|| !strcmp(col, "actor_2_facebook_likes") || !strcmp(col, "movie_facebook_likes")) {

			if (getIntElement(&L[i], col) < getIntElement(&R[j], col))
				movies[k++] = L[i++];
			else
				movies[k++] = R[j++];

		} else if (!strcmp(col, "imdb_score") || !strcmp(col, "aspect_ratio")) { // all double types

			if (getDblElement(&L[i], col) < getDblElement(&R[j], col))
				movies[k++] = L[i++];
			else
				movies[k++] = R[j++];

		} else { //all char* types

			if (strcmp(getStrElement(&L[i], col), getStrElement(&R[j], col)) < 0)
				movies[k++] = L[i++];
			else
				movies[k++] = R[j++];
		}
	}
	while (i < l)
		movies[k++] = L[i++];
	while (j < r)
		movies[k++] = R[j++];
}

void mergeFiles(char * outpath, char * column) {
	DIR * dir = opendir("./tmp/");
	struct dirent* currentFile;
	char* nameEnd = "abcdefghijk";
	char* sorted = (char*)malloc(sizeof(column) + 13);
	int nameLength = 0;	//length of filename (includes possible "-sorted-<whatever>.csv")
	int endLength = 0;	//length of "-sorted-<whatever>.csv"
	int numFiles = 20; //hope to get this as a global var instead
	int size = sizeof("./tmp/" + 64);
	char filePaths[numFiles][size];
	char * filePath;
	int i = 0;

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
						strcpy(filePath, "./tmp/");
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
		int size = sizeof("./tmp/" + 64);
		while(j < 4){
			printf("FILE IS AT %s\n", filePaths[j * size]);
			j++;
		}
		//mergeTwoFiles(outpath, column, filePaths);
	}
	free(sorted);
	return;
}

void mergeTwoFiles(char * outpath, char * column, char * path1, char * path2) {

}

int getIntElement(Line *line, char* col) {
	if (!strcmp(col, "num_critic_for_reviews"))
		return line -> num_critic_for_reviews;
	else if (!strcmp(col, "duration"))
		return line -> duration;
	else if (!strcmp(col, "director_facebook_likes"))
		return line -> director_facebook_likes;
	else if (!strcmp(col, "actor_3_facebook_likes"))
		return line -> actor_3_facebook_likes;
	else if (!strcmp(col, "actor_1_facebook_likes"))
		return line -> actor_1_facebook_likes;
	else if (!strcmp(col, "gross"))
		return line -> gross;
	else if (!strcmp(col, "num_voted_users"))
		return line -> num_voted_users;
	else if (!strcmp(col, "cast_total_facebook_likes"))
		return line -> cast_total_facebook_likes;
	else if (!strcmp(col, "facenumber_in_poster"))
		return line -> facenumber_in_poster;
	else if (!strcmp(col, "num_user_for_reviews"))
		return line -> num_user_for_reviews;
	else if (!strcmp(col, "budget"))
		return line -> budget;
	else if (!strcmp(col, "title_year"))
		return line -> title_year;
	else if (!strcmp(col, "actor_2_facebook_likes"))
		return line -> actor_2_facebook_likes;
	else if (!strcmp(col, "movie_facebook_likes"))
		return line -> movie_facebook_likes;
	else
		return 0;


}

double getDblElement(Line *line, char* col) {
	if (!strcmp(col, "imdb_score"))
		return line -> imdb_score;
	else if (!strcmp(col, "aspect_ratio"))
		return line -> aspect_ratio;
	else
		return 0.0;
}

char* getStrElement(Line *line, char* col) { 	
	if (!strcmp(col, "color"))				
		return line -> color;
	else if (!strcmp(col, "director_name"))
		return line -> director_name;
	else if (!strcmp(col, "actor_2_name"))
		return line -> actor_2_name;
	else if (!strcmp(col, "genres"))
		return line -> genres;
	else if (!strcmp(col, "actor_1_name"))
		return line -> actor_1_name;
	else if (!strcmp(col, "movie_title"))
		return line -> movie_title;
	else if (!strcmp(col, "actor_3_name"))
		return line -> actor_3_name;
	else if (!strcmp(col, "plot_keywords"))
		return line -> plot_keywords;
	else if (!strcmp(col, "movie_imdb_link"))
		return line -> movie_imdb_link;
	else if (!strcmp(col, "language"))
		return line -> language;
	else if (!strcmp(col, "country"))
		return line -> country;
	else if (!strcmp(col, "content_rating"))
		return line -> content_rating;
	else
		return "";
	}