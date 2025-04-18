/* Definition section */
%{
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>

   #define YY_NO_UNPUT
   #define YY_NO_INPUT
   #define print_token(token) \
       printf("%-8s \t %s\n", strcmp(token, "NEWLINE")? yytext: "", token)

   int line_num = 0;
   int comment_num = 0;
   int last_comment_line = -1;
   int isCommentLine = 0;

%}


/* Define regular expression label */
letter [a-zA-Z_]
digit [0-9]
func fn\ {letter}
ident {letter}({letter}|{digit})*
%x STRING
%x MULTICOMMENT

/* Rules section */
%%
"//".*      { print_token("COMMENT"); comment_num++; }
"/*"        { BEGIN(MULTICOMMENT); printf("%s", yytext); isCommentLine = 1; }
<MULTICOMMENT>.    { printf("%s", yytext); isCommentLine = 1; }
<MULTICOMMENT>\n    { printf("%s", yytext); comment_num++; line_num++; }
<MULTICOMMENT>"*/"  { print_token("MUTI_LINE_COMMENT"); BEGIN(INITIAL); isCommentLine = 1; }
"print"     { print_token("PRINT"); }
"println"   { print_token("PRINTLN"); }
"if"        { print_token("IF"); }
"else"      { print_token("ELSE"); }
"for"       { print_token("FOR"); }
"i32"      { print_token("INT"); }
"f32"      { print_token("FLOAT"); }
".."        { print_token("DOTDOT"); }
"bool"     { print_token("BOOL"); }
"true"      { print_token("TRUE"); }
"false"     { print_token("FALSE"); }
"let"      { print_token("LET"); }
"mut"       { print_token("MUT"); }
"return"    { print_token("RETURN"); }
"break"     { print_token("BREAK"); }
"as"        { print_token("AS"); }
"in"        { print_token("IN"); }
"while"     { print_token("WHILE"); }
"loop"      { print_token("LOOP"); }
{digit}+    { print_token("INT_LIT"); }
{digit}+\.{digit}+  { print_token("FLOAT_LIT"); }
"\""        { print_token("QUOTA"); BEGIN(STRING); }
<STRING>[^\"\n]*        { yymore(); }
<STRING>\"  { if(strlen(yytext) != 1) {yytext[strlen(yytext) - 1] = '\0'; print_token("STRING_LIT");} yytext = "\""; print_token("QUOTA"); BEGIN(INITIAL);}
{func}      { yyless(3); print_token("FUNC"); }
{ident}     { print_token("IDENT"); }
"->"        { print_token("ARROW"); }
"+"         { print_token("ADD"); }
"-"         { print_token("SUB"); }
"*"         { print_token("MUL"); }
"/"         { print_token("QUO"); }
"%"         { print_token("REM"); }
">"         { print_token("GTR"); }
"<"         { print_token("LSS"); }
">="        { print_token("GEQ"); }
"<="        { print_token("LEQ"); }
"=="        { print_token("EQL"); }
"!="        { print_token("NEQ"); }
"="         { print_token("ASSIGN"); }
"+="        { print_token("ADD_ASSIGN"); }
"-="        { print_token("SUB_ASSIGN"); }
"*="        { print_token("MUL_ASSIGN"); }
"/="        { print_token("QUO_ASSIGN"); }
"%="        { print_token("REM_ASSIGN"); }
"&"         { print_token("BAND"); }
"|"         { print_token("BOR"); }
"~"         { print_token("BNOT"); }
">>"        { print_token("RSHIFT"); }
"<<"        { print_token("LSHIFT"); }
"&&"        { print_token("LAND"); }
"||"        { print_token("LOR"); }
"!"         { print_token("NOT"); }
"("         { print_token("LPAREN"); }
")"         { print_token("RPAREN"); }
"["         { print_token("LBRACK"); }
"]"         { print_token("RBRACK"); }
"{"         { print_token("LBRACE"); }
"}"         { print_token("RBRACE"); }
";"         { print_token("SEMICOLON"); }
","         { print_token("COMMA"); }
":"         { print_token("COLON"); }


"\n"        { line_num++, print_token("NEWLINE"); if (isCommentLine) { isCommentLine = 0; comment_num++; }}
<<EOF>>     { line_num++; yyterminate(); }
[ \t]+      {;}
.           {;}
%%

/*  C Code section */
int yywrap(void)
{
   return 1;
}

int main(int argc, char *argv[])
{
   if (argc == 2) {
       yyin = fopen(argv[1], "r");
   } else {
       yyin = stdin;
   }
   yylex();
   printf("\nFinish scanning,\n");
   printf("total line: %d\n", line_num);
   printf("comment line: %d\n", comment_num);
   fclose(yyin);
   return 0;
}
