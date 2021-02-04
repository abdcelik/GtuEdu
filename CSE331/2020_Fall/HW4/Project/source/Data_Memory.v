module Data_Memory(input MemWrite, input MemRead, input [17:0] address, input [31:0] writeData, input CLK, output [31:0] readData);

	reg [7:0] datamem[100:0];
	
	assign readData[31:24] = (MemRead == 0)? 8'b0: datamem[address];
	assign readData[23:16] = (MemRead == 0)? 8'b0: datamem[address + 18'b1];
	assign readData[15:8] = (MemRead == 0)? 8'b0: datamem[address + 18'b10];
	assign readData[7:0] = (MemRead == 0)? 8'b0: datamem[address + 18'b11];
	
	always @(posedge CLK)
	begin
		if(MemWrite)
		begin
			datamem[address] <= writeData[31:24];
			datamem[address + 18'b1] <= writeData[23:16];
			datamem[address + 18'b10] <= writeData[15:8];
			datamem[address + 18'b11] <= writeData[7:0];
		end
	end
endmodule