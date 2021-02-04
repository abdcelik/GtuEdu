module ALU_1bit_MSB(input a, input b, input c, input [2:0] ALUop, output r, output cout);
	wire res0, res1, res2, res3, res4, res5, res6, res7, res8, r1, r2;
	
	xor(res0, b, ALUop[2]);
	or(res1, res0, a);
	and(res2, res0, a);
	not(res3, res2);
	and(res4, res3, res1);
	and(res5, res4, c);
	or(res7, res4, c);
	not(res6, res5);
	and(res8, res6, res7);
	or(cout, res2, res5);
	
	mux_2x1_1bit mux1(res2, res8, ALUop[1], r1);
	mux_2x1_1bit mux2(res1, res4, ALUop[1], r2);
	mux_2x1_1bit mux3(r1, r2, ALUop[0], r);
endmodule