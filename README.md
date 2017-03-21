# passgen

Simple, command line password generator utility. Prints random passwords up to 50
characters long (although, that limit is arbitrary and easily changed).

### usage

```
$ passgen [-l passlength]
```
The default minimum password length `passgen` prints out is 13 characters. Use `-l`
to specify a different length, up to 50.

### why?

Because I like making my own tools. And the cloud is scary. Why on earth would you use
a webpage to generate random passwords? It's best to use a native utility that does not
talk to the internet at all.

### build

```
$ make
```

Currently only builds on [OpenBSD](https://www.openbsd.org/), because what other platform
would you trust to generate good random numbers?
