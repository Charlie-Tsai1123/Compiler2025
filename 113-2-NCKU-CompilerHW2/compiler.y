/* Please feel free to modify any content */

/* Definition section */
%{
    #include "compiler_common.h"
    // #define YYDEBUG 1
    // int yydebug = 1;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    int yylex_destroy ();
    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno, s);
    }

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;
    

    /* Define symbol table node */
    typedef struct symbol {
        int index;
        char *name;
        int mut;
        char *type;
        int addr;
        int lineno;
        char *func_sig;
        struct symbol *next;
        struct symbol *prev;
    } symbol_t;

    typedef struct symbol_table {
        int parent;
        int scope_level;
        symbol_t *element;
        struct symbol_table *next;
        struct symbol_table *prev;
    } symbol_table_t;

    symbol_table_t *dummy_table;

    symbol_table_t *current_table;

    /* Record next address */
    int next_addr = -1;

    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void insert_symbol(char *name, int mut, char *type, char *func_sig);
    symbol_t* lookup_symbol(char *name);
    static void dump_symbol();
    static void parent_table();

    /* Global variables */
    bool HAS_ERROR = false;

%}

/* %error-verbose */
/* %define parse.error verbose */

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 *  - you can add new fields if needed.
 */
%union {
    int i_val;
    float f_val;
    char *s_val;
    /* ... */
}

/* Token without return */
%token LET MUT NEWLINE
%token INT FLOAT BOOL STR
%token TRUE FALSE
%token GEQ LEQ EQL NEQ LOR LAND
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN REM_ASSIGN
%token IF ELSE FOR WHILE LOOP
%token PRINT PRINTLN
%token FUNC RETURN BREAK
%token ARROW AS IN DOTDOT RSHIFT LSHIFT

/* Token with return, which need to sepcify type */
%token <i_val> INT_LIT
%token <f_val> FLOAT_LIT
%token <s_val> STRING_LIT
%token <s_val> ID

/* Nonterminal with return, which need to sepcify type */
%type <s_val> Type
%type <s_val> Expr
%type <s_val> Operator

/* Yacc will start at this nonterminal */
%start Program

/* Grammar section */
%%
Program
    : { create_symbol(); } GlobalStatementList { dump_symbol(); }
;

GlobalStatementList 
    : GlobalStatementList GlobalStatement
    | GlobalStatement
;

GlobalStatement
    : FunctionDeclStmt
    | NEWLINE
;

FunctionDeclStmt
    : FUNC ID '(' Type ')' { 
        printf("func: %s\n", $<s_val>2); 
        char *sig = (char *)malloc(strlen($<s_val>4) + 10);
        sprintf(sig, "(%s)V", $<s_val>4);
        insert_symbol($<s_val>2, -1, "func", sig);
    } '{' { create_symbol(); } StmtList '}' { parent_table(); }
;

StmtList
    : StmtList Stmt
    | /* empty */
;

Stmt
    : PrintStmt
    | DeclarationStmt
;

Expr
    : ID {
        symbol_t *tmp = lookup_symbol($<s_val>1);
        printf("IDENT (name=%s, address=%d)\n", $<s_val>1, tmp->addr);
        $$ = tmp->type; 
    }
    | Expr Operator Expr { 
        printf("%s\n", $<s_val>2); 
        $$ = (strcmp($<s_val>1, "f32") == 0 || strcmp($<s_val>3, "f32") == 0) ? "f32" : "i32";
    }
;


PrintStmt
    : PRINTLN '(' '"' STRING_LIT '"' ')' ';' {
        printf("STRING_LIT \"%s\"\n", $<s_val>4);
        printf("PRINTLN str\n");
    }
    | PRINTLN '(' Expr ')' ';' {
        printf("PRINTLN %s\n", $<s_val>3);
    }
;

DeclarationStmt
    : LET ID ':' INT '=' INT_LIT ';' { printf("INT_LIT %d\n", $<i_val>6); insert_symbol($<s_val>2, 0, "i32", "-"); }
    | LET ID ':' FLOAT '=' FLOAT_LIT ';' { printf("FLOAT_LIT %f\n", $<f_val>6); insert_symbol($<s_val>2, 0, "f32", "-"); }
    | LET ID ':' STR '=' '"' STRING_LIT '"' ';' { printf("STRING_LIT %s\n", $<s_val>7); insert_symbol($<s_val>2, 0, "str", "-"); }
    | LET MUT ID ':' INT '=' INT_LIT ';' { printf("INT_LIT %d\n", $<i_val>7); insert_symbol($<s_val>3, 1, "i32", "-"); }
    | LET MUT ID ':' FLOAT '=' FLOAT_LIT ';' { printf("FLOAT_LIT %f\n", $<f_val>7); insert_symbol($<s_val>3, 1, "f32", "-"); }
    | LET MUT ID ':' STR '=' '"' STRING_LIT '"' ';' { printf("STRING_LIT %s\n", $<s_val>8); insert_symbol($<s_val>3, 1, "str", "-"); }
