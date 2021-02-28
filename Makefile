IDIR=include
SDIR=src
BDIR=build

CFLAGS=-I$(IDIR)

$(BDIR)/abfm: $(SDIR)/*.c
	$(CC) -o $@ $^ $(CFLAGS)


