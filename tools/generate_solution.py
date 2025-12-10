import os
import subprocess
import argparse
import sys

def main():
    generator = "Visual Studio 18 2026"   # adjust if CMake changes naming

    # Paths
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.abspath(os.path.join(script_dir, ".."))
    build_dir = os.path.join(project_root, "build")
    os.makedirs(build_dir, exist_ok=True)

    # Parse args
    parser = argparse.ArgumentParser(
        description="Generate Visual Studio solution with CMake",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python generate_solution.py              # Generate with tests (default)
  python generate_solution.py --no-tests   # Generate without tests (for distribution)
  python generate_solution.py --arch Win32 # 32-bit architecture
        """
    )
    
    parser.add_argument("--arch", default="x64", choices=["x64", "Win32", "ARM64"], help="Target architecture (default: x64)")
    parser.add_argument("--no-tests", action="store_true", help="Don't build tests (for distribution/CI builds)")
                        
    args = parser.parse_args()

    print("\n" + "=" * 70 + "\n")
    print("CMake Solution Generation")
    print("\n" + "=" * 70 + "\n")
    print(f"Project root:      {project_root}")
    print(f"Build directory:   {build_dir}")
    print(f"Generator:         {generator}")
    print(f"Architecture:      {args.arch}")
    print(f"Build tests:       {not args.no_tests}")
    print("\n" + "=" * 70 + "\n")

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
        cmd.append("-DMATHLIB_BUILD_TESTS=OFF")
    else:
        cmd.append("-DMATHLIB_BUILD_TESTS=ON")

    print("Running CMake...")
    print(f"Command: {' '.join(cmd)}")
    
    # Run command
    result = subprocess.run(cmd)
    if result.returncode != 0:
        print("\n" + "=" * 70 + "\n")
        print("❌ CMake generation failed.")
        print("\n" + "=" * 70 + "\n")
        sys.exit(result.returncode)

    print("\n" + "=" * 70 + "\n")
    print("✅ Solution generated successfully!")
    print("\n" + "=" * 70 + "\n")
    print(f"Location: {build_dir}\\MathLib.sln")
    print("\nNext steps:")
    print("  - Open in Visual Studio: start  build\\MathLib.sln")
    print("  - Build via script:      python tools\\build_mathlib.py")
    print("\n" + "=" * 70 + "\n")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n⚠️  Generation interrupted by user.")
        sys.exit(1)
    except Exception as e:
        print(f"\n❌ Unexpected error: {e}")
        sys.exit(1)