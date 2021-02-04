module adder_8bit(input [7:0] in1, input [7:0] in2, input carry_in, output [7:0] out, output carry_out);
	wire C;
	
	adder_4bit add1(in1[3:0], in2[3:0], carry_in, out[3:0], C);
	adder_4bit add2(in1[7:4], in2[7:4], C, out[7:4], carry_out);
endmodule