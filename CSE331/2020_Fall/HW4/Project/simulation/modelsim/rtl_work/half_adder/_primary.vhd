library verilog;
use verilog.vl_types.all;
entity half_adder is
    port(
        in1             : in     vl_logic;
        in2             : in     vl_logic;
        \out\           : out    vl_logic;
        carry_out       : out    vl_logic
    );
end half_adder;
