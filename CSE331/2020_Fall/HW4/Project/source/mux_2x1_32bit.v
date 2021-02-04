module mux_2x1_32bit (input [31:0] in1, input [31:0] in2, input s, output [31:0] out);
	mux_2x1_16bit mux0(in1[15:0], in2[15:0], s, out[15:0]);
	mux_2x1_16bit mux1(in1[31:16], in2[31:16], s, out[31:16]);
endmodule