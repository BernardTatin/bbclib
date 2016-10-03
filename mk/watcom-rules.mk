#
# watcom-rules.mk
#

LIB = $(_LIB).lib

$(ODIR)/%.o: src/%.c
	$(CC) $(subst /,\\,$<) $(ALLFLAGS) -fo=$(subst /,\\,$@)

$(ODIR)/%.o: src/tests/%.c
	$(CC) $(subst /,\\,$<) $(ALLFLAGS) -fo=$(subst /,\\,$@)

$(ODIR)/%.o: src/structures/%.c
	$(CC) $(subst /,\\,$<) $(ALLFLAGS) -fo=$(subst /,\\,$@)

$(LIB): $(LOBJS)
	$(AR) $@ $(subst $(ODIR)/,-+$(ODIR)\\,$(LOBJS))
	
$(EXE): $(OBJS)
	echo "NAME $@" > $(compiler).lk1
	echo "SYSTEM nt" >> $(compiler).lk1
	echo "FILE {$(OBJS)}" >> $(compiler).lk1
	echo "LIBFILE $(LIB)" >> $(compiler).lk1
	$(LD) d all op m op maxe=25 op symf @$(compiler).lk1