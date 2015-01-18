
// Copyright 2015 Connor Taffe <cpaynetaffe@gmail.com>
// This program is free software licensed under the MIT license.

#ifndef CHAN_LIST_H_
#define CHAN_LIST_H_

// list struct
typedef struct list {
	void *data;
	struct list *next;
} list;

// make & free
list *make_list();
void free_list(list *ls);

// list operations
int list_rm(list *ls); // remove next node
int list_ins(list *ls, list *next); // inserts as next node

#endif // CHAN_LIST_H_
