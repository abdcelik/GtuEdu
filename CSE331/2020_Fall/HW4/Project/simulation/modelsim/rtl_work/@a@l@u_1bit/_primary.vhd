library verilog;
use verilog.vl_types.all;
entity ALU_1bit is
    port(
        a               : in     vl_logic;
        b               : in     vl_logic;
        c               : in     vl_logic;
        ALUop           : in     vl_logic_vector(2 downto 0);
        r               : out    vl_logic;
        cout            : out    vl_logic
    );
end ALU_1bit;
