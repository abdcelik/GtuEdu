module sign_extender_16_to_32 (input [15:0] in, output [31:0] out);
	assign out[15:0] = in;
	assign out[31:16] = {16{in[15]}};
endmodule