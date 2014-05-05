/* A small application used to test the optparse API.

   For example, run this program as:

      ./test-optparse -z

      ./test-optparse --help

      ./test-optparse -1 -u 0xc -f 1.23 -s xyzzy foo bar

   Copyright (c) 2009-2014 Christer Weinigel <christer@weinigel.se>.

   This software is licensed under the MIT License.
*/

#include "optparse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    optparse_t *parser;
    int argi;
    const char *progname;

    /* Create and initialize a bunch of variables which will be
     * updated by the command line option parser */
    signed flag_int = 0;
    unsigned flag_unsigned = 0;
    double flag_double = 0;
    char *flag_string = NULL;

    /* Strip off any path to make error and help messages nicer */
    progname = strrchr(argv[0], '/');
    if (progname)
	progname++;
    else
	progname = argv[0];

    /* Create a new option parser instance, pass it the program name
     * and extra text that should be shown in help messages. */
    parser = optparse_new(progname, "ARGS...");

    /* Add the standard help option (-h, --help) */
    optparse_add_help(parser);

    /* Add three option to set an integer to specific values.  This is
     * meant to be used to add boolean or multiple choice options. */
    optparse_add_set(parser, '1', "1", 1, &flag_int, "set 1");
    optparse_add_set(parser, '2', "2", 2, &flag_int, "set 2");
    optparse_add_set(parser, '3', "3", 3, &flag_int, "set 3");

    /* Add an option which takes an integer argument */
    optparse_add_int(parser, 'i', "int", "NUM", 0, &flag_int,
		     "integer argument");

    /* Add options which take an unsigned integer argument */
    optparse_add_unsigned(parser, 'u', "unsigned", "NUM", 0, &flag_unsigned,
			  "unsigned argument");

    optparse_add_unsigned(parser, 'd', "decimal", "NUM", 10, &flag_unsigned,
			  "unsigned decimal argument");

    optparse_add_unsigned(parser, 'x', "hex", "NUM", 10, &flag_unsigned,
			  "unsigned hexadecimal argument");

    /* Add an option which takes a float argument */
    optparse_add_double(parser, 'f', "float", "NUM", &flag_double,
			"floating point argument");

    /* Add a couple of different variant of string arguments */
    optparse_add_string(parser, 's', "string", NULL, &flag_string,
			"string argument");

    optparse_add_string(parser, 't', NULL, "T", &flag_string,
			"short string argument");

    /* optparse_arg_optional modifies an option so that the argument
     * becomes optional.  So far this is only useful for string
     * arguments, and in case of no argument the char pointer will be
     * set to NULL.  If used with int/unsigned/float options the
     * parser will crash with a NULL pointer exception.
     *
     * Also note that optional arguments only work with the long
     * option form, short options always require an argument. */
    optparse_arg_optional(
	optparse_add_string(parser, 0, "ostring", "OPT", &flag_string,
			    "optional string argument"));

    /* Parse the arguments */
    argi = optparse_parse(parser, argc - 1, argv + 1);
    if (argi < 0)
	exit(1);

    /* Free the option parser */
    optparse_del(parser);

    /* Print the results */
    printf("int:            %d\n", flag_int);
    printf("unsigned:       %u\n", flag_unsigned);
    printf("double:         %f\n", flag_double);
    printf("string:         %s\n", flag_string);

    printf("remaining args:");
    while (++argi < argc)
	printf(" %s", argv[argi]);
    printf("\n");

    exit(0);
}
