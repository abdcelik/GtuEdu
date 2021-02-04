library verilog;
use verilog.vl_types.all;
entity full_adder is
    port(
        in1             : in     vl_logic;
        in2             : in     vl_logic;
        carry_in        : in     vl_logic;
        \out\           : out    vl_logic;
        carry_out       : out    vl_logic
    );
end full_adder;
