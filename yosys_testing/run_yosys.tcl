yosys -import


set files [glob -directory ./hls_verilog -tails *.v]
foreach file $files {
    puts "read_verilog $file"
    read_verilog ./hls_verilog/$file
}

hierarchy -check -auto-top

synth_xilinx -nolutram -noiopad -abc9

stat

write_verilog hls_out.v
