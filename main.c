
// Copyright 2015 Connor Taffe <cpaynetaffe@gmail.com>
// This program is free software licensed under the MIT license.

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "chan.h"

void *test_chan_get(void *v) {
	chan *ch = (chan *) v;

	void *i;
	for (int j = 1; (i = chan_get(ch)); j++) {
		if (j != (int) i) {
			printf("insequentail access, FAIL!\n");
			break;
		}
	}

	return NULL;
}

void *test_chan_put(void *v) {
	chan *ch = (chan *) v;

	int arr[100];
	for (int i = 0; i < 100; i++) {
		arr[i] = i + 1;
		chan_put(ch, (void *) (intptr_t) arr[i]);
	}

	chan_kill(ch);

	return NULL;
}

int main() {

	chan *ch = make_chan();
	if (!ch) { return 1; }

	pthread_t thread[2];

	pthread_create(&thread[0], NULL, &test_chan_put, (void *) ch);
	pthread_create(&thread[1], NULL, &test_chan_get, (void *) ch);

	for (int i = 0; i < 2; i++) { pthread_join(thread[i], NULL); }

	free_chan(ch);

	printf("PASS!\n");
}
