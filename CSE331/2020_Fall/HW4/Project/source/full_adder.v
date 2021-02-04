module full_adder (input in1, input in2, input carry_in, output out, output carry_out);
	wire first_carry_out, second_carry_out, temp_sum;
	
	half_adder first_sum (in1, in2, temp_sum, first_carry_out);
	half_adder second_sum (temp_sum, carry_in, out, second_carry_out);
	or(carry_out, first_carry_out, second_carry_out);
endmodule