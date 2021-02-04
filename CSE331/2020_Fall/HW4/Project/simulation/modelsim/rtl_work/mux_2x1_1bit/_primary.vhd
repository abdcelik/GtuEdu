library verilog;
use verilog.vl_types.all;
entity mux_2x1_1bit is
    port(
        in1             : in     vl_logic;
        in2             : in     vl_logic;
        s               : in     vl_logic;
        \out\           : out    vl_logic
    );
end mux_2x1_1bit;
