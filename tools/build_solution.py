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
    parser = argparse.ArgumentParser(description="Build Visual Studio solution")
    parser.add_argument("--config", default="Debug", choices=["Debug", "Release"])
    args = parser.parse_args()

    print(f"Building from: {build_dir}")
    print(f"Config:        {args.config}")

    # Build solution command
    cmd = [
        "cmake",
        "--build", build_dir,
        "--config", args.config
    ]
	
    # Run command
    result = subprocess.run(cmd)
    if result.returncode != 0:
        print("❌ Build failed.")
        sys.exit(result.returncode)

    print("Build complete (check lib/ for output).")
    print(f"✔ Build complete.")

if __name__ == "__main__":
    main()
