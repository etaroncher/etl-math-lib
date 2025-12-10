import os
import sys
import subprocess
import argparse
from .utils.color_print import print_bright_red, print_bright_green, print_bright_yellow

def main():

    # Parse args
    parser = argparse.ArgumentParser(
        description="Build MathLib. Optionally run tests.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python build_mathlib.py                    # Build Debug, run tests
  python build_mathlib.py --config Release   # Build Release, run tests
  python build_mathlib.py --no-tests         # Build without running tests
  python build_mathlib.py --clean            # Clean prev build
        """
    )

    parser.add_argument("--config", default="Debug", choices=["Debug", "Release"], help="Build configuration (default: Debug)")
    parser.add_argument("--no-tests", action="store_true", help="Skip running tests after build")
    parser.add_argument("--clean", action="store_true", help="Run 'clean' target before building")
    args = parser.parse_args()

    # Paths
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.abspath(os.path.join(script_dir, "..", ".."))
    build_dir = os.path.join(project_root, "build")
    output_dir = os.path.join(project_root, "lib", args.config)

    print("=" * 70 + "\n")
    print("MathLib Build Script")
    print("\n" + "=" * 70 + "\n")
    print(f"Build directory:  {build_dir}")
    print(f"Configuration:    {args.config}")
    print(f"Clean build:      {args.clean}")
    print(f"Output directory: {output_dir}")
    print(f"Run tests:        {not args.no_tests}")
    print("\n" + "=" * 70 + "\n")

    # Run clean target if required
    if args.clean:
        print_bright_yellow("🧹 Cleaning...")
        print_bright_yellow("Running 'clean' target\n")
        clean_cmd = [
            "cmake",
            "--build", build_dir,
            "--target", "clean",
            "--config", args.config
        ]

        clean_result = subprocess.run(clean_cmd)
        if clean_result.returncode != 0:
            # Note: A clean failure is often not fatal, but we check return code anyway.
            print_bright_red("❌ Clean target failed. Proceeding with build anyway...")
        else:
            print_bright_green("✅ Clean operation complete.")

        print("\n" + "=" * 70 + "\n")

    # Build solution command
    build_cmd = [
        "cmake",
        "--build", build_dir,
        "--config", args.config
    ]
    
    print("🔨 Building MathLib...")
    print(f"Command: {' '.join(build_cmd)}\n")

    # Run build command
    result = subprocess.run(build_cmd)
    if result.returncode != 0:
        print_bright_red("\n" + "=" * 70 + "\n")
        print_bright_red("❌ Build failed.")
        print_bright_red("\n" + "=" * 70 + "\n")
        sys.exit(result.returncode)

    print_bright_green("\n" + "=" * 70 + "\n")
    print_bright_green(f"✅ Build completed successfully!")
    print_bright_green("\n" + "=" * 70)

    # Run tests if not disabled
    if not args.no_tests:
        print("\nRunning Tests...\n")

        test_exe = os.path.join(output_dir, "mathlib_tests.exe")

        if not os.path.exists(test_exe):
            print_bright_yellow(f"⚠️  Test executable not found: {test_exe}")
            print_bright_yellow("    Tests may not have been built (check '--no-tests' NOT set when running tools\\generate.bat).")
            print("\n" + "=" * 70)
        else:# Run tests with console reporter for nice output
            test_cmd = [test_exe, "--reporter", "console"]
            test_result = subprocess.run(test_cmd)

            if test_result.returncode != 0:
                print_bright_red("\n" + "=" * 70 + "\n")
                print_bright_red("❌ Some tests failed.")
                print_bright_red("\n" + "=" * 70)
                sys.exit(test_result.returncode)

            print_bright_green("\n" + "=" * 70 + "\n")
            print_bright_green("✅ All tests passed!")
            print_bright_green("\n" + "=" * 70)



if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n⚠️  Build interrupted by user.")
        sys.exit(1)
    except Exception as e:
        print(f"\n❌ Unexpected error: {e}")
        sys.exit(1)