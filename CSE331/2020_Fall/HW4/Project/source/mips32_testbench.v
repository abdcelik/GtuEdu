`define DELAY 200 
module mips32_testbench();

	reg CLK = 1'b0;
	reg [31:0] halt = 32'b10110000;	// It must be last instruction address
	
	mips32 mips(CLK);
	
	initial begin
		$readmemb("..\\..\\Instruction_Memory.mem", mips.inst_mem.instruction_memory);
		$readmemb("..\\..\\Register_Memory.mem", mips.register.regs);
		$readmemb("..\\..\\Data_Memory.mem", mips.data_memory.datamem);
	end
	
	always #5 CLK = ~CLK;
	
	always @(posedge CLK) begin
		if(mips.pc == halt) begin
			$writememb("..\\..\\Register_Memory_after.mem", mips.register.regs);
			$writememb("..\\..\\Data_Memory_after.mem", mips.data_memory.datamem);
			$stop;
		end
	end
	
	initial begin
		$monitor("pc= %32b", mips.pc);
	end
endmodule