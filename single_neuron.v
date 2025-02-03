module single_neuron #(parameter INPUT_SIZE = 4) (
    input wire clk,
    input wire reset,
    input wire start,
    input wire signed [19:0] inputs [INPUT_SIZE-1:0],
    input wire signed [19:0] weights [INPUT_SIZE-1:0],
    output reg busy,
    output reg signed [19:0] output_value
);

    localparam STATE_IDLE        = 0;
    localparam STATE_ACCUMULATE  = 1;
    localparam STATE_TRIGGER_ACT = 2;
    localparam STATE_DEASSERT    = 3;
    localparam STATE_WAIT_RESULT = 4;

    reg [3:0] state;
    reg signed [19:0] act_input;
    wire busy_tanh;
    wire signed [19:0] tanh_result;
    reg start_act;

    // Accumulator for weighted sum
    reg signed [19:0] accumulator;

    integer index;

    // Wires for multiplier and adder outputs
    wire signed [19:0] prod;
    wire signed [19:0] sum_out;

    multiplier #(.Q(18), .N(20)) mult_inst (
        .i_multiplicand(inputs[index]),
        .i_multiplier(weights[index]),
        .o_result(prod),
        .ovr() // Overflow signal not used
    );

    adder #(.Q(18), .N(20)) add_inst (
        .a(accumulator),
        .b(prod),
        .c(sum_out)
    );

    cordic_tanh act_module (
        .clk(clk),
        .reset(reset),
        .start(start_act),
        .input_angle(act_input),
        .busy(busy_tanh),
        .tanh_value(tanh_result)
    );

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state         <= STATE_IDLE;
            busy          <= 0;
            accumulator   <= 0;
            index         <= 0;
            start_act     <= 0;
            output_value  <= 0;
        end else begin
            case (state)
                STATE_IDLE: begin
                    if (start) begin
                        accumulator <= 0;
                        index       <= 0;
                        busy        <= 1;
                        state       <= STATE_ACCUMULATE;
                    end
                end

                STATE_ACCUMULATE: begin
                    accumulator <= sum_out;
                    if (index == INPUT_SIZE - 1)
                        state <= STATE_TRIGGER_ACT;
                    else
                        index <= index + 1;
                end

                STATE_TRIGGER_ACT: begin
                    act_input   <= accumulator;
                    start_act   <= 1;
                    state       <= STATE_DEASSERT;
                end

                STATE_DEASSERT: begin
                    start_act   <= 0;
                    state       <= STATE_WAIT_RESULT;
                end

                STATE_WAIT_RESULT: begin
                    if (!busy_tanh) begin
                        output_value <= tanh_result;
                        busy         <= 0;
                        state        <= STATE_IDLE;
                    end
                end

                default: state <= STATE_IDLE;
            endcase
        end
    end
endmodule
