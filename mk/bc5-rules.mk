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
	
$(EXE): $(OBJS)
	echo "/Lc:\\Borland\\bc5\\lib;. /c c0ws +" > bc5.lk1
	echo "$(OBJS),$(EXE) +" >> bc5.lk1
	echo "$(EXE).map +" >> bc5.lk1
	echo "$(LIB) cws" >> bc5.lk1
	$(LD) @bc5.lk1

#	$(LD) Lc:\\Borland\\bc5\\lib;. -Twe $(OBJS),, $(LIB)
