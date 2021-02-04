TARGET = out

YACC_OBJ = gpp_interpreter.y

YACC_C_OBJ = gpp_interpreter.c

LEX_OBJ = gpp_interpreter.l

LEX_C_OBJ = gpp_lexer.c

YACC_CC = yacc

FLEX_CC = flex

GCC = gcc

all:
	$(YACC_CC) -o $(YACC_C_OBJ) -d $(YACC_OBJ)
	$(FLEX_CC) -o $(LEX_C_OBJ) $(LEX_OBJ)
	$(CC) $(LEX_C_OBJ) $(YACC_C_OBJ) -o $(TARGET)
clean:
	rm gpp_lexer.out