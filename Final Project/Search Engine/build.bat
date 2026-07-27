@echo off
REM ISSUE FIX: Links Winsock and builds the lightweight native HTTP server (no cpp-httplib compile).
setlocal
set "GPP=C:\msys64\ucrt64\bin\g++.exe"
if not exist "%GPP%" set "GPP=g++"

cd /d "%~dp0backend"

"%GPP%" -std=c++17 -O2 -o search_server.exe ^
  Main.cpp ^
  server/WebServer.cpp ^
  server/WebServerApi.cpp ^
  server/WebServerJson.cpp ^
  engine/SearchEngine.cpp ^
  engine/Indexer.cpp ^
  engine/Parser.cpp ^
  ds/Trie.cpp ^
  -lws2_32 -lwsock32

if errorlevel 1 (
  echo Build failed.
  exit /b 1
)

echo.
echo Build OK: backend\search_server.exe
echo Run from project root:  backend\search_server.exe
echo Then open:             http://localhost:8080
exit /b 0
