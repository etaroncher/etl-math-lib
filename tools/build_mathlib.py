import os
import sys
import subprocess
import argparse

def main():

    # Paths
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.abspath(os.path.join(script_dir, ".."))
    build_dir = os.path.join(project_root, "build")

    # Parse args
    parser = argparse.ArgumentParser(
        description="Build MathLib. Optionally run tests.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python build_mathlib.py                    # Build Debug, run tests
  python build_mathlib.py --config Release   # Build Release, run tests
  python build_mathlib.py --no-tests         # Build without running tests
        """
    )

    parser.add_argument("--config", default="Debug", choices=["Debug", "Release"], help="Build configuration (default: Debug)")
    parser.add_argument("--no-tests", action="store_true", help="Skip running tests after build")           

    args = parser.parse_args()

    print("\n" + "=" * 70 + "\n")
    print("MathLib Build Script")
    print("\n" + "=" * 70 + "\n")
    print(f"Build directory: {build_dir}")
    print(f"Configuration:   {args.config}")
    print(f"Run tests:       {not args.no_tests}")
    print("\n" + "=" * 70 + "\n")

    # Build solution command
    build_cmd = [
        "cmake",
        "--build", build_dir,
        "--config", args.config
    ]
    
    print("\n🔨 Building MathLib...")
    print(f"Command: {' '.join(build_cmd)}\n")

    # Run build command
    result = subprocess.run(build_cmd)
    if result.returncode != 0:
        print("\n" + "=" * 70 + "\n")
        print("❌ Build failed.")
        print("\n" + "=" * 70 + "\n")
        sys.exit(result.returncode)

    print("\n" + "=" * 70 + "\n")
    print(f"✅ Build complete successfully! (output in lib/{args.config}/).")
    print("\n" + "=" * 70 + "\n")

    # Run tests if not disabled
    if not args.no_tests:
        print("\n" + "=" * 70 + "\n")
        print("Running Tests")
        print("\n" + "=" * 70 + "\n")

        test_exe = os.path.join(project_root, "lib", args.config, "mathlib_tests.exe")

        if not os.path.exists(test_exe):
            print(f"⚠️  Test executable not found: {test_exe}")
            print("    Tests may not have been built (check '--no-tests' NOT set when running tools\\generate_solution.py).")
            print("\n" + "=" * 70 + "\n")
        else:# Run tests with console reporter for nice output
            test_cmd = [test_exe, "--reporter", "console"]
            test_result = subprocess.run(test_cmd)

            if test_result.returncode != 0:
                print("\n" + "=" * 70 + "\n")
                print("❌ Some tests failed.")
                print("\n" + "=" * 70 + "\n")
                sys.exit(test_result.returncode)

            print("\n" + "=" * 70 + "\n")
            print("✅ All tests passed!")
            print("\n" + "=" * 70 + "\n")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n⚠️  Build interrupted by user.")
        sys.exit(1)
    except Exception as e:
        print(f"\n❌ Unexpected error: {e}")
        sys.exit(1)