#include <sketchacitor.h>
#include <stdio.h>
#include <string.h>

void read_file(char *outbuf, FILE *ftr) {
	if (ftr == NULL || outbuf == NULL) {
		return;
	}
	int c = '\0';
	int i = 0;
	while ((c = fgetc(ftr)) != EOF) {
		outbuf[i] = c;
		i++;
	}
	outbuf[i + 1] = '\0';
	return;
}
