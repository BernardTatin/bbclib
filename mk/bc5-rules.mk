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
	$(AR) $@ $(subst $(ODIR)/,-+$(ODIR)\\,$(LOBJS))
	
BLIB = $(subst /,\,c:/Borland/Bc5/lib)
NOBJS = $(subst t,T,$(subst /,\,$(OBJS)))

$(EXE): $(OBJS)
	echo "-v -L$(BLIB) -c -wdpl -went -wdup -wdef -wimt -wbdl -wsrf -wmsk  -Tpe -ap $(BLIB)\\C0x32.obj+" > bc5.lk1
	echo "$(NOBJS)" >> bc5.lk1
	echo "$(EXE), $(EXE).map" >> bc5.lk1
	echo "$(LIB) $(BLIB)\\IMPORT32.lib $(BLIB)\\Cw32i.lib" >> bc5.lk1
	$(LD) @bc5.lk1

#	$(LD) Lc:\\Borland\\bc5\\lib;. -Twe $(OBJS),, $(LIB)
