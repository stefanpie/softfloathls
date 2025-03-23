from pathlib import Path

from synth_scaffold import SynthReport, SynthScaffold, unwrap

DIR_CURRENT = Path(__file__).parent
input_source_files = [
    DIR_CURRENT / "test_kernel.cpp",
    *(DIR_CURRENT / "hlsfloat").glob("*"),
]

run_name = "synth_scaffold__float"
s = SynthScaffold(
    input_source_files=input_source_files,
    includes=[
        '"test_kernel.cpp"',  # include "hlsfloat.h"
    ],
    output_dir=DIR_CURRENT / run_name,
    target_fn="top",
)
result = s.generate_and_run()
assert result is not None
report: SynthReport = unwrap(result)
report.print_text_summary()
