library verilog;
use verilog.vl_types.all;
entity Registers is
    port(
        RegWrite        : in     vl_logic;
        RegWrite2       : in     vl_logic;
        readReg1        : in     vl_logic_vector(4 downto 0);
        readReg2        : in     vl_logic_vector(4 downto 0);
        writeReg        : in     vl_logic_vector(4 downto 0);
        writeData       : in     vl_logic_vector(31 downto 0);
        writeReg2       : in     vl_logic_vector(4 downto 0);
        writeData2      : in     vl_logic_vector(31 downto 0);
        CLK             : in     vl_logic;
        readData1       : out    vl_logic_vector(31 downto 0);
        readData2       : out    vl_logic_vector(31 downto 0)
    );
end Registers;
