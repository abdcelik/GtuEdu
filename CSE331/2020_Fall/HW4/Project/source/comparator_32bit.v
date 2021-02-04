module comparator_32bit(input [31:0] in1, input [31:0] in2, output gt, output eq);
	wire [31:0] in2not;
	
	not(in2not[0], in2[0]);
	not(in2not[1], in2[1]);
	not(in2not[2], in2[2]);
	not(in2not[3], in2[3]);
	not(in2not[4], in2[4]);
	not(in2not[5], in2[5]);
	not(in2not[6], in2[6]);
	not(in2not[7], in2[7]);
	not(in2not[8], in2[8]);
	not(in2not[9], in2[9]);
	not(in2not[10], in2[10]);
	not(in2not[11], in2[11]);
	not(in2not[12], in2[12]);
	not(in2not[13], in2[13]);
	not(in2not[14], in2[14]);
	not(in2not[15], in2[15]);
	not(in2not[16], in2[16]);
	not(in2not[17], in2[17]);
	not(in2not[18], in2[18]);
	not(in2not[19], in2[19]);
	not(in2not[20], in2[20]);
	not(in2not[21], in2[21]);
	not(in2not[22], in2[22]);
	not(in2not[23], in2[23]);
	not(in2not[24], in2[24]);
	not(in2not[25], in2[25]);
	not(in2not[26], in2[26]);
	not(in2not[27], in2[27]);
	not(in2not[28], in2[28]);
	not(in2not[29], in2[29]);
	not(in2not[30], in2[30]);
	not(in2not[31], in2[31]);
	
	wire [31:0] r;
	wire ignore, nr31, neq, eqn;
	adder_32bit adder(in1, in2not, 1'b1, r, ignore);
	
	or(eqn, r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9], r[10], r[11], r[12], r[13], r[14], r[15], r[16],
		r[17], r[18], r[19], r[20], r[21], r[22], r[23], r[24], r[25], r[26], r[27], r[28], r[29], r[30], r[31]);
	not(eq, eqn);
	not(nr31, r[31]);
	not(neq, eq);
	and(gt, nr31, neq);
endmodule