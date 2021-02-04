module mux_2x1_1bit (input in1, input in2, input s, output out);
	wire sn, out1, out2;
	not(sn, s);
	and(out1, in1, sn);
	and(out2, in2, s);
	or(out, out1, out2);
endmodule