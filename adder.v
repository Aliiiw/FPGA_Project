module adder #(
    parameter Q = 15,
    parameter N = 32
    )
    (
        input  wire [N-1:0] a,
        input  wire [N-1:0] b,
        output wire [N-1:0] c
    );

    reg [N-1:0] result;

    assign c = result;

    always @(a, b) begin
        if (a[N-1] == b[N-1]) begin
            result[N-2:0] = a[N-2:0] + b[N-2:0];
            result[N-1] = a[N-1];
        end else if (a[N-1] == 0 && b[N-1] == 1) begin
            if (a[N-2:0] > b[N-2:0]) begin
                result[N-2:0] = a[N-2:0] - b[N-2:0];
                result[N-1] = 0;
            end else begin
                result[N-2:0] = b[N-2:0] - a[N-2:0];
                result[N-1] = (result[N-2:0] == 0) ? 0 : 1;
            end
        end else begin
            if (a[N-2:0] > b[N-2:0]) begin
                result[N-2:0] = a[N-2:0] - b[N-2:0];
                result[N-1] = (result[N-2:0] == 0) ? 0 : 1;
            end else begin
                result[N-2:0] = b[N-2:0] - a[N-2:0];
                result[N-1] = 0;
            end
        end
    end

endmodule
