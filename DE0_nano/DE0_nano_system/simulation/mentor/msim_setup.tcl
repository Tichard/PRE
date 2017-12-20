
# (C) 2001-2017 Altera Corporation. All rights reserved.
# Your use of Altera Corporation's design tools, logic functions and 
# other software and tools, and its AMPP partner logic functions, and 
# any output files any of the foregoing (including device programming 
# or simulation files), and any associated documentation or information 
# are expressly subject to the terms and conditions of the Altera 
# Program License Subscription Agreement, Altera MegaCore Function 
# License Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by Altera 
# or its authorized distributors. Please refer to the applicable 
# agreement for further details.

# ----------------------------------------
# Auto-generated simulation script msim_setup.tcl
# ----------------------------------------
# This script provides commands to simulate the following IP detected in
# your Quartus project:
#     DE0_nano_system
# 
# Altera recommends that you source this Quartus-generated IP simulation
# script from your own customized top-level script, and avoid editing this
# generated script.
# 
# To write a top-level script that compiles Altera simulation libraries and
# the Quartus-generated IP in your project, along with your design and
# testbench files, copy the text from the TOP-LEVEL TEMPLATE section below
# into a new file, e.g. named "mentor.do", and modify the text as directed.
# 
# ----------------------------------------
# # TOP-LEVEL TEMPLATE - BEGIN
# #
# # QSYS_SIMDIR is used in the Quartus-generated IP simulation script to
# # construct paths to the files required to simulate the IP in your Quartus
# # project. By default, the IP script assumes that you are launching the
# # simulator from the IP script location. If launching from another
# # location, set QSYS_SIMDIR to the output directory you specified when you
# # generated the IP script, relative to the directory from which you launch
# # the simulator.
# #
# set QSYS_SIMDIR <script generation output directory>
# #
# # Source the generated IP simulation script.
# source $QSYS_SIMDIR/mentor/msim_setup.tcl
# #
# # Set any compilation options you require (this is unusual).
# set USER_DEFINED_COMPILE_OPTIONS <compilation options>
# set USER_DEFINED_VHDL_COMPILE_OPTIONS <compilation options for VHDL>
# set USER_DEFINED_VERILOG_COMPILE_OPTIONS <compilation options for Verilog>
# #
# # Call command to compile the Quartus EDA simulation library.
# dev_com
# #
# # Call command to compile the Quartus-generated IP simulation files.
# com
# #
# # Add commands to compile all design files and testbench files, including
# # the top level. (These are all the files required for simulation other
# # than the files compiled by the Quartus-generated IP simulation script)
# #
# vlog <compilation options> <design and testbench files>
# #
# # Set the top-level simulation or testbench module/entity name, which is
# # used by the elab command to elaborate the top level.
# #
# set TOP_LEVEL_NAME <simulation top>
# #
# # Set any elaboration options you require.
# set USER_DEFINED_ELAB_OPTIONS <elaboration options>
# #
# # Call command to elaborate your design and testbench.
# elab
# #
# # Run the simulation.
# run -a
# #
# # Report success to the shell.
# exit -code 0
# #
# # TOP-LEVEL TEMPLATE - END
# ----------------------------------------
# 
# IP SIMULATION SCRIPT
# ----------------------------------------
# If DE0_nano_system is one of several IP cores in your
# Quartus project, you can generate a simulation script
# suitable for inclusion in your top-level simulation
# script by running the following command line:
# 
# ip-setup-simulation --quartus-project=<quartus project>
# 
# ip-setup-simulation will discover the Altera IP
# within the Quartus project, and generate a unified
# script which supports all the Altera IP within the design.
# ----------------------------------------
# ACDS 17.1 590 win32 2017.11.23.17:08:06

# ----------------------------------------
# Initialize variables
if ![info exists SYSTEM_INSTANCE_NAME] { 
  set SYSTEM_INSTANCE_NAME ""
} elseif { ![ string match "" $SYSTEM_INSTANCE_NAME ] } { 
  set SYSTEM_INSTANCE_NAME "/$SYSTEM_INSTANCE_NAME"
}

if ![info exists TOP_LEVEL_NAME] { 
  set TOP_LEVEL_NAME "DE0_nano_system"
}

