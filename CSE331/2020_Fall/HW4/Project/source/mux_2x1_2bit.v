module mux_2x1_2bit (input [1:0] in1, input [1:0] in2, input s, output [1:0] out);
	mux_2x1_1bit mux0 (in1[0], in2[0], s, out[0]);
	mux_2x1_1bit mux1 (in1[1], in2[1], s, out[1]);
endmodule