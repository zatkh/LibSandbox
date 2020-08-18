CC = gcc
CFLAGS = -g -Wall 
SBOX_DIR = $(PWD)/../intra_proc_sbox/
LIBS = -L$(SBOX_DIR) -lsbox -lpthread
CFLAGS += -I$(SBOX_DIR)
OBJ_FILES = privilage_test

all: $(OBJ_FILES)

privilage_test:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)

tc_smv_create:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)

tc_memdom_create:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)

tc_smvthread_create:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)

tc_shared_mm:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)

tc_cond_var:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)

tc_memdom_alloc:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)

clean:
	rm *.o $(OBJ_FILES)
