dist_doc_DATA = AUTHORS ChangeLog COPYING INSTALL LICENSE NEWS README

ACLOCAL_AMFLAGS = -I build-aux/m4 -Wall -Werror

if DEBUG
    AM_CPPFLAGS = -g3 -O0 -DDEBUG
else
    AM_CPPFLAGS = -O2 $(PROTOBUF_OPT_FLAG)
endif

if RELPROTOPATH
    PROTOPATH = ../src/protobuffs
else
    PROTOPATH = src/protobuffs
endif


bin_PROGRAMS = \
	csgoprs


csgoprs_SOURCES = \
	src/demofile.cc	\
	src/main.cc

nodist_csgoprs_SOURCES = \
	src/cstrike15_gcmessages.pb.cc src/cstrike15_gcmessages.pb.h \
	src/cstrike15_usermessages_public.pb.cc src/cstrike15_usermessages_public.pb.h \
	src/netmessages_public.pb.cc src/netmessages_public.pb.h \
	src/steammessages.pb.cc src/steammessages.pb.h

csgoprs_LDFLAGS = \
	$(PTHREAD_CFLAGS) \
	${PROTOBUF_CFLAGS}

csgoprs_LDADD = \
	$(PTHREAD_LIBS) \
	${PROTOBUF_LIBS}


src/%.pb.cc src/%.pb.h: src/protobuffs/%.proto
	$(PROTOC) --proto_path=${PROTOPATH} --cpp_out=src $^

dist_noinst_DATA = \
	src/protobuffs/cstrike15_gcmessages.proto \
	src/protobuffs/cstrike15_usermessages_public.proto \
	src/protobuffs/netmessages_public.proto \
	src/protobuffs/steammessages.proto

BUILT_SOURCES = \
	src/cstrike15_gcmessages.pb.cc \
	src/cstrike15_gcmessages.pb.h \
	src/cstrike15_usermessages_public.pb.cc \
	src/cstrike15_usermessages_public.pb.h \
	src/netmessages_public.pb.cc \
	src/netmessages_public.pb.h \
	src/steammessages.pb.cc \
	src/steammessages.pb.h

MOSTLYCLEANFILES = \
	src/cstrike15_gcmessages.pb.cc \
	src/cstrike15_gcmessages.pb.h \
	src/cstrike15_usermessages_public.pb.cc \
	src/cstrike15_usermessages_public.pb.h \
	src/netmessages_public.pb.cc \
	src/netmessages_public.pb.h \
	src/steammessages.pb.cc \
	src/steammessages.pb.h
