
/* Please feel free to modify any content */

/* Definition section */
%{
    #include "compiler_common.h" //Extern variables that communicate with lex
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

    /* Used to generate code */
    /* As printf; the usage: CODEGEN("%d - %s\n", 100, "Hello world"); */
    /* We do not enforce the use of this macro */
    #define CODEGEN(...) \
        do { \
            for (int i = 0; i < g_indent_cnt; i++) { \
                fprintf(fout, "\t"); \
                printf("\t"); \
            } \
            fprintf(fout, __VA_ARGS__); \
            printf(__VA_ARGS__); \
        } while (0)

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
    int block_stack[100];
    int block_top = -1;

    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void insert_symbol(char *name, int mut, char *type, char *func_sig);
    symbol_t* lookup_symbol(char *name);
    static void dump_symbol();

    /* Global variables */
    bool g_has_error = false;
    FILE *fout = NULL;
    int g_indent_cnt = 0;
    int g_label_cnt = 0;
%}

/* %error-verbose */

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
        if (strcmp($<s_val>2, "main") == 0) {
            CODEGEN(".method public static %s([Ljava/lang/String;)%s\n", $<s_val>2, $<s_val>6);
        } else {
            CODEGEN(".method public static %s(%s)%s\n", $<s_val>2, $<s_val>4, $<s_val>6);
        }
        CODEGEN(".limit stack 100\n");
        CODEGEN(".limit locals 100\n");

        char *sig = (char *)malloc(strlen($<s_val>4) + 10);
        sprintf(sig, "(%s)%s", $<s_val>4, $<s_val>6);
        insert_symbol($<s_val>2, -1, "func", sig);
    } Block {
        if (strcmp($<s_val>6, "V") == 0) {
            CODEGEN("return\n");
        } else {
            CODEGEN("%sreturn\n", $<s_val>6);
        }
        
        g_indent_cnt--;

        CODEGEN(".end method\n");
    }
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
    : '{' { create_symbol(); g_indent_cnt++; } StmtList '}' { 
        dump_symbol(); 
    }
;

