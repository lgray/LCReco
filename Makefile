#Path to project directory
ifndef PROJECT_DIR
    PROJECT_DIR = YOUR_PATH_HERE
endif

#Paths to project dependencies
ifndef PANDORA_DIR
    PANDORA_DIR = YOUR_PATH_HERE
endif

ifndef PANDORA_LARCONTENT_DIR
    PANDORA_LARCONTENT_DIR = YOUR_PATH_HERE
endif

ifdef MONITORING
    DEFINES = -DMONITORING=1
endif

PROJECT_INCLUDE_DIR = $(PROJECT_DIR)/include/
PROJECT_SOURCE_DIR  = $(PROJECT_DIR)/src/
PROJECT_BINARY_DIR  = $(PROJECT_DIR)/bin/

INCLUDES  = -I $(PROJECT_INCLUDE_DIR)
INCLUDES += -I $(PANDORA_DIR)/PandoraSDK/include/
INCLUDES += -I $(PANDORA_DIR)/FineGranularityContent/include/
ifdef MONITORING
    INCLUDES += -I$(shell root-config --incdir)
    INCLUDES += -I$(PANDORA_DIR)/PandoraMonitoring/include/
endif

CC = g++
CFLAGS = -c -Wall -g -w -fPIC -O2
ifdef BUILD_32BIT_COMPATIBLE
    CFLAGS += -m32
endif

SOURCES = $(wildcard $(PROJECT_SOURCE_DIR)/*.cc)

OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)

LIBS  = -L$(PANDORA_DIR)/lib -lPandoraSDK -lFineGranularityContent
ifdef MONITORING
    LIBS += $(shell root-config --glibs --evelibs)
    LIBS += -lPandoraMonitoring
endif
ifdef BUILD_32BIT_COMPATIBLE
    LIBS += -m32
endif

LDFLAGS  = $(shell root-config --auxcflags)
LDFLAGS += $(LIBS) -Wl,-rpath

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
