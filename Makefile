GOAL    := a.out
CC      := gcc-10
LDFLAGS :=
SRC     := se_scan.c se_parse.c se.c main.c
LEX     := flex
LFLAGS  :=
YACC    := bison
YFLAGS  :=
CFLAGS  := -Wall -Wextra -pedantic -Wno-unused-function
DEPFILE := dep.mk

.PHONY : all
all : $(GOAL)

.PHONY : clean
clean :
	$(RM) *.o
	$(RM) se_scan.c se_scan.h
	$(RM) se_parse.c se_parse.h
	$(RM) $(GOAL)
	$(RM) $(DEPFILE)

$(GOAL) : $(SRC:%.c=%.o)
	$(CC) -o $@ $(LDFLAGS) $^

se_scan.c se_scan.h &: se_scan.l se_parse.h
	$(LEX) -o se_scan.c $(LFLAGS) --header-file=$(@:%.c=%.h) $<

se_parse.c se_parse.h &: se_parse.y
	$(YACC) -o se_parse.c $(YFLAGS) -d $<

$(DEPFILE) : $(SRC)
	$(CC) -o $@ -MM -MG $^

include $(DEPFILE)


