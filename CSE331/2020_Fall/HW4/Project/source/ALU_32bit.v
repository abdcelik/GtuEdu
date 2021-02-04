module ALU_32bit(input [31:0] a, input [31:0] b, input [2:0] ALUop, output [31:0] r, output zero);

	wire c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16,
			c17, c18, c19, c20, c21, c22, c23, c24, c25, c26, c27, c28, c29, c30, c31, c32, res1;

	ALU_1bit ALU0(a[0], b[0], ALUop[2], ALUop, r[0], c1);
	ALU_1bit ALU1(a[1], b[1], c1, ALUop, r[1], c2);
	ALU_1bit ALU2(a[2], b[2], c2, ALUop, r[2], c3);
	ALU_1bit ALU3(a[3], b[3], c3, ALUop, r[3], c4);
	ALU_1bit ALU4(a[4], b[4], c4, ALUop, r[4], c5);
	ALU_1bit ALU5(a[5], b[5], c5, ALUop, r[5], c6);
	ALU_1bit ALU6(a[6], b[6], c6, ALUop, r[6], c7);
	ALU_1bit ALU7(a[7], b[7], c7, ALUop, r[7], c8);
	ALU_1bit ALU8(a[8], b[8], c8, ALUop, r[8], c9);
	ALU_1bit ALU9(a[9], b[9], c9, ALUop, r[9], c10);
	ALU_1bit ALU10(a[10], b[10], c10, ALUop, r[10], c11);
	ALU_1bit ALU11(a[11], b[11], c11, ALUop, r[11], c12);
	ALU_1bit ALU12(a[12], b[12], c12, ALUop, r[12], c13);
	ALU_1bit ALU13(a[13], b[13], c13, ALUop, r[13], c14);
	ALU_1bit ALU14(a[14], b[14], c14, ALUop, r[14], c15);
	ALU_1bit ALU15(a[15], b[15], c15, ALUop, r[15], c16);
	ALU_1bit ALU16(a[16], b[16], c16, ALUop, r[16], c17);
	ALU_1bit ALU17(a[17], b[17], c17, ALUop, r[17], c18);
	ALU_1bit ALU18(a[18], b[18], c18, ALUop, r[18], c19);
	ALU_1bit ALU19(a[19], b[19], c19, ALUop, r[19], c20);
	ALU_1bit ALU20(a[20], b[20], c20, ALUop, r[20], c21);
	ALU_1bit ALU21(a[21], b[21], c21, ALUop, r[21], c22);
	ALU_1bit ALU22(a[22], b[22], c22, ALUop, r[22], c23);
	ALU_1bit ALU23(a[23], b[23], c23, ALUop, r[23], c24);
	ALU_1bit ALU24(a[24], b[24], c24, ALUop, r[24], c25);
	ALU_1bit ALU25(a[25], b[25], c25, ALUop, r[25], c26);
	ALU_1bit ALU26(a[26], b[26], c26, ALUop, r[26], c27);
	ALU_1bit ALU27(a[27], b[27], c27, ALUop, r[27], c28);
	ALU_1bit ALU28(a[28], b[28], c28, ALUop, r[28], c29);
	ALU_1bit ALU29(a[29], b[29], c29, ALUop, r[29], c30);
	ALU_1bit ALU30(a[30], b[30], c30, ALUop, r[30], c31);
	ALU_1bit_MSB ALU31(a[31], b[31], c31, ALUop, r[31], c32);
	
	or(res1, r[0], r[1], r[2], r[3], r[4]);
	not(zero, res1);
endmodule