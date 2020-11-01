# winver-cli

## What

A stupidly simple tool that does what `winver.exe` does, but in console.

## Why

The `winver.exe` provided by Windows displays a dialog, which is not ideal for command-line usages.

## How

Compile the project using Visual Studio (2015 or higher), and put `winver-cli.exe` somewhere in PATH. Then it can be used as following:

```powershell
winver-cli
```

Never replace or override the default `winver.exe`, since it will cause problems. If you are using PowerShell and prefer to replace the original `winver` only in CLI, you can create a new alias in your PowerShell profile:

```powershell
New-Alias winver winver-cli
```