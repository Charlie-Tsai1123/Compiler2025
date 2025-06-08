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
        printf("error:%d: %s\n", yylineno + 1, s);
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
        int scope_level;
        symbol_t *element;
        struct symbol_table *next;
    } symbol_table_t;

    /* Current Symbol Table alway dummy_table->next */
    symbol_table_t *dummy_table;


    /* Record next address */
    int next_addr = -1;

    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void insert_symbol(char *name, int mut, char *type, char *func_sig);
    symbol_t* lookup_symbol(char *name);
    static void dump_symbol();

    /* Global variables */
    bool HAS_ERROR = false;

%}

/* %error-verbose */
/* %define parse.error verbose */

/* solve conflict state */
/* %debug */
/* %verbose */

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
%type <s_val> PrintType
%type <i_val> MutType
%type <s_val> AssignmentOperatorType
%type <s_val> ArrayElements
%type <s_val> FunctionArguments
%type <s_val> ArrowType

/* Define operator precedence and associativity */
%nonassoc IFX
%nonassoc ELSE
%left LOR
%left LAND
%right '!'
%nonassoc GEQ LEQ EQL NEQ '>' '<'
%left LSHIFT RSHIFT
%left '+' '-'
%left '*' '/' '%'
%right UMINUS
%right AS

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
    : FUNC ID '(' FunctionArguments ')' ArrowType { 
        printf("func: %s\n", $<s_val>2); 
        char *sig = (char *)malloc(strlen($<s_val>4) + 10);
        sprintf(sig, "(%s)%s", $<s_val>4, $<s_val>6);
        insert_symbol($<s_val>2, -1, "func", sig);
    } Block
;

StmtList
    : StmtList Stmt
    | /* empty */
;

Stmt
    : PrintStmt
    | DeclarationStmt
    | AssignmentStmt
    | Block
    | IfStmt
    | WhileStmt
;

Block
    : '{' { create_symbol(); } StmtList '}' { dump_symbol(); }
;