Expr
    : ID {
        symbol_t *tmp = lookup_symbol($<s_val>1);
        if (tmp == NULL) {
            char msg[100];
            sprintf(msg, "undefined: %s", $<s_val>1);
            yyerror(msg);
            g_has_error = TRUE;
            $$ = "undefined";
        } else {
            char type;
            if (tmp->type[0] == 'Z') {
                type = 'i';
            } else if (strcmp(tmp->type, "Ljava/lang/String;") == 0) {
                type = 'a';
            } else {
                type = tmp->type[0] + 32;
            }
            CODEGEN("%cload %d\n", type, tmp->addr);
            // printf("IDENT (name=%s, address=%d)\n", $<s_val>1, tmp->addr);
            $$ = tmp->type; 
        }
        
    }
    | INT_LIT {
        CODEGEN("ldc %d\n", $<i_val>1);
        $$ = "I";
    }
    | FLOAT_LIT {
        CODEGEN("ldc %f\n", $<f_val>1);
        $$ = "F";
    }
    | '"' STRING_LIT '"' {
        CODEGEN("ldc \"%s\"\n", $<s_val>2);

        // printf("STRING_LIT \"%s\"\n", $<s_val>2);
        $$ = "Ljava/lang/String;";
    }
    | '"' '"' {
        CODEGEN("ldc \"\"\n");

        //printf("STRING_LIT \"\"\n");
        $$ = "Ljava/lang/String;";
    }
    | TRUE {
        CODEGEN("iconst_1\n");
        $$ = "Z";
    }
    | FALSE {
        CODEGEN("iconst_0\n");
        $$ = "Z";
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
        CODEGEN("%cneg\n", $<s_val>2[0] + 32);
        $$ = $<s_val>2;
    }
    | '!' Expr {
        CODEGEN("iconst_1\n");
        CODEGEN("ixor\n");
        // printf("NOT\n");
        $$ = $<s_val>2;
    }
    | '(' Expr ')' { $$ = $<s_val>2; }
    | Expr '*' Expr {
        CODEGEN("%cmul\n", $<s_val>1[0] + 32);
        $$ = (strcmp($<s_val>1, "F") == 0 || strcmp($<s_val>3, "F") == 0) ? "F" : "I";
    }
    | Expr '/' Expr {
        CODEGEN("%cdiv\n", $<s_val>1[0] + 32);
        $$ = (strcmp($<s_val>1, "F") == 0 || strcmp($<s_val>3, "F") == 0) ? "F" : "I";
    }
    | Expr '%' Expr {
        CODEGEN("%crem\n", $<s_val>1[0] + 32);
        $$ = (strcmp($<s_val>1, "F") == 0 || strcmp($<s_val>3, "F") == 0) ? "F" : "I";
    }
    | Expr '+' Expr {
        CODEGEN("%cadd\n", $<s_val>1[0] + 32);
        $$ = (strcmp($<s_val>1, "F") == 0 || strcmp($<s_val>3, "F") == 0) ? "F" : "I";
    }
    | Expr '-' Expr {
        CODEGEN("%csub\n", $<s_val>1[0] + 32);
        $$ = (strcmp($<s_val>1, "F") == 0 || strcmp($<s_val>3, "F") == 0) ? "F" : "I";
    }
    | Expr LSHIFT Expr {
        
        if (strcmp($<s_val>1, "I") != 0 || strcmp($<s_val>3, "I") != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: LSHIFT (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            g_has_error = true;
        }
        printf("LSHIFT\n");
        $$ = $<s_val>1;
        
    }
    | Expr RSHIFT Expr {
        printf("RSHIFT\n");
        if (strcmp($<s_val>1, "I") == 0 && strcmp($<s_val>3, "I") == 0) {
            $$ = $<s_val>1;
        } else {
            char msg[100];
            sprintf(msg, "invalid operation: RSHIFT (mismatched types %s and %s)\n", $<s_val>1, $<s_val>3);
        }
    }
    | Expr LAND Expr {
        CODEGEN("iand\n");
        //printf("LAND\n");
        $$ = "Z";
    }
    | Expr LOR Expr {
        CODEGEN("ior\n");
        //printf("LOR\n");
        $$ = "Z";
    }
    | Expr GEQ Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: GEQ (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            g_has_error = true;
        }
        printf("GEQ\n");
        $$ = "Z";
    }
    | Expr LEQ Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: LEQ (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            g_has_error = true;
        }
        printf("LEQ\n");
        $$ = "Z";
    }

    | Expr EQL Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: EQL (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            g_has_error = true;
        }
        //printf("EQL\n");
        CODEGEN("%csub\n", $<s_val>1[0] + 32);
        if (strcmp($<s_val>1, "F") == 0) {
            CODEGEN("fconst_0\n");
            CODEGEN("fcmpg\n");
        }
        CODEGEN("ifeq L_true%d\n", g_label_cnt);
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end%d\n", g_label_cnt);
        CODEGEN("L_true%d:\n", g_label_cnt);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end%d:\n", g_label_cnt);
        g_label_cnt++;
        $$ = "Z";
    }

    | Expr NEQ Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: NEQ (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            g_has_error = true;
        }
        //printf("NEQ\n");
        CODEGEN("%csub\n", $<s_val>1[0] + 32);
        if (strcmp($<s_val>1, "F") == 0) {
            CODEGEN("fconst_0\n");
            CODEGEN("fcmpg\n");
        }
        CODEGEN("ifeq L_true%d\n", g_label_cnt);
        CODEGEN("iconst_1\n");
        CODEGEN("goto L_end%d\n", g_label_cnt);
        CODEGEN("L_true%d:\n", g_label_cnt);
        CODEGEN("iconst_0\n");
        CODEGEN("L_end%d:\n", g_label_cnt);
        g_label_cnt++;
        $$ = "Z";
    }
    | Expr '>' Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: GTR (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            g_has_error = true;
        }

        CODEGEN("%csub\n", $<s_val>1[0] + 32);
        // CODEGEN("%cconst_0\n", $<s_val>1[0] + 32);
        if (strcmp($<s_val>1, "F") == 0) {
            CODEGEN("fconst_0\n");
            CODEGEN("fcmpg\n");
        }
        CODEGEN("ifgt L_true%d\n", g_label_cnt);
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end%d\n", g_label_cnt);
        CODEGEN("L_true%d:\n", g_label_cnt);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end%d:\n", g_label_cnt);
        g_label_cnt++;
        //printf("GTR\n");
        $$ = "Z";
    }

    | Expr '<' Expr {
        if (strcmp($<s_val>1, $<s_val>3) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: LSS (mismatched types %s and %s)", $<s_val>1, $<s_val>3);
            yyerror(msg);
            g_has_error = true;
        }

        CODEGEN("%csub\n", $<s_val>1[0] + 32);
        // CODEGEN("%cconst_0\n", $<s_val>1[0] + 32);
        if (strcmp($<s_val>1, "F") == 0) {
            CODEGEN("fconst_0\n");
            CODEGEN("fcmpg\n");
        }
        CODEGEN("iflt L_true%d\n", g_label_cnt);
        CODEGEN("iconst_0\n");
        CODEGEN("goto L_end%d\n", g_label_cnt);
        CODEGEN("L_true%d:\n", g_label_cnt);
        CODEGEN("iconst_1\n");
        CODEGEN("L_end%d:\n", g_label_cnt);
        g_label_cnt++;
        //printf("GTR\n");
        $$ = "Z";
    }
    | Expr AS Type { 
        //printf("%c2%c\n", $<s_val>1[0], $<s_val>3[0]);
        CODEGEN("%c2%c\n", $<s_val>1[0] + 32, $<s_val>3[0] + 32);
        $$ = $<s_val>3;
    }
