module Registers(input RegWrite, input RegWrite2, input [4:0] readReg1, input [4:0] readReg2,
						input [4:0] writeReg, input [31:0] writeData, input [4:0] writeReg2, input [31:0] writeData2, input CLK,
						output [31:0] readData1, output [31:0] readData2);

	reg [31:0] regs[31:0];
	
	assign readData1 = regs[readReg1];
	assign readData2 = regs[readReg2];
	
	always @(posedge CLK)
	begin
		if(RegWrite)
		begin
			regs[writeReg] <= writeData;
		end
		
		if(RegWrite2)
		begin
			regs[writeReg2] <= writeData2;
		end
	end
endmodule