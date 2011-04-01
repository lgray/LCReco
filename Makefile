#Path to project directory
PROJECT_DIR = YOUR_PATH_HERE

#Paths to project dependencies
PANDORAPFANEW_DIR = YOUR_PATH_HERE
PANDORAMONITORING_DIR = YOUR_PATH_HERE

PROJECT_INCLUDE_DIR = $(PROJECT_DIR)/include/
PROJECT_SOURCE_DIR  = $(PROJECT_DIR)/src/
PROJECT_BINARY_DIR  = $(PROJECT_DIR)/bin/

INCLUDES  = -I$(PROJECT_INCLUDE_DIR)
INCLUDES += -I$(PANDORAPFANEW_DIR)/Framework/include/
INCLUDES += -I$(PANDORAPFANEW_DIR)/FineGranularityContent/include/ -I$(PANDORAPFANEW_DIR)/KMeansContent/include/
ifdef MONITORING
    INCLUDES += -I$(shell $(ROOTSYS)/bin/root-config --incdir)
    INCLUDES += -I$(PANDORAMONITORING_DIR)/include/
endif

CC = gcc
CFLAGS = -c -Wall -g -w -fPIC
CFLAGS += $(INCLUDES)
ifdef MONITORING
    CFLAGS += -DMONITORING
endif
ifdef BUILD_32BIT_COMPATIBLE
    CFLAGS += -m32
endif

SOURCES = $(wildcard $(PROJECT_SOURCE_DIR)*.cc)

OBJECTS = $(SOURCES:.cc=.o)

LIBS  = -L$(PANDORAPFANEW_DIR)/lib -lPandoraFramework -lPandoraFineGranularityContent -lPandoraKMeansContent
ifdef MONITORING
    LIBS += $(shell $(ROOTSYS)/bin/root-config --glibs)
    LIBS += -L$(PANDORAMONITORING_DIR)/lib -lPandoraMonitoring
endif
ifdef BUILD_32BIT_COMPATIBLE
    LIBS += -m32
endif

LDFLAGS = $(LIBS) -Wl,-rpath

all: $(OBJECTS) PandoraInterface

PandoraInterface:
	@echo Creating binary: $(PROJECT_BINARY_DIR)/PandoraInterface
	$(CC) $(INCLUDES) $(LIBS) $(OBJECTS) -o $(PROJECT_BINARY_DIR)/PandoraInterface
	@echo Created binary: $(PROJECT_BINARY_DIR)/PandoraInterface

.cc.o:
	$(CC) $(CFLAGS) $(DEFINES) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(PROJECT_BINARY_DIR)/PandoraInterface
