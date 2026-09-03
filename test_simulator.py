import subprocess
from pathlib import Path

# Locate the compiled simulator beside this test file.
simulator = Path(__file__).resolve().with_name("conveyor.exe")

# Send invalid input, request status, then exit.
result = subprocess.run(
    [str(simulator)],
    input="1abc\n4\n9\n",
    capture_output=True,
    text=True,
    timeout=5
)

# Confirm invalid input cannot start the conveyor.
passed = (
    result.returncode == 0
    and "Invalid option" in result.stdout
    and "Conveyor: STOPPED" in result.stdout
    and "Conveyor started successfully" not in result.stdout
)

if passed:
    print("PASS: Mixed input rejected; conveyor stayed stopped.")
else:
    print("FAIL: Unexpected simulator behavior.")
    print(result.stdout)
    print(result.stderr)

# A nonzero exit code signals a failed test.
raise SystemExit(0 if passed else 1)