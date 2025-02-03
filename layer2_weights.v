module layer2_weights (
    input [7:0] addr,
    output reg [19:0] dout
);

    reg [19:0] ram [255:0]; // 256 x 20-bit weights

    initial begin
        ram[0] = 20'h13333;
        ram[1] = 20'hB3333;
        ram[2] = 20'h20000;
        ram[3] = 20'h9999A;
        ram[4] = 20'h1999A;
        ram[5] = 20'h93333;
        ram[6] = 20'h26666;
        ram[7] = 20'hB999A;
        ram[8] = 20'h0CCCD;
        ram[9] = 20'h8CCCD;
        ram[10] = 20'h1999A;
        ram[11] = 20'hA0000;
        ram[12] = 20'h33333;
        ram[13] = 20'h86666;
        ram[14] = 20'h2CCCD;
    end

    always @(*) begin
        dout = ram[addr];
    end

endmodule
