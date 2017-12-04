
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

void * mergeTwoFiles(void * data) {
	pthread_mutex_lock(&mutex2);
	char outpath[256];
	char column[32];
	char file1path[256];
	char file2path[256];	
	MergeData * input = (MergeData *) data;
	int filenum = input->filenum;

	strcpy(outpath, input->outpath);
	strcpy(column, input->column);
	strcpy(file1path, input->file1);
	strcpy(file2path, input->file2);
	pthread_mutex_unlock(&mutex2);

	FILE * f1count = fopen(file1path, "r");
	FILE * f2count = fopen(file2path, "r");

	//multithread this
	int numLines1 = line_count(f1count);
	fclose(f1count);
	int numLines2 = line_count(f2count);
	fclose(f2count);

	
	char* sorted = (char*)malloc(sizeof(column) + 13);
	strcpy(sorted, "-sorted-");
	strcat(sorted, column);
	strcat(sorted, ".csv");

	char outfile[128];
	if (strcmp(outpath, "./bboyisverysexy420yoloswag69/") == 0)
		sprintf(outfile, "./bboyisverysexy420yoloswag69/temp%d%s", filenum, sorted);
	else
		sprintf(outfile, "%sAllFiles%s", outpath, sorted);
	free(sorted);

	FILE * file1 = fopen(file1path, "r");
	FILE * file2 = fopen(file2path, "r");
	mkdir(outpath, 0755);
	FILE * result = fopen(outfile, "w");

	char buf1[1024];
	char buf2[1024];

	//get headers
	fgets(buf1,1024,file1);
	fgets(buf2,1024,file2);

	//compare headers
	if(strcmp(buf1, buf2))
		return;	// not the same header, can't combine
	fprintf(result, "%s", buf1); //store header

	while (fgets(buf1, 1024, file1) != NULL){
		fprintf(result, "%s", buf1);
	}

	while (fgets(buf2, 1024, file2) != NULL){
		fprintf(result, "%s", buf2);
	}

	
	fclose(file1);
	fclose(file2);
	remove(file1path);
	remove(file2path);
	fclose(result);
	return;

	/*Line *f1Line = (Line*)malloc(sizeof(Line));
	Line *f2Line = (Line*)malloc(sizeof(Line));

	char buf1[1024];
	char buf2[1024];

	//get headers
	fgets(buf1,1024,file1);
	fgets(buf2,1024,file2);

	//compare headers
	if(strcmp(buf1, buf2))
		return;	// not the same header, can't combine
	fprintf(result, "%s", buf1); //store header

	int end1 = 0;
	int end2 = 0;

	fgets(buf1,1024,file1);
	fgets(buf2,1024,file2);
	f1Line = importLine(buf1);
	f2Line = importLine(buf2);
	end1++;
	end2++;
	while((end1 < numLines1) && (end2 < numLines2)) {
		if (strcmp(buf1, buf2) == 0){
			fprintf(result, "%s", buf1);
			fgets(buf1,1024,file1);
			fgets(buf2,1024,file2);
			f1Line = importLine(buf1);
			f2Line = importLine(buf2);
			end1++;
			end2++;
		} else {
			if (!strcmp(column, "num_critic_for_reviews") || !strcmp(column, "duration")
				|| !strcmp(column, "director_facebook_likes") || !strcmp(column, "actor_3_facebook_likes")
				|| !strcmp(column, "actor_1_facebook_likes") || !strcmp(column, "gross") || !strcmp(column, "num_voted_users")
				|| !strcmp(column, "cast_total_facebook_likes") || !strcmp(column, "facenumber_in_poster")
				|| !strcmp(column, "num_user_for_reviews") || !strcmp(column, "budget") || !strcmp(column, "title_year")
				|| !strcmp(column, "actor_2_facebook_likes") || !strcmp(column, "movie_facebook_likes")) {

				if (getIntElement(f1Line, column) < getIntElement(f2Line, column)){
					fprintf(result, "%s", buf1);
					fgets(buf1,1024,file1);
					f1Line = importLine(buf1);
					end1++;
				}
				else if (getIntElement(f1Line, column) > getIntElement(f2Line, column)){
					fprintf(result, "%s", buf2);
					fgets(buf2,1024,file2);
					f2Line = importLine(buf2);
					end2++;
				} else {
					fprintf(result, "%s", buf1);
					fgets(buf1,1024,file1);
					fgets(buf2,1024,file2);
					f1Line = importLine(buf1);
					f2Line = importLine(buf2);
					end1++;
					end2++;

				}

			} else if (!strcmp(column, "imdb_score") || !strcmp(column, "aspect_ratio")) {
				if (getDblElement(f1Line, column) < getDblElement(f2Line, column)){
					fprintf(result, "%s", buf1);
					fgets(buf1,1024,file1);
					f1Line = importLine(buf1);
					end1++;
				}
				else if (getDblElement(f1Line, column) > getDblElement(f2Line, column)){
					fprintf(result, "%s", buf2);
					fgets(buf2,1024,file2);
					f2Line = importLine(buf2);
					end2++;
				} else {
					fprintf(result, "%s", buf1);
					fgets(buf1,1024,file1);
					fgets(buf2,1024,file2);
					f1Line = importLine(buf1);
					f2Line = importLine(buf2);
					end1++;
					end2++;
				}

			} else {
				if (strcmp(getStrElement(f1Line, column), getStrElement(f2Line, column)) < 0){
					fprintf(result, "%s", buf1);
					fgets(buf1,1024,file1);
					f1Line = importLine(buf1);
					end1++;
				}
				else if (strcmp(getStrElement(f1Line, column), getStrElement(f2Line, column)) > 0){
					fprintf(result, "%s", buf2);
					fgets(buf2,1024,file2);
					f2Line = importLine(buf2);
					end2++;
				} else{
					fprintf(result, "%s", buf1);
					fgets(buf1,1024,file1);
					fgets(buf2,1024,file2);
					f1Line = importLine(buf1);
					f2Line = importLine(buf2);
					end1++;
					end2++;
				}
			}
		}
	}

	if (end1 == numLines1) {
		while (fgets(buf2, 1024, file2) != NULL){
			fprintf(result, "%s", buf2);
		}
	} else if (end2 == numLines2){
		while (fgets(buf1, 1024, file1) != NULL){
			fprintf(result, "%s", buf1);
		}
	}

	fclose(file1);
	fclose(file2);
	remove(file1path);
	remove(file2path);
	fclose(result);
	free(f1Line);
	free(f2Line);

	return;*/
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