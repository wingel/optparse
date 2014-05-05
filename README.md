# optparse - a library for command line option parsing

This library allows one to create an option parser which can parse
both short (-o) and long options (--option) with and without arguments
(-o foo or --option=foo).  The main goal for this library is to be
simple to use and extend, the goal is not to be very efficient or to
cover every corner case.

I started writing this library a long time ago but had forgotten all
about it until I once again needed to parse some command line options
and stumbled upon the code again.  This project is a cleanup of my old
code so that it hopefully won't look too horrible.

See the file test-optparse.c to see how the library is used.

A note, all strings and pointers that are passed to optparse must stay
in memory until optparse_del has been called.  If you dynamically want
to create some strings, remember to use something like strdup or
asprintf to create copies of the strings and don't free them until
after optparse_del has been called.
