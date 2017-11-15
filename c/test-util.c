/*
 * Copyright (c) 2017 Scott Bennett
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <stdio.h>

#include "util.h"

void
test_shuffle() {
	printf("Testing shuffle()...\n\n");

	int sizes[4] = {
		1, 5, 12, 26
	};

	for (int k = 0; k < 4; k++) {
		int size = sizes[k];
		unsigned char arr[size];

		// initialize array
		unsigned char c = 'a';
		for (int i = 0; i < size; i++) {
			arr[i] = c;
			c++;
		}

		printf("\nsize of buffer (should be %d): %lu\n", size, sizeof(arr));

		printf("\ninitial buffer: ");
		for (int i = 0; i < size; i++) {
			printf("%c", arr[i]);
		}

		shuffle(arr, sizeof(arr));

		printf("\nafter shuffle:  ");
		for (int i = 0; i < size; i++) {
			printf("%c", arr[i]);
		}

		printf("\n");
	}
}

int
main(int argc, char * argv[]) {
	test_shuffle();
	return 0;
}
