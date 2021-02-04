module mux_2x1_8bit (input [7:0] in1, input [7:0] in2, input s, output [7:0] out);
	mux_2x1_4bit mux0(in1[3:0], in2[3:0], s, out[3:0]);
	mux_2x1_4bit mux1(in1[7:4], in2[7:4], s, out[7:4]);
endmodule