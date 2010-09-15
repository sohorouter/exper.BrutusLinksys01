PROG=brutus_linksys
OBJS=obj/brutuslinksys.o obj/socket_client.o obj/base64.o

GCC=/usr/bin/gcc
CFLAGS=-g -O0 -I include
LDFLAGS=


all : make_obj_dir $(PROG)
		rm -rf obj

make_obj_dir :
	mkdir -p obj

clean :
	rm -rf obj

distclean : clean
	rm -f $(PROG)


$(PROG)	:	$(OBJS)
	$(GCC) $(LDFLAGS) -o $(PROG) $(OBJS)

$(OBJS) : obj/%.o : src/%.c
	$(GCC) $(CFLAGS) -c $< -o $@
