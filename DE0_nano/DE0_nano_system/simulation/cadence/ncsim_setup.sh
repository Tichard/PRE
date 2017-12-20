
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

# ACDS 17.1 590 win32 2017.11.23.17:08:06

# ----------------------------------------
# ncsim - auto-generated simulation script

# ----------------------------------------
# This script provides commands to simulate the following IP detected in
# your Quartus project:
#     DE0_nano_system
# 
# Altera recommends that you source this Quartus-generated IP simulation
# script from your own customized top-level script, and avoid editing this
# generated script.
# 
# To write a top-level shell script that compiles Altera simulation libraries
# and the Quartus-generated IP in your project, along with your design and
# testbench files, copy the text from the TOP-LEVEL TEMPLATE section below
# into a new file, e.g. named "ncsim.sh", and modify text as directed.
# 
# You can also modify the simulation flow to suit your needs. Set the
# following variables to 1 to disable their corresponding processes:
# - SKIP_FILE_COPY: skip copying ROM/RAM initialization files
# - SKIP_DEV_COM: skip compiling the Quartus EDA simulation library
# - SKIP_COM: skip compiling Quartus-generated IP simulation files
# - SKIP_ELAB and SKIP_SIM: skip elaboration and simulation
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
# # the simulator. In this case, you must also copy the generated files
# # "cds.lib" and "hdl.var" - plus the directory "cds_libs" if generated - 
# # into the location from which you launch the simulator, or incorporate
# # into any existing library setup.
# #
# # Run Quartus-generated IP simulation script once to compile Quartus EDA
# # simulation libraries and Quartus-generated IP simulation files, and copy
# # any ROM/RAM initialization files to the simulation directory.
# # - If necessary, specify any compilation options:
# #   USER_DEFINED_COMPILE_OPTIONS
# #   USER_DEFINED_VHDL_COMPILE_OPTIONS applied to vhdl compiler
# #   USER_DEFINED_VERILOG_COMPILE_OPTIONS applied to verilog compiler
# #
# source <script generation output directory>/cadence/ncsim_setup.sh \
# SKIP_ELAB=1 \
# SKIP_SIM=1 \
# USER_DEFINED_COMPILE_OPTIONS=<compilation options for your design> \
# USER_DEFINED_VHDL_COMPILE_OPTIONS=<VHDL compilation options for your design> \
# USER_DEFINED_VERILOG_COMPILE_OPTIONS=<Verilog compilation options for your design> \
# QSYS_SIMDIR=<script generation output directory>
# #
# # Compile all design files and testbench files, including the top level.
# # (These are all the files required for simulation other than the files
# # compiled by the IP script)
# #
# ncvlog <compilation options> <design and testbench files>
# #
# # TOP_LEVEL_NAME is used in this script to set the top-level simulation or
# # testbench module/entity name.
# #
# # Run the IP script again to elaborate and simulate the top level:
# # - Specify TOP_LEVEL_NAME and USER_DEFINED_ELAB_OPTIONS.
# # - Override the default USER_DEFINED_SIM_OPTIONS. For example, to run
# #   until $finish(), set to an empty string: USER_DEFINED_SIM_OPTIONS="".
# #
# source <script generation output directory>/cadence/ncsim_setup.sh \
# SKIP_FILE_COPY=1 \
# SKIP_DEV_COM=1 \
# SKIP_COM=1 \
# TOP_LEVEL_NAME=<simulation top> \
# USER_DEFINED_ELAB_OPTIONS=<elaboration options for your design> \
# USER_DEFINED_SIM_OPTIONS=<simulation options for your design>
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
# initialize variables
TOP_LEVEL_NAME="DE0_nano_system"
QSYS_SIMDIR="./../"
QUARTUS_INSTALL_DIR="C:/intelfpga_lite/17.1/quartus/"
SKIP_FILE_COPY=0
SKIP_DEV_COM=0
SKIP_COM=0
SKIP_ELAB=0
SKIP_SIM=0
USER_DEFINED_ELAB_OPTIONS=""
USER_DEFINED_SIM_OPTIONS="-input \"@run 100; exit\""

