module multiplier #(
    parameter Q = 15,   
    parameter N = 32    
)(
    input  wire [N-1:0] i_multiplicand,
    input  wire [N-1:0] i_multiplier,
    output reg  [N-1:0] o_result,
    output reg          ovr
);

    wire signed [N-1:0] a = i_multiplicand;
    wire signed [N-1:0] b = i_multiplier;

    wire signed [2*N-1:0] full_product = a * b;

    wire signed [2*N-1:0] round_const = full_product[2*N-1] ? -(1'b1 << (Q-1)) : (1'b1 << (Q-1));
    
    wire signed [2*N-1:0] rounded_product = full_product + round_const;
    
    wire signed [2*N-Q-1:0] shifted_product = rounded_product >>> Q;

    wire signed [N-1:0] candidate = shifted_product[N-1:0];

    localparam EXTRA = (2*N - Q) - N;  
    
    wire [EXTRA-1:0] upper_bits = shifted_product[2*N-Q-1:N];
    wire [EXTRA-1:0] sign_extension = {EXTRA{candidate[N-1]}};

    always @(*) begin
        o_result = candidate;
        ovr = (upper_bits != sign_extension);
    end

endmodule