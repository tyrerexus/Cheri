#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "../ast.h"
#include "../symtbl.h"

/**
 * Compiles an AST node and puts result on to the out file stream.
 */
void compile_ast_to_cpp(ASTNode *ast, FILE* out, bool in_expr, bool do_next, int start_indent);
