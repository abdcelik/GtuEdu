TARGET = gpp_lexer.out

LEX_OBJ = gpp_lexer.l

C_OBJ = gpp_lexer.c

FLEX_CC = flex

GCC = gcc

all:
	$(FLEX_CC) -o $(C_OBJ) $(LEX_OBJ)
	$(CC) $(C_OBJ) -o $(TARGET)
clean:
	rm gpp_lexer.out