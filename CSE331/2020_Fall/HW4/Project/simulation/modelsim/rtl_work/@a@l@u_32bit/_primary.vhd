library verilog;
use verilog.vl_types.all;
entity ALU_32bit is
    port(
        a               : in     vl_logic_vector(31 downto 0);
        b               : in     vl_logic_vector(31 downto 0);
        ALUop           : in     vl_logic_vector(2 downto 0);
        r               : out    vl_logic_vector(31 downto 0);
        zero            : out    vl_logic
    );
end ALU_32bit;
