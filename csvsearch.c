
void csvSearch(char* path){
	DIR * dir = opendir(path);
	struct dirent* currentFile;
	char* lastFour = "abcd";
	int length=0;
	int status=0;
	char* newpath;
	pid_t PID, child, wpid;

	if (dir){
		while((currentFile = readdir(dir)) != NULL){
			length = strlen(currentFile->d_name);
			if(strcmp(currentFile->d_name,".") == 0 || strcmp(currentFile->d_name,"..") == 0);
			else{
				newpath = (char*)malloc((sizeof(char)*strlen(path)) + (sizeof(char)*length) + 8);
				strcpy(newpath, path);
				strcat(newpath, "/");
				strcat(newpath, currentFile->d_name);
				if((child = fork()) == 0){
					csvSearch(newpath);
					exit(0);
				}
			}
			if(length>4){
				lastFour = currentFile->d_name;
				lastFour = lastFour + (length - 4);
			}
			if(strcmp(lastFour, ".csv")==0)
				printf("%s\n", newpath);
		}
		if(newpath != NULL)
			free(newpath);
		while((wpid = wait(&status)) > 0);
	}
}
