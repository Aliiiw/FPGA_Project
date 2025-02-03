module mlp_network (
    input wire clk,
    input wire reset,
    input wire start,
    input wire signed [19:0] network_inputs [2:0],
    output reg network_busy,
    output reg network_output
);

    localparam LAYER1_SIZE = 5;  // 5 neurons, each with 3 weights
    localparam LAYER2_SIZE = 3;  // 3 neurons, each with 5 weights
    localparam LAYER3_SIZE = 3;  // For the output neuron, 3 weights

    reg [3:0] network_state;
    reg [3:0] next_state;
    localparam IDLE         = 0;
    localparam LAYER1_START = 1;
    localparam LAYER1_WAIT  = 2;
    localparam LAYER2_START = 3;
    localparam LAYER2_WAIT  = 4;
    localparam LAYER3_START = 5;
    localparam LAYER3_WAIT  = 6;
    localparam OUTPUT_READY = 7;

    wire signed [19:0] weight1 [0:14];
    genvar j;
    generate
        for(j = 0; j < 15; j = j + 1) begin : layer1_weight_inst
            layer1_weights lw_inst (
                .addr(j),
                .dout(weight1[j])
            );
        end
    endgenerate

    wire signed [19:0] weights_1 [4:0][2:0];
    assign weights_1[0] = { weight1[0],  weight1[1],  weight1[2]  };
    assign weights_1[1] = { weight1[3],  weight1[4],  weight1[5]  };
    assign weights_1[2] = { weight1[6],  weight1[7],  weight1[8]  };
    assign weights_1[3] = { weight1[9],  weight1[10], weight1[11] };
    assign weights_1[4] = { weight1[12], weight1[13], weight1[14] };

    
    wire signed [19:0] weight2 [0:14];
    generate
        for(j = 0; j < 15; j = j + 1) begin : layer2_weight_inst
            layer2_weights lw2_inst (
                .addr(j),
                .dout(weight2[j])
            );
        end
    endgenerate

    wire signed [19:0] weights_2 [2:0][4:0];
    assign weights_2[0] = { weight2[0],  weight2[1],  weight2[2],  weight2[3],  weight2[4]  };
    assign weights_2[1] = { weight2[5],  weight2[6],  weight2[7],  weight2[8],  weight2[9]  };
    assign weights_2[2] = { weight2[10], weight2[11], weight2[12], weight2[13], weight2[14] };

    wire signed [19:0] weight3 [0:2];
    generate
        for(j = 0; j < 3; j = j + 1) begin : layer3_weight_inst
            layer3_weights lw3_inst (
                .addr(j),
                .dout(weight3[j])
            );
        end
    endgenerate

    wire signed [19:0] weights_3 [2:0];
    assign weights_3[0] = weight3[0];
    assign weights_3[1] = weight3[1];
    assign weights_3[2] = weight3[2];

    wire signed [19:0] layer1_outputs [LAYER1_SIZE-1:0];
    wire signed [19:0] layer2_outputs [LAYER2_SIZE-1:0];
    wire signed [19:0] final_layer_output;
    
    wire [LAYER1_SIZE-1:0] layer1_busy;
    wire [LAYER2_SIZE-1:0] layer2_busy;
    wire output_neuron_busy;
    reg [LAYER1_SIZE-1:0] layer1_start;
    reg [LAYER2_SIZE-1:0] layer2_start;
    reg output_neuron_start;

    reg [5:0] wait_counter;
    localparam WAIT_CYCLES = 32;

    always @(*) begin
        next_state = network_state;
        case (network_state)
            IDLE: 
                if (start) next_state = LAYER1_START;
            
            LAYER1_START: 
                next_state = LAYER1_WAIT;
            
            LAYER1_WAIT: 
                if (wait_counter == 0 && layer1_busy == 0) 
                    next_state = LAYER2_START;
            
            LAYER2_START: 
                next_state = LAYER2_WAIT;
            
            LAYER2_WAIT: 
                if (wait_counter == 0 && layer2_busy == 0) 
                    next_state = LAYER3_START;
            
            LAYER3_START: 
                next_state = LAYER3_WAIT;
            
            LAYER3_WAIT: 
                if (wait_counter == 0 && !output_neuron_busy) 
                    next_state = OUTPUT_READY;
            
            OUTPUT_READY: 
                next_state = IDLE;
        endcase
    end

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            network_state        <= IDLE;
            network_busy         <= 0;
            layer1_start         <= 0;
            layer2_start         <= 0;
            output_neuron_start  <= 0;
            network_output       <= 0;
            wait_counter         <= 0;
        end else begin
            network_state <= next_state;
            
            case (network_state)
                IDLE: begin
                    if (start)
                        network_busy <= 1;
                end

                LAYER1_START: begin
                    layer1_start <= {LAYER1_SIZE{1'b1}};
                    wait_counter <= WAIT_CYCLES;
                end

                LAYER1_WAIT: begin
                    layer1_start <= 0;
                    if (wait_counter > 0)
                        wait_counter <= wait_counter - 1;
                end

                LAYER2_START: begin
                    layer2_start <= {LAYER2_SIZE{1'b1}};
                    wait_counter <= WAIT_CYCLES;
                end

                LAYER2_WAIT: begin
                    layer2_start <= 0;
                    if (wait_counter > 0)
                        wait_counter <= wait_counter - 1;
                end

                LAYER3_START: begin
                    output_neuron_start <= 1;
                    wait_counter <= WAIT_CYCLES;
                end

                LAYER3_WAIT: begin
                    output_neuron_start <= 0;
                    if (wait_counter > 0)
                        wait_counter <= wait_counter - 1;
                end

                OUTPUT_READY: begin
                    network_output <= !final_layer_output[19];
                    network_busy   <= 0;
                end
            endcase
        end
    end

    
    genvar i;
    generate
        for (i = 0; i < LAYER1_SIZE; i = i + 1) begin : L1_NEURONS
            single_neuron #(
                .INPUT_SIZE(3)
            ) neuron (
                .clk(clk),
                .reset(reset),
                .start(layer1_start[i]),
                .inputs(network_inputs),
                .weights(weights_1[i]),  // Each neuron gets its 3 weights from ROM
                .busy(layer1_busy[i]),
                .output_value(layer1_outputs[i])
            );
        end
    endgenerate

    generate
        for (i = 0; i < LAYER2_SIZE; i = i + 1) begin : L2_NEURONS
            single_neuron #(
                .INPUT_SIZE(5)
            ) neuron (
                .clk(clk),
                .reset(reset),
                .start(layer2_start[i]),
                .inputs(layer1_outputs),
                .weights(weights_2[i]),  // Each neuron gets its 5 weights from ROM
                .busy(layer2_busy[i]),
                .output_value(layer2_outputs[i])
            );
        end
    endgenerate

    single_neuron #(
        .INPUT_SIZE(3)
    ) output_neuron (
        .clk(clk),
        .reset(reset),
        .start(output_neuron_start),
        .inputs(layer2_outputs),
        .weights(weights_3),  // Output neuron weights from ROM
        .busy(output_neuron_busy),
        .output_value(final_layer_output)
    );

endmodule
