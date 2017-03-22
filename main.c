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
#include <string.h>
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
	u_int passnum = 1;
	while ((c = getopt(argc, argv, "l:n:")) != -1) {
		switch (c) {
			case 'l':
				length = strtonum(optarg, MIN_LENGTH, MAX_LENGTH, &errstr);
				if (errstr) {
					errx(1, "length is %s: %s", errstr, optarg);
				}
				break;
			case 'n':
				passnum = strtonum(optarg, 1, UINT_MAX, &errstr);
				if (errstr) {
					errx(1, "passnum is %s: %s", errstr, optarg);
				}
				break;
			default:
				usage();
				break;
		}
	}
	argc -= optind;
	argv += optind;

	unsigned char p[length];

	for (u_int i = 0; i < passnum; i++) {
		generate(p, length);
		printpass(p, length);
		explicit_bzero(p, length);
	}

	return 0;
}

void
usage(void) {
	fprintf(stderr, "usage: passgen [-l passlength] [-n passnum]\n");
	exit(1);
}
