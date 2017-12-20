--IP Functional Simulation Model
--VERSION_BEGIN 17.1 cbx_mgl 2017:10:25:18:08:29:SJ cbx_simgen 2017:10:25:18:06:53:SJ  VERSION_END


-- Copyright (C) 2017  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details.

-- You may only use these simulation model output files for simulation
-- purposes and expressly not for synthesis or any other purposes (in which
-- event Intel disclaims all warranties of any kind).


--synopsys translate_off

 LIBRARY cycloneive;
 USE cycloneive.cycloneive_components.all;

--synthesis_resources = cycloneive_pll 1 lut 6 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  DE0_nano_system_altpll_sys IS 
	 PORT 
	 ( 
		 address	:	IN  STD_LOGIC_VECTOR (1 DOWNTO 0);
		 areset	:	IN  STD_LOGIC;
		 c0	:	OUT  STD_LOGIC;
		 c1	:	OUT  STD_LOGIC;
		 c2	:	OUT  STD_LOGIC;
		 clk	:	IN  STD_LOGIC;
		 configupdate	:	IN  STD_LOGIC;
		 locked	:	OUT  STD_LOGIC;
		 phasecounterselect	:	IN  STD_LOGIC_VECTOR (3 DOWNTO 0);
		 phasedone	:	OUT  STD_LOGIC;
		 phasestep	:	IN  STD_LOGIC;
		 phaseupdown	:	IN  STD_LOGIC;
		 read	:	IN  STD_LOGIC;
		 readdata	:	OUT  STD_LOGIC_VECTOR (31 DOWNTO 0);
		 reset	:	IN  STD_LOGIC;
		 scanclk	:	IN  STD_LOGIC;
		 scanclkena	:	IN  STD_LOGIC;
		 scandata	:	IN  STD_LOGIC;
		 scandataout	:	OUT  STD_LOGIC;
		 scandone	:	OUT  STD_LOGIC;
		 write	:	IN  STD_LOGIC;
		 writedata	:	IN  STD_LOGIC_VECTOR (31 DOWNTO 0)
	 ); 
 END DE0_nano_system_altpll_sys;

 ARCHITECTURE RTL OF DE0_nano_system_altpll_sys IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
	 SIGNAL  wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_clk	:	STD_LOGIC_VECTOR (4 DOWNTO 0);
	 SIGNAL  wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_fbout	:	STD_LOGIC;
	 SIGNAL  wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_inclk	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_locked	:	STD_LOGIC;
	 SIGNAL	de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_pll_lock_sync_133q	:	STD_LOGIC := '0';
	 SIGNAL	de0_nano_system_altpll_sys_pfdena_reg_24q	:	STD_LOGIC := '0';
	 SIGNAL	de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe4a_0_121q	:	STD_LOGIC := '0';
	 SIGNAL	de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe5a_0_124q	:	STD_LOGIC := '0';
	 SIGNAL	de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe6a_0_125q	:	STD_LOGIC := '0';
	 SIGNAL	de0_nano_system_altpll_sys_prev_reset_17q	:	STD_LOGIC := '0';
	 SIGNAL  wire_w_lg_w_lg_w22w23w24w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_lg_w16w18w19w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w22w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w16w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w17w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_address_range2w5w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_reset10w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w87w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_address_range3w4w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w22w23w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w16w18w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  s_wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_locked_131_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_de0_nano_system_altpll_sys_w_select_control_15_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_de0_nano_system_altpll_sys_w_select_status_16_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_de0_nano_system_altpll_sys_wire_pfdena_reg_ena_12_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_de0_nano_system_altpll_sys_wire_sd1_areset_19_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_vcc :	STD_LOGIC;
	 SIGNAL  wire_w_address_range2w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_address_range3w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
 BEGIN

	wire_w_lg_w_lg_w22w23w24w(0) <= wire_w_lg_w22w23w(0) AND read;
	wire_w_lg_w_lg_w16w18w19w(0) <= wire_w_lg_w16w18w(0) AND read;
	wire_w22w(0) <= s_wire_de0_nano_system_altpll_sys_w_select_control_15_dataout AND de0_nano_system_altpll_sys_pfdena_reg_24q;
	wire_w16w(0) <= s_wire_de0_nano_system_altpll_sys_w_select_control_15_dataout AND de0_nano_system_altpll_sys_prev_reset_17q;
	wire_w17w(0) <= s_wire_de0_nano_system_altpll_sys_w_select_status_16_dataout AND de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe6a_0_125q;
	wire_w_lg_w_address_range2w5w(0) <= wire_w_address_range2w(0) AND wire_w_lg_w_address_range3w4w(0);
	wire_w_lg_reset10w(0) <= NOT reset;
	wire_w87w(0) <= NOT s_wire_de0_nano_system_altpll_sys_wire_sd1_areset_19_dataout;
	wire_w_lg_w_address_range3w4w(0) <= NOT wire_w_address_range3w(0);
	wire_w_lg_w22w23w(0) <= wire_w22w(0) OR s_wire_de0_nano_system_altpll_sys_w_select_status_16_dataout;
	wire_w_lg_w16w18w(0) <= wire_w16w(0) OR wire_w17w(0);
	c0 <= wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_clk(0);
	c1 <= wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_clk(1);
	c2 <= wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_clk(2);
	locked <= s_wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_locked_131_dataout;
	phasedone <= '0';
	readdata <= ( "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & wire_w_lg_w_lg_w22w23w24w & wire_w_lg_w_lg_w16w18w19w);
	s_wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_locked_131_dataout <= (de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_pll_lock_sync_133q AND wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_locked);
	s_wire_de0_nano_system_altpll_sys_w_select_control_15_dataout <= wire_w_lg_w_address_range2w5w(0);
	s_wire_de0_nano_system_altpll_sys_w_select_status_16_dataout <= ((NOT address(0)) AND wire_w_lg_w_address_range3w4w(0));
	s_wire_de0_nano_system_altpll_sys_wire_pfdena_reg_ena_12_dataout <= (s_wire_de0_nano_system_altpll_sys_w_select_control_15_dataout AND write);
	s_wire_de0_nano_system_altpll_sys_wire_sd1_areset_19_dataout <= (de0_nano_system_altpll_sys_prev_reset_17q OR areset);
	s_wire_vcc <= '1';
	scandataout <= '0';
	scandone <= '0';
	wire_w_address_range2w(0) <= address(0);
	wire_w_address_range3w(0) <= address(1);
	wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_inclk <= ( "0" & clk);
	de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143 :  cycloneive_pll
	  GENERIC MAP (
		BANDWIDTH_TYPE => "auto",
		CLK0_DIVIDE_BY => 1,
		CLK0_DUTY_CYCLE => 50,
		CLK0_MULTIPLY_BY => 2,
		CLK0_PHASE_SHIFT => "0",
		CLK1_DIVIDE_BY => 1,
		CLK1_DUTY_CYCLE => 50,
		CLK1_MULTIPLY_BY => 2,
		CLK1_PHASE_SHIFT => "-1667",
		CLK2_DIVIDE_BY => 5,
		CLK2_DUTY_CYCLE => 50,
		CLK2_MULTIPLY_BY => 1,
		CLK2_PHASE_SHIFT => "0",
		COMPENSATE_CLOCK => "clk0",
		INCLK0_INPUT_FREQUENCY => 20000,
		OPERATION_MODE => "normal",
		PLL_TYPE => "auto"
	  )
	  PORT MAP ( 
		areset => s_wire_de0_nano_system_altpll_sys_wire_sd1_areset_19_dataout,
		clk => wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_clk,
		fbin => wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_fbout,
		fbout => wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_fbout,
		inclk => wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_inclk,
		locked => wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_locked
	  );
	PROCESS (wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_locked, s_wire_de0_nano_system_altpll_sys_wire_sd1_areset_19_dataout)
	BEGIN
		IF (s_wire_de0_nano_system_altpll_sys_wire_sd1_areset_19_dataout = '1') THEN
				de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_pll_lock_sync_133q <= '0';
		ELSIF (wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_locked = '1' AND wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_cycloneive_pll_pll7_143_locked'event) THEN
				de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_pll_lock_sync_133q <= s_wire_vcc;
		END IF;
	END PROCESS;
	PROCESS (clk, reset)
	BEGIN
		IF (reset = '1') THEN
				de0_nano_system_altpll_sys_pfdena_reg_24q <= '1';
		ELSIF (clk = '1' AND clk'event) THEN
			IF (s_wire_de0_nano_system_altpll_sys_wire_pfdena_reg_ena_12_dataout = '1') THEN
				de0_nano_system_altpll_sys_pfdena_reg_24q <= writedata(1);
			END IF;
		END IF;
		if (now = 0 ns) then
			de0_nano_system_altpll_sys_pfdena_reg_24q <= '1' after 1 ps;
		end if;
	END PROCESS;
	PROCESS (clk, reset)
	BEGIN
		IF (reset = '1') THEN
				de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe4a_0_121q <= '0';
				de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe5a_0_124q <= '0';
				de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe6a_0_125q <= '0';
				de0_nano_system_altpll_sys_prev_reset_17q <= '0';
		ELSIF (clk = '1' AND clk'event) THEN
				de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe4a_0_121q <= s_wire_de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_altpll_gch2_sd1_locked_131_dataout;
				de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe5a_0_124q <= de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe4a_0_121q;
				de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe6a_0_125q <= de0_nano_system_altpll_sys_de0_nano_system_altpll_sys_stdsync_sv6_stdsync2_de0_nano_system_altpll_sys_dffpipe_l2c_dffpipe3_dffe5a_0_124q;
				de0_nano_system_altpll_sys_prev_reset_17q <= (s_wire_de0_nano_system_altpll_sys_wire_pfdena_reg_ena_12_dataout AND writedata(0));
		END IF;
	END PROCESS;

 END RTL; --DE0_nano_system_altpll_sys
--synopsys translate_on
--VALID FILE
