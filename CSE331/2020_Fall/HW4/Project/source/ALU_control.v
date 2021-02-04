module ALU_control(input [1:0] ALUOp, input [5:0] funcfield, output [2:0] ALUControlOp);
	wire ALUOp0n, ALUOp1n, funcfield2n, res1, res2, res3, res4, res5;
	not(ALUOp0n, ALUOp[0]);
	and(res1, ALUOp[1], ALUOp[0]);
	and(res2, ALUOp[1], ALUOp0n, funcfield[0]);
	or(ALUControlOp[0], res1, res2);
	
	not(ALUOp1n, ALUOp[1]);
	not(funcfield2n, funcfield[2]);
	and(res3, ALUOp0n, funcfield2n);
	or(ALUControlOp[1], res3, ALUOp1n);
	
	and(res4, ALUOp1n, ALUOp[0]);
	and(res5, ALUOp[1], ALUOp0n, funcfield[1]);
	or(ALUControlOp[2], res4, res5);
endmodule