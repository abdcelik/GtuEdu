module mips32(input CLK);

	reg [31:0] pc = 32'b0;
	
	wire bus_RegDst, bus_Branch, bus_MemRead, bus_MemToReg, bus_MemWrite, bus_ALUSrc, bus_RegWrite, bus_RegWrite2, bus_bne,
			bus_ntype, bus_ori, bus_lui, bus_j, bus_jal, bus_jr, bus_zero, bus_gt, bus_eq, bus_zeron, res_and_branch, bus_mux5_out, bus_adder1_cout, bus_adder2_cout;
	wire [1:0] bus_ALUOp;
	wire [2:0] bus_ALUcontrol_out;
	wire [4:0] bus_mux0_out, bus_mux1_out;
	wire [31:0] bus_instruction,
				bus_mux2_out, bus_mux3_out, bus_mux4_out, bus_mux6_out, bus_mux7_out, bus_mux8_out, bus_mux9_out, bus_mux10_out, bus_mux11_out, bus_mux12_out, bus_mux13_out,
				bus_sign_extender_out, bus_zero_extender_out, bus_read_data1, bus_read_data2, bus_ALU_res, bus_mem_read_data,
				bus_adder1_out, bus_shifter_out, bus_adder2_out;
	
	Instruction_Memory inst_mem(pc[13:0], bus_instruction);
	
	Control control(bus_instruction[31:26], bus_instruction[5:0], bus_ALUOp, bus_RegDst, bus_Branch, bus_MemRead, bus_MemToReg, bus_MemWrite,
							bus_ALUSrc, bus_RegWrite, bus_RegWrite2, bus_bne, bus_ntype, bus_ori, bus_lui, bus_j, bus_jal, bus_jr);
	
	mux_2x1_5bit mux0(bus_instruction[20:16], bus_instruction[15:11], bus_RegDst, bus_mux0_out);
	mux_2x1_5bit mux1(bus_mux0_out, 5'b11111, bus_jal, bus_mux1_out);
	mux_2x1_32bit mux2(bus_mux10_out, {bus_instruction[15:0],16'b0}, bus_lui, bus_mux2_out);
	
	sign_extender_16_to_32 sign_extender(bus_instruction[15:0], bus_sign_extender_out);
	zero_extender_16_to_32 zero_extender(bus_instruction[15:0], bus_zero_extender_out);
	mux_2x1_32bit mux3(bus_sign_extender_out, bus_zero_extender_out, bus_ori, bus_mux3_out);
	
	Registers register(bus_RegWrite, bus_RegWrite2, bus_instruction[25:21], bus_instruction[20:16], bus_mux1_out, bus_mux2_out, bus_instruction[25:21], bus_ALU_res, CLK, bus_read_data1, bus_read_data2);
	
	mux_2x1_32bit mux4(bus_read_data2, bus_mux3_out, bus_ALUSrc, bus_mux4_out);
	ALU_control ALUcontrol(bus_ALUOp, bus_instruction[5:0], bus_ALUcontrol_out);
	ALU_32bit ALU(bus_read_data1, bus_mux4_out, bus_ALUcontrol_out, bus_ALU_res, bus_zero);
	
	not(bus_zeron, bus_zero);
	mux_2x1_1bit mux5(bus_zero, bus_zeron, bus_bne, bus_mux5_out);
	and(res_and_branch, bus_Branch, bus_mux5_out);
	
	adder_32bit adder1(pc, 32'b100, 1'b0, bus_adder1_out, bus_adder1_cout);
	left_shifter_2bit shifter(bus_mux3_out, bus_shifter_out);
	adder_32bit adder2(bus_adder1_out, bus_shifter_out, 1'b0, bus_adder2_out, bus_adder2_cout);
	mux_2x1_32bit mux12(bus_adder1_out, bus_adder2_out, res_and_branch, bus_mux12_out);
	
	Data_Memory data_memory(bus_MemWrite, bus_MemRead, bus_ALU_res[17:0], bus_read_data2, CLK, bus_mem_read_data);
	
	mux_2x1_32bit mux6(bus_ALU_res, bus_mem_read_data, bus_MemToReg, bus_mux6_out);
	
	comparator_32bit comparator(bus_ALU_res, 32'b0, bus_gt, bus_eq);
	mux_2x1_32bit mux7(32'b10, 32'b1, bus_eq, bus_mux7_out);
	mux_2x1_32bit mux8(bus_mux7_out, 32'b11, bus_gt, bus_mux8_out);
	mux_2x1_32bit mux9(bus_mux6_out, bus_mux8_out, bus_ntype, bus_mux9_out);
	mux_2x1_32bit mux10(bus_mux9_out, bus_mux12_out, bus_jal, bus_mux10_out);
	mux_2x1_32bit mux11({bus_mux12_out[31:28], bus_instruction[25:0], 2'b0}, bus_read_data1, bus_jr, bus_mux11_out);
	mux_2x1_32bit mux13(bus_mux12_out, bus_mux11_out, bus_j, bus_mux13_out);
	
	always @(posedge CLK)
	begin
		pc <= bus_mux13_out;
	end
endmodule