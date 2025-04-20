
# Bender: Sudoku‑Solving Robotic Arm

**Bender** is a standalone system that uses the Dobot Magician robotic arm to read, solve, and physically write the solution to a Sudoku puzzle on paper. citeturn1file0

---

## Features

- **Grid Capture**  
  Uses a USB camera and OpenCV to find and crop the Sudoku grid. citeturn1file1
- **OCR Recognition**  
  Reads existing digits with EasyOCR, handling grayscale conversion, thresholding, and contour detection. citeturn1file1
- **Sudoku Solver**  
  Implements a backtracking algorithm in Python to fill empty cells, tracking changes for precise drawing. citeturn1file2
- **Robotic Drawing**  
  Maps the solved numbers onto the paper grid and uses the Dobot Magician to write each digit with a pen. citeturn1file5

---

## Requirements

- **Hardware**  
  - Dobot Magician 4‑axis robotic arm  
  - USB camera  
  - PC or laptop with Python support  
- **Software**  
  - Python 3.7+  
  - OpenCV, EasyOCR, Pygame, PIL  
  - Dobot SDK / API  

---

## Installation

1. Clone this repository:  
   ```bash
   git clone https://github.com/agaba-mohamed/bender-sudoku-robot.git
   cd bender-sudoku-robot
   ```
2. Create a virtual environment and install dependencies:  
   ```bash
   python3 -m venv venv
   source venv/bin/activate
   pip install -r requirements.txt
   ```
3. Connect your USB camera and Dobot arm to the computer.

---

## Usage

1. **Positioning**  
   - Move the arm to the top‑left corner of the Sudoku grid and press **Enter**.  
   - Move the arm to the bottom‑right corner and press **Enter**.  
2. **Run the script**  
   ```bash
   python main.py
   ```
3. **Workflow**  
   - The camera image is processed and OCR extracts the current numbers.  
   - You confirm the OCR result in the terminal.  
   - The solver fills the puzzle in code.  
   - The arm writes the missing digits on paper. citeturn1file1

---

## Performance

- **Accuracy**  
  High OCR accuracy under good lighting; the arm reliably draws each digit.  
- **Speed**  
  Complete read‑solve‑write cycle in about **1 minute** per puzzle. citeturn1file6

---

## Limitations & Future Work

- **Image Quality**  
  Blurriness and lens distortion can affect OCR.  
- **Drawing Precision**  
  Occasional missed points due to communication constraints.  
- **Next Steps**  
  - Upgrade to a high‑resolution camera and apply lens‑correction algorithms.  
  - Improve the Dobot communication protocol and add error‑retry logic.  
  - Optimize path planning for smoother drawing. citeturn1file4

---

## Structure

```
bender-sudoku-robot/
├── main.py          # Entry point: integrates capture, solve, and draw
├── reader.py        # Grid detection & OCR
├── solver.py        # Backtracking solver algorithm
├── drawer.py        # Dobot movement & drawing commands
├── requirements.txt # Python dependencies
└── README.md        # This file
```

---
