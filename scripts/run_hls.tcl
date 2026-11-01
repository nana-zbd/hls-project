set prj_name [lindex $argv 0]
set cpp_file [lindex $argv 1]
set tb_file  [lindex $argv 2]
set top_func [lindex $argv 3]

set ::env(RDI_LOGFILE) ""

file delete -force $prj_name
open_project $prj_name
set_top $top_func
add_files $cpp_file
add_files -tb $tb_file

open_solution "solution1" -flow_target vivado
set_part {xc7a35tcsg324-1}
create_clock -period 10 -name default

# Run C Simulation
if {[catch {csim_design -clean} result]} {
    puts "CSIM_FAIL"
} else {
    puts "CSIM_PASS"
}

# Run C Synthesis
if {[catch {csynth_design} result]} {
    puts "CSYNTH_FAIL"
} else {
    puts "CSYNTH_PASS"
}

close_project