if ![info exists QSYS_SIMDIR] { 
  set QSYS_SIMDIR "./../"
}

if ![info exists QUARTUS_INSTALL_DIR] { 
  set QUARTUS_INSTALL_DIR "C:/intelfpga_lite/17.1/quartus/"
}

if ![info exists USER_DEFINED_COMPILE_OPTIONS] { 
  set USER_DEFINED_COMPILE_OPTIONS ""
}
if ![info exists USER_DEFINED_VHDL_COMPILE_OPTIONS] { 
  set USER_DEFINED_VHDL_COMPILE_OPTIONS ""
}
if ![info exists USER_DEFINED_VERILOG_COMPILE_OPTIONS] { 
  set USER_DEFINED_VERILOG_COMPILE_OPTIONS ""
}
if ![info exists USER_DEFINED_ELAB_OPTIONS] { 
  set USER_DEFINED_ELAB_OPTIONS ""
}

# ----------------------------------------
# Initialize simulation properties - DO NOT MODIFY!
set ELAB_OPTIONS ""
set SIM_OPTIONS ""
if ![ string match "*-64 vsim*" [ vsim -version ] ] {
} else {
}

# ----------------------------------------
# Copy ROM/RAM files to simulation directory
alias file_copy {
  echo "\[exec\] file_copy"
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_bht_ram.dat ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_bht_ram.hex ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_bht_ram.mif ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_dc_tag_ram.dat ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_dc_tag_ram.hex ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_dc_tag_ram.mif ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ic_tag_ram.dat ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ic_tag_ram.hex ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ic_tag_ram.mif ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ociram_default_contents.dat ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ociram_default_contents.hex ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ociram_default_contents.mif ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_a.dat ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_a.hex ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_a.mif ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_b.dat ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_b.hex ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_b.mif ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_onchip_mem.hex ./
  file copy -force $QSYS_SIMDIR/submodules/DE0_nano_system_epcs_boot_rom.hex ./
}

