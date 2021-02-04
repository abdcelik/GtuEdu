library verilog;
use verilog.vl_types.all;
entity left_shifter_2bit is
    port(
        \in\            : in     vl_logic_vector(31 downto 0);
        \out\           : out    vl_logic_vector(31 downto 0)
    );
end left_shifter_2bit;
