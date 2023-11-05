# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_control {
a { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
value_r { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 28
	offset_end 35
}
done { 
	dir I
	width 1
	depth 1
	mode ap_none
	offset 36
	offset_end 43
}
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
}
dict set axilite_register_dict control $port_control


