library verilog;
use verilog.vl_types.all;
entity ALU_control is
    port(
        ALUOp           : in     vl_logic_vector(1 downto 0);
        funcfield       : in     vl_logic_vector(5 downto 0);
        ALUControlOp    : out    vl_logic_vector(2 downto 0)
    );
end ALU_control;
