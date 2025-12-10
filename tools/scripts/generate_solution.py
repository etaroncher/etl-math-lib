import os
import subprocess
import argparse
import sys
import shutil
from .utils.color_print import print_bright_red, print_bright_green, print_bright_yellow

def main():

    # Parse args
    parser = argparse.ArgumentParser(
        description="Generate Visual Studio solution with CMake",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python generate_solution.py                   # Generate with tests (default)
  python generate_solution.py --no-tests        # Generate without tests (for distribution)
  python generate_solution.py --clean           # Clean prev solution
  python generate_solution.py --arch Win32      # 32-bit architecture
  python generate_solution.py --target vs2026   # Generate for Visual Studio 2026 (default)
        """
    )

    parser.add_argument("--arch", default="x64", choices=["x64", "Win32", "ARM64"], help="Target architecture (default: x64)")
    parser.add_argument("--no-tests", action="store_true", help="Don't build tests (for distribution/CI builds)")
    parser.add_argument("--clean", action="store_true", help="Generate a clean solution")
    parser.add_argument("--target", default="vs2026", choices=["vs2026", "vs2022"], help="Target generator")
    args = parser.parse_args()

    # Paths
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.abspath(os.path.join(script_dir, "..", ".."))
    build_dir = os.path.join(project_root, "build")

    # Select generator
    generator = "Visual Studio 18 2026" if args.target == "vs2026" else "Visual Studio 17 2022"

    print("=" * 70 + "\n")
    print("CMake Solution Generation")
    print("\n" + "=" * 70 + "\n")
    print(f"Project root:      {project_root}")
    print(f"Build directory:   {build_dir}")
    print(f"Clean build:       {args.clean}")
    print(f"Generator:         {generator}")
    print(f"Architecture:      {args.arch}")
    print(f"Generate tests:    {not args.no_tests}")
    print("\n" + "=" * 70 + "\n")

    # Clean prev build
    if args.clean:
        print_bright_yellow("🧹 Cleaning...")
        print_bright_yellow(f"Deleting build directory: {build_dir}\n")
        try:
            # Recursively delete the directory and all its contents
            shutil.rmtree(build_dir, ignore_errors=True)
            print_bright_green("✅ Clean operation complete.")
            print("\n" + "=" * 70 + "\n")
        except OSError as e:
            print_bright_red(f"❌ Error during cleanup: {e}")
            print("\n" + "=" * 70)
            sys.exit(1)
    
    # Make sure build dir exists
    os.makedirs(build_dir, exist_ok=True)

    # Generate solution command
    cmd = [
        "cmake",
        "-S", project_root,
        "-B", build_dir,
        "-G", generator,
        "-A", args.arch
    ]

    # Add CMake options based on arguments
    if args.no_tests:
        cmd.append("-DBUILD_TESTS=OFF")
    else:
        cmd.append("-DBUILD_TESTS=ON")

    print("Running CMake...")
    print(f"Command: {' '.join(cmd)}\n")
    
    # Run command
    result = subprocess.run(cmd)
    if result.returncode != 0:
        print_bright_red("\n" + "=" * 70 + "\n")
        print_bright_red("❌ CMake generation failed.")
        print_bright_red("\n" + "=" * 70)
        sys.exit(result.returncode)

    print_bright_green("\n" + "=" * 70 + "\n")
    print_bright_green("✅ Solution generated successfully!")
    print_bright_green("\n" + "=" * 70)



if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n⚠️  Generation interrupted by user.")
        sys.exit(1)
    except Exception as e:
        print(f"\n❌ Unexpected error: {e}")
        sys.exit(1)