LPATHS += $(LIBDIR)/uta/uta.o
CFLAGS += -Ilib/uta/
HPATHS += lib/uta/uta.h

$(LIBDIR)/uta:
	mkdir -p $@

$(LIBDIR)/uta/uta.o: lib/uta/uta.c | $(LIBDIR)/uta
	$(CC) $(CFLAGS) $< -c -o $@
