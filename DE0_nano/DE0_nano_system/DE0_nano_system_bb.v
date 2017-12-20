
module DE0_nano_system (
	adc_spi_conduit_MISO,
	adc_spi_conduit_MOSI,
	adc_spi_conduit_SCLK,
	adc_spi_conduit_SS_n,
	altpll_sys_c1_clk,
	altpll_sys_locked_conduit_export,
	clk_clk,
	epcs_dclk,
	epcs_sce,
	epcs_sdo,
	epcs_data0,
	ext_sensor_irq_export,
	g_sensor_irq_export,
	i2c_ext_sda_export,
	i2c_scl_export,
	i2c_sda_export,
	pio_key_export,
	pio_leds_export,
	pio_switch_export,
	reset_reset_n,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	xbee_rxd,
	xbee_txd);	

	input		adc_spi_conduit_MISO;
	output		adc_spi_conduit_MOSI;
	output		adc_spi_conduit_SCLK;
	output		adc_spi_conduit_SS_n;
	output		altpll_sys_c1_clk;
	output		altpll_sys_locked_conduit_export;
	input		clk_clk;
	output		epcs_dclk;
	output		epcs_sce;
	output		epcs_sdo;
	input		epcs_data0;
	input		ext_sensor_irq_export;
	input		g_sensor_irq_export;
	inout		i2c_ext_sda_export;
	output		i2c_scl_export;
	inout		i2c_sda_export;
	input	[1:0]	pio_key_export;
	output	[7:0]	pio_leds_export;
	input	[3:0]	pio_switch_export;
	input		reset_reset_n;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	input		xbee_rxd;
	output		xbee_txd;
endmodule
