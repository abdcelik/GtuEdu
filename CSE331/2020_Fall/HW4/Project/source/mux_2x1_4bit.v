module mux_2x1_4bit (input [3:0] in1, input [3:0] in2, input s, output [3:0] out);
	mux_2x1_2bit mux0 (in1[1:0], in2[1:0], s, out[1:0]);
	mux_2x1_2bit mux1 (in1[3:2], in2[3:2], s, out[3:2]);
endmodule