# passgen

Simple, command line password generator utility. Prints random passwords up to
50 characters long (although, that limit is arbitrary and easily changed).

### usage

```
$ passgen [-l passlength] [-n passnum]
```
The default minimum password length that `passgen` prints out is 13 characters.
Use `-l` to specify a different length, up to 50.

`passgen` only generates 1 password by default. Use `-n` to generate 'n' number
of passwords, one per line.

### build

```
$ make && make install
```

`passgen` currently only builds on [OpenBSD](https://www.openbsd.org/), because
what other platform would you trust to generate good random numbers? Portability
would not be too hard to achieve, though, and may happen in the future.

### why?

Just for fun. And also the cloud is scary. Who on earth thought it was a good
idea to use web pages to generate passwords? It's best to use a native utility
that does not talk to the internet at all.
