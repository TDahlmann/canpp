import time
import sys
import win32pipe, win32file, pywintypes
# requires pywin32: python -m pip install --upgrade pywin32

# pipe client sending "START\n" etc.
try:
    handle = win32file.CreateFile(
        r'\\.\pipe\CanppServerPipe',
        win32file.GENERIC_READ | win32file.GENERIC_WRITE,
        0,
        None,
        win32file.OPEN_EXISTING,
        0,
        None
    )    
    res = win32pipe.SetNamedPipeHandleState(handle, win32pipe.PIPE_WAIT, None, None)
    if res == 0:
        print(f"SetNamedPipeHandleState returns {res}")        
    
    # send START
    resp = win32file.WriteFile(handle, "START\n".encode('ascii'))            

    # send COMMAND
    time.sleep(2)
    resp = win32file.WriteFile(handle, "COMMAND:TEST1\n".encode('ascii'))            
    
    # send STOP
    time.sleep(5)
    resp = win32file.WriteFile(handle, "STOP\n".encode('ascii'))            


except pywintypes.error as e:
    if e.args[0] == 2:
        print("pipe not available")        
    elif e.args[0] == 109:
        print("pipe is damaged")        



    