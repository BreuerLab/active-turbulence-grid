# Active Turbulence Grid (ATG) Control Software

This repository contains the software used to control the **Active Turbulence Grid (ATG)** developed in the [**Breuer Lab**](https://sites.brown.edu/breuerlab/) at Brown University**. The software interfaces C++ motor control libraries with MATLAB using the MEX framework, allowing precise and programmable control of the ATG through MATLAB commands.

---

## 🛠 How to Use

### 1. 📥 Download the Repository

Clone or download the repo to your local machine:

```bash
git clone https://github.com/BreuerLab/active-turbulence-grid.git
cd active-turbulence-grid
```

### 2. 🧱 Build the MEX File

Navigate to the `mex/` directory in MATLAB and run:

```matlab
build_mex('ATG')
```

This will compile the C++ source file located in `src/` and generate a `ATG.mexw64` file in the `mex/compiled` directory for MATLAB to use.

You should get the following message: 
**Building with 'Microsoft Visual C++ 2022'.**
**MEX completed successfully.**

> ✅ **Important:** Ensure that the `sFoundation20.dll` file is in the **same directory** as the compiled MEX file (`mex/`) before running any commands.

---

## 🎛️ Command Options

Once built, you can control the ATG in MATLAB using the following commands:

```matlab
ATG('COMMAND', Channels, Value, [OptionalSpeed])
```

### Supported Commands:

- **`RUN`** — Continuously run selected channels at a set RPM.  
  Example:  
  ```matlab
  ATG('RUN', [0, 1], 500)
  ```

- **`FLAP`** — Continuously oscillate motors back and forth at a specified angle and speed.  
  Example:  
  ```matlab
  ATG('FLAP', [0, 1], 20, 400)
  ```

- **`POSITION`** — Move motors to a specific position relative to home (in degrees).  
  Example:  
  ```matlab
  ATG('POSITION', [0, 1], 90)
  ```

- **`SETHOME`** — Set the current position of the motors as the new home (0°).  
  Example:  
  ```matlab
  ATG('SETHOME', [0, 1], 0)
  ```

---

## ⚠️ MATLAB Control App (In Development)

A MATLAB-based GUI app for ATG control is also included in this repository. **However, this app is still under development** and may contain bugs or incomplete features. Use it at your own risk.

---

## 📎 Dependencies

- [Teknic ClearView SDK](https://www.teknic.com/)
  - Includes `sFoundation20.lib` and `sFoundation20.dll`
- Visual C++ compiler (configured in MATLAB via `mex -setup`)
- MATLAB with MEX support for C++

---

## 📁 Project Structure

```
active-turbulence-grid/
│
├── src/         # C++ source code for ATG control
├── lib/         # Header files needed for compilation
├── mex/         # MEX build script and compiled outputs
├── matlab-app/  # MATLAB GUI app (WIP)
├── .gitignore   # Files to ignore when pushing to Git
└── README.md    # This file
```

---

## 🧪 Contact / Support

This software is maintained by members of the Breuer Lab at Brown University.  

## 👥 Authors

- [Karunmay Aggarwal](https://karunmay.com) – Software Developer & Undergraduate Researcher
- [Rehaan Irani](https://www.linkedin.com/in/rehaanirani/) - Mechanical Designer
- [Kenny Breuer](https://vivo.brown.edu/display/kbreuer) – Principal Investigator, Prof. of Engineering
