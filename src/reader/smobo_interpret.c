#include <sketchacitor.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

struct ivice_node *smobo_interpret(char *input) {
	if (input == NULL) {
		return NULL;
	}
	bool comment = false;
	enum smobo_mode mode = KEY;
	enum smobo_value valuemode = NODE;
	char *stringuse = malloc(1);
	stringuse[0] = '\0';
	struct ivice_node *output = calloc(16, sizeof(struct ivice_node));
	int x = 0;

	#ifdef DEBUG
		printf("Note: debugging information enabled\n");
	#endif

	for (int i = 0; input[i] != '\0'; i++) {
		bool skip = false;
		switch (input[i]) {
			case '#': {
				if (input[i - 1] != '\\' && input[i - 2] != '\\') {
					comment = true;
				}
				break;
			}
			case '\n': {
				comment = false;
				if (valuemode == NODE) {
					x = atoi(stringuse);
				} else if (valuemode == ID) {
					output[x].id = atoi(stringuse);
				}
				free(stringuse);
				stringuse = malloc(1);
				stringuse[0] = '\0';
				mode = KEY;
				skip = true;
				break;
			}
			case ':': {
				if (comment) {
					break;
				}
				mode = VALUE;
				if (strcmp(stringuse, "node") == 0) {
					valuemode = NODE;
				} else if (strcmp(stringuse, "id") == 0) {
					valuemode = ID;
				} else {
					printf("Interpreting error! failed on character %d:\n%s\n", i, input);
					free(output);
					return NULL;
				}
				free(stringuse);
				stringuse = malloc(1);
				stringuse[0] = '\0';
				skip = true;
				break;
			}
		}
		if (skip || comment) {
			continue;
		}
		int sz = strlen(stringuse);
		char *t = realloc(stringuse, sz + 2);
		if (t == NULL) {
			printf("Reallocation error! cannot continue interpreting.");
			free(stringuse);
			free(output);
			return NULL;
		}
		t[sz] = input[i];
		t[sz + 1] = '\0';
		stringuse = t;
		#ifdef DEBUG
		printf("Helper string %d: %s\n", i, stringuse);
		#endif
	}
	free(stringuse);
	return output;
}
