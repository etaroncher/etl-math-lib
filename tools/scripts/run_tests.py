import os
import sys
import subprocess
import argparse
from .utils.color_print import print_bright_red, print_bright_green

def main():

    # Parse args
    parser = argparse.ArgumentParser(description="Run MathLib tests")
    parser.add_argument("--config", default="Debug", choices=["Debug", "Release"], help="Test configuration to run (default: Debug)")
    args = parser.parse_args()

    # Paths
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.abspath(os.path.join(script_dir, "..", ".."))

    print("=" * 70 + "\n")
    print(f"Running MathLib Tests ({args.config})")
    print("\n" + "=" * 70 + "\n")

    # Construct text .exe path and check it exists
    test_exe = os.path.join(project_root, "lib", args.config, "mathlib_tests.exe")
    if not os.path.exists(test_exe):
        print_bright_red(f"❌ Test executable not found: {test_exe}")
        print_bright_red(f"   Build first with: python tools\\build_mathlib.py --config {args.config} --no-tests")
        print("\n" + "=" * 70)
        sys.exit(1)

    # Run tests command
    test_cmd = [test_exe, "--reporter", "console"]

    # Run command
    result = subprocess.run(test_cmd)
    if result.returncode != 0:
        print_bright_red("\n" + "=" * 70 + "\n")
        print_bright_red("❌ Some tests failed.")
        print_bright_red("\n" + "=" * 70)
        sys.exit(result.returncode)

    print_bright_green("\n" + "=" * 70 + "\n")
    print_bright_green("✅ All tests passed!")
    print_bright_green("\n" + "=" * 70)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n⚠️  Tests interrupted by user")
        sys.exit(1)
    except Exception as e:
        print(f"\n❌ Unexpected error: {e}")
        sys.exit(1)