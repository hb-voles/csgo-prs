dist_doc_DATA = AUTHORS ChangeLog COPYING INSTALL LICENSE NEWS README

ACLOCAL_AMFLAGS = -I build-aux/m4 -Wall -Werror

if DEBUG
    AM_CPPFLAGS = -g3 -O0 -DDEBUG
else
    AM_CPPFLAGS = -O2 $(PROTOBUF_OPT_FLAG)
endif

if RELPROTOPATH
    PROTOPATH = ../src/protobuffs
    AM_CPPFLAGS += -Isrc/
else
    PROTOPATH = src/protobuffs
endif


bin_PROGRAMS = \
	csgoprs


csgoprs_SOURCES = \
	src/demofile.cc	\
	src/main.cc

nodist_csgoprs_SOURCES = \
	src/protobuffs/cstrike15_gcmessages.pb.cc src/protobuffs/cstrike15_gcmessages.pb.h \
	src/protobuffs/cstrike15_usermessages_public.pb.cc src/protobuffs/cstrike15_usermessages_public.pb.h \
	src/protobuffs/netmessages_public.pb.cc src/protobuffs/netmessages_public.pb.h \
	src/protobuffs/steammessages.pb.cc src/protobuffs/steammessages.pb.h

csgoprs_LDFLAGS = \
	$(PTHREAD_CFLAGS) \
	${PROTOBUF_CFLAGS}

csgoprs_LDADD = \
	$(PTHREAD_LIBS) \
	${PROTOBUF_LIBS}


src/protobuffs/%.pb.cc src/protobuffs/%.pb.h: src/protobuffs/%.proto
	$(PROTOC) --proto_path=${PROTOPATH} --cpp_out=${PROTOPATH} $^

dist_noinst_DATA = \
	src/protobuffs/cstrike15_gcmessages.proto \
	src/protobuffs/cstrike15_usermessages_public.proto \
	src/protobuffs/netmessages_public.proto \
	src/protobuffs/steammessages.proto

BUILT_SOURCES = \
	src/protobuffs/cstrike15_gcmessages.pb.cc \
	src/protobuffs/cstrike15_gcmessages.pb.h \
	src/protobuffs/cstrike15_usermessages_public.pb.cc \
	src/protobuffs/cstrike15_usermessages_public.pb.h \
	src/protobuffs/netmessages_public.pb.cc \
	src/protobuffs/netmessages_public.pb.h \
	src/protobuffs/steammessages.pb.cc \
	src/protobuffs/steammessages.pb.h

MOSTLYCLEANFILES = \
	${PROTOPATH}/cstrike15_gcmessages.pb.cc \
	${PROTOPATH}/cstrike15_gcmessages.pb.h \
	${PROTOPATH}/cstrike15_usermessages_public.pb.cc \
	${PROTOPATH}/cstrike15_usermessages_public.pb.h \
	${PROTOPATH}/netmessages_public.pb.cc \
	${PROTOPATH}/netmessages_public.pb.h \
	${PROTOPATH}/steammessages.pb.cc \
	${PROTOPATH}/steammessages.pb.h

