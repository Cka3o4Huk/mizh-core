W_ASM = nasmw
UNIX_ASM = nasm
_OBJ_DIR = obj
_SRC_DIR = src
_CUR_DIR = .
SUBDIRS = src

ifeq (${OS},Windows_NT)
WINNT = yes
SHEEL = cmd.exe
MAKER = make
ASM = $(W_ASM)
OBJ_DIR = $(_CUR_DIR)\\$(_OBJ_DIR)
SRC_DIR = $(_CUR_DIR)\\$(_SRC_DIR)
else
UNIX = yes
ASM = $(UNIX_ASM)
MAKER = gmake
OBJ_DIR = $(_CUR_DIR)/$(_OBJ_DIR)
SRC_DIR = $(_CUR_DIR)/$(_SRC_DIR)
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
#	@for i in $(SUBDIRS); do (cd $$i; echo $$i; $(MAKE)) || exit; done
	$(foreach dir,$(SUBDIRS),$(MAKER) -C $(dir))


clean_obj:
	@echo "###### Clean all" 
ifdef UNIX
	rm -rf ./obj
	rm -f load2
	rm -f core
endif
ifdef WINNT
	$(SHEEL) /Q /C rmdir /Q /S obj
	del /Q /S obj 
	del /Q load2 
	del /Q core
endif


clean:  clean_obj
ifdef UNIX
	rm -f loader
else 
	del loader
endif