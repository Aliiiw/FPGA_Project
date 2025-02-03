module layer1_weights (
    input [7:0] addr,
    output reg [19:0] dout
);

    reg [19:0] ram [255:0]; // 256 x 20-bit weights

    initial begin
        ram[0] = 20'h0CCCD;
        ram[1] = 20'hA6666;
        ram[2] = 20'h06666;
        ram[3] = 20'hA0000;
        ram[4] = 20'h2CCCD;
        ram[5] = 20'h9999A;
        ram[6] = 20'h33333;
        ram[7] = 20'hB999A;
        ram[8] = 20'h13333;
        ram[9] = 20'hACCCD;
        ram[10] = 20'h3999A;
        ram[11] = 20'h8CCCD;
        ram[12] = 20'h26666;
        ram[13] = 20'hB3333;
        ram[14] = 20'h20000;
    end

    always @(*) begin
        dout = ram[addr];
    end

endmodule
