library verilog;
use verilog.vl_types.all;
entity comparator_32bit is
    port(
        in1             : in     vl_logic_vector(31 downto 0);
        in2             : in     vl_logic_vector(31 downto 0);
        gt              : out    vl_logic;
        eq              : out    vl_logic
    );
end comparator_32bit;
