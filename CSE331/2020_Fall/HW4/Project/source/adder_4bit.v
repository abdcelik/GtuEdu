module adder_4bit(input [3:0] in1, input [3:0] in2, input carry_in, output [3:0] out, output carry_out);
	wire C;
	
	adder_2bit add1(in1[1:0], in2[1:0], carry_in, out[1:0], C);
	adder_2bit add2(in1[3:2], in2[3:2], C, out[3:2], carry_out);
endmodule