`define HYP_ROT 0
`define LIN_VEC 1

module cordic_tanh (
    input wire clk,      // we want to know how many times sholud be run
    input wire reset,
    input wire start,
    input wire signed [19:0] input_angle,
    output reg busy,
    output reg signed [19:0] tanh_value
);
    localparam IDLE = 3'd0;
    localparam START_HYPERBOLIC = 3'd1;
    localparam WAIT_HYPERBOLIC = 3'd2;
    localparam CAPTURE = 3'd6; // for knowing sinh and cosh be calculated
    localparam START_LINEAR = 3'd3;
    localparam WAIT_LINEAR = 3'd4;
    localparam DONE = 3'd5;
    
    localparam signed [19:0] K_INVERSE = 20'h0D413;   //with python
    
    reg [2:0] state, next_state;
    reg signed [20:0] sinh_value, cosh_value;
    reg start_hyperbolic, start_linear;

    wire busy_cordic, busy_linear;
    wire signed [20:0] x_cordic, y_cordic, z_cordic;
    wire signed [20:0] x_linear, y_linear, z_linear;

    cordic cordic_hyp_rot (
        .clk(clk),
        .reset(reset),
        .calc_mode(`HYP_ROT),
        .start(start_hyperbolic),
        .x_0(20'h7FFFF),
        .y_0(20'h00000),
        .z_0(input_angle),
        .busy(busy_cordic),
        .x(x_cordic),
        .y(y_cordic),
        .z(z_cordic)
    );

    cordic cordic_lin_vec (
        .clk(clk),
        .reset(reset),
        .calc_mode(`LIN_VEC),
        .start(start_linear),
        .x_0(cosh_value[20:1]),
        .y_0(sinh_value[20:1]),
        .z_0(20'h00000),
        .busy(busy_linear),
        .x(x_linear),
        .y(y_linear),
        .z(z_linear)
    );

    always @(*) begin
        next_state = state;
        start_hyperbolic = 0;
        start_linear = 0;

        case (state)
            IDLE: begin
                if (start)
                    next_state = START_HYPERBOLIC;
            end
            
            START_HYPERBOLIC: begin
                start_hyperbolic = 1;
                next_state = WAIT_HYPERBOLIC;
            end
            
            WAIT_HYPERBOLIC: begin
                if (!busy_cordic)
                    next_state = CAPTURE;
            end
            
            CAPTURE: begin
                next_state = START_LINEAR;
            end
            
            START_LINEAR: begin
                start_linear = 1;
                next_state = WAIT_LINEAR;
            end
            
            WAIT_LINEAR: begin
                if (!busy_linear)
                    next_state = DONE;
            end
            
            DONE: begin
                next_state = IDLE;
            end
            
            default: next_state = IDLE;
        endcase
    end

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= IDLE;
            busy <= 1;
            sinh_value <= 0;
            cosh_value <= 0;
            tanh_value <= 0;
        end else begin
            state <= next_state;
            
            case (state)
                IDLE: begin
                    if (start)
                        busy <= 1;
                end
                
                CAPTURE: begin
                    sinh_value <= (y_cordic * K_INVERSE) >>> 18;    //fixed points
                    cosh_value <= (x_cordic * K_INVERSE) >>> 18;
                end
                
                WAIT_LINEAR: begin
                    if (!busy_linear) begin
                        tanh_value <= z_linear[20:1];   //sign bit not important
                    end
                end
                
                DONE: begin
                    busy <= 0;
                end

                default: begin
                    // Default assignments to prevent latches
                    sinh_value <= sinh_value;
                    cosh_value <= cosh_value;
                end
            endcase
        end
    end

endmodule
