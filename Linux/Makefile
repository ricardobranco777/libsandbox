CFLAGS	:= -Wall -Wextra -fPIC
LDFLAGS	:= -shared
LIB	:= libsandbox.so

CLEANFILES = *.so *.o a.out

$(LIB): sandbox.c lib.c
	$(LINK.c) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(CLEANFILES)
