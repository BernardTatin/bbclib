#
# bc5-rules.mk
#

LIB = $(_LIB).lib

$(ODIR)/%.o: src/%.c
	$(CC) $(ALLFLAGS) -o$(subst /,\\,$@) $(subst /,\\,$<)

$(ODIR)/%.o: tests/%.c
	$(CC) $(ALLFLAGS) -o$(subst /,\\,$@) $(subst /,\\,$<)

$(ODIR)/%.o: structures/%.c
	$(CC) $(subst /,\\,$<) $(ALLFLAGS) -fo=$(subst /,\\,$@)

$(LIB): $(LOBJS)
	$(AR) $@ $(subst $(ODIR)/,-+$(ODIR)\\,$(LOBJS))
	
$(EXE): $(OBJS)
	echo "NAME $@" > watcom.lk1
	echo "SYSTEM nt" >> watcom.lk1
	echo "FILE {$(OBJS)}" >> watcom.lk1
	echo "LIBFILE $(LIB)" >> watcom.lk1
	$(LD) d all op m op maxe=25 op symf @watcom.lk1
