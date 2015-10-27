import ipaddress
from netaddr import *
import math

ip = input('Enter the IP address in CIDR form\n')
cidr=ip[(len(ip)-2):len(ip)]
q = int(int(cidr)/8)
print("The CIDR number is:",cidr)
interface = ipaddress.ip_interface(ip)
print('The network interface is :',interface.network)
n_networks = ipaddress.ip_network(interface.network)
print('Total number of Networks possible : ',int(math.pow(2,8*q)))
subnets=8*(q+1)-int(cidr)
print('The total number of subnets possible are : ',int(math.pow(2,subnets)))
print('Total number of possibele Hosts = ',n_networks.num_addresses-2)
print('\nThe different possible host addresses are\n')
for i in IPNetwork(ip).iter_hosts():
       print ('%s' % i)
