#include <sketchacitor.h>

int main(void) {
	char *input = "node:0\n#Hello!\nid:3\n";
	printf("Input:\n%s\n", input);
	struct ivice_node *output = smobo_interpret(input);
	printf("output:\nnode 0:\nid:%d\n", output[0].id);
	return 0;
}
