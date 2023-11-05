# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: /home/frank/Documents/Git/Group_6_Assignments/vitis/AXI_Master_ReadImage_AddValue_system/_ide/scripts/debugger_axi_master_readimage_addvalue-emulation.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source /home/frank/Documents/Git/Group_6_Assignments/vitis/AXI_Master_ReadImage_AddValue_system/_ide/scripts/debugger_axi_master_readimage_addvalue-emulation.tcl
# 
connect -url tcp:localhost:4354
targets 3
dow /home/frank/Documents/Git/Group_6_Assignments/vitis/AXI_Master_ReadImage_AddValue/Debug/AXI_Master_ReadImage_AddValue.elf
mask_write 0xfd1a0104 [expr (0x401 << 0) | 0x100] 0
targets 3
con
