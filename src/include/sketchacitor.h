#ifndef SKETCHACITOR
#define SKETCHACITOR

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

enum wire_type {
	RAW = 0,
	ENAMLED,
	SILVERED,
	INSULATRD
};

enum node_type {
	WIRE = 0,
	POWER_SOURCE
};

struct ivice_node {
	int id;
	enum node_type type;
	union {
		struct { double resistance_per_meter; double length_cm; enum wire_type wire_type; } wire;
		struct { double volts; double amps; bool ac_power; } power_source;
	} type_info;
	int from;
	int to;
};

enum smobo_mode {
	KEY = 0,
	VALUE
};

enum smobo_value {
	NODE = 0,
	ID
};

void read_file(char *outbuf, FILE *ftr);
struct ivice_node *smobo_interpret(char *input);

#endif