;

ArrayElements
    : ArrayElements ',' Expr { $$ = $<s_val>3; }
    | Expr { $$ = $<s_val>1; }
;

PrintStmt
    : PrintType { CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n"); } '(' Expr ')' ';' {
        CODEGEN("invokevirtual java/io/PrintStream/%s(%s)V\n", $<s_val>1, $<s_val>4);

        // printf("%s %s\n", $<s_val>1, $<s_val>3);
    }
;

DeclarationStmt
    : LET MutType ID ':' Type '=' Expr ';' { 
        insert_symbol($<s_val>3, $<i_val>2, $<s_val>5, "-");
        char type;
        if ($<s_val>5[0] == 'Z') {
            type = 'i';
        } else if (strcmp($<s_val>5, "Ljava/lang/String;") == 0) {
            type = 'a';
        } else {
            type = $<s_val>5[0] + 32;
        }
        CODEGEN("%cstore %d\n", type, lookup_symbol($<s_val>3)->addr);
    } 
    | LET MutType ID ':' Type ';' { 
        insert_symbol($<s_val>3, $<i_val>2, $<s_val>5, "-");
        // char type;
        // if ($<s_val>5[0] == 'Z') {
        //     type = 'i';
        // } else if (strcmp($<s_val>5, "Ljava/lang/String;") == 0) {
        //     type = 'a';
        // } else {
        //     type = $<s_val>5[0] + 32;
        // }
        // CODEGEN("%cstore %d\n", type, lookup_symbol($<s_val>3)->addr);
    }
    | LET MutType ID '=' Expr ';' { 
        insert_symbol($<s_val>3, $<i_val>2, $<s_val>5, "-");
        char type;
        if ($<s_val>5[0] == 'Z') {
            type = 'i';
        } else if (strcmp($<s_val>5, "Ljava/lang/String;") == 0) {
            type = 'a';
        } else {
            type = $<s_val>5[0] + 32;
        }
        CODEGEN("%cstore %d\n", type, lookup_symbol($<s_val>3)->addr);
    }
;

AssignmentStmt
    :ID '=' Expr ';' {
        symbol_t *target = lookup_symbol($<s_val>1);
        if (target == NULL) {
            char msg[100];
            sprintf(msg, "undefined: %s", $<s_val>1);
            yyerror(msg);
            g_has_error = true;
        }else {
            //printf("%s\n", $<s_val>2);
            if (target->mut != 1) {
                char msg[100];
                sprintf(msg, "cannot borrow immutable borrowed content `%s` as mutable", $<s_val>1);
                yyerror(msg);
                g_has_error = true;
            }
            char type;
            if ($<s_val>3[0] == 'Z') {
                type = 'i';
            } else if (strcmp($<s_val>3, "Ljava/lang/String;") == 0) {
                type = 'a';
            } else {
                type = target->type[0] + 32;
            }

            CODEGEN("%cstore %d\n", type, target->addr);
        } 
    }
    | ID {
        symbol_t *target = lookup_symbol($<s_val>1);
        if (target == NULL) {
            char msg[100];
            sprintf(msg, "undefined: %s", $<s_val>1);
            yyerror(msg);
            g_has_error = true;
        }else {
            //printf("%s\n", $<s_val>2);
            if (target->mut != 1) {
                char msg[100];
                sprintf(msg, "cannot borrow immutable borrowed content `%s` as mutable", $<s_val>1);
                yyerror(msg);
                g_has_error = true;
            }
            char type;
            if (target->type[0] == 'Z') {
                type = 'i';
            } else if (strcmp(target->type, "Ljava/lang/String;") == 0) {
                type = 'a';
            } else {
                type = target->type[0] + 32;
            }
            CODEGEN("%cload %d\n", type, target->addr);
        } 
    }   AssignmentOperatorType Expr ';' { 
        symbol_t *target = lookup_symbol($<s_val>1);
        if (target == NULL) {
            char msg[100];
            sprintf(msg, "undefined: %s", $<s_val>1);
            yyerror(msg);
            g_has_error = true;
        }else {
            //printf("%s\n", $<s_val>2);
            if (target->mut != 1) {
                char msg[100];
                sprintf(msg, "cannot borrow immutable borrowed content `%s` as mutable", $<s_val>1);
                yyerror(msg);
                g_has_error = true;
            }
            char type;
            if ($<s_val>4[0] == 'Z') {
                type = 'i';
            } else if (strcmp($<s_val>4, "Ljava/lang/String;") == 0) {
                type = 'a';
            } else {
                type = target->type[0] + 32;
            }
            CODEGEN("%c%s\n", type, $<s_val>3);
            CODEGEN("%cstore %d\n", type, target->addr);
        } 
    }
