#ifndef sorter_h
#define sorter_h

//Line struct stores the data of each line of the CSV input file.
typedef struct{					//I used typedef so we can reference just "Line" instead 
						//of "struct line" every time
	char color[32];
	char director_name[128];
	int num_critic_for_reviews;
	int duration;				//must change to datetime?
	int director_facebook_likes;
	int actor_3_facebook_likes;
	char actor_2_name[128];
	int actor_1_facebook_likes;
	int gross;
	char genres[512];
	char actor_1_name[128];
	char movie_title[128];
	int num_voted_users;
	int cast_total_facebook_likes;
	char actor_3_name[128];
	int facenumber_in_poster;
	char plot_keywords[256];
	char movie_imdb_link[256];
	int num_user_for_reviews;
	char language[64];
	char country[64];
	char content_rating[8];
	int budget;
	int title_year;
	int actor_2_facebook_likes;
	double imdb_score;
	double aspect_ratio;
	int movie_facebook_likes;	
} Line;


//prototypes
Line* importLine (char* buf);
char* clearWhitespace (char* input);
char* getNextToken(char* tokPointer, char temp[], char* tempPointer);
Line* Mergesort(Line* movies, char* col);
void sort(Line* movies, int n, char* col);
void merge(Line* movies, Line* L, int l, Line* R, int r, char* col);

//functions

//creates a Line struct made from an input line of the csv input file and returns it
Line* importLine (char* buf){

	//TODO catch for empty string/null string



	//add a space between each place where ",," is found for two purposes
	//1. allow strtok to work
	//2. Make sorting easier, because " " instead of null string
	char spaceMaker[1024];
	char *spacePointer = spaceMaker;
	if(*buf == ','){
		spaceMaker[0] = ' ';
		spaceMaker[1] = '\0';
		spacePointer = strcat(spacePointer, buf);
		strncpy(buf, spacePointer, strlen(spacePointer));
		buf[strlen(spacePointer)]='\0';
	}
	char justASpace[2];
	justASpace[0]=' ';
	justASpace[1]='\0';
	char *commaPointer = strstr(buf, ",,");
	while(commaPointer!=NULL){
		memset(spacePointer, 0, 1024);
		strncpy(spaceMaker, buf, commaPointer-buf+1);
		spaceMaker[commaPointer-buf+1]='\0';
		spacePointer = strcat(spacePointer, justASpace);
		commaPointer++;
		spacePointer = strcat(spacePointer, commaPointer);
		strncpy(buf, spacePointer, strlen(spacePointer));
		buf[strlen(spacePointer)] = '\0';
		commaPointer = strstr(buf, ",,");		
	}

//	printf("%s\n", buf);

	Line *toReturn;
	toReturn = malloc(sizeof(Line));

	char* tokPointer;
	char temp[512];
	char* tempPointer;
	tokPointer = strtok(buf, ",");
	strncpy(temp, tokPointer, strlen(tokPointer));
	temp[strlen(tokPointer)]='\0';
	tempPointer = temp;
	
	tempPointer = clearWhitespace(temp);
	strncpy(temp, tempPointer, strlen(tempPointer));

	
	//store EVERYTHING!!!
	strncpy(toReturn->color, tempPointer, strlen(tempPointer));
	toReturn->color[strlen(tempPointer)]='\0';
	
	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->director_name, tempPointer, strlen(tempPointer));
	toReturn->director_name[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->num_critic_for_reviews = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->duration = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->director_facebook_likes = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->actor_3_facebook_likes = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->actor_2_name, tempPointer, strlen(tempPointer));
	toReturn->actor_2_name[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->actor_1_facebook_likes = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->gross = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->genres, tempPointer, strlen(tempPointer));
	toReturn->genres[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->actor_1_name, tempPointer, strlen(tempPointer));
	toReturn->actor_1_name[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->movie_title, tempPointer, strlen(tempPointer));
	toReturn->movie_title[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->num_voted_users = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->cast_total_facebook_likes = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->actor_3_name, tempPointer, strlen(tempPointer));
	toReturn->actor_3_name[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->facenumber_in_poster = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->plot_keywords, tempPointer, strlen(tempPointer));
	toReturn->plot_keywords[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->movie_imdb_link, tempPointer, strlen(tempPointer));
	toReturn->movie_imdb_link[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->num_user_for_reviews = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->language, tempPointer, strlen(tempPointer));
	toReturn->language[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->country, tempPointer, strlen(tempPointer));
	toReturn->country[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	strncpy(toReturn->content_rating, tempPointer, strlen(tempPointer));
	toReturn->content_rating[strlen(tempPointer)]='\0';

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->budget = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->title_year = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->actor_2_facebook_likes = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->imdb_score = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->aspect_ratio = atoi(tempPointer);

	tempPointer = getNextToken(tokPointer, temp, tempPointer);
	toReturn->movie_facebook_likes = atoi(tempPointer);

//	printf("%s\n%d\n", toReturn->movie_title,toReturn->gross);
	return toReturn;
}

//takes a string and trims white space from the front and back, then returns it
char* clearWhitespace(char* input){
	while(input[0]==' '){
		input++;
	}
	while(input[strlen(input)-1]==' '){
		input[strlen(input)-1]='\0';
	}

return input;
}

char* getNextToken(char* tokPointer, char temp[], char* tempPointer){
	tokPointer = strtok(NULL, ",");
	strncpy(temp, tokPointer, strlen(tokPointer));
	temp[strlen(tokPointer)]='\0';
	tempPointer = temp;
	
	tempPointer = clearWhitespace(temp);
	strncpy(temp, tempPointer, strlen(tempPointer));

	//account for extra commas in names (shown by quotation marks in csv file)
	if(temp[0]=='"'){
		tempPointer = strcat(tempPointer, ",\0");
		strncpy(temp, tempPointer, strlen(tempPointer));
		//while the last characters are not exactly ' "'
		while(temp[strlen(tempPointer)-1] != '\"'){// || temp[strlen(tempPointer)-2] != ' '){
			tempPointer = strcat(tempPointer, strtok(NULL, ","));
			strncpy(temp, tempPointer, strlen(tempPointer));
		}
			temp[strlen(tempPointer)-1]='\0';
			tempPointer = clearWhitespace(tempPointer);
			strncpy(temp, tempPointer, strlen(tempPointer));
			temp[strlen(tempPointer)]='\0';
			tempPointer++;
	}
	
	return tempPointer;
}


#endif