# ----------------------------------------
# Create compilation libraries
proc ensure_lib { lib } { if ![file isdirectory $lib] { vlib $lib } }
ensure_lib          ./libraries/     
ensure_lib          ./libraries/work/
vmap       work     ./libraries/work/
vmap       work_lib ./libraries/work/
if ![ string match "*ModelSim ALTERA*" [ vsim -version ] ] {
  ensure_lib                  ./libraries/altera_ver/      
  vmap       altera_ver       ./libraries/altera_ver/      
  ensure_lib                  ./libraries/lpm_ver/         
  vmap       lpm_ver          ./libraries/lpm_ver/         
  ensure_lib                  ./libraries/sgate_ver/       
  vmap       sgate_ver        ./libraries/sgate_ver/       
  ensure_lib                  ./libraries/altera_mf_ver/   
  vmap       altera_mf_ver    ./libraries/altera_mf_ver/   
  ensure_lib                  ./libraries/altera_lnsim_ver/
  vmap       altera_lnsim_ver ./libraries/altera_lnsim_ver/
  ensure_lib                  ./libraries/cycloneive_ver/  
  vmap       cycloneive_ver   ./libraries/cycloneive_ver/  
  ensure_lib                  ./libraries/altera/          
  vmap       altera           ./libraries/altera/          
  ensure_lib                  ./libraries/lpm/             
  vmap       lpm              ./libraries/lpm/             
  ensure_lib                  ./libraries/sgate/           
  vmap       sgate            ./libraries/sgate/           
  ensure_lib                  ./libraries/altera_mf/       
  vmap       altera_mf        ./libraries/altera_mf/       
  ensure_lib                  ./libraries/altera_lnsim/    
  vmap       altera_lnsim     ./libraries/altera_lnsim/    
  ensure_lib                  ./libraries/cycloneive/      
  vmap       cycloneive       ./libraries/cycloneive/      
}
ensure_lib                                            ./libraries/error_adapter_0/                           
vmap       error_adapter_0                            ./libraries/error_adapter_0/                           
ensure_lib                                            ./libraries/rsp_mux/                                   
vmap       rsp_mux                                    ./libraries/rsp_mux/                                   
ensure_lib                                            ./libraries/rsp_demux/                                 
vmap       rsp_demux                                  ./libraries/rsp_demux/                                 
ensure_lib                                            ./libraries/cmd_mux/                                   
vmap       cmd_mux                                    ./libraries/cmd_mux/                                   
ensure_lib                                            ./libraries/cmd_demux/                                 
vmap       cmd_demux                                  ./libraries/cmd_demux/                                 
ensure_lib                                            ./libraries/router_001/                                
vmap       router_001                                 ./libraries/router_001/                                
ensure_lib                                            ./libraries/router/                                    
vmap       router                                     ./libraries/router/                                    
ensure_lib                                            ./libraries/avalon_st_adapter_005/                     
vmap       avalon_st_adapter_005                      ./libraries/avalon_st_adapter_005/                     
ensure_lib                                            ./libraries/avalon_st_adapter/                         
vmap       avalon_st_adapter                          ./libraries/avalon_st_adapter/                         
ensure_lib                                            ./libraries/crosser/                                   
vmap       crosser                                    ./libraries/crosser/                                   
ensure_lib                                            ./libraries/sdram_s1_rsp_width_adapter/                
vmap       sdram_s1_rsp_width_adapter                 ./libraries/sdram_s1_rsp_width_adapter/                
ensure_lib                                            ./libraries/rsp_mux_001/                               
vmap       rsp_mux_001                                ./libraries/rsp_mux_001/                               
ensure_lib                                            ./libraries/rsp_demux_002/                             
vmap       rsp_demux_002                              ./libraries/rsp_demux_002/                             
ensure_lib                                            ./libraries/rsp_demux_001/                             
vmap       rsp_demux_001                              ./libraries/rsp_demux_001/                             
ensure_lib                                            ./libraries/cmd_mux_001/                               
vmap       cmd_mux_001                                ./libraries/cmd_mux_001/                               
ensure_lib                                            ./libraries/cmd_demux_001/                             
vmap       cmd_demux_001                              ./libraries/cmd_demux_001/                             
ensure_lib                                            ./libraries/sdram_s1_burst_adapter/                    
vmap       sdram_s1_burst_adapter                     ./libraries/sdram_s1_burst_adapter/                    
ensure_lib                                            ./libraries/nios2_cpu_data_master_limiter/             
vmap       nios2_cpu_data_master_limiter              ./libraries/nios2_cpu_data_master_limiter/             
ensure_lib                                            ./libraries/router_007/                                
vmap       router_007                                 ./libraries/router_007/                                
ensure_lib                                            ./libraries/router_003/                                
vmap       router_003                                 ./libraries/router_003/                                
ensure_lib                                            ./libraries/router_002/                                
vmap       router_002                                 ./libraries/router_002/                                
ensure_lib                                            ./libraries/jtag_uart_avalon_jtag_slave_agent_rsp_fifo/
vmap       jtag_uart_avalon_jtag_slave_agent_rsp_fifo ./libraries/jtag_uart_avalon_jtag_slave_agent_rsp_fifo/
ensure_lib                                            ./libraries/jtag_uart_avalon_jtag_slave_agent/         
vmap       jtag_uart_avalon_jtag_slave_agent          ./libraries/jtag_uart_avalon_jtag_slave_agent/         
ensure_lib                                            ./libraries/nios2_cpu_data_master_agent/               
vmap       nios2_cpu_data_master_agent                ./libraries/nios2_cpu_data_master_agent/               
ensure_lib                                            ./libraries/jtag_uart_avalon_jtag_slave_translator/    
vmap       jtag_uart_avalon_jtag_slave_translator     ./libraries/jtag_uart_avalon_jtag_slave_translator/    
ensure_lib                                            ./libraries/nios2_cpu_data_master_translator/          
vmap       nios2_cpu_data_master_translator           ./libraries/nios2_cpu_data_master_translator/          
ensure_lib                                            ./libraries/cpu/                                       
vmap       cpu                                        ./libraries/cpu/                                       
ensure_lib                                            ./libraries/rst_controller/                            
vmap       rst_controller                             ./libraries/rst_controller/                            
ensure_lib                                            ./libraries/irq_synchronizer/                          
vmap       irq_synchronizer                           ./libraries/irq_synchronizer/                          
ensure_lib                                            ./libraries/irq_mapper/                                
vmap       irq_mapper                                 ./libraries/irq_mapper/                                
ensure_lib                                            ./libraries/mm_interconnect_1/                         
vmap       mm_interconnect_1                          ./libraries/mm_interconnect_1/                         
ensure_lib                                            ./libraries/mm_interconnect_0/                         
vmap       mm_interconnect_0                          ./libraries/mm_interconnect_0/                         
ensure_lib                                            ./libraries/xbee_uart/                                 
vmap       xbee_uart                                  ./libraries/xbee_uart/                                 
ensure_lib                                            ./libraries/timer/                                     
vmap       timer                                      ./libraries/timer/                                     
ensure_lib                                            ./libraries/sysid_qsys/                                
vmap       sysid_qsys                                 ./libraries/sysid_qsys/                                
ensure_lib                                            ./libraries/sdram/                                     
vmap       sdram                                      ./libraries/sdram/                                     
ensure_lib                                            ./libraries/pio_switch/                                
vmap       pio_switch                                 ./libraries/pio_switch/                                
ensure_lib                                            ./libraries/pio_leds/                                  
vmap       pio_leds                                   ./libraries/pio_leds/                                  
ensure_lib                                            ./libraries/pio_key/                                   
vmap       pio_key                                    ./libraries/pio_key/                                   
ensure_lib                                            ./libraries/onchip_mem/                                
vmap       onchip_mem                                 ./libraries/onchip_mem/                                
ensure_lib                                            ./libraries/nios2_cpu/                                 
vmap       nios2_cpu                                  ./libraries/nios2_cpu/                                 
ensure_lib                                            ./libraries/jtag_uart/                                 
vmap       jtag_uart                                  ./libraries/jtag_uart/                                 
ensure_lib                                            ./libraries/i2c_scl/                                   
vmap       i2c_scl                                    ./libraries/i2c_scl/                                   
ensure_lib                                            ./libraries/i2c_EXT_sda/                               
vmap       i2c_EXT_sda                                ./libraries/i2c_EXT_sda/                               
ensure_lib                                            ./libraries/g_sensor_int/                              
vmap       g_sensor_int                               ./libraries/g_sensor_int/                              
ensure_lib                                            ./libraries/ext_sensor_int/                            
vmap       ext_sensor_int                             ./libraries/ext_sensor_int/                            
ensure_lib                                            ./libraries/epcs/                                      
vmap       epcs                                       ./libraries/epcs/                                      
ensure_lib                                            ./libraries/clock_crossing_bridge_IO/                  
vmap       clock_crossing_bridge_IO                   ./libraries/clock_crossing_bridge_IO/                  
ensure_lib                                            ./libraries/altpll_sys/                                
vmap       altpll_sys                                 ./libraries/altpll_sys/                                
ensure_lib                                            ./libraries/adc_spi_int/                               
vmap       adc_spi_int                                ./libraries/adc_spi_int/                               

