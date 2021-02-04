library verilog;
use verilog.vl_types.all;
entity Instruction_Memory is
    port(
        program_counter : in     vl_logic_vector(13 downto 0);
        instruction     : out    vl_logic_vector(31 downto 0)
    );
end Instruction_Memory;
