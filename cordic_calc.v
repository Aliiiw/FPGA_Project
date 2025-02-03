`define HYP_ROT 0       // for sinh and cosh
`define LIN_VEC 1       // for div

module cordic_calc (
    input wire [3:0] stage_num, 
    input wire calc_mode, 
    input wire signed [20:0] x_in,      // 1 bit sign 2 bits int rest fract
    input wire signed [20:0] y_in,     
    input wire signed [20:0] z_in,     
    
    output reg signed [20:0] x_out,    
    output reg signed [20:0] y_out,    
    output reg signed [20:0] z_out     
);

reg [3:0] iter_idx;

function [3:0] hyperbolic_idx_lut([3:0] iter);
    begin
        case (iter)
            0:   hyperbolic_idx_lut = 4'd1;
            1:   hyperbolic_idx_lut = 4'd2;
            2:   hyperbolic_idx_lut = 4'd3;
            3:   hyperbolic_idx_lut = 4'd4;
            4:   hyperbolic_idx_lut = 4'd4;
            5:   hyperbolic_idx_lut = 4'd5;
            6:   hyperbolic_idx_lut = 4'd6;
            7:   hyperbolic_idx_lut = 4'd7;
            8:   hyperbolic_idx_lut = 4'd8;
            9:   hyperbolic_idx_lut = 4'd9;
            10:  hyperbolic_idx_lut = 4'd10;
            11:  hyperbolic_idx_lut = 4'd11;
            12:  hyperbolic_idx_lut = 4'd12;
            13:  hyperbolic_idx_lut = 4'd13;
            14:  hyperbolic_idx_lut = 4'd13;
            15:  hyperbolic_idx_lut = 4'd14;
        endcase
    end
endfunction

function [20:0] linear_lut([3:0] n);
    begin
        case (n)
            0:  linear_lut = 21'h3FFFF; 
            1:  linear_lut = 21'h1FFFF;
            2:  linear_lut = 21'h0FFFF;
            3:  linear_lut = 21'h07FFF;
            4:  linear_lut = 21'h03FFF;
            5:  linear_lut = 21'h01FFF;
            6:  linear_lut = 21'h00FFF;
            7:  linear_lut = 21'h007FF;
            8:  linear_lut = 21'h003FF;
            9:  linear_lut = 21'h001FF;
            10: linear_lut = 21'h000FF;
            11: linear_lut = 21'h0007F;
            12: linear_lut = 21'h0003F;
            13: linear_lut = 21'h0001F;
            14: linear_lut = 21'h0000F;
            15: linear_lut = 21'h00007;
        endcase
    end
endfunction

function [20:0] atanh_lut([3:0] n);
    begin
        case (n)
            1:  atanh_lut = 21'h232D2; 
            2:  atanh_lut = 21'h1054E; 
            3:  atanh_lut = 21'h0802A;
            4:  atanh_lut = 21'h04001;
            5:  atanh_lut = 21'h02000;
            6:  atanh_lut = 21'h01000;
            7:  atanh_lut = 21'h00800;
            8:  atanh_lut = 21'h00400;
            9:  atanh_lut = 21'h00200;
            10: atanh_lut = 21'h00100;
            11: atanh_lut = 21'h00080;
            12: atanh_lut = 21'h00040;
            13: atanh_lut = 21'h00020;
            14: atanh_lut = 21'h00010;
            default: atanh_lut = 21'h00000;
        endcase
    end
endfunction

always @(*) begin : iteration_mux
    case (calc_mode)
    `HYP_ROT: iter_idx = hyperbolic_idx_lut(stage_num);
    default: iter_idx = stage_num;
    endcase
end

reg [20:0] e_lut;

always @(*) begin : lut_mux
    case (calc_mode)
    `LIN_VEC: e_lut = linear_lut(iter_idx);
    `HYP_ROT: e_lut = atanh_lut(iter_idx);
    default: e_lut = atanh_lut(iter_idx);
    endcase
end

wire d_pos_rot = (z_in[20] == 0) ? 1 : 0;
wire d_pos_vec = (y_in[20] == 1) ? 1 : 0;
wire d_flag = (~calc_mode) ? d_pos_rot : d_pos_vec;

always @(*) begin : cordic_calculation
    if (d_flag) begin
        case (calc_mode)
        `LIN_VEC: x_out = x_in;
        `HYP_ROT: x_out = x_in + (y_in >>> iter_idx);
        default: x_out = x_in - (y_in >>> iter_idx);
        endcase

        y_out = y_in + (x_in >>> iter_idx);
        z_out = z_in - e_lut;
    end else begin
        case (calc_mode)
        `LIN_VEC: x_out = x_in;
        `HYP_ROT: x_out = x_in - (y_in >>> iter_idx);
        default: x_out = x_in + (y_in >>> iter_idx);
        endcase

        y_out = y_in - (x_in >>> iter_idx);
        z_out = z_in + e_lut;
    end
end

endmodule