# ----------------------------------------
# Compile device library files
alias dev_com {
  echo "\[exec\] dev_com"
  if ![ string match "*ModelSim ALTERA*" [ vsim -version ] ] {
    eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives.v"              -work altera_ver      
    eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/220model.v"                       -work lpm_ver         
    eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate.v"                          -work sgate_ver       
    eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf.v"                      -work altera_mf_ver   
    eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_lnsim.sv"                  -work altera_lnsim_ver
    eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/cycloneive_atoms.v"               -work cycloneive_ver  
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_syn_attributes.vhd"        -work altera          
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_standard_functions.vhd"    -work altera          
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/alt_dspbuilder_package.vhd"       -work altera          
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_europa_support_lib.vhd"    -work altera          
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives_components.vhd" -work altera          
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives.vhd"            -work altera          
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/220pack.vhd"                      -work lpm             
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/220model.vhd"                     -work lpm             
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate_pack.vhd"                   -work sgate           
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate.vhd"                        -work sgate           
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf_components.vhd"         -work altera_mf       
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf.vhd"                    -work altera_mf       
    eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QUARTUS_INSTALL_DIR/eda/sim_lib/mentor/altera_lnsim_for_vhdl.sv"  -work altera_lnsim    
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_lnsim_components.vhd"      -work altera_lnsim    
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/cycloneive_atoms.vhd"             -work cycloneive      
    eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QUARTUS_INSTALL_DIR/eda/sim_lib/cycloneive_components.vhd"        -work cycloneive      
  }
}