# ----------------------------------------
# overwrite variables - DO NOT MODIFY!
# This block evaluates each command line argument, typically used for 
# overwriting variables. An example usage:
#   sh <simulator>_setup.sh SKIP_SIM=1
for expression in "$@"; do
  eval $expression
  if [ $? -ne 0 ]; then
    echo "Error: This command line argument, \"$expression\", is/has an invalid expression." >&2
    exit $?
  fi
done

# ----------------------------------------
# initialize simulation properties - DO NOT MODIFY!
ELAB_OPTIONS=""
SIM_OPTIONS=""
if [[ `ncsim -version` != *"ncsim(64)"* ]]; then
  :
else
  :
fi

# ----------------------------------------
# create compilation libraries
mkdir -p ./libraries/work/
mkdir -p ./libraries/error_adapter_0/
mkdir -p ./libraries/rsp_mux/
mkdir -p ./libraries/rsp_demux/
mkdir -p ./libraries/cmd_mux/
mkdir -p ./libraries/cmd_demux/
mkdir -p ./libraries/router_001/
mkdir -p ./libraries/router/
mkdir -p ./libraries/avalon_st_adapter_005/
mkdir -p ./libraries/avalon_st_adapter/
mkdir -p ./libraries/crosser/
mkdir -p ./libraries/sdram_s1_rsp_width_adapter/
mkdir -p ./libraries/rsp_mux_001/
mkdir -p ./libraries/rsp_demux_002/
mkdir -p ./libraries/rsp_demux_001/
mkdir -p ./libraries/cmd_mux_001/
mkdir -p ./libraries/cmd_demux_001/
mkdir -p ./libraries/sdram_s1_burst_adapter/
mkdir -p ./libraries/nios2_cpu_data_master_limiter/
mkdir -p ./libraries/router_007/
mkdir -p ./libraries/router_003/
mkdir -p ./libraries/router_002/
mkdir -p ./libraries/jtag_uart_avalon_jtag_slave_agent_rsp_fifo/
mkdir -p ./libraries/jtag_uart_avalon_jtag_slave_agent/
mkdir -p ./libraries/nios2_cpu_data_master_agent/
mkdir -p ./libraries/jtag_uart_avalon_jtag_slave_translator/
mkdir -p ./libraries/nios2_cpu_data_master_translator/
mkdir -p ./libraries/cpu/
mkdir -p ./libraries/rst_controller/
mkdir -p ./libraries/irq_synchronizer/
mkdir -p ./libraries/irq_mapper/
mkdir -p ./libraries/mm_interconnect_1/
mkdir -p ./libraries/mm_interconnect_0/
mkdir -p ./libraries/xbee_uart/
mkdir -p ./libraries/timer/
mkdir -p ./libraries/sysid_qsys/
mkdir -p ./libraries/sdram/
mkdir -p ./libraries/pio_switch/
mkdir -p ./libraries/pio_leds/
mkdir -p ./libraries/pio_key/
mkdir -p ./libraries/onchip_mem/
mkdir -p ./libraries/nios2_cpu/
mkdir -p ./libraries/jtag_uart/
mkdir -p ./libraries/i2c_scl/
mkdir -p ./libraries/i2c_EXT_sda/
mkdir -p ./libraries/g_sensor_int/
mkdir -p ./libraries/ext_sensor_int/
mkdir -p ./libraries/epcs/
mkdir -p ./libraries/clock_crossing_bridge_IO/
mkdir -p ./libraries/altpll_sys/
mkdir -p ./libraries/adc_spi_int/
mkdir -p ./libraries/altera_ver/
mkdir -p ./libraries/lpm_ver/
mkdir -p ./libraries/sgate_ver/
mkdir -p ./libraries/altera_mf_ver/
mkdir -p ./libraries/cycloneive_ver/
mkdir -p ./libraries/altera/
mkdir -p ./libraries/lpm/
mkdir -p ./libraries/sgate/
mkdir -p ./libraries/altera_mf/
mkdir -p ./libraries/altera_lnsim/
mkdir -p ./libraries/cycloneive/