;

Type
    : INT { $$ = "i32"; }
    | FLOAT { $$ = "f32"; }
    | BOOL { $$ = "bool"; }
    | STR { $$ = "str"; }
    | /* empty */ { $$ = "V"; }
;

Operator
    : '+' { $$ = "ADD"; }
    | '-' { $$ = "SUB"; }
    | '*' { $$ = "MUL"; }
    | '/' { $$ = "DIV"; }
    | '%' { $$ = "REM"; }
;

%%

/* C code section */
int main(int argc, char *argv[])
{
    /* Initialize symbol table */
    dummy_table = (symbol_table_t*) malloc(sizeof(symbol_table_t));
    dummy_table->parent = -1;
    dummy_table->scope_level = -1;
    dummy_table->element = NULL;
    dummy_table->next = dummy_table;
    dummy_table->prev = dummy_table;
    current_table = dummy_table;

    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    yylineno = 0;
    yyparse();

	printf("Total lines: %d\n", yylineno);
    fclose(yyin);
    return 0;
}

static void parent_table() {
    for (int i = 0; i <= current_table->parent; i++) {
        current_table = dummy_table->prev;
    }
}

static void create_symbol() {
    /* Create dummy symbol */
    symbol_t *dummy_symbol = (symbol_t*) malloc(sizeof(symbol_t));
    dummy_symbol->index = -1;
    dummy_symbol->name = NULL;
    dummy_symbol->mut = -1;
    dummy_symbol->type = NULL;
    dummy_symbol->addr = -1;
    dummy_symbol->lineno = -1;
    dummy_symbol->func_sig = NULL;
    dummy_symbol->next = dummy_symbol;
    dummy_symbol->prev = dummy_symbol;

    /* Create symbol table */
    symbol_table_t *new_symbol_table = (symbol_table_t*) malloc(sizeof(symbol_table_t));
    new_symbol_table->parent = current_table->scope_level;
    new_symbol_table->scope_level = dummy_table->next->scope_level + 1;
    new_symbol_table->element = dummy_symbol;
    new_symbol_table->prev = dummy_table;
    new_symbol_table->next = dummy_table->next;
    dummy_table->next->prev = new_symbol_table;
    dummy_table->next = new_symbol_table;
    current_table = new_symbol_table;

    printf("> Create symbol table (scope level %d)\n", current_table->scope_level);
}

static void insert_symbol(char *name, int mut, char *type, char *func_sig) {
    printf("> Insert `%s` (addr: %d) to scope level %d\n", name, next_addr, current_table->scope_level);
    symbol_t *new_symbol = (symbol_t*) malloc(sizeof(symbol_t));
    new_symbol->index = current_table->element->prev->index + 1;
    new_symbol->name = name;
    new_symbol->mut = mut;
    new_symbol->type = type;
    new_symbol->addr = next_addr++;
    new_symbol->lineno = yylineno + 1;
    new_symbol->func_sig = func_sig;
    new_symbol->next = current_table->element;
    new_symbol->prev = current_table->element->prev;

    current_table->element->prev->next = new_symbol;
    current_table->element->prev = new_symbol;

}

symbol_t* lookup_symbol(char *name) {
    symbol_t *tmp = current_table->element->next;
    while (tmp != current_table->element) {
        if (strcmp(tmp->name, name) == 0) {
            return tmp;
        }
        tmp = tmp->next;
    }

    return NULL;
}

static void dump_symbol() {
    /* printf("\n> Dump symbol table (scope level: %d)\n", 0);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig"); */
    /* printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
            0, "name", 0, "type", 0, 0, "func_sig"); */


    current_table = dummy_table->next;
    while (current_table != dummy_table) {
        printf("\n> Dump symbol table (scope level: %d)\n", current_table->scope_level);
        printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
            "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig");
        symbol_t *current_symbol = current_table->element->next;
        while (current_symbol != current_table->element) {
            printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
                current_symbol->index, current_symbol->name, current_symbol->mut, current_symbol->type, current_symbol->addr, current_symbol->lineno, current_symbol->func_sig);
            current_symbol = current_symbol->next;
        }
        current_table = current_table->next;
    }
}
