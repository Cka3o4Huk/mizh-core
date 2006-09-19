.SUFFIXES: .asm

OBJECTS=startup.c mm.c core.c tty.c kbr.c dev\hdd.c idt.c st_lib.c debug.c cmd.c
FLAGS= -ffreestanding -c
ASM = nasmw
BUILD_DIR = obj


all: core

.c.o:
	gcc $(FLAGS) -o ..\$(BUILD_DIR)\$@ $<

.asm.o: 
	$(ASM) -f bin -o ..\$(BUILD_DIR)\$@ $<

core: init_dir $(OBJECTS:.c=.o) 
	ld -Ttext 0x200000 -o ..\core $(addprefix ..\$(BUILD_DIR)\,$(OBJECTS:.c=.o))
	objcopy ..\core -O binary

startup.o: startup.c

init_dir: 
	make clean_obj
	if not exist ..\$(BUILD_DIR) 			mkdir ..\$(BUILD_DIR)
	if not exist ..\$(BUILD_DIR)\dev 		mkdir ..\$(BUILD_DIR)\dev 

st_lib.o: st_lib.c

debug.o: debug.c

tty.o: tty.c

core.o: core.c

idt.o:  idt.c

kbr.o: kbr.c

cmd.o: cmd.c

mm.o: mm.c

clean_obj: 
	if exist ..\$(BUILD_DIR)\
	 del $(addprefix ..\$(BUILD_DIR)\,$(OBJECTS:.c=.o))
	if exist ..\$(BUILD_DIR)\dev rmdir ..\$(BUILD_DIR)\dev
	if exist ..\$(BUILD_DIR) rmdir ..\$(BUILD_DIR)

clean:  clean_obj	
