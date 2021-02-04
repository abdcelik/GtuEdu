module adder_2bit (input [1:0] in1, input [1:0] in2, input carry_in, output [1:0] out, output carry_out);
	wire C;
	
	full_adder fa1(in1[0], in2[0], carry_in, out[0], C);
	full_adder fa2(in1[1], in2[1], C, out[1], carry_out);
endmodule