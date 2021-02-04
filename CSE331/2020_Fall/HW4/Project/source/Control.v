module Control(input [5:0] opcode, input [5:0] funcfield, output [1:0] ALUOp, output RegDst, output Branch, output MemRead, output MemToReg, output MemWrite, output AluSrc,
					output RegWrite, output RegWrite2, output bne, output ntype, output ori, output lui, output j, output jal, output jr);
					
	wire o5n, o4n, o3n, o2n, o1n, o0n, res1, res2, res3, res4;
	assign ALUOp[0] = opcode[2];
	not(o5n, opcode[5]);
	not(o4n, opcode[4]);
	not(o3n, opcode[3]);
	not(o2n, opcode[2]);
	not(o1n, opcode[1]);
	not(o0n, opcode[0]);
	and(res1, o5n, o4n, o1n);
	and(res2, o3n, o2n, o0n);
	and(res3, opcode[3], opcode[2], opcode[0]);
	or(res4, res2, res3);
	and(ALUOp[1], res1, res4);
	
	wire Reg1, Reg2, Reg3, Reg4, J1, ff3n;
	not(ff3n, funcfield[3]);
	
	assign RegDst = o0n;
	and(Branch, o3n, opcode[2]);
	and(MemRead, opcode[5], o3n);
	assign MemToReg = opcode[1];
	and(MemWrite, opcode[5], opcode[3]);
	or(AluSrc, opcode[5], opcode[3]);
	and(Reg1, opcode[5], o3n);
	and(Reg2, o5n, opcode[1], opcode[0]);
	and(Reg3, opcode[3], o1n, opcode[0]);
	and(Reg4, o2n, o1n, funcfield[5]);
	or(RegWrite, Reg1, Reg2, Reg3, Reg4);
	and(RegWrite2, o2n, o1n, o0n, ff3n);
	assign bne = opcode[0];
	assign ntype = o0n;
	and(ori, o5n, opcode[3]);
	and(lui, opcode[2], opcode[1]);
	or(J1, opcode[1], funcfield[3]);
	and(j, J1, o5n, o2n);
	and(jal, o5n, o3n, opcode[0]);
	assign jr = o1n;
endmodule