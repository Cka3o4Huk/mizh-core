W_ASM = nasmw
UNIX_ASM = nasm
ifeq (${OS},Windows_NT)
SHEEL = cmd.exe
MAKER = make
ASM = W_ASM
else
ASM = UNIX_ASM
MAKER = gmake
endif

all: init_make boot.asm load2
	$(ASM) -fbin -o loader boot.asm
	$(MAKER) clean_obj

init_make:
	@echo OS: ${OS}

load2: core
	$(ASM) -fbin -o load2 bootload.asm
core:
	@echo "###### Compiling core files"
	$(MAKER) -C ./src -f ./Makefile all

clean_obj:
	@echo "###### Clean all" 
	rm -rf ${.CURDIR}/obj
	rm -f load2
	rm -f core
clean:  clean_obj
	rm -f loader
