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
    parser = argparse.ArgumentParser(description="Generate Visual Studio solution with CMake")
    parser.add_argument("--arch", default="x64", choices=["x64", "Win32", "ARM64"])
    args = parser.parse_args()

    print(f"Project root: {project_root}")
    print(f"Build dir:    {build_dir}")
    print(f"Arch:         {args.arch}")

    # Generate solution command
    cmd = [
        "cmake",
        "-S", project_root,
        "-B", build_dir,
        "-G", generator,
        f"-A{args.arch}"
    ]

    # Run command
    result = subprocess.run(cmd)
    if result.returncode != 0:
        print("❌ CMake generation failed.")
        sys.exit(result.returncode)

    print(f"✔  Solution generated successfully in '{build_dir}'.")

if __name__ == "__main__":
    main()