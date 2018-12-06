%{
#include "scanner.h"
%}

%%
"print"							return PRINT;
,								return COMMA;
=								return EQUAL;
"if"							return IF_STATEMENT;
"else"							return ELSE_STATEMENT;
"def"							return DEFINITION;
[\+\-\*\/]						return MATH;
">"								return COMPARISON;
"<"								return COMPARISON;
">="							return COMPARISON;
"<="							return COMPARISON;
"=="							return COMPARISON;
"!="							return COMPARISON;
:								return COLON;
[1-9][0-9]*						return INTEGER;
[a-zA-Z][_a-zA-Z0-9\!]*			return IDENTIFIER;
[\0\n]							return EOL;
#								return COMMENT;
.								return ALL;
"\t*[a-zA-Z0-9]*"				return NESTED;
\"(.*?)\"						return QUOTE;
%%

int yywrap(void) {
	return 1;
}
