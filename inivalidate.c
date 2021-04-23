#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <confini.h>

#define INIVALIDATE_VERSION "1.0.0"

static void usage(void)
{
	fprintf(stderr,
			"inivalidate %s\n"
			"Uses libconfini to validate that input.ini is a valid INI\n"
			"\n"
			"Usage: inivalidate <input.ini>\n"
			"  -h, --help              Output this help and exit\n"
			"  -V, --version           Output version and exit\n"
			"\n", INIVALIDATE_VERSION);
	exit(EXIT_FAILURE);
}

char * inputFilePath=0;

static void parse_options(int argc, char **argv)
{
	int i;

	for(i=1;i<argc;i++)
	{
		//int lastarg = i==argc-1;

		if(!strcmp(argv[i],"-h") || !strcmp(argv[i], "--help"))
		{
			usage();
		}
		else if(!strcmp(argv[i],"-V") || !strcmp(argv[i], "--version"))
		{
			printf("inivalidate %s\n", INIVALIDATE_VERSION);
			exit(EXIT_SUCCESS);
		}
		else
		{
			break;
		}
	}

	argc -= i;
	argv += i;

	if(argc<1)
		usage();

	inputFilePath = argv[0];
}

uint32_t sectionCount = 0;

static int callback_handler(IniDispatch * dispatch, __attribute__((unused)) void * v_null)
{
	if(dispatch->type==INI_SECTION)
		sectionCount++;

	/*if(dispatch->type!=INI_COMMENT && dispatch->type!=INI_INLINE_COMMENT)
	{
		printf("DATA: %s\nVALUE: %s\nNODE TYPE: %s\nPARENT: %s\n\n",
			dispatch->data,
			dispatch->value == INI_GLOBAL_IMPLICIT_VALUE ? "true (implicit boolean)" : dispatch->value,
			dispatch->type == INI_SECTION ? "section" : dispatch->type == INI_KEY ? "key" : dispatch->type == INI_DISABLED_SECTION ? "disabled section" : dispatch->type == INI_DISABLED_KEY ? "disabled key" : "unknown",
			dispatch->at_len ? dispatch->append_to : "{top-level}");
	}*/

	return 0;
}

int main(int argc, char ** argv)
{
	parse_options(argc, argv);

	if(load_ini_path(inputFilePath, INI_DEFAULT_FORMAT, 0, callback_handler, 0) || sectionCount==0)
	{
    	printf("false\n");
    	return EXIT_FAILURE;
	}
	
	printf("true\n");
	return EXIT_SUCCESS;
}
