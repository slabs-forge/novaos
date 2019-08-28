
# Tools
TARGET=aarch64-none-elf

AS=$(TARGET)-as
LD=$(TARGET)-ld
CC=$(TARGET)-gcc
OC=$(TARGET)-objcopy
ST=$(TARGET)-strip

CFLAGS=-g -MT $@ -MMD -MP -MF $(DEP)/$*.d

# Directories
BLD=./.bld
DEP=./.dep

OBJECTS=$(patsubst %.s,$(BLD)/%.o,$(wildcard *.s)) $(patsubst %.c,$(BLD)/%.o,$(wildcard *.c))
DEPENDS=$(patsubst %.c,$(DEP)/%.d,$(wildcard *.c))

all: kernel.elf kernel.sym

$(DEPENDS):
include $(DEPENDS)

kernel.elf: kernel.bin kernel.sym
	$(ST) -g -o $@ $<
	$(OC) --add-gnu-debuglink=kernel.sym $@

kernel.bin: $(OBJECTS) kernel.ld
	$(LD) -Tkernel.ld $(OBJECTS) -o $@

kernel.sym: kernel.bin
	$(OC) --only-keep-debug $< $@

# Implicit rules
$(BLD)/%.o : %.s | $(BLD)
	$(AS) $< -o $@

%.o : %.c
$(BLD)/%.o : %.c $(DEP)/%.d | $(BLD) $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@


$(BLD):
	mkdir $@

$(DEP):
	mkdir $@

info:
	@echo $(OBJECTS)
	@echo $(DEPENDS)

.PHONY: clean

clean:
	rm -f kernel.elf
	rm -f kernel.bin
	rm -f kernel.sym