# ----------------------------------------
# copy RAM/ROM files to simulation directory
if [ $SKIP_FILE_COPY -eq 0 ]; then
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_bht_ram.dat ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_bht_ram.hex ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_bht_ram.mif ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_dc_tag_ram.dat ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_dc_tag_ram.hex ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_dc_tag_ram.mif ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ic_tag_ram.dat ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ic_tag_ram.hex ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ic_tag_ram.mif ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ociram_default_contents.dat ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ociram_default_contents.hex ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_ociram_default_contents.mif ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_a.dat ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_a.hex ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_a.mif ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_b.dat ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_b.hex ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_rf_ram_b.mif ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_onchip_mem.hex ./
  cp -f $QSYS_SIMDIR/submodules/DE0_nano_system_epcs_boot_rom.hex ./
fi

# ----------------------------------------
# compile device library files
if [ $SKIP_DEV_COM -eq 0 ]; then
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives.v"              -work altera_ver    
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/220model.v"                       -work lpm_ver       
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate.v"                          -work sgate_ver     
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf.v"                      -work altera_mf_ver 
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/cycloneive_atoms.v"               -work cycloneive_ver
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_syn_attributes.vhd"        -work altera        
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_standard_functions.vhd"    -work altera        
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/alt_dspbuilder_package.vhd"       -work altera        
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_europa_support_lib.vhd"    -work altera        
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives_components.vhd" -work altera        
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives.vhd"            -work altera        
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/220pack.vhd"                      -work lpm           
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/220model.vhd"                     -work lpm           
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate_pack.vhd"                   -work sgate         
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate.vhd"                        -work sgate         
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf_components.vhd"         -work altera_mf     
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf.vhd"                    -work altera_mf     
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_lnsim.sv"                  -work altera_lnsim  
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_lnsim_components.vhd"      -work altera_lnsim  
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/cycloneive_atoms.vhd"             -work cycloneive    
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QUARTUS_INSTALL_DIR/eda/sim_lib/cycloneive_components.vhd"        -work cycloneive    
fi

