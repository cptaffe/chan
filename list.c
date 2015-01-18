
// Copyright 2015 Connor Taffe <cpaynetaffe@gmail.com>
// This program is free software licensed under the MIT license.

#include <stdlib.h>

#include "list.h"

list *make_list() {
	list *ls = calloc(sizeof(list), 1); // initially zeroed
	return ls;
}

void free_list(list *ls) {
	free(ls);
}

int list_rm(list *ls) {
	if (ls == NULL) {
		return 1;
	} else if (ls->next == NULL) {
		return 2;
	} else {
		list *nx = ls->next;
		ls->next = ls->next->next;
		free_list(nx);
		return 0;
	}
}

int list_ins(list *ls, list *next) {
	if (ls == NULL) {
		return 1;
	} else {
		list *nx = ls->next;
		ls->next = next;
		ls->next->next = nx;
		return 0;
	}
}
