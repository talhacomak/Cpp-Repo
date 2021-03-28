#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct instruction_s {
	int step; //line
	int index; //word
};

char* get_word(char* s, int n) {
	char* word = (char*)malloc(sizeof(char) * 30);
	int i, j, word_num = 1;

	for (i = 0; i < 30; i++) {
		word[i] = '\0';
		if (word_num == n) break;
		if (*(s + i) == ' ') {
			word_num++;
		}
	}

	for (; i < 200; i++) {
		if (word_num == n) break;
		if (*(s + i) == 32) {
			word_num++;
		}
	}
	i--;
	for (j = 0; j < 50; j++) {
		i++;
		if (s[i] == 32 || s[i] == '\n') break;
		else word[j] = s[i];
	}
	return word;
}

void get_sentence(char** lines, struct instruction_s* instruction, int n_instructions, char* sentence) {
	int i, x, y;
	for (i = 0; i < n_instructions; i++) {
		x = (instruction + i)->step;
		y = (instruction + i)->index;
		strcat(sentence, get_word(lines[x], y));
		if(i != n_instructions-1) strcat(sentence, " ");
	}
}

int main(int argc, char** argv) {
	int i, j, size_line, size_line2, c, x, y, x2 = 0;
	struct instruction_s* instruc;

	char sentence[10000];
	char** book = (char**)malloc(10000 * sizeof(char*));
	char** book2 = (char**)malloc(10000 * sizeof(char*));
	char** ins = (char**)malloc(10000 * sizeof(char*));
	for (i = 0; i < 10000; i++) {
		sentence[i] = 0;
		ins[i] = (char*)malloc(13 * sizeof(char));
		for (j = 0; j < 12; j++) {
			ins[i][j] = '\0';
		}

		book[i] = (char*)malloc(200 * sizeof(char));
		book2[i] = (char*)malloc(200 * sizeof(char));
		for (j = 0; j < 200; j++) {
			book[i][j] = '\0';
			book2[i][j] = '\0';
		}
	}
	
	FILE* ptr = fopen(argv[1], "r");
	if (ptr == NULL) {
		printf("%s File not found.\n", argv[1]);
		return EXIT_FAILURE;
	}
	else {
		int first_char = 0;
		for (i = 1; i < 10000; i++) {
			size_line = i;
			first_char = 0;
			for (j = 0; j < 200; j++) {
				c = fgetc(ptr);
				if (feof(ptr)) {
					c = -1;
					break;
				}
				if (c == '\n') break;
				if (c >= 97 && c <= 122) {
					first_char = 1;
					book[i][j] = '\0' + c;
				}
				else if (c >= 65 && c <= 90) {
					c += 32;
					book[i][j] = '\0' + c;
					first_char = 1;
				}
				else if (c==32){
					if (first_char) book[i][j] = '\0' + c;
				}
			}
			if (c == -1) break;
		}
	}
	fclose(ptr);

	FILE* ptr_ins = fopen(argv[2], "r");
	if (ptr_ins == NULL) {
		printf("Instructions file not found.\n");
		return 1;
	}
	else {
		size_line2 = 0;
		for (i = 0; i < 10000; i++) {
			if (feof(ptr_ins)) break;
			fgets(ins[i], 13, ptr_ins);
			if (ins[i][0] == '\n' || ins[i][0] == '\0') break;
			size_line2++;
		}
	}
	fclose(ptr_ins);


	/* instructions into structs */
	instruc = (struct instruction_s*) malloc(size_line2 * sizeof(struct instruction_s));
	for (i = 0; i < size_line2; i++) {
		sscanf(ins[i], "%d %d", &x, &y);
		x2 += x;
		(instruc + i)->step = x2;
		(instruc + i)->index = y;
	}
	
	get_sentence(book, instruc, size_line2, sentence);
	printf("%s", sentence);

	for (i = 0; i < 10000; i++) {
		free(book[i]);
		free(ins[i]);
	}
	free(book);
	free(ins);

	return 0;
}
