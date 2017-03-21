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
#include <sys/types.h>

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

/*
 * Randomly switch the case of the given letter, 'c'. If c is not a
 * letter (as determined by isalpha(3)), then c will be returned
 * unmodified.
 */
unsigned char
randomcase(unsigned char c) {
	if (!isalpha(c)) {
		return c;
	}

	const u_int cutpoint = (UINT_MAX / 2);
	u_int rand = arc4random();

	if (rand < cutpoint) {
		// switch case
		if (isupper(c)) {
			return tolower(c);
		}
		if (islower(c)) {
			return toupper(c);
		}
	}

	return c;
}

/*
 * Randomly switch the case of the letters in 'arr'. Any non-letter
 * characters (as determined by isalpha(3)) are left unmodified.
 */
void
randomcase_buf(unsigned char * arr, size_t length) {
	unsigned char bits[length / 8], *b;
	u_int i = 0;

	arc4random_buf(bits, (length + 7) / 8);
	b = bits;
	while (*arr) {
		if (isalpha(*arr)) {
			*arr = (*b & (1 << i)) ? toupper(*arr) : tolower(*arr);
		}
		arr++;
		i++;
		if (i == 8) {
			b++;
			i = 0;
		}
	}
}

/*
 * Shuffle the contents of the array 'arr' by randomly switching the
 * positions of the characters.
 */
void
shuffle(unsigned char * arr, size_t length) {
	if (length < 2) {
		return;
	}

	for (u_int i = 0; i < (length - 1); i++) {
		u_int j = i + arc4random_uniform(length - i);
		unsigned char t = arr[j];
		arr[j] = arr[i];
		arr[i] = t;
	}
}
