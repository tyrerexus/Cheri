#include <vector>
#include <string>
#include <string.h>
#include "AST/ASTBase.hpp"
#include "ClassCompile.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Builtins.hpp"
#include "Version.hpp"

using std::string;

static void printVersion()
{
	std::cout << Version::name << " v" << Version::version << std::endl;
	std::cout << "© 2017 TYREREXUS ALL RIGHTS RESERVED" << std::endl;
}


/**
 * Just prints the help information. (^.^)
 */
static void help()
{
	std::cout << "Usage: cheri [options] files..." << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "    --help        Dispays this help section." << std::endl;
	std::cout << "    -v            Prints out the version" << std::endl;
	std::cout << "    -o            Specifies where to place output binary." << std::endl;
	std::cout << "    --out-dir     Specifies where to place build files." << std::endl;
}

/** If we are testing then main is defined in @file Test.cpp. */
#ifndef TEST

int main(int argc, char *args[])
{	
	
	std::vector<string> files_list;
	char* output_filename = NULL;

	// FIXME: Add a separate file for this.
	/*** PARSE ARGUMENTS ***/
	for(int arg_index = 1; arg_index < argc; arg_index++) {
		char* arg_to_parse = args[arg_index];
		if (arg_to_parse[0] == '-') {

			/* The output flag. */
			if (strcmp(arg_to_parse, "-o") == 0) {
				arg_index++;
				output_filename = args[arg_index];
			}

			else if (strcmp(arg_to_parse, "-v") == 0) {
				printVersion();

				// FIXME: Do proper clean-up maybe...
				return 0;
			}

			/* Set the output dir. */
			else if (strcmp(arg_to_parse, "--out-dir") == 0) {
				arg_index++;
				ClassCompile::default_out_dir = args[arg_index];
			}

			/* The help option. */
			else if (strcmp(arg_to_parse, "-h") == 0 || strcmp(arg_to_parse, "--help") == 0) {
				help();
				return 0;
			}

			/* Show an error. */
			else {
				printf("Unknown switch: %s", arg_to_parse);
				return 1;
			}
		}

		/* If this wasn't an option than we append to list of files to compile. */
		else {
			files_list.push_back(arg_to_parse);
		}
	}

#	ifdef DEBUG
		printf("[DEBUG] Output: %s\n", output_filename);
#	endif
		
	Builtins::install_types();
	
	/* Open the output file. If none specified use the stdout. */
	//out_file = output_filename != NULL ? fopen(output_filename, "w") : stdout;

	/*** COMPILE STUFF ***/

	/* Parse each file that were given as input. */
	for(string filename : files_list) {
		ClassCompile compiler (filename);
		compiler.compileFile();
		std::cout << "[DONE] Parsing: " << filename << std::endl;
	}
	
	
	/*** CLEAN UP ***/

	return 0;
}
#endif
