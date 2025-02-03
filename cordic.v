module cordic (
    input wire clk,        
    input wire reset,      
    input wire calc_mode,
    input wire start,       
    input wire signed [19:0] x_0,
    input wire signed [19:0] y_0,
    input wire signed [19:0] z_0,
    
    output reg busy,       
    output reg signed [20:0] x,
    output reg signed [20:0] y,
    output reg signed [20:0] z
);

reg [3:0] iter_count;
reg [20:0] x_out, y_out, z_out;

cordic_calc cordic_ins (iter_count, calc_mode, x, y, z, x_out, y_out, z_out);

localparam IDLE = 1;
localparam CALC = 2;
reg [1:0] state = IDLE;

always @ (posedge clk) begin
    if (reset) begin
        state <= IDLE;
        busy <= 1;
        x = 0;
        y = 0;
        z = 0;
        iter_count <= 0;
    end else begin
        case (state)
            IDLE: begin
                if (start) begin
                    busy <= 1;
                    state <= CALC;
                    iter_count <= 0;
                    x = {x_0[19], x_0};
                    y = {y_0[19], y_0};
                    z = {z_0[19], z_0};
                end
            end
            CALC: begin
                if (iter_count == 15) begin
                    busy <= 0;
                    state <= IDLE;
                end else begin
                    iter_count <= iter_count + 1;
                    x = x_out;
                    y = y_out;
                    z = z_out;
                end
            end
        endcase
    end
end

endmodule