;

IfStmt
    : IF IfCondition Block %prec IFX {
        CODEGEN("L_else%d:\n", block_stack[block_top--]);
    }
    | IF IfCondition Block ELSE {
        CODEGEN("goto L_else_end%d\n", block_stack[block_top]);
        CODEGEN("L_else%d:\n", block_stack[block_top]);
    } Block {
        CODEGEN("L_else_end%d:\n", block_stack[block_top--]);
    }
;

IfCondition
    : Expr {
        CODEGEN("ifeq L_else%d\n", g_label_cnt);
        block_stack[++block_top] = g_label_cnt++;
    }
;

WhileStmt
    : WHILE { block_stack[++block_top] = g_label_cnt++; CODEGEN("L_while%d:\n", block_stack[block_top]); } 
      Expr { CODEGEN("ifeq L_while_end%d\n", block_stack[block_top]); } 
      Block { CODEGEN("goto L_while%d\n", block_stack[block_top]); CODEGEN("L_while_end%d:\n", block_stack[block_top--]); }
;

Type
    : INT { $$ = "I"; }
    | FLOAT { $$ = "F"; }
    | BOOL { $$ = "Z"; }
    | '&' STR { $$ = "Ljava/lang/String;"; }
    | '[' Type ';' Expr ']' { 
        char buf[100];
        sprintf(buf, "newarray %s", $<s_val>2);
        $$ = buf;
    }
    | /* empty */ { $$ = "V"; }
;

PrintType
    : PRINT { $$ = "print"; }
    | PRINTLN { $$ = "println"; }
;

MutType
    : MUT { $$ = 1; }
    | /* empty */ { $$ = 0; }
;

AssignmentOperatorType
    : ADD_ASSIGN { $$ = "add"; }
    | SUB_ASSIGN { $$ = "sub"; }
    | MUL_ASSIGN { $$ = "mul"; }
    | DIV_ASSIGN { $$ = "div"; }
    | REM_ASSIGN { $$ = "rem"; }
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
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    if (!yyin) {
        printf("file `%s` doesn't exists or cannot be opened\n", argv[1]);
        exit(1);
    }

    /* Codegen output init */
    char *bytecode_filename = "hw3.j";
    fout = fopen(bytecode_filename, "w");
    CODEGEN(".source hw3.j\n");
    CODEGEN(".class public Main\n");
    CODEGEN(".super java/lang/Object\n");

    /* Symbol table init */
    // Add your code
    dummy_table = (symbol_table_t*) malloc(sizeof(symbol_table_t));
    dummy_table->scope_level = -1;
    dummy_table->element = NULL;
    dummy_table->next = dummy_table;
    
    yylineno = 0;
    yyparse();

    /* Symbol table dump */
    // Add your code

	printf("Total lines: %d\n", yylineno);
    fclose(fout);
    fclose(yyin);

    if (g_has_error) {
        remove(bytecode_filename);
    }
    yylex_destroy();
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

    /* printf("> Create symbol table (scope level %d)\n", dummy_table->next->scope_level); */
}

static void insert_symbol(char *name, int mut, char *type, char *func_sig) {
    /* printf("> Insert `%s` (addr: %d) to scope level %d\n", name, next_addr, dummy_table->next->scope_level); */
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

    /* printf("\n> Dump symbol table (scope level: %d)\n", dummy_table->next->scope_level);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig"); */
    symbol_t *cur = dummy_table->next->element->next;
    while (cur != dummy_table->next->element) {
        /* printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
            cur->index, cur->name, cur->mut, cur->type, cur->addr, cur->lineno, cur->func_sig); */
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