# ----------------------------------------
# Compile the design files in correct order
alias com {
  echo "\[exec\] com"
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_avalon_st_adapter_005_error_adapter_0.sv" -work error_adapter_0                           
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_avalon_st_adapter_error_adapter_0.sv"     -work error_adapter_0                           
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_rsp_mux.sv"                               -work rsp_mux                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work rsp_mux                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_rsp_demux.sv"                             -work rsp_demux                                 
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_cmd_mux.sv"                               -work cmd_mux                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work cmd_mux                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_cmd_demux.sv"                             -work cmd_demux                                 
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_router_001.sv"                            -work router_001                                
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_router.sv"                                -work router                                    
  eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_avalon_st_adapter_005.vhd"                -work avalon_st_adapter_005                     
  eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_avalon_st_adapter.vhd"                    -work avalon_st_adapter                         
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_handshake_clock_crosser.v"                                 -work crosser                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_clock_crosser.v"                                           -work crosser                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_pipeline_base.v"                                           -work crosser                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_std_synchronizer_nocut.v"                                            -work crosser                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_width_adapter.sv"                                             -work sdram_s1_rsp_width_adapter                
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_address_alignment.sv"                                         -work sdram_s1_rsp_width_adapter                
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_uncompressor.sv"                                        -work sdram_s1_rsp_width_adapter                
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_rsp_mux_001.sv"                           -work rsp_mux_001                               
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work rsp_mux_001                               
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_rsp_mux.sv"                               -work rsp_mux                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work rsp_mux                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_rsp_demux_002.sv"                         -work rsp_demux_002                             
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_rsp_demux_001.sv"                         -work rsp_demux_001                             
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_rsp_demux.sv"                             -work rsp_demux                                 
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_cmd_mux_001.sv"                           -work cmd_mux_001                               
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work cmd_mux_001                               
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_cmd_mux.sv"                               -work cmd_mux                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work cmd_mux                                   
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_cmd_demux_001.sv"                         -work cmd_demux_001                             
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_cmd_demux.sv"                             -work cmd_demux                                 
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_adapter.sv"                                             -work sdram_s1_burst_adapter                    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_adapter_uncmpr.sv"                                      -work sdram_s1_burst_adapter                    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_adapter_13_1.sv"                                        -work sdram_s1_burst_adapter                    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_adapter_new.sv"                                         -work sdram_s1_burst_adapter                    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_incr_burst_converter.sv"                                             -work sdram_s1_burst_adapter                    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_wrap_burst_converter.sv"                                             -work sdram_s1_burst_adapter                    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_default_burst_converter.sv"                                          -work sdram_s1_burst_adapter                    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_address_alignment.sv"                                         -work sdram_s1_burst_adapter                    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_pipeline_stage.sv"                                         -work sdram_s1_burst_adapter                    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_pipeline_base.v"                                           -work sdram_s1_burst_adapter                    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_traffic_limiter.sv"                                           -work nios2_cpu_data_master_limiter             
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_reorder_memory.sv"                                            -work nios2_cpu_data_master_limiter             
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_sc_fifo.v"                                                    -work nios2_cpu_data_master_limiter             
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_pipeline_base.v"                                           -work nios2_cpu_data_master_limiter             
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_router_007.sv"                            -work router_007                                
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_router_003.sv"                            -work router_003                                
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_router_002.sv"                            -work router_002                                
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_router_001.sv"                            -work router_001                                
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_router.sv"                                -work router                                    
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_avalon_sc_fifo.v"                                                    -work jtag_uart_avalon_jtag_slave_agent_rsp_fifo
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_slave_agent.sv"                                               -work jtag_uart_avalon_jtag_slave_agent         
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_uncompressor.sv"                                        -work jtag_uart_avalon_jtag_slave_agent         
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_master_agent.sv"                                              -work nios2_cpu_data_master_agent               
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_slave_translator.sv"                                          -work jtag_uart_avalon_jtag_slave_translator    
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_master_translator.sv"                                         -work nios2_cpu_data_master_translator          
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu.vo"                                           -work cpu                                       
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_debug_slave_sysclk.v"                         -work cpu                                       
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_debug_slave_tck.v"                            -work cpu                                       
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_debug_slave_wrapper.v"                        -work cpu                                       
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_mult_cell.v"                                  -work cpu                                       
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_test_bench.v"                                 -work cpu                                       
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_reset_controller.v"                                                  -work rst_controller                            
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_reset_synchronizer.v"                                                -work rst_controller                            
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_irq_clock_crosser.sv"                                                -work irq_synchronizer                          
  eval  vlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_irq_mapper.sv"                                              -work irq_mapper                                
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1.v"                                        -work mm_interconnect_1                         
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0.v"                                        -work mm_interconnect_0                         
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_xbee_uart.v"                                                -work xbee_uart                                 
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_timer.v"                                                    -work timer                                     
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_sysid_qsys.v"                                               -work sysid_qsys                                
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_sdram.v"                                                    -work sdram                                     
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_pio_switch.v"                                               -work pio_switch                                
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_pio_leds.v"                                                 -work pio_leds                                  
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_pio_key.v"                                                  -work pio_key                                   
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_onchip_mem.v"                                               -work onchip_mem                                
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu.v"                                                -work nios2_cpu                                 
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_jtag_uart.v"                                                -work jtag_uart                                 
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_i2c_scl.v"                                                  -work i2c_scl                                   
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_i2c_EXT_sda.v"                                              -work i2c_EXT_sda                               
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_g_sensor_int.v"                                             -work g_sensor_int                              
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_ext_sensor_int.v"                                           -work ext_sensor_int                            
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_epcs.v"                                                     -work epcs                                      
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_avalon_mm_clock_crossing_bridge.v"                                   -work clock_crossing_bridge_IO                  
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_avalon_dc_fifo.v"                                                    -work clock_crossing_bridge_IO                  
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_dcfifo_synchronizer_bundle.v"                                        -work clock_crossing_bridge_IO                  
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_std_synchronizer_nocut.v"                                            -work clock_crossing_bridge_IO                  
  eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QSYS_SIMDIR/submodules/DE0_nano_system_altpll_sys.vho"                                             -work altpll_sys                                
  eval  vlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_adc_spi_int.v"                                              -work adc_spi_int                               
  eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QSYS_SIMDIR/DE0_nano_system.vhd"                                                                                                                   
  eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QSYS_SIMDIR/de0_nano_system_rst_controller.vhd"                                                                                                    
  eval  vcom $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS        "$QSYS_SIMDIR/de0_nano_system_rst_controller_001.vhd"                                                                                                
}

