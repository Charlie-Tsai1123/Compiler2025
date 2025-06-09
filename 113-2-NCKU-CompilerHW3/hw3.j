.source hw3.j
.class public Main
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
.limit stack 100
.limit locals 100
	ldc 1
	istore 0
	L_while0:
	iload 0
	ldc 101
	isub
	iflt L_true1
	iconst_0
	goto L_end1
	L_true1:
	iconst_1
	L_end1:
	ifeq L_while_end0
		getstatic java/lang/System/out Ljava/io/PrintStream;
		iload 0
		invokevirtual java/io/PrintStream/println(I)V
		iload 0
		ldc 1
		iadd
		istore 0
		goto L_while0
		L_while_end0:
		return
	.end method
