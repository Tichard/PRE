	component DE0_nano_system is
		port (
			adc_spi_conduit_MISO             : in    std_logic                     := 'X';             -- MISO
			adc_spi_conduit_MOSI             : out   std_logic;                                        -- MOSI
			adc_spi_conduit_SCLK             : out   std_logic;                                        -- SCLK
			adc_spi_conduit_SS_n             : out   std_logic;                                        -- SS_n
			altpll_sys_c1_clk                : out   std_logic;                                        -- clk
			altpll_sys_locked_conduit_export : out   std_logic;                                        -- export
			clk_clk                          : in    std_logic                     := 'X';             -- clk
			epcs_dclk                        : out   std_logic;                                        -- dclk
			epcs_sce                         : out   std_logic;                                        -- sce
			epcs_sdo                         : out   std_logic;                                        -- sdo
			epcs_data0                       : in    std_logic                     := 'X';             -- data0
			ext_sensor_irq_export            : in    std_logic                     := 'X';             -- export
			g_sensor_irq_export              : in    std_logic                     := 'X';             -- export
			i2c_ext_sda_export               : inout std_logic                     := 'X';             -- export
			i2c_scl_export                   : out   std_logic;                                        -- export
			i2c_sda_export                   : inout std_logic                     := 'X';             -- export
			pio_key_export                   : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			pio_leds_export                  : out   std_logic_vector(7 downto 0);                     -- export
			pio_switch_export                : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			reset_reset_n                    : in    std_logic                     := 'X';             -- reset_n
			sdram_wire_addr                  : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba                    : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n                 : out   std_logic;                                        -- cas_n
			sdram_wire_cke                   : out   std_logic;                                        -- cke
			sdram_wire_cs_n                  : out   std_logic;                                        -- cs_n
			sdram_wire_dq                    : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm                   : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_wire_ras_n                 : out   std_logic;                                        -- ras_n
			sdram_wire_we_n                  : out   std_logic;                                        -- we_n
			xbee_rxd                         : in    std_logic                     := 'X';             -- rxd
			xbee_txd                         : out   std_logic                                         -- txd
		);
	end component DE0_nano_system;

	u0 : component DE0_nano_system
		port map (
			adc_spi_conduit_MISO             => CONNECTED_TO_adc_spi_conduit_MISO,             --           adc_spi_conduit.MISO
			adc_spi_conduit_MOSI             => CONNECTED_TO_adc_spi_conduit_MOSI,             --                          .MOSI
			adc_spi_conduit_SCLK             => CONNECTED_TO_adc_spi_conduit_SCLK,             --                          .SCLK
			adc_spi_conduit_SS_n             => CONNECTED_TO_adc_spi_conduit_SS_n,             --                          .SS_n
			altpll_sys_c1_clk                => CONNECTED_TO_altpll_sys_c1_clk,                --             altpll_sys_c1.clk
			altpll_sys_locked_conduit_export => CONNECTED_TO_altpll_sys_locked_conduit_export, -- altpll_sys_locked_conduit.export
			clk_clk                          => CONNECTED_TO_clk_clk,                          --                       clk.clk
			epcs_dclk                        => CONNECTED_TO_epcs_dclk,                        --                      epcs.dclk
			epcs_sce                         => CONNECTED_TO_epcs_sce,                         --                          .sce
			epcs_sdo                         => CONNECTED_TO_epcs_sdo,                         --                          .sdo
			epcs_data0                       => CONNECTED_TO_epcs_data0,                       --                          .data0
			ext_sensor_irq_export            => CONNECTED_TO_ext_sensor_irq_export,            --            ext_sensor_irq.export
			g_sensor_irq_export              => CONNECTED_TO_g_sensor_irq_export,              --              g_sensor_irq.export
			i2c_ext_sda_export               => CONNECTED_TO_i2c_ext_sda_export,               --               i2c_ext_sda.export
			i2c_scl_export                   => CONNECTED_TO_i2c_scl_export,                   --                   i2c_scl.export
			i2c_sda_export                   => CONNECTED_TO_i2c_sda_export,                   --                   i2c_sda.export
			pio_key_export                   => CONNECTED_TO_pio_key_export,                   --                   pio_key.export
			pio_leds_export                  => CONNECTED_TO_pio_leds_export,                  --                  pio_leds.export
			pio_switch_export                => CONNECTED_TO_pio_switch_export,                --                pio_switch.export
			reset_reset_n                    => CONNECTED_TO_reset_reset_n,                    --                     reset.reset_n
			sdram_wire_addr                  => CONNECTED_TO_sdram_wire_addr,                  --                sdram_wire.addr
			sdram_wire_ba                    => CONNECTED_TO_sdram_wire_ba,                    --                          .ba
			sdram_wire_cas_n                 => CONNECTED_TO_sdram_wire_cas_n,                 --                          .cas_n
			sdram_wire_cke                   => CONNECTED_TO_sdram_wire_cke,                   --                          .cke
			sdram_wire_cs_n                  => CONNECTED_TO_sdram_wire_cs_n,                  --                          .cs_n
			sdram_wire_dq                    => CONNECTED_TO_sdram_wire_dq,                    --                          .dq
			sdram_wire_dqm                   => CONNECTED_TO_sdram_wire_dqm,                   --                          .dqm
			sdram_wire_ras_n                 => CONNECTED_TO_sdram_wire_ras_n,                 --                          .ras_n
			sdram_wire_we_n                  => CONNECTED_TO_sdram_wire_we_n,                  --                          .we_n
			xbee_rxd                         => CONNECTED_TO_xbee_rxd,                         --                      xbee.rxd
			xbee_txd                         => CONNECTED_TO_xbee_txd                          --                          .txd
		);

