.SUFFIXES: .asm

OBJECTS = startup.c mm.c core.c tty.c kbr.c dev/hdd.c idt.c st_lib.c debug.c cmd.c
FLAGS = -ffreestanding -c
W_ASM = nasmw
ASM = nasm
BUILD_DIR = obj
MAKER = gmake

all: core

clean_obj:
	rm -rf ../${BUILD_DIR}/dev
	rm -rf ../${BUILD_DIR}

.c.o:
	@echo "###### Compiling file $< to $@"
	@gcc ${FLAGS} -o ../${BUILD_DIR}/$@ ./$<

.asm.o: 
	@echo "###### Compiling asm file... $@"	
	@${ASM} -f bin -o ../${BUILD_DIR}/$@ $<

core: init_dir ${OBJECTS:.c=.o}
	@echo $(join a b,.c .o)
	ld -Ttext 0x200000 -o ../core $(addprefix ../${BUILD_DIR}/,${OBJECTS:.c=.o})
	objcopy ../core -O binary

startup.o: startup.c

init_dir: 
	@echo "###### Initializing directories..."
	@mkdir -p ../${BUILD_DIR}/
	@mkdir -p ../${BUILD_DIR}/dev/

st_lib.o: st_lib.c

debug.o: debug.c

tty.o: tty.c

core.o: core.c

idt.o:  idt.c

kbr.o: kbr.c

cmd.o: cmd.c

mm.o: mm.c

clean:  clean_obj	