Expr
    : ID {
        symbol_t *tmp = lookup_symbol($<s_val>1);
        if (tmp == NULL) {
            char msg[100];
            sprintf(msg, "undefined: %s", $<s_val>1);
            yyerror(msg);
            HAS_ERROR = TRUE;
            $$ = "undefined";
        } else {
            printf("IDENT (name=%s, address=%d)\n", $<s_val>1, tmp->addr);
            $$ = tmp->type; 
        }
        
    }
    | INT_LIT {
        printf("INT_LIT %d\n", $<i_val>1);
        $$ = "i32";
    }
    | FLOAT_LIT {
        printf("FLOAT_LIT %f\n", $<f_val>1);
        $$ = "f32";
    }
    | '"' STRING_LIT '"' {
        printf("STRING_LIT \"%s\"\n", $<s_val>2);
        $$ = "str";
    }
    | '"' '"' {
        printf("STRING_LIT \"\"\n");
        $$ = "str";
    }
    | TRUE {
        printf("bool TRUE\n");
        $$ = "bool";
    }
    | FALSE {
        printf("bool FALSE\n");
        $$ = "bool";
    }
    | '[' ArrayElements ']' {
        $$ = $<s_val>2;
    }
    | ID '[' INT_LIT ']' {
        symbol_t *tmp = lookup_symbol($<s_val>1);
        printf("IDENT (name=%s, address=%d)\n", $<s_val>1, tmp->addr);
        $$ = tmp->type; 
        printf("INT_LIT %d\n", $<i_val>3);
        $$ = "array";
    }
    | '-' Expr %prec UMINUS {
        printf("NEG\n");
        $$ = $<s_val>2;
    }
    | '!' Expr {
        printf("NOT\n");
        $$ = $<s_val>2;
    }
    | '(' Expr ')' { $$ = $<s_val>2; }
    | Expr '*' Expr {
        printf("MUL\n");
        $$ = (strcmp($<s_val>1, "f32") == 0 || strcmp($<s_val>3, "f32") == 0) ? "f32" : "i32";
    }
    | Expr '/' Expr {
        printf("DIV\n");
        $$ = (strcmp($<s_val>1, "f32") == 0 || strcmp($<s_val>3, "f32") == 0) ? "f32" : "i32";
    }
    | Expr '%' Expr {
        printf("REM\n");
        $$ = (strcmp($<s_val>1, "f32") == 0 || strcmp($<s_val>3, "f32") == 0) ? "f32" : "i32";
    }
    | Expr '+' Expr {
        printf("ADD\n");
        $$ = (strcmp($<s_val>1, "f32") == 0 || strcmp($<s_val>3, "f32") == 0) ? "f32" : "i32";
    }
    | Expr '-' Expr {
        printf("SUB\n");
        $$ = (strcmp($<s_val>1, "f32") == 0 || strcmp($<s_val>3, "f32") == 0) ? "f32" : "i32";
    }
    | Expr LSHIFT Expr {
        
        if (strcmp($<s_val>1, "i32") != 0 || strcmp($<s_val>3, "i32") != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: LSHIFT (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("LSHIFT\n");
        $$ = $<s_val>1;
        
    }
    | Expr RSHIFT Expr {
        printf("RSHIFT\n");
        if (strcmp($<s_val>1, "i32") == 0 && strcmp($<s_val>3, "i32") == 0) {
            $$ = $<s_val>1;
        } else {
            char msg[100];
            sprintf(msg, "invalid operation: RSHIFT (mismatched types %s and %s)\n", $<s_val>1, $<s_val>3);
        }
    }
    | Expr LAND Expr {
        printf("LAND\n");
        $$ = "bool";
    }
    | Expr LOR Expr {
        printf("LOR\n");
        $$ = "bool";
    }
    | Expr GEQ Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: GEQ (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("GEQ\n");
        $$ = "bool";
    }
    | Expr LEQ Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: LEQ (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("LEQ\n");
        $$ = "bool";
    }

    | Expr EQL Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: EQL (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("EQL\n");
        $$ = "bool";
    }

    | Expr NEQ Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: NEQ (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("NEQ\n");
        $$ = "bool";
    }
    | Expr '>' Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: GTR (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("GTR\n");
        $$ = "bool";
    }

    | Expr '<' Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: LSS (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("LSS\n");
        $$ = "bool";
    }
    | Expr AS Type { 
        printf("%c2%c\n", $<s_val>1[0], $<s_val>3[0]);
        $$ = $<s_val>3;
    }
    
;

ArrayElements
    : ArrayElements ',' Expr { $$ = $<s_val>3; }
    | Expr { $$ = $<s_val>1; }
;

PrintStmt
    : PrintType '(' Expr ')' ';' {
        printf("%s %s\n", $<s_val>1, $<s_val>3);
    }
;

DeclarationStmt
    : LET MutType ID ':' Type '=' Expr ';' { insert_symbol($<s_val>3, $<i_val>2, $<s_val>5, "-"); } 
    | LET MutType ID ':' Type ';' { insert_symbol($<s_val>3, $<i_val>2, $<s_val>5, "-"); }
    | LET MutType ID '=' Expr ';' { insert_symbol($<s_val>3, $<i_val>2, $<s_val>5, "-"); }
;

AssignmentStmt
    : ID AssignmentOperatorType Expr ';' { 
        symbol_t *target = lookup_symbol($<s_val>1);
        if (target == NULL) {
            char msg[100];
            sprintf(msg, "undefined: %s", $<s_val>1);
            yyerror(msg);
            HAS_ERROR = true;
        }else {
            printf("%s\n", $<s_val>2);
            if (target->mut != 1) {
                char msg[100];
                sprintf(msg, "cannot borrow immutable borrowed content `%s` as mutable", $<s_val>1);
                yyerror(msg);
                HAS_ERROR = true;
            }
        } 
    }
;

IfStmt
    : IF Expr Block %prec IFX
    | IF Expr Block ELSE Block 
;

WhileStmt
    : WHILE Expr Block
;

Type
    : INT { $$ = "i32"; }
    | FLOAT { $$ = "f32"; }
    | BOOL { $$ = "bool"; }
    | '&' STR { $$ = "str"; }
    | '[' Type ';' Expr ']' { $$ = "array"; }
    | /* empty */ { $$ = "V"; }
;

PrintType
    : PRINT { $$ = "PRINT"; }
    | PRINTLN { $$ = "PRINTLN"; }
;

MutType
    : MUT { $$ = 1; }
    | /* empty */ { $$ = 0; }
;

AssignmentOperatorType
    : '=' { $$ = "ASSIGN"; }
    | ADD_ASSIGN { $$ = "ADD_ASSIGN"; }
    | SUB_ASSIGN { $$ = "SUB_ASSIGN"; }
    | MUL_ASSIGN { $$ = "MUL_ASSIGN"; }
    | DIV_ASSIGN { $$ = "DIV_ASSIGN"; }
    | REM_ASSIGN { $$ = "REM_ASSIGN"; }
;

FunctionArguments
    : FunctionArguments ',' Type ID {
        char *buf = malloc(strlen($<s_val>1) + strlen($<s_val>3) + 10);
        sprintf(buf, "%s%s", $<s_val>1, $<s_val>3);
        $$ = buf;
    }
    | Type ID { $$ = $<s_val>1; }
    | /* empty */ { $$ = "V"; }
;

ArrowType
    : ARROW Type { $$ = $<s_val>2; }
    | /* empty */ { $$ = "V"; }
;

%%

/* C code section */
int main(int argc, char *argv[])
{
    /* Initialize symbol table */
    dummy_table = (symbol_table_t*) malloc(sizeof(symbol_table_t));
    dummy_table->scope_level = -1;
    dummy_table->element = NULL;
    dummy_table->next = dummy_table;

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
    new_symbol_table->scope_level = dummy_table->next->scope_level + 1;
    new_symbol_table->element = dummy_symbol;
    new_symbol_table->next = dummy_table->next;
    dummy_table->next = new_symbol_table;

    printf("> Create symbol table (scope level %d)\n", dummy_table->next->scope_level);
}

static void insert_symbol(char *name, int mut, char *type, char *func_sig) {
    printf("> Insert `%s` (addr: %d) to scope level %d\n", name, next_addr, dummy_table->next->scope_level);
    symbol_t *new_symbol = (symbol_t*) malloc(sizeof(symbol_t));
    new_symbol->index = dummy_table->next->element->prev->index + 1;
    new_symbol->name = strdup(name);
    new_symbol->mut = mut;
    new_symbol->type = strdup(type);
    new_symbol->addr = next_addr++;
    new_symbol->lineno = yylineno + 1;
    new_symbol->func_sig = strdup(func_sig);
    new_symbol->next = dummy_table->next->element;
    new_symbol->prev = dummy_table->next->element->prev;

    dummy_table->next->element->prev->next = new_symbol;
    dummy_table->next->element->prev = new_symbol;

}

symbol_t* lookup_symbol(char *name) {
    symbol_table_t *temp_table = dummy_table->next;
    while (temp_table != dummy_table) {
        symbol_t *tmp = temp_table->element->next;
        while (tmp != temp_table->element) {
            if (strcmp(tmp->name, name) == 0) {
                return tmp;
            }
            tmp = tmp->next;
        }
        temp_table = temp_table->next;
    }

    return NULL;
}

static void dump_symbol() {
    /* printf("\n> Dump symbol table (scope level: %d)\n", 0);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig"); */
    /* printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
            0, "name", 0, "type", 0, 0, "func_sig"); */

    printf("\n> Dump symbol table (scope level: %d)\n", dummy_table->next->scope_level);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig");
    symbol_t *cur = dummy_table->next->element->next;
    while (cur != dummy_table->next->element) {
        printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
            cur->index, cur->name, cur->mut, cur->type, cur->addr, cur->lineno, cur->func_sig);
        symbol_t *tmp = cur->next;

        free(cur->name);
        free(cur->type);
        free(cur->func_sig);
        free(cur);

        cur = tmp;
    }

    symbol_table_t *temp = dummy_table->next;
    dummy_table->next = temp->next;
    free(temp->element);
    free(temp);
    
}
