# Schedule Manager (AED Project)

Schedule Manager is a simple C++ console application for managing student schedules, classes and course units. It provides features to load schedules from CSV files, manage student registrations, handle requests (add/remove students or classes), list schedules and generate reports. This project was designed as a course assignment and includes file managers to read and write CSV data primarily stored in the `schedule/` folder.

---

## ✅ Features
- Load and save schedules, class lists and student enrolments from CSV files
- Manage students (add/remove/manage classes)
- Queue and process requests; invalid requests are persisted
- List schedules by student and class
- Search and list students by number or alphabetically
- Doxygen integration for generated code documentation

---

## 🔧 Build Requirements
- CMake >= 3.23
- A C++ compiler with C++14 support (MSVC, GCC, Clang)
- (Optional) Doxygen for generating documentation

---

## 🛠️ Building (Cross-platform)
Open a terminal at the repository root and run:

PowerShell / Windows:
```powershell
mkdir build; cd build
cmake ..
cmake --build . --config Release
```

Linux/macOS:
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

The main executable generated will be named `aed2223_project` (or `aed2223_project.exe` on Windows).

---

## ▶️ Running the Application
The application expects the CSV data to be in a `schedule/` directory **relative to the executable** location (the project includes a `schedule/` folder with sample data). Build the project and then run the executable from the `build/` directory so the relative paths match:

PowerShell:
```powershell
# After building
cd build
.\aed2223_project.exe
```

Linux/macOS:
```bash
cd build
./aed2223_project
```

When the program runs it shows a menu allowing you to load CSV files, manipulate students and requests, list schedules and save changes back to CSVs.

---

## 📁 Input / Output CSV files
The app reads/writes CSVs from the `schedule/` folder. Sample files included in repository:

- `classes.csv` — list of classes / lectures
	- Header: `ClassCode,UcCode,Weekday,StartHour,Duration,Type`
	- Example: `1LEIC01,L.EIC001,Monday,10.5,1.5,TP`
- `classes_per_uc.csv` — mapping of Course Unit (UC) to classes
	- Header: `UcCode,ClassCode`
- `students_classes.csv` — students and their enrolled classes
	- Header: `StudentCode,StudentName,UcCode,ClassCode`
- `invalid_requests.csv` — all invalid requests appended by the app

Notes:
- The application loads and saves using relative paths `../schedule/` from the executable location.
- To use your own CSVs, keep the same headers and structure.

---

## 📚 Documentation
The CMake setup includes a Doxygen target; if Doxygen is installed it will generate API documentation (documentation is generated in `docs/output/` under the project root).

To build only the docs (after configuring with CMake):

```powershell
cd build
cmake --build . --target Doxygen
```

---

## 🧪 Tests
No automated test suite is included. The sample CSV files in `schedule/` serve as sample data to manually exercise the program.

---

## 🤝 Contributing
- Feel free to open issues or pull requests to improve the project.
- Consider adding unit tests and a test harness to automate core feature verification.

---

## 📄 License
This project does not include an explicit license. Consider adding a `LICENSE` file (e.g., MIT) if you wish to make the project open-source.

---

## ℹ️ Notes & Assumptions
- The default class capacity is 26 (set by `ScheduleManager::CLASS_CAP`).
- The application uses some inline includes (e.g., `main.cpp` includes `application.cpp`) to keep the project simple for the assignment.
- Paths are relative: the program expects the `schedule/` directory to be at `../schedule/` relative to the executable.

---

If you want me to further improve `README.md` (add badges, CI instructions, examples of common flows, or to add a license), tell me which sections you'd like to expand. 💡