# ----------------------------------------
# Elaborate top level design
alias elab {
  echo "\[exec\] elab"
  eval vsim -t ps $ELAB_OPTIONS $USER_DEFINED_ELAB_OPTIONS -L work -L work_lib -L error_adapter_0 -L rsp_mux -L rsp_demux -L cmd_mux -L cmd_demux -L router_001 -L router -L avalon_st_adapter_005 -L avalon_st_adapter -L crosser -L sdram_s1_rsp_width_adapter -L rsp_mux_001 -L rsp_demux_002 -L rsp_demux_001 -L cmd_mux_001 -L cmd_demux_001 -L sdram_s1_burst_adapter -L nios2_cpu_data_master_limiter -L router_007 -L router_003 -L router_002 -L jtag_uart_avalon_jtag_slave_agent_rsp_fifo -L jtag_uart_avalon_jtag_slave_agent -L nios2_cpu_data_master_agent -L jtag_uart_avalon_jtag_slave_translator -L nios2_cpu_data_master_translator -L cpu -L rst_controller -L irq_synchronizer -L irq_mapper -L mm_interconnect_1 -L mm_interconnect_0 -L xbee_uart -L timer -L sysid_qsys -L sdram -L pio_switch -L pio_leds -L pio_key -L onchip_mem -L nios2_cpu -L jtag_uart -L i2c_scl -L i2c_EXT_sda -L g_sensor_int -L ext_sensor_int -L epcs -L clock_crossing_bridge_IO -L altpll_sys -L adc_spi_int -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L cycloneive $TOP_LEVEL_NAME
}

