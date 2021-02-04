module half_adder (input in1, input in2, output out, output carry_out);
	xor(out, in1, in2);
	and(carry_out, in1, in2);
endmodule