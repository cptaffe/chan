
// Copyright 2015 Connor Taffe <cpaynetaffe@gmail.com>
// This program is free software licensed under the MIT license.

#ifndef CHAN_H_
#define CHAN_H_

#include <pthread.h>

#include "list.h"

// list struct
typedef struct {
	list *ls;
	list *end;

	pthread_cond_t cond;
	pthread_mutex_t mut;
	int alive;
} chan;

// make & free
chan *make_chan();
void free_chan(chan *ch);

// list operations
void *chan_get(chan *ch); // remove next node
int chan_put(chan *ch, void *data); // inserts as next node

// mutex operations
int chan_empty(chan *ch);
int chan_alive(chan *ch);
void chan_kill(chan *ch);

#endif // CHAN_H_
