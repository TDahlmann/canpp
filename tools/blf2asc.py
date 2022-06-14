 # 
 # This program is free software: you can redistribute it and/or modify  
 # it under the terms of the GNU General Public License as published by  
 # the Free Software Foundation, version 3.
 #
 # This program is distributed in the hope that it will be useful, but 
 # WITHOUT ANY WARRANTY; without even the implied warranty of 
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 # General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License 
 # along with this program. If not, see <http://www.gnu.org/licenses/>.
 #
 # Author: Thomas Dahlmann 2022

import can
import sys
import os

if len(sys.argv) != 2:
    print("usage: blf2asc <filename.blf>")
    sys.exit(1)

filename = sys.argv[1]
filename_asc = os.path.splitext(filename)[0]
filename_asc += ".asc"
with open(filename, 'rb') as f_in:
    log_in = can.io.BLFReader(f_in)

    print(f"{filename} => {filename_asc}")

    with open(filename_asc, 'w') as f_out:
        log_out = can.io.ASCWriter(f_out)
        for msg in log_in:
            log_out.on_message_received(msg)
        log_out.stop()
