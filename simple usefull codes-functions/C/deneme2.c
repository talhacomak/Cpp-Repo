#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct instruction_s {
	int step; //satýr
	int index; //kelime
};


char* get_word(char* s, int n){
	char* word = (char*) malloc(sizeof(char) * 30);
	int i, j, word_num = 1;
	
	for(i=0; i<30; i++){
		word[i]='\0';
	}
	
	for(i=0; i<200; i++){
		if(word_num == n) break;
		if(*(s+i) == ' '){
			word_num ++;
		}
	}
	i--;
	for(j=0; j<30; j++){
		i++;
		if(s[i] == ' ') break;
		else if(s[i] == '\n') break;
		word[j] = s[i];
	}
	word[j] = ' ';
	
	return word;
}


void get_sentence(char** lines, struct instruction_s* instruction, int n_instructions, char* sentence){
	char* w = (char*) malloc(sizeof(char) * 30);
	int i, x, y;
	for(i=0; i<30; i++){
		w[i]='\0';
	}

	for(i=0; i<n_instructions; i++){
		x = (instruction+i)->step;
		y = (instruction+i)->index;
		strcpy(w, get_word(lines[x], y));
		strcat(sentence, w);
	}
}



int main(int argc, char** argv){
	int i, j, size_line, size_line2, c, x, y, x2 = 0, y2 = 0;
	struct instruction_s* instruc;
	
	char sentence[10000];
	for(i=0; i<10000; i++){
		sentence[i]='\0';
	}
	
	char** book = (char**) malloc(10000*sizeof(char*));
	for(i=0; i<10000; i++){
		book[i] = (char*) malloc(200*sizeof(char));
		for(j=0; j<200; j++){
			book[i][j]='\0';
		}
	}
	
	char** book2 = (char**) malloc(10000*sizeof(char*));
	for(i=0; i<10000; i++){
		book2[i] = (char*) malloc(200*sizeof(char));
		for(j=0; j<200; j++){
			book2[i][j]='\0';
		}
	}
	
	char** ins = (char**) malloc(10000*sizeof(char*));
	for(i=0; i<10000; i++){
		ins[i] = (char*) malloc(12*sizeof(char));
		for(j=0; j<12; j++){
			ins[i][j]='\0';
		}
	}


	FILE* ptr = fopen(argv[0], "r");
	if(ptr == NULL) printf("File not found.\n");
	else{
		for(i=1; i<10000; i++){
			size_line = i;
			for(j=0; j<200; j++){
				c = fgetc(ptr);
				if (feof(ptr)){
					c = -1;
					break;
				}
				book[i][j] = '\0' + c;
				if(book[i][j] == '\n') break;
			}
			if (c == -1) break;
		}
	}
	fclose(ptr);


	
	FILE* ptr_ins = fopen(argv[1], "r");
	if(ptr_ins == NULL) printf("File not found.\n");
	else{
		for(i=0; i<10000; i++){
			size_line2 = i;
			for(j=0; j<12; j++){
				c = fgetc(ptr_ins);
				if (feof(ptr_ins)){
					c = -1;
					break;
				}
				ins[i][j] = '\0' + c;
				if(ins[i][j] == '\n') break;
			}
			if (c == -1) break;
		}
	}
	fclose(ptr_ins);
	
	
/* talimatlarý struct a yerleþtirme */
	instruc = (struct instruction_s*) malloc(size_line2*sizeof(struct instruction_s));	
	for(i=0; i<size_line2; i++){
		sscanf(ins[i], "%d %d", &x, &y);
		x2 += x;
		y2 = y;
		(instruc+i)->step = x2;
		(instruc+i)->index = y2;
	}



	for(i=1; i<size_line; i++){
		c=0;
		for(j=0; j<200; j++){
			if(book[i][j] == '\n'){
				book2[i][c] = book[i][j];
				break;
			}
			
			else if(book[i][j] == ' '){
				if(j == 0) c--;
				else{
					book2[i][c] = book[i][j];
				} 
			}
			
			else if(book[i][j] < 48 || (book[i][j] < 65 && book[i][j] > 57) || (book[i][j] < 97 && book[i][j] > 90) || book[i][j] > 122){
				c--;
			}
			
			else if(book[i][j] > 64 && book[i][j] < 91)
				book2[i][c] = book[i][j] + 32;
				
			else{
				book2[i][c] = book[i][j];
			}
			c++;
		}
	}
	
	for(i=0; i<10000; i++){
		for(j=0; j<200; j++){
			book[i][j]='\0';
		}
	}
	
	for(i=1; i<size_line; i++){ // i'm in trouble with spaces :)
		c = 0;
		for(j=0; j<200; j++){
			if(book2[i][j] == ' '){
				if(j == 0) c--;
				else if(book2[i][j-1] == ' ') c--;
				else{
					book[i][c] = book2[i][j];
				}
			}
			else{
				book[i][c] = book2[i][j];
			}
			c++;
		}
	}
	
	for(i=0; i<10000; i++){
		free(book2[i]);
	}
	free(book2);
	
	get_sentence(book, instruc, size_line2, sentence);
	printf("%s", sentence);

	for(i=0; i<10000; i++){
		free(book[i]);
	}
	free(book);
	
	for(i=0; i<10000; i++){
		free(ins[i]);
	}
	free(ins);
	
	return 0;
}
