import shutil
import subprocess
from pathlib import Path


def auto_find_vitis_hls_dir() -> Path | None:
    vitis_hls_bin_path_str = shutil.which("vitis_hls")
    if vitis_hls_bin_path_str is None:
        return None
    vitis_hls_dist_path = Path(vitis_hls_bin_path_str).parent.parent
    return vitis_hls_dist_path


def auto_find_vitis_hls_bin() -> Path | None:
    vitis_hls_dir = auto_find_vitis_hls_dir()
    if vitis_hls_dir is None:
        return None
    vitis_hls_bin = vitis_hls_dir / "bin" / "vitis_hls"
    if not vitis_hls_bin.exists():
        raise RuntimeError(
            f"Vitis HLS dir exists but vitis_hls bin not found: {vitis_hls_bin}"
        )
    return vitis_hls_bin


DIR_CURRENT = Path(__file__).parent
DIR_HLSFLOAT = DIR_CURRENT / "softfloathls"


DIR_RUN_TB = DIR_CURRENT / "softfloathls__run_tb"
if DIR_RUN_TB.exists():
    shutil.rmtree(DIR_RUN_TB)
DIR_RUN_TB.mkdir()


shutil.copytree(DIR_HLSFLOAT, DIR_RUN_TB, dirs_exist_ok=True)

tcl_txt = ""
tcl_txt += "open_project -reset softfloathls__run_tb\n"
tcl_txt += 'add_files -csimflags "-Wall" softfloat_processed.h\n'
tcl_txt += 'add_files -csimflags "-Wall" softfloathls.h\n'
tcl_txt += 'add_files -tb -csimflags "-Wall" softfloathls_tb.cpp\n'
tcl_txt += 'open_solution -reset -flow_target vitis "csim_solution"\n'
tcl_txt += "csim_design\n"
tcl_txt += "exit\n"

tcl_file = DIR_RUN_TB / "csim.tcl"
tcl_file.write_text(tcl_txt)

BIN_VITIS_HLS = auto_find_vitis_hls_bin()
assert BIN_VITIS_HLS is not None, (
    "Vitis HLS binary not found. Please ensure Vitis HLS is installed and in your PATH."
)

args = [
    str(BIN_VITIS_HLS),
    str(DIR_RUN_TB / "csim.tcl"),
    "-l",
    str(DIR_RUN_TB / "csim.log"),
]

subprocess.run(args, check=True, cwd=DIR_RUN_TB)
