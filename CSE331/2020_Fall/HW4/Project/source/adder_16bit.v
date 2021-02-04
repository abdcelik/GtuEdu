module adder_16bit(input [15:0] in1, input [15:0] in2, input carry_in, output [15:0] out, output carry_out);
	wire C;
	
	adder_8bit add1(in1[7:0], in2[7:0], carry_in, out[7:0], C);
	adder_8bit add2(in1[15:8], in2[15:8], C, out[15:8], carry_out);
endmodule