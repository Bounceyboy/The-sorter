
Line* Mergesort(Line* movies, char* col) {
	int i = sizeof(Line);	// length of line (1 movie) in bytes
	int n = sizeof(movies)/i;	// number of movies in array

	sort(movies, n, col);
	return movies;
}

void sort(Line* movies, int n, char* col) {
	int mid, i;
	Line *L, *R;

	if (n < 2) return;

	mid = n/2;

	L = (Line*)malloc(mid*sizeof(Line));
	R = (Line*)malloc((n - mid)*sizeof(Line));

	for(i = 0; i < mid; i++)
		L[i] = movies[i];
	for(i = mid; i < n; i++)
		R[i - mid] = movies[i];

	sort(L, mid, col);
	sort(R, n - mid, col);
	merge(movies, L, mid, R, n - mid, col);
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

}

double getDblElement(Line *line, char* col) {
	if (!strcmp(col, "imdb_score"))
		return line -> imdb_score;
	else if (!strcmp(col, "aspect_ratio"))
		return line -> aspect_ratio;
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
	}