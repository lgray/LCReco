#Path to project directory
PROJECT_DIR = YOUR_PATH_HERE

#Paths to project dependencies
PANDORAPFANEW_DIR = YOUR_PATH_HERE

PROJECT_INCLUDE_DIR = $(PROJECT_DIR)/include/
PROJECT_SOURCE_DIR  = $(PROJECT_DIR)/src/
PROJECT_BINARY_DIR  = $(PROJECT_DIR)/bin/

ifdef MONITORING
    DEFINES = -DMONITORING=1
endif

INCLUDES  = -I$(PROJECT_INCLUDE_DIR)
INCLUDES += -I$(PANDORAPFANEW_DIR)/PandoraSDK/include/
INCLUDES += -I$(PANDORAPFANEW_DIR)/FineGranularityContent/include/
ifdef MONITORING
    INCLUDES += -I$(shell $(ROOTSYS)/bin/root-config --incdir)
    INCLUDES += -I$(PANDORAPFANEW_DIR)/PandoraMonitoring/include/
endif

CC = g++
CFLAGS = -c -Wall -g -w -fPIC -O2
ifdef BUILD_32BIT_COMPATIBLE
    CFLAGS += -m32
endif

SOURCES = $(wildcard $(PROJECT_SOURCE_DIR)*.cc)

OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)

LIBS  = -L$(PANDORAPFANEW_DIR)/lib -lPandoraSDK-lFineGranularityContent
ifdef MONITORING
    LIBS += $(shell $(ROOTSYS)/bin/root-config --glibs)
    LIBS += -lPandoraMonitoring
endif
ifdef BUILD_32BIT_COMPATIBLE
    LIBS += -m32
endif

LDFLAGS = $(LIBS) -Wl,-rpath

all: $(OBJECTS) PandoraInterface

PandoraInterface:
	@echo Creating binary: $(PROJECT_BINARY_DIR)/PandoraInterface
	$(CC) $(LIBS) $(OBJECTS) -o $(PROJECT_BINARY_DIR)/PandoraInterface
	@echo Created binary: $(PROJECT_BINARY_DIR)/PandoraInterface

-include $(DEPENDS)

.cc.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -MP -MMD -MT $*.o -MT $*.d -MF $*.d -o $*.o $*.cc

clean:
	rm -f $(OBJECTS)
	rm -f $(DEPENDS)
	rm -f $(PROJECT_BINARY_DIR)/PandoraInterface
