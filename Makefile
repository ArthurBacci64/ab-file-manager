IDIR=include
SDIR=src

CFLAGS=-I$(IDIR)

abfm: $(SDIR)/*.c
	$(CC) -o $@ $^ $(CFLAGS)


