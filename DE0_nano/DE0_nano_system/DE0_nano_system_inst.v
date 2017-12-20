	DE0_nano_system u0 (
		.adc_spi_conduit_MISO             (<connected-to-adc_spi_conduit_MISO>),             //           adc_spi_conduit.MISO
		.adc_spi_conduit_MOSI             (<connected-to-adc_spi_conduit_MOSI>),             //                          .MOSI
		.adc_spi_conduit_SCLK             (<connected-to-adc_spi_conduit_SCLK>),             //                          .SCLK
		.adc_spi_conduit_SS_n             (<connected-to-adc_spi_conduit_SS_n>),             //                          .SS_n
		.altpll_sys_c1_clk                (<connected-to-altpll_sys_c1_clk>),                //             altpll_sys_c1.clk
		.altpll_sys_locked_conduit_export (<connected-to-altpll_sys_locked_conduit_export>), // altpll_sys_locked_conduit.export
		.clk_clk                          (<connected-to-clk_clk>),                          //                       clk.clk
		.epcs_dclk                        (<connected-to-epcs_dclk>),                        //                      epcs.dclk
		.epcs_sce                         (<connected-to-epcs_sce>),                         //                          .sce
		.epcs_sdo                         (<connected-to-epcs_sdo>),                         //                          .sdo
		.epcs_data0                       (<connected-to-epcs_data0>),                       //                          .data0
		.ext_sensor_irq_export            (<connected-to-ext_sensor_irq_export>),            //            ext_sensor_irq.export
		.g_sensor_irq_export              (<connected-to-g_sensor_irq_export>),              //              g_sensor_irq.export
		.i2c_ext_sda_export               (<connected-to-i2c_ext_sda_export>),               //               i2c_ext_sda.export
		.i2c_scl_export                   (<connected-to-i2c_scl_export>),                   //                   i2c_scl.export
		.i2c_sda_export                   (<connected-to-i2c_sda_export>),                   //                   i2c_sda.export
		.pio_key_export                   (<connected-to-pio_key_export>),                   //                   pio_key.export
		.pio_leds_export                  (<connected-to-pio_leds_export>),                  //                  pio_leds.export
		.pio_switch_export                (<connected-to-pio_switch_export>),                //                pio_switch.export
		.reset_reset_n                    (<connected-to-reset_reset_n>),                    //                     reset.reset_n
		.sdram_wire_addr                  (<connected-to-sdram_wire_addr>),                  //                sdram_wire.addr
		.sdram_wire_ba                    (<connected-to-sdram_wire_ba>),                    //                          .ba
		.sdram_wire_cas_n                 (<connected-to-sdram_wire_cas_n>),                 //                          .cas_n
		.sdram_wire_cke                   (<connected-to-sdram_wire_cke>),                   //                          .cke
		.sdram_wire_cs_n                  (<connected-to-sdram_wire_cs_n>),                  //                          .cs_n
		.sdram_wire_dq                    (<connected-to-sdram_wire_dq>),                    //                          .dq
		.sdram_wire_dqm                   (<connected-to-sdram_wire_dqm>),                   //                          .dqm
		.sdram_wire_ras_n                 (<connected-to-sdram_wire_ras_n>),                 //                          .ras_n
		.sdram_wire_we_n                  (<connected-to-sdram_wire_we_n>),                  //                          .we_n
		.xbee_rxd                         (<connected-to-xbee_rxd>),                         //                      xbee.rxd
		.xbee_txd                         (<connected-to-xbee_txd>)                          //                          .txd
	);

