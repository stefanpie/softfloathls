import sys
from pathlib import Path

from pcpp.pcmd import CmdPreprocessor

DIR_CIRRENT = Path(__file__).parent
DIR_SOFTFLOAT_CLEANDED = DIR_CIRRENT / "softfloat_prepared"
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


def patch_add128(file_path: Path):
    txt = file_path.read_text()
    # count number of finds
    count_find = txt.count(
        "add128(aSig0, aSig1, alternateASig0, alternateASig1, &sigMean0, &sigMean1);"
    )
    assert count_find == 1, (
        "Expected exactly one occurrence of the line to patch. "
        f"Found {count_find} occurrences."
    )
    txt = txt.replace(
        "add128(aSig0, aSig1, alternateASig0, alternateASig1, &sigMean0, &sigMean1);",
        "// add128(aSig0, aSig1, alternateASig0, alternateASig1, &sigMean0, &sigMean1);\n// PATCH HERE\nadd128(aSig0, aSig1, alternateASig0, alternateASig1, (bits64*)&sigMean0, (bits64*)&sigMean1);",
    )
    file_path.write_text(txt)


patch_add128(output_c_file)


output_h_file = DIR_CIRRENT / "softfloat_processed.h"
output_c_file.rename(output_h_file)
DIR_HLSFLOAT = DIR_CIRRENT / "softfloathls"
if not DIR_HLSFLOAT.exists():
    DIR_HLSFLOAT.mkdir()
output_h_file.rename(DIR_HLSFLOAT / "softfloat_processed.h")
