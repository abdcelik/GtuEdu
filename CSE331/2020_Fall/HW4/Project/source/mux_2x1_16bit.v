module mux_2x1_16bit (input [15:0] in1, input [15:0] in2, input s, output [15:0] out);
	mux_2x1_8bit mux0(in1[7:0], in2[7:0], s, out[7:0]);
	mux_2x1_8bit mux1(in1[15:8], in2[15:8], s, out[15:8]);
endmodule