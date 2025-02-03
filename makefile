CXX = g++
VERILATOR = verilator
VERILATOR_ROOT = $(shell verilator -V | grep VERILATOR_ROOT | head -1 | awk '{ print $$3 }')
VINC = $(VERILATOR_ROOT)/include

# Compiler flags (add -arch arm64)
CXXFLAGS = -std=c++11 -Wall -arch arm64 -I$(VINC) -I$(VINC)/vltstd -I./obj_dir

# Linker flags - add verilated library and -arch arm64
LDFLAGS = -L$(VERILATOR_ROOT)/include -arch arm64

# Warning flags for verilator
VERILATOR_FLAGS = -Wno-fatal -Wno-BLKSEQ -Wno-COMBDLY -Wno-LATCH -Wno-SYNCASYNCNET -Wno-UNUSED -Wno-EOFNEWLINE -Wno-PINCONNECTEMPTY

all: test_mlp

# Compile and link the test program
test_mlp: test_mlp.cpp verilate
	$(CXX) $(CXXFLAGS) \
		test_mlp.cpp \
		obj_dir/Vmlp_network__ALL.a \
		$(VINC)/verilated.cpp \
		-o $@

# Run verilator to create the model
verilate:
	$(VERILATOR) $(VERILATOR_FLAGS) --cc --exe --build mlp_network.v test_mlp.cpp -CFLAGS "-arch arm64" -LDFLAGS "-arch arm64"

clean:
	rm -rf obj_dir test_mlp

.PHONY: all clean verilate