# ----------------------------------------
# Elaborate the top level design with novopt option
alias elab_debug {
  echo "\[exec\] elab_debug"
  eval vsim -novopt -t ps $ELAB_OPTIONS $USER_DEFINED_ELAB_OPTIONS -L work -L work_lib -L error_adapter_0 -L rsp_mux -L rsp_demux -L cmd_mux -L cmd_demux -L router_001 -L router -L avalon_st_adapter_005 -L avalon_st_adapter -L crosser -L sdram_s1_rsp_width_adapter -L rsp_mux_001 -L rsp_demux_002 -L rsp_demux_001 -L cmd_mux_001 -L cmd_demux_001 -L sdram_s1_burst_adapter -L nios2_cpu_data_master_limiter -L router_007 -L router_003 -L router_002 -L jtag_uart_avalon_jtag_slave_agent_rsp_fifo -L jtag_uart_avalon_jtag_slave_agent -L nios2_cpu_data_master_agent -L jtag_uart_avalon_jtag_slave_translator -L nios2_cpu_data_master_translator -L cpu -L rst_controller -L irq_synchronizer -L irq_mapper -L mm_interconnect_1 -L mm_interconnect_0 -L xbee_uart -L timer -L sysid_qsys -L sdram -L pio_switch -L pio_leds -L pio_key -L onchip_mem -L nios2_cpu -L jtag_uart -L i2c_scl -L i2c_EXT_sda -L g_sensor_int -L ext_sensor_int -L epcs -L clock_crossing_bridge_IO -L altpll_sys -L adc_spi_int -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L cycloneive $TOP_LEVEL_NAME
}

# ----------------------------------------
# Compile all the design files and elaborate the top level design
alias ld "
  dev_com
  com
  elab
"

# ----------------------------------------
# Compile all the design files and elaborate the top level design with -novopt
alias ld_debug "
  dev_com
  com
  elab_debug
"

# ----------------------------------------
# Print out user commmand line aliases
alias h {
  echo "List Of Command Line Aliases"
  echo
  echo "file_copy                                         -- Copy ROM/RAM files to simulation directory"
  echo
  echo "dev_com                                           -- Compile device library files"
  echo
  echo "com                                               -- Compile the design files in correct order"
  echo
  echo "elab                                              -- Elaborate top level design"
  echo
  echo "elab_debug                                        -- Elaborate the top level design with novopt option"
  echo
  echo "ld                                                -- Compile all the design files and elaborate the top level design"
  echo
  echo "ld_debug                                          -- Compile all the design files and elaborate the top level design with -novopt"
  echo
  echo 
  echo
  echo "List Of Variables"
  echo
  echo "TOP_LEVEL_NAME                                    -- Top level module name."
  echo "                                                     For most designs, this should be overridden"
  echo "                                                     to enable the elab/elab_debug aliases."
  echo
  echo "SYSTEM_INSTANCE_NAME                              -- Instantiated system module name inside top level module."
  echo
  echo "QSYS_SIMDIR                                       -- Platform Designer base simulation directory."
  echo
  echo "QUARTUS_INSTALL_DIR                               -- Quartus installation directory."
  echo
  echo "USER_DEFINED_COMPILE_OPTIONS                      -- User-defined compile options, added to com/dev_com aliases."
  echo
  echo "USER_DEFINED_ELAB_OPTIONS                         -- User-defined elaboration options, added to elab/elab_debug aliases."
  echo
  echo "USER_DEFINED_VHDL_COMPILE_OPTIONS                 -- User-defined vhdl compile options, added to com/dev_com aliases."
  echo
  echo "USER_DEFINED_VERILOG_COMPILE_OPTIONS              -- User-defined verilog compile options, added to com/dev_com aliases."
}
file_copy
h
