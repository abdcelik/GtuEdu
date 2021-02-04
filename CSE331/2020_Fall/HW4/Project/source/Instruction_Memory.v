module Instruction_Memory(input [13:0] program_counter, output [31:0] instruction);
	reg [7:0] instruction_memory [16383:0];
	
	assign instruction[31:24] = instruction_memory[program_counter];
	assign instruction[23:16] = instruction_memory[program_counter + 13'b1];
	assign instruction[15:8] = instruction_memory[program_counter + 13'b10];
	assign instruction[7:0] = instruction_memory[program_counter + 13'b11];
endmodule