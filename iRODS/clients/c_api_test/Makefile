include ../../config/external_versions.txt

ifndef buildDir
buildDir =      $(CURDIR)/../..
endif

include $(buildDir)/config/config.mk
include $(buildDir)/config/platform.mk
include $(buildDir)/config/directories.mk
include $(buildDir)/config/common.mk

GCC = gcc

ifeq ($(IRODS_BUILD_COVERAGE), 1)
GCC += -fprofile-arcs -ftest-coverage -lgcov
endif

CFLAGS = -I../../lib/core/include/ \
	-I../../lib/api/include/ \
	-I../../lib/hasher/include/ \
	-I../../server/icat/include/ \
	-I../../server/re/include/ \
	-I../../server/core/include/

BOOST_LIBS = $(BOOST_DIR)/stage/lib/libboost_system.a \
	$(BOOST_DIR)/stage/lib/libboost_filesystem.a \
	$(BOOST_DIR)/stage/lib/libboost_regex.a \
	$(BOOST_DIR)/stage/lib/libboost_thread.a \
	$(BOOST_DIR)/stage/lib/libboost_chrono.a \
	$(BOOST_DIR)/stage/lib/libboost_program_options.a

LDFLAGS = $(LIBRARY) $(LIB_CLIENT_EXEC) $(BOOST_LIBS)

# include jansson for zonereport
CFLAGS += -I../../../external/$(JANSSONVERSION)/src/
LDFLAGS += ../../../external/$(JANSSONVERSION)/src/.libs/libjansson.a

# include for control plane
CFLAGS += -I../../../external/$(ZEROMQVERSION)/include/
LDFLAGS += ../../../external/$(ZEROMQVERSION)/src/.libs/libzmq.a

CFLAGS += -I../../../external/$(AVROVERSION)
LDFLAGS += ../../../external/$(AVROVERSION)/build/libavrocpp_s.a

# include miscellaneous
LDFLAGS += -lz -lssl -lcrypto -ldl -lpthread -lm

# include realtime library except for macosx (already included)
ifneq (${OS_platform}, osx_platform)
LDFLAGS += -lrt
endif

# include c++ standard library linkage
LDFLAGS += -lstdc++

# make all symbols available for dynamic linking
LDFLAGS += -rdynamic

default:
	$(V_at)$(GCC) $(CFLAGS) -o mytest test.c $(LDFLAGS)

clean:
	@echo "Cleaning C API test..."
	@rm -f mytest
	@rm -f *.o
	@rm -f *~
