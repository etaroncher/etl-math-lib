@echo off
REM --- Execution Script for project_root/tools/scripts/build_mathlib.py ---

REM 1. Define the directory containing the 'scripts' package.
REM    This sets the environment variable for the duration of this batch script.
set PYTHONPATH=%~dp0

REM 2. Execute the script as a module. The Python interpreter inherits the PYTHONPATH.
REM    and pass ALL arguments provided to this Batch file using the special variable %*.
python -m scripts.build_mathlib %*

REM --- End of script ---