IDIR=include
SDIR=src
BDIR=build

CFLAGS=-I$(IDIR)

$(BDIR)/abfm: $(SDIR)/*.c
	mkdir -p $(BDIR)
	$(CC) -o $@ $^ $(CFLAGS)


