library verilog;
use verilog.vl_types.all;
entity mux_2x1_5bit is
    port(
        in1             : in     vl_logic_vector(4 downto 0);
        in2             : in     vl_logic_vector(4 downto 0);
        s               : in     vl_logic;
        \out\           : out    vl_logic_vector(4 downto 0)
    );
end mux_2x1_5bit;
