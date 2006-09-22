.SUFFIXES: .asm

OBJECTS = startup.c mm/mm.c kernel/core.c tty.c dev/kbr.c dev/hdd.c idt.c lib/st_lib.c lib/debug.c cmd.c
FLAGS = -ffreestanding -c
W_ASM = nasmw
ASM = nasm
OBJ_DIR = obj
MAKER = gmake
INCLUDE = include

ifeq (${OS},Windows_NT)
WINNT = yes
else
UNIX = yes
endif

SUBDIRS = dev mm kernel lib

all: core

clean_obj:
	rm -rf ../${BUILD_DIR}/dev
	rm -rf ../${BUILD_DIR}

.c.o:
	@echo "###### Compiling file $< to $@"
	@gcc ${FLAGS} -I${INCLUDE} -o ../${OBJ_DIR}/$@ ./$<

.asm.o: 
	@echo "###### Compiling asm file... $@"	
	@${ASM} -f bin -o ../${OBJ_DIR}/$@ $<

core: init_dir ${OBJECTS:.c=.o}	
	ld -Ttext 0x200000 -o ../core $(addprefix ../${OBJ_DIR}/,${OBJECTS:.c=.o})
	objcopy ../core -O binary

startup.o: startup.c

init_dir: 
	@echo "###### Initializing directories..."
ifdef WINNT	
	mkdir ..\$(OBJ_DIR)
	$(foreach dir,$(SUBDIRS),mkdir ..\$(OBJ_DIR)\$(dir);)
endif

ifdef UNIX
	mkdir -p ../${OBJ_DIR}
	$(foreach dir,$(SUBDIRS),mkdir -p ../$(OBJ_DIR)/$(dir);)
endif


st_lib.o: st_lib.c

debug.o: debug.c

tty.o: tty.c

core.o: core.c

idt.o:  idt.c

kbr.o: kbr.c

cmd.o: cmd.c

mm.o: mm.c

clean:  clean_obj	
