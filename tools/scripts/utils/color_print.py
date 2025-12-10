from enum import Enum
from typing import Optional


# --- Configuration using Enums for Type Hinting and Validation ---

class Color(Enum):
    """
    Standard ANSI 8-color set values.
    Used for type-hinting and validation in the main function.
    """
    BLACK = 0
    RED = 1
    GREEN = 2
    YELLOW = 3
    BLUE = 4
    MAGENTA = 5
    CYAN = 6
    WHITE = 7
    DEFAULT = 9


def colored_text(text: str, fg_color: Color = Color.DEFAULT, bg_color: Color = Color.DEFAULT, bold: bool = False) -> str:
    """
    Formats the given text with ANSI escape codes for coloring and bolding.

    Args:
        text: The string content to be colored.
        fg_color: The desired foreground (text) color (must be a Color Enum).
        bg_color: The desired background color (must be a Color Enum).
        bold: If True, the text will be rendered in bold.

    Returns:
        The formatted string with ANSI escape codes.
    """

    # ANSI code for resetting all formats (essential)
    RESET = "\033[0m"
    
    # Base code for setting format (bold, etc.)
    format_code = "1" if bold else ""
    
    # Foreground color code: 30-37 (39 is default)
    # Background color code: 40-47 (49 is default)
    fg_code = f"3{fg_color.value}" if fg_color != Color.DEFAULT else "39"
    bg_code = f"4{bg_color.value}" if bg_color != Color.DEFAULT else "49"
    
    
    # Build the full ANSI code string
    # This way we skip the first code if "not bold" (i.e. format_code = "")
    codes = [code for code in [format_code, fg_code, bg_code] if code]
    # Components are separated by semicolons (e.g., \033[1;31;47m)
    ansi_code = f"\033[{';'.join(codes)}m"

    return f"{ansi_code}{text}{RESET}"


def print_bright_red(text: str):
    """Prints the text in Bright Red."""
    print(colored_text(text, fg_color=Color.RED, bold=True))

def print_bright_green(text: str):
    """Prints the text in Bright Green."""
    print(colored_text(text, fg_color=Color.GREEN, bold=True))

def print_bright_yellow(text: str):
    """Prints the text in Bright Yellow."""
    print(colored_text(text, fg_color=Color.YELLOW, bold=True))