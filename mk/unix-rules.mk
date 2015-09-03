#
# unix-rules.mk
#

LIB = lib$(_LIB).a

$(ODIR)/%.o: src/%.c
	$(CC) $(ALLFLAGS) -c $< -o $@

$(ODIR)/%.o: tests/%.c
	$(CC) $(ALLFLAGS) -c $< -o $@

$(ODIR)/%.o: structures/%.c
	$(CC) $(ALLFLAGS) -c $< -o $@

$(LIB): $(LOBJS)
	$(AR) $(ARFLAGS) $@ $(LOBJS)
	
$(EXE): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -L. -l$(_LIB) -o $@