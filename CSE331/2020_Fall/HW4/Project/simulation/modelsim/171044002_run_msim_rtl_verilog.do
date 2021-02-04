transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/mux_2x1_1bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/mux_2x1_2bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/mux_2x1_4bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/mux_2x1_5bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/mux_2x1_8bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/mux_2x1_16bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/mux_2x1_32bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/half_adder.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/full_adder.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/adder_2bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/adder_4bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/adder_8bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/adder_16bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/adder_32bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/sign_extender_16_to_32.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/zero_extender_16_to_32.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/left_shifter_2bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/comparator_32bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/ALU_1bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/ALU_1bit_MSB.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/ALU_32bit.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/ALU_control.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/Control.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/Instruction_Memory.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/Registers.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/Data_Memory.v}
vlog -vlog01compat -work work +incdir+C:/altera/13.1/workspace/171044002/source {C:/altera/13.1/workspace/171044002/source/mips32.v}

