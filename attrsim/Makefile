CFLAGS+=-O3

TARGETS=attrsim36 attrsim37 attrsim-dnh

all: $(TARGETS)

clean:
	rm $(TARGETS)

attrsim36: attrsim.c attr.c
	$(CC) $(CFLAGS) -DNH_36 $^ -o $@ -lm

attrsim37: attrsim.c attr.c
	$(CC) $(CFLAGS) -DNH_37 $^ -o $@ -lm

attrsim-dnh: attrsim-dnh.c attr.c
	$(CC) $(CFLAGS) -DNH_36 $^ -o $@ -lm