# ----------------------------------------
# compile design files in correct order
if [ $SKIP_COM -eq 0 ]; then
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_avalon_st_adapter_005_error_adapter_0.sv" -work error_adapter_0                            -cdslib ./cds_libs/error_adapter_0.cds.lib                           
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_avalon_st_adapter_error_adapter_0.sv"     -work error_adapter_0                            -cdslib ./cds_libs/error_adapter_0.cds.lib                           
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_rsp_mux.sv"                               -work rsp_mux                                    -cdslib ./cds_libs/rsp_mux.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work rsp_mux                                    -cdslib ./cds_libs/rsp_mux.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_rsp_demux.sv"                             -work rsp_demux                                  -cdslib ./cds_libs/rsp_demux.cds.lib                                 
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_cmd_mux.sv"                               -work cmd_mux                                    -cdslib ./cds_libs/cmd_mux.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work cmd_mux                                    -cdslib ./cds_libs/cmd_mux.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_cmd_demux.sv"                             -work cmd_demux                                  -cdslib ./cds_libs/cmd_demux.cds.lib                                 
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_router_001.sv"                            -work router_001                                 -cdslib ./cds_libs/router_001.cds.lib                                
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1_router.sv"                                -work router                                     -cdslib ./cds_libs/router.cds.lib                                    
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_avalon_st_adapter_005.vhd"                -work avalon_st_adapter_005                      -cdslib ./cds_libs/avalon_st_adapter_005.cds.lib                     
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_avalon_st_adapter.vhd"                    -work avalon_st_adapter                          -cdslib ./cds_libs/avalon_st_adapter.cds.lib                         
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_handshake_clock_crosser.v"                                 -work crosser                                    -cdslib ./cds_libs/crosser.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_clock_crosser.v"                                           -work crosser                                    -cdslib ./cds_libs/crosser.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_pipeline_base.v"                                           -work crosser                                    -cdslib ./cds_libs/crosser.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_std_synchronizer_nocut.v"                                            -work crosser                                    -cdslib ./cds_libs/crosser.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_width_adapter.sv"                                             -work sdram_s1_rsp_width_adapter                 -cdslib ./cds_libs/sdram_s1_rsp_width_adapter.cds.lib                
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_address_alignment.sv"                                         -work sdram_s1_rsp_width_adapter                 -cdslib ./cds_libs/sdram_s1_rsp_width_adapter.cds.lib                
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_uncompressor.sv"                                        -work sdram_s1_rsp_width_adapter                 -cdslib ./cds_libs/sdram_s1_rsp_width_adapter.cds.lib                
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_rsp_mux_001.sv"                           -work rsp_mux_001                                -cdslib ./cds_libs/rsp_mux_001.cds.lib                               
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work rsp_mux_001                                -cdslib ./cds_libs/rsp_mux_001.cds.lib                               
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_rsp_mux.sv"                               -work rsp_mux                                    -cdslib ./cds_libs/rsp_mux.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work rsp_mux                                    -cdslib ./cds_libs/rsp_mux.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_rsp_demux_002.sv"                         -work rsp_demux_002                              -cdslib ./cds_libs/rsp_demux_002.cds.lib                             
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_rsp_demux_001.sv"                         -work rsp_demux_001                              -cdslib ./cds_libs/rsp_demux_001.cds.lib                             
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_rsp_demux.sv"                             -work rsp_demux                                  -cdslib ./cds_libs/rsp_demux.cds.lib                                 
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_cmd_mux_001.sv"                           -work cmd_mux_001                                -cdslib ./cds_libs/cmd_mux_001.cds.lib                               
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work cmd_mux_001                                -cdslib ./cds_libs/cmd_mux_001.cds.lib                               
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_cmd_mux.sv"                               -work cmd_mux                                    -cdslib ./cds_libs/cmd_mux.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                                                -work cmd_mux                                    -cdslib ./cds_libs/cmd_mux.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_cmd_demux_001.sv"                         -work cmd_demux_001                              -cdslib ./cds_libs/cmd_demux_001.cds.lib                             
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_cmd_demux.sv"                             -work cmd_demux                                  -cdslib ./cds_libs/cmd_demux.cds.lib                                 
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_adapter.sv"                                             -work sdram_s1_burst_adapter                     -cdslib ./cds_libs/sdram_s1_burst_adapter.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_adapter_uncmpr.sv"                                      -work sdram_s1_burst_adapter                     -cdslib ./cds_libs/sdram_s1_burst_adapter.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_adapter_13_1.sv"                                        -work sdram_s1_burst_adapter                     -cdslib ./cds_libs/sdram_s1_burst_adapter.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_adapter_new.sv"                                         -work sdram_s1_burst_adapter                     -cdslib ./cds_libs/sdram_s1_burst_adapter.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_incr_burst_converter.sv"                                             -work sdram_s1_burst_adapter                     -cdslib ./cds_libs/sdram_s1_burst_adapter.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_wrap_burst_converter.sv"                                             -work sdram_s1_burst_adapter                     -cdslib ./cds_libs/sdram_s1_burst_adapter.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_default_burst_converter.sv"                                          -work sdram_s1_burst_adapter                     -cdslib ./cds_libs/sdram_s1_burst_adapter.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_address_alignment.sv"                                         -work sdram_s1_burst_adapter                     -cdslib ./cds_libs/sdram_s1_burst_adapter.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_pipeline_stage.sv"                                         -work sdram_s1_burst_adapter                     -cdslib ./cds_libs/sdram_s1_burst_adapter.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_pipeline_base.v"                                           -work sdram_s1_burst_adapter                     -cdslib ./cds_libs/sdram_s1_burst_adapter.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_traffic_limiter.sv"                                           -work nios2_cpu_data_master_limiter              -cdslib ./cds_libs/nios2_cpu_data_master_limiter.cds.lib             
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_reorder_memory.sv"                                            -work nios2_cpu_data_master_limiter              -cdslib ./cds_libs/nios2_cpu_data_master_limiter.cds.lib             
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_sc_fifo.v"                                                    -work nios2_cpu_data_master_limiter              -cdslib ./cds_libs/nios2_cpu_data_master_limiter.cds.lib             
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_avalon_st_pipeline_base.v"                                           -work nios2_cpu_data_master_limiter              -cdslib ./cds_libs/nios2_cpu_data_master_limiter.cds.lib             
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_router_007.sv"                            -work router_007                                 -cdslib ./cds_libs/router_007.cds.lib                                
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_router_003.sv"                            -work router_003                                 -cdslib ./cds_libs/router_003.cds.lib                                
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_router_002.sv"                            -work router_002                                 -cdslib ./cds_libs/router_002.cds.lib                                
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_router_001.sv"                            -work router_001                                 -cdslib ./cds_libs/router_001.cds.lib                                
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0_router.sv"                                -work router                                     -cdslib ./cds_libs/router.cds.lib                                    
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_avalon_sc_fifo.v"                                                    -work jtag_uart_avalon_jtag_slave_agent_rsp_fifo -cdslib ./cds_libs/jtag_uart_avalon_jtag_slave_agent_rsp_fifo.cds.lib
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_slave_agent.sv"                                               -work jtag_uart_avalon_jtag_slave_agent          -cdslib ./cds_libs/jtag_uart_avalon_jtag_slave_agent.cds.lib         
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_burst_uncompressor.sv"                                        -work jtag_uart_avalon_jtag_slave_agent          -cdslib ./cds_libs/jtag_uart_avalon_jtag_slave_agent.cds.lib         
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_master_agent.sv"                                              -work nios2_cpu_data_master_agent                -cdslib ./cds_libs/nios2_cpu_data_master_agent.cds.lib               
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_slave_translator.sv"                                          -work jtag_uart_avalon_jtag_slave_translator     -cdslib ./cds_libs/jtag_uart_avalon_jtag_slave_translator.cds.lib    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_merlin_master_translator.sv"                                         -work nios2_cpu_data_master_translator           -cdslib ./cds_libs/nios2_cpu_data_master_translator.cds.lib          
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu.vo"                                           -work cpu                                        -cdslib ./cds_libs/cpu.cds.lib                                       
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_debug_slave_sysclk.v"                         -work cpu                                        -cdslib ./cds_libs/cpu.cds.lib                                       
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_debug_slave_tck.v"                            -work cpu                                        -cdslib ./cds_libs/cpu.cds.lib                                       
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_debug_slave_wrapper.v"                        -work cpu                                        -cdslib ./cds_libs/cpu.cds.lib                                       
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_mult_cell.v"                                  -work cpu                                        -cdslib ./cds_libs/cpu.cds.lib                                       
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu_cpu_test_bench.v"                                 -work cpu                                        -cdslib ./cds_libs/cpu.cds.lib                                       
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_reset_controller.v"                                                  -work rst_controller                             -cdslib ./cds_libs/rst_controller.cds.lib                            
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_reset_synchronizer.v"                                                -work rst_controller                             -cdslib ./cds_libs/rst_controller.cds.lib                            
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/altera_irq_clock_crosser.sv"                                                -work irq_synchronizer                           -cdslib ./cds_libs/irq_synchronizer.cds.lib                          
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/submodules/DE0_nano_system_irq_mapper.sv"                                              -work irq_mapper                                 -cdslib ./cds_libs/irq_mapper.cds.lib                                
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_1.v"                                        -work mm_interconnect_1                          -cdslib ./cds_libs/mm_interconnect_1.cds.lib                         
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_mm_interconnect_0.v"                                        -work mm_interconnect_0                          -cdslib ./cds_libs/mm_interconnect_0.cds.lib                         
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_xbee_uart.v"                                                -work xbee_uart                                  -cdslib ./cds_libs/xbee_uart.cds.lib                                 
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_timer.v"                                                    -work timer                                      -cdslib ./cds_libs/timer.cds.lib                                     
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_sysid_qsys.v"                                               -work sysid_qsys                                 -cdslib ./cds_libs/sysid_qsys.cds.lib                                
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_sdram.v"                                                    -work sdram                                      -cdslib ./cds_libs/sdram.cds.lib                                     
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_pio_switch.v"                                               -work pio_switch                                 -cdslib ./cds_libs/pio_switch.cds.lib                                
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_pio_leds.v"                                                 -work pio_leds                                   -cdslib ./cds_libs/pio_leds.cds.lib                                  
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_pio_key.v"                                                  -work pio_key                                    -cdslib ./cds_libs/pio_key.cds.lib                                   
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_onchip_mem.v"                                               -work onchip_mem                                 -cdslib ./cds_libs/onchip_mem.cds.lib                                
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_nios2_cpu.v"                                                -work nios2_cpu                                  -cdslib ./cds_libs/nios2_cpu.cds.lib                                 
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_jtag_uart.v"                                                -work jtag_uart                                  -cdslib ./cds_libs/jtag_uart.cds.lib                                 
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_i2c_scl.v"                                                  -work i2c_scl                                    -cdslib ./cds_libs/i2c_scl.cds.lib                                   
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_i2c_EXT_sda.v"                                              -work i2c_EXT_sda                                -cdslib ./cds_libs/i2c_EXT_sda.cds.lib                               
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_g_sensor_int.v"                                             -work g_sensor_int                               -cdslib ./cds_libs/g_sensor_int.cds.lib                              
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_ext_sensor_int.v"                                           -work ext_sensor_int                             -cdslib ./cds_libs/ext_sensor_int.cds.lib                            
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_epcs.v"                                                     -work epcs                                       -cdslib ./cds_libs/epcs.cds.lib                                      
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_avalon_mm_clock_crossing_bridge.v"                                   -work clock_crossing_bridge_IO                   -cdslib ./cds_libs/clock_crossing_bridge_IO.cds.lib                  
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_avalon_dc_fifo.v"                                                    -work clock_crossing_bridge_IO                   -cdslib ./cds_libs/clock_crossing_bridge_IO.cds.lib                  
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_dcfifo_synchronizer_bundle.v"                                        -work clock_crossing_bridge_IO                   -cdslib ./cds_libs/clock_crossing_bridge_IO.cds.lib                  
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/altera_std_synchronizer_nocut.v"                                            -work clock_crossing_bridge_IO                   -cdslib ./cds_libs/clock_crossing_bridge_IO.cds.lib                  
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QSYS_SIMDIR/submodules/DE0_nano_system_altpll_sys.vho"                                             -work altpll_sys                                 -cdslib ./cds_libs/altpll_sys.cds.lib                                
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/submodules/DE0_nano_system_adc_spi_int.v"                                              -work adc_spi_int                                -cdslib ./cds_libs/adc_spi_int.cds.lib                               
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QSYS_SIMDIR/DE0_nano_system.vhd"                                                                                                                                                                                         
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QSYS_SIMDIR/de0_nano_system_rst_controller.vhd"                                                                                                                                                                          
  ncvhdl -v93 $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS   "$QSYS_SIMDIR/de0_nano_system_rst_controller_001.vhd"                                                                                                                                                                      
fi

# ----------------------------------------
# elaborate top level design
if [ $SKIP_ELAB -eq 0 ]; then
  export GENERIC_PARAM_COMPAT_CHECK=1
  ncelab -access +w+r+c -namemap_mixgen -relax $ELAB_OPTIONS $USER_DEFINED_ELAB_OPTIONS $TOP_LEVEL_NAME
fi

# ----------------------------------------
# simulate
if [ $SKIP_SIM -eq 0 ]; then
  eval ncsim -licqueue $SIM_OPTIONS $USER_DEFINED_SIM_OPTIONS $TOP_LEVEL_NAME
fi
