module mux_2x1_5bit(input [4:0] in1, input [4:0] in2, input s, output [4:0] out);
	mux_2x1_1bit mux0(in1[0], in2[0], s, out[0]);
	mux_2x1_1bit mux1(in1[1], in2[1], s, out[1]);
	mux_2x1_1bit mux2(in1[2], in2[2], s, out[2]);
	mux_2x1_1bit mux3(in1[3], in2[3], s, out[3]);
	mux_2x1_1bit mux4(in1[4], in2[4], s, out[4]);
endmodule