
### locaction run commend: (.venv) PS C:\Users\Dawid\zephyrproject\zephyr> 
Example build:
- west build -p always -b nucleo_f091rc samples/basic/blinky\


## Run environemt:
:: cmd.exe
zephyrproject\.venv\Scripts\activate.bat
:: PowerShell
zephyrproject\.venv\Scripts\Activate.ps1

### If not working in VS code powersheell windows:
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

##  ===================================================

west build -p always -b nucleo_f091rc MyProject\Zadanie1

west flash

##  ===================================================


