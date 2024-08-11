# To work with can++ connecting to RaspberryPi via WLAN or LAN

- WLAN: RaspberryPi has to be assigned ip address 192.168.10.1 for wlan0 (Change at /etc/dhcpcd.conf)
- LAN: Use `ifconfig` to get ip address for eth0 and use when connecting from can++ to RaspberryPi

# Install on RaspberryPi

- `source build_can2win`
- Call can2win with the desired can channels. For instance when using can0 and can1: `./can2win can0 can1`

# Connect to can2win from PC via Can++

- Start Can++
- `Goto Settings => Harware Select => Wlan`
- For connecting over Ehternet cable goto `Settings => Harware Select => Ip address`

# How to enable can2win service at boot

Edit the path to can2win binary in file can2win.service. Then do following commands to start can2win at boot automatically:

sudo su  
chmod +x can2win.service  
cp can2win.service /etc/systemd/system  
sudo systemctl daemon-reload  
sudo systemctl enable can2win.service  

Also make sure that your socketcan device like "can0" is started at boot.