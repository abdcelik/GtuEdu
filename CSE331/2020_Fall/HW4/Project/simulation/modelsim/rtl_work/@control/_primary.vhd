library verilog;
use verilog.vl_types.all;
entity Control is
    port(
        opcode          : in     vl_logic_vector(5 downto 0);
        funcfield       : in     vl_logic_vector(5 downto 0);
        ALUOp           : out    vl_logic_vector(1 downto 0);
        RegDst          : out    vl_logic;
        Branch          : out    vl_logic;
        MemRead         : out    vl_logic;
        MemToReg        : out    vl_logic;
        MemWrite        : out    vl_logic;
        AluSrc          : out    vl_logic;
        RegWrite        : out    vl_logic;
        RegWrite2       : out    vl_logic;
        bne             : out    vl_logic;
        ntype           : out    vl_logic;
        ori             : out    vl_logic;
        lui             : out    vl_logic;
        j               : out    vl_logic;
        jal             : out    vl_logic;
        jr              : out    vl_logic
    );
end Control;
