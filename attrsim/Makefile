CFLAGS+=-O3

TARGETS=attrsim36 attrsim37

all: $(TARGETS)

clean:
	rm $(TARGETS)

attrsim36: attrsim.c
	$(CC) $(CFLAGS) -DNH_36 $^ -o $@ -lm

attrsim37: attrsim.c
	$(CC) $(CFLAGS) -DNH_37 $^ -o $@ -lm
