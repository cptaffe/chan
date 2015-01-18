
// Copyright 2015 Connor Taffe <cpaynetaffe@gmail.com>
// This program is free software licensed under the MIT license.

#include <stdlib.h>

#include "chan.h"

chan *make_chan() {
	chan *ch = calloc(sizeof(chan), 1); // initially zeroed

	// condition & mutex init
	if (pthread_cond_init(&ch->cond, NULL)) { return NULL; }
	if (pthread_mutex_init(&ch->mut, NULL)) { return NULL; }

	return ch;
}

void free_chan(chan *ch) {
	pthread_cond_destroy(&ch->cond);
	pthread_mutex_destroy(&ch->mut);
	free(ch);
}

int chan_empty(chan *ch) {
	return ch->ls == NULL;
}

int chan_alive(chan *ch) {
	return !ch->alive;
}

void chan_kill(chan *ch) {
	int mls = pthread_mutex_lock(&ch->mut);
	if (mls) {
		return;
	}

	ch->alive = 1;
	pthread_cond_broadcast(&ch->cond);
	pthread_mutex_unlock(&ch->mut);
}

void *chan_get(chan *ch) {

	// get mutex
	int mls = pthread_mutex_lock(&ch->mut);
	if (mls) { return NULL; }

	while (chan_empty(ch) && chan_alive(ch)) {
		int cws = pthread_cond_wait(&ch->cond, &ch->mut);
		if (cws) { return NULL; }
	}
	if (!chan_alive(ch) && chan_empty(ch)) { return NULL; } // die on dead

	void *ret = NULL;
	if (ch->ls != NULL) {
		list *ls = ch->ls;
		ch->ls = ch->ls->next;
		if (!ch->ls) {
			ch->end = NULL;
		}
		void *data = ls->data;
		free_list(ls);
		ret = data;
	}

	pthread_mutex_unlock(&ch->mut);

	return ret;
}

int chan_put(chan *ch, void *data) {

	int mls = pthread_mutex_lock(&ch->mut);
	if (mls) { return 1; }

	int ret = 0;
	if (ch->end == NULL) {
		ch->end = make_list();
		if (!ch->end) {
			ret = 1;
		} else {
			ch->end->data = data;
			ch->ls = ch->end;
		}
	} else {
		ch->end->next = make_list();
		if (!ch->end->next) {
			ret = 1;
		} else {
			ch->end->next->data = data;
			ch->end = ch->end->next;
		}
	}

	pthread_cond_signal(&ch->cond);
	pthread_mutex_unlock(&ch->mut);

	return ret;
}
