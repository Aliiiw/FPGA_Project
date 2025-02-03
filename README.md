# FPGA_Project
this is the fpga poject implementing tanh using cordic and mlp


## Compilation

To compile the project, follow these steps:

1. Install verilator, flex, bison, systemC and gcc

2. Execute verilator to generate obj_dir:
   ```bash
   make -C obj_dir -f Vcordic.mk Vcordic
   ```

3. Run the simulation which is cpp file (this is the test for tanh simulation):
   ```bash
   ./obj_dir/Vcordic 0.5   
   ```


## Change
if you want to write another test you sholud change make file to work with your system architecture(now is for m1 chips) and run the (make clean) and again run make
