library verilog;
use verilog.vl_types.all;
entity adder_32bit is
    port(
        in1             : in     vl_logic_vector(31 downto 0);
        in2             : in     vl_logic_vector(31 downto 0);
        carry_in        : in     vl_logic;
        \out\           : out    vl_logic_vector(31 downto 0);
        carry_out       : out    vl_logic
    );
end adder_32bit;
