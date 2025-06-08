.source hw3.j
.class public Main
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
.limit stack 100
.limit locals 100
	ldc 1
	istore 0
	iload 0
	ldc 101
	isub
	iflt L_true0
	iconst_0
	goto L_end0
	L_true0:
	iconst_1
	L_end0:
		getstatic java/lang/System/out Ljava/io/PrintStream;
		iload 0
		invokevirtual java/io/PrintStream/println(I)V
		iload 0
		ldc 1
		iadd
		istore 0
		return
	.end method
