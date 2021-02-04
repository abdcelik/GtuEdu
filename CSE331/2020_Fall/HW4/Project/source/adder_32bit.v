module adder_32bit(input [31:0] in1, input [31:0] in2, input carry_in, output [31:0] out, output carry_out);
	wire C;
	
	adder_16bit add1(in1[15:0], in2[15:0], carry_in, out[15:0], C);
	adder_16bit add2(in1[31:16], in2[31:16], C, out[31:16], carry_out);
endmodule