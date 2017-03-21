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
#include <err.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

#define MIN_LENGTH 13
#define MAX_LENGTH 50

static const char alpha[] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
	'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
	's', 't', 'u', 'v', 'w', 'x', 'y', 'z',		// alpha  :  0 - 25
	'0', '1', '2', '3', '4', '5', '6', '7', '8',
	'9',						// num    : 26 - 35
	'@', '#', '$', '%', '^', '&', '*', '[', ']',
	'~', '<', '>', '?', ':', ';', '"', '{', '}',
	'+', '-', '='					// special: 36 - sizeof(alpha)
};

static void generate(unsigned char *, size_t);
static void printpass(unsigned char *, size_t);

static void
usage(void) {
	fprintf(stderr, "usage: passgen [-l passlength]\n");
	exit(1);
}

int
main(int argc, char * argv[]) {
	int c;
	const char * errstr;

	if (pledge("stdio", NULL) == -1) {
		err(1, "pledge");
	}

	size_t length = MIN_LENGTH;
	while ((c = getopt(argc, argv, "l:")) != -1) {
		switch (c) {
			case 'l':
				length = strtonum(optarg, 0, INT_MAX, &errstr);
				if (errstr)
					errx(1, "length is %s: %s", errstr, optarg);
				break;
			default:
				usage();
				break;
		}
	}
	argc -= optind;
	argv += optind;

	if (length < MIN_LENGTH) {
		err(1, "can't generate a password less than %d", MIN_LENGTH);
	}
	if (length > MAX_LENGTH) {
		err(1, "max password length is %d", MAX_LENGTH);
	}

	unsigned char p[length];
	generate(p, length);
	printpass(p, length);
	puts("");

	return 0;
}

void
generate(unsigned char * p, size_t length) {
	size_t upperbound = sizeof(alpha);

	for (size_t i = 0; i < length; i++) {
		u_int j = (i % 3 == 0)
				? arc4random_uniform(upperbound)
				: arc4random_uniform(35);
		p[i] = alpha[j];
	}

	/* randomize letter capitolization */
	randomcase_buf(p, length);

	/* randomly shuffle the characters around at least once*/
	for (int i = 0; i < arc4random_uniform(3) + 1; i++) {
		shuffle(p, length);
	}
}

void
printpass(unsigned char * p, size_t length) {
	for (size_t i = 0; i < length; i++) {
		putchar(p[i]);
	}
}
