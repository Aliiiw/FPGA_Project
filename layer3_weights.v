module layer3_weights (
    input [7:0] addr,
    output reg [19:0] dout
);

    reg [19:0] ram [255:0]; // 256 x 20-bit weights

    initial begin
        ram[0] = 20'h06666;
        ram[1] = 20'hACCCD;
        ram[2] = 20'h0CCCD;
    end

    always @(*) begin
        dout = ram[addr];
    end

endmodule
