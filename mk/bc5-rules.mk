#
# bc5-rules.mk
#

LIB = $(_LIB).lib

$(ODIR)/%.o: src/%.c
	$(CC) $(ALLFLAGS) -c -o$(subst /,\\,$@) $(subst /,\\,$<)

$(ODIR)/%.o: tests/%.c
	$(CC) $(ALLFLAGS) -c -o$(subst /,\\,$@) $(subst /,\\,$<)

$(ODIR)/%.o: structures/%.c
	$(CC) $(ALLFLAGS) -c -o$(subst /,\\,$@) $(subst /,\\,$<)

$(LIB): $(LOBJS)
	$(AR) $@ /C $(shell echo $(subst $(ODIR),+-$(ODIR),$(LOBJS)) | tr [a-z/] [A-Z\\\\])
	
BLIB = $(subst /,\,c:/Borland/Bc5/lib)
NOBJS = $(subst t,T,$(subst /,\,$(OBJS)))

$(EXE): $(OBJS)
	echo "-v -L$(BLIB) -c -w-dpl -went -wdup -w-def -wimt -wbdl -wsrf -wmsk  -Tpe -ap $(BLIB)\\C0x32.obj+" > $(compiler).lk1
	echo "$(NOBJS)" >> $(compiler).lk1
	echo "$(EXE), $(EXE).map" >> $(compiler).lk1
	echo "$(LIB) $(BLIB)\\IMPORT32.lib $(BLIB)\\Cw32.lib" >> $(compiler).lk1
	$(LD) @$(compiler).lk1

#	$(LD) Lc:\\Borland\\bc5\\lib;. -Twe $(OBJS),, $(LIB)
