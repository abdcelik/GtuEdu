library verilog;
use verilog.vl_types.all;
entity adder_16bit is
    port(
        in1             : in     vl_logic_vector(15 downto 0);
        in2             : in     vl_logic_vector(15 downto 0);
        carry_in        : in     vl_logic;
        \out\           : out    vl_logic_vector(15 downto 0);
        carry_out       : out    vl_logic
    );
end adder_16bit;
