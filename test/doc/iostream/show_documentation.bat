@echo off
if exist doxygen\html\index.html (
  start doxygen\html\index.html
) else (
  echo No documentation found
  pause
)
