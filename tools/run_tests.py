import os
import sys
import subprocess
import argparse

def main():

    # Paths
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.abspath(os.path.join(script_dir, ".."))

    # Parse args
    parser = argparse.ArgumentParser(description="Run MathLib tests")
    parser.add_argument("--config", default="Debug", choices=["Debug", "Release"], help="Test configuration to run (default: Debug)")
    
    args = parser.parse_args()

    print("\n" + "=" * 70 + "\n")
    print(f"Running MathLib Tests ({args.config})")
    print("\n" + "=" * 70 + "\n")

    # Construct text .exe path and check it exists
    test_exe = os.path.join(project_root, "lib", args.config, "mathlib_tests.exe")
    if not os.path.exists(test_exe):
        print(f"❌ Test executable not found: {test_exe}")
        print(f"   Build first with: python tools\\build_mathlib.py --config {args.config} --no-tests")
        print("\n" + "=" * 70 + "\n")
        sys.exit(1)


    # Run tests command
    test_cmd = [test_exe, "--reporter", "console"]

    # Run command
    result = subprocess.run(test_cmd)

    if result.returncode != 0:
        print("\n" + "=" * 70 + "\n")
        print("❌ Some tests failed.")
        print("\n" + "=" * 70 + "\n")
        sys.exit(result.returncode)

    print("\n" + "=" * 70 + "\n")
    print("✅ All tests passed!")
    print("\n" + "=" * 70 + "\n")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n⚠️  Tests interrupted by user")
        sys.exit(1)
    except Exception as e:
        print(f"\n❌ Unexpected error: {e}")
        sys.exit(1)