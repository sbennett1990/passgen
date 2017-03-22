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
#include <err.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "passgen.h"

#define MIN_LENGTH 13
#define MAX_LENGTH 50

static void usage(void);

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

	return 0;
}

void
usage(void) {
	fprintf(stderr, "usage: passgen [-l passlength]\n");
	exit(1);
}
