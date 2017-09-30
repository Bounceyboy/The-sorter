

Line* Mergesort(Line* movies, char* col) {
	int i = sizeof(Line);	// length of line (1 movie) in bytes
	int n = sizeof(movies)/i;	// number of movies in array

	return sort(movies, n, col);
}

Line* sort(Line* movies, n, char* col) {
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
	return merge(movies, L, mid, R, n - mid);
}

Line* merge(Line* movies, Line* L, int l, Line* R, int r, col) {
	int i, j, k;
	i = 0, j = 0, k = 0;

	while(i < l && j < r) {
		if (strcmp(L[i] -> col, R[j] -> col) < 0)
			movies[k++] = L[i++];
		else
			movies[k++] = R[j++];
	}
	while (i < l)
		movies[k++] = L[i++];
	while (j < r)
		movies[k++] = R[j++];

	free(L);
	free(R);
	return movies;
}
