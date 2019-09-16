echo -n "Enter username :"
read username
echo -n "Enter password :"
read -s passwd
echo
curl -s -u  $username:$passwd https://vpn.iiit.ac.in/secure/ubuntu.ovpn > ubuntu.ovpn
#echo $PWD
cp /etc/resolv.conf orig_resolv.conf
touch resolv.conf
echo "nameserver 10.4.20.204" > resolv.conf
cat orig_resolv.conf >> resolv.conf
sudo cp resolv.conf /etc/resolv.conf
echo "connecting to VPN"
sudo openvpn --daemon --config $PWD/ubuntu.ovpn
sudo cp orig_resolv.conf /etc/resolv.conf
rm ubuntu.ovpn resolv.conf orig_resolv.conf
