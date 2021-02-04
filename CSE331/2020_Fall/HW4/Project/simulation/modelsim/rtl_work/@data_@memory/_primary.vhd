library verilog;
use verilog.vl_types.all;
entity Data_Memory is
    port(
        MemWrite        : in     vl_logic;
        MemRead         : in     vl_logic;
        address         : in     vl_logic_vector(17 downto 0);
        writeData       : in     vl_logic_vector(31 downto 0);
        CLK             : in     vl_logic;
        readData        : out    vl_logic_vector(31 downto 0)
    );
end Data_Memory;
