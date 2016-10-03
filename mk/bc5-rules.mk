#
# bc5-rules.mk
#

# LIB = $(_LIB).lib
LIB = bc5.lib

$(ODIR)/%.o: src/%.c
	$(CC) $(ALLFLAGS) -c -o$(subst /,\\,$@) $(subst /,\\,$<)

$(ODIR)/%.o: tests/%.c
	$(CC) $(ALLFLAGS) -c -o$(subst /,\\,$@) $(subst /,\\,$<)

$(ODIR)/%.o: structures/%.c
	$(CC) $(ALLFLAGS) -c -o$(subst /,\\,$@) $(subst /,\\,$<)

NLOBJS = $(subst /,\\, $(subst $(ODIR),+-$(ODIR),$(LOBJS)))
$(LIB): $(LOBJS)
	$(AR) $@ $(NLOBJS)
	$(TDUMP) $@
	
BLIB = $(subst /,\,$(WIN_BC5_BASE)/lib)
NOBJS = $(shell echo $(OBJS) | tr [a-z/] [A-Z\\\\])
#$(subst t,T,$(subst /,\,$(OBJS)))

$(EXE): $(OBJS)
	echo "-v -L$(BLIB) -c -w-dpl -went -wdup -w-def -wimt -wbdl -wsrf -wmsk  -Tpe -ap $(BLIB)\\C0x32.obj+" > $(compiler).lk1
	echo "$(NOBJS)" >> $(compiler).lk1
	echo "$(EXE), $(EXE).map" >> $(compiler).lk1
	echo "$(LIB) $(BLIB)\\IMPORT32.lib $(BLIB)\\Cw32.lib" >> $(compiler).lk1
	$(LD) @$(compiler).lk1
