import sys
from pathlib import Path

from pcpp.pcmd import CmdPreprocessor

DIR_CIRRENT = Path(__file__).parent

DIR_SOFTFLOAT_CLEANDED = DIR_CIRRENT / "softfloat_cleaned"


FP_SOFTFLOAT = DIR_SOFTFLOAT_CLEANDED / "softfloat.c"

output_c_file = DIR_CIRRENT / "softfloat_preprocessed.c"

fake_argv = [
    sys.argv[0],
    "-o",
    str(output_c_file),
    "-I",
    str(DIR_SOFTFLOAT_CLEANDED),
    str(FP_SOFTFLOAT),
]

CmdPreprocessor(fake_argv)


def remove_line_directives(file_path: Path):
    txt = file_path.read_text()
    lines = txt.splitlines()
    lines_filtered = [l for l in lines if not l.startswith("#line ")]
    txt = "\n".join(lines_filtered)
    file_path.write_text(txt)


remove_line_directives(output_c_file)
# reanme to .h
output_h_file = DIR_CIRRENT / "softfloat_preprocessed.h"
output_c_file.rename(output_h_file)
