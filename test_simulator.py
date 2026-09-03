import subprocess
from pathlib import Path

simulator = Path(__file__).resolve().with_name("conveyor.exe")

# Each test launches a fresh simulator with a known starting state.
tests = [
    {
        "name": "Mixed input cannot start the conveyor",
        "input": "1abc\n4\n9\n",
        "expected": ["Invalid option", "Conveyor: STOPPED"],
        "forbidden": ["Conveyor started successfully"],
    },
    {
        "name": "Valid commands start and process an item",
        "input": "1\n3\n4\n9\n",
        "expected": ["Conveyor: RUNNING", "Items processed: 1"],
        "forbidden": ["BLOCKED"],
    },
    {
        "name": "Clearing a jam does not bypass emergency stop",
        "input": "5\n7\n6\n1\n4\n9\n",
        "expected": [
            "START BLOCKED: Reset the emergency stop first.",
            "Conveyor: STOPPED",
        ],
        "forbidden": ["Conveyor started successfully"],
    },
    {
        "name": "Emergency reset does not automatically restart",
        "input": "1\n7\n8\n4\n9\n",
        "expected": [
            "Emergency stop reset. Conveyor remains stopped.",
            "Conveyor: STOPPED",
        ],
        "forbidden": ["Conveyor: RUNNING"],
    },
]

failures = 0

for test in tests:
    try:
        result = subprocess.run(
            [str(simulator)],
            input=test["input"],
            capture_output=True,
            text=True,
            timeout=5,
        )

        # Check successful exit, required messages, and unwanted behavior.
        passed = (
            result.returncode == 0
            and all(text in result.stdout for text in test["expected"])
            and all(text not in result.stdout for text in test["forbidden"])
        )

        if passed:
            print(f"PASS: {test['name']}")
        else:
            failures += 1
            print(f"FAIL: {test['name']}")
            print(result.stdout)
            print(result.stderr)

    except (subprocess.TimeoutExpired, OSError) as error:
        failures += 1
        print(f"FAIL: {test['name']} — {error}")

print(f"\nResults: {len(tests) - failures}/{len(tests)} tests passed.")

# Signal failure to automated tools if any test fails.
raise SystemExit(1 if failures else 0)