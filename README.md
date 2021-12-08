ft_malcom
=======

An [ARP spoofing](https://en.wikipedia.org/wiki/ARP_spoofing) program developped in C language.

**IMPORTANT:** This program has been developped for educationnal purpose, do not use it in a public network.

## Concept

_ARP spoofing_ is used to sniff network transmitted packets in the [Man-in-the-middle](https://en.wikipedia.org/wiki/Man-in-the-middle_attack) attack.

It's a vulnerability exploit of the ARP (_Address Resolution Protocol_) protocol, that change the intended target of
a network communication.

## How to compile the program

### Prerequisites

You'll have to make sure that the following dependencies are installed:
- Clang (C Compiler).
- Make
- lolcat & figlet (for pretty output during compilation).

### Compilation w/Make

```sh
$ make
```

## How to run

In order to run this program in a safe & legal environment, I provided this program with a virtual private network.

### Start a test environment

#### Requirements

In order to use this program safely in a virtual network, you'll have to download & install 
both _[VirtualBox](https://www.virtualbox.org/)_ and _[Vagrant](https://www.vagrantup.com/)_.

To see the inbound & outbound network packets, please download [Wireshark](https://www.wireshark.org/).

#### Install the environnement

A `Vagrantfile` is provided with this project to ease the installation & setup of the
virtual network.

Make sure `vboxnet0` virtual private network is available in
VirtualBox.

To install the virtual environment, you can type:
```sh
$ vagrant up
```

This virtual network will start the following virtual machines:

| Hostname |   IP address   |        purpose        |
|----------|----------------|-----------------------|
| blackhat | `192.168.42.2` |     attack targets    |
| target1  | `192.168.42.3` | communicate w/target2 |
| target2  | `192.168.42.4` | communicate w/target1 |

> Then, you'll be able to access to each virtual computer with the command `vagrant ssh <hostname>`.

> All the inbound & outbound network traffic is written through a `.pcap` _fifo_ created during VMs creation.
> You will be able to sniff the network with wireshark.

To ease this process, you can `source` the [env](./env) file, which provides a command to run wireshark with one of these generated files.

```sh
$ source ./env
$ sniff blackhat.pcap # sniff network in/out on 192.168.42.2 [if=eth1]
```

> To remove the environment, type `vagrant destroy` and confirm each computer removal.

### Usage:

```
Usage:
sudo ./ft_malcom [ -h -v ] [ -I ] | [-p <src IP / hostname> <src MAC addr> <target IP / hostname> <target MAC>] | [-f [-i interval] <src IP / hostname> <target IP / hostname>]
 -h     Display usage & exit.
 -v     Enable verbose mode.
 -p     Perform an ARP Poisoning attack.
 -f     Perform an ARP Flooding attack.
 -I     Use the interactive mode (using ARP flooding).

Poisonning arguments:
 src host/IP    Source IP address / hostname.
 src MAC        Source MAC address.
 dst host/IP    Targetted IP address / hostname.
 dst MAC        Targetted MAC address.

Poisonning arguments:
 src host/IP    Source IP address / hostname.
 dst host/IP    Targetted IP address / hostname.

Poisonning options:
 -i <interval>  Custom flooding interval (default 5 secs).
```

### Getting started with the interactive mode

> This mode is based on an ARP flooding attack (see below) with an interval between each ARP request of 5 seconds (default).

#### Sniff the in/out network packets on _blackhat_ VM

```sh
$ . ./env
$ sniff ./blackhat.pcap # This will open a Wireshark window
```

#### Connect to _target1_ in order to ping _target2_

```sh
$ vagrant ssh target1
Last login: Wed Dec  8 12:47:13 2021 from 10.0.2.2
[vagrant@target1 ~]$ ping 192.168.42.4 # let this command running in a terminal
```

#### Attack your targets

```sh
$ vagrant ssh blackhat
Last login: Wed Dec  8 09:24:22 2021 from 10.0.2.2
[vagrant@blackhat ~]$ cd /tmp/ft_malcom/
[vagrant@blackhat ~]$ sudo sysctl -w net.ipv4.ip_forward=1 # ensure packets forwarding
[vagrant@blackhat ft_malcom]$ make # build the program
[...]
[vagrant@blackhat ft_malcom]$ sudo ./ft_malcom -I
```

1. Select the network interface to use & wait for the network scanning
	- select `eth1`
2. Select the targetted computer
	- either `192.168.42.3` (_target1_) or `192.168.42.4` (_target2_)
3. Select the spoofed IP address
	- The opposite of the previous step

### ARP poisoning (mandatory part of the subject)

This attack will answer to arp `who-has` request from a specific _target_ with a custom ARP packet containing a _spoofed IP_ (comming from the `who-has` request) and the MAC address of the _attacker_.

Usually `who-has` requests are sent to the Link layer broadcast (`ff:ff:ff:ff:ff:ff`) to initiate connections.

The first step for you, will be to get your (_blackhat_ VM) mac address (`ip a` command).

Then type:
```sh
[vagrant@blackhat ~]$ cd /tmp/ft_malcom
[vagrant@blackhat ft_malcom]$ make
[...]
[vagrant@blackhat ft_malcom]$ sudo ./ft_malcom -p <target IP> ff:ff:ff:ff:ff:ff <spoofed IP> <your MAC address>
```

### ARP flooding

This attack method will flood the network with ARP `is-at` packets to a specific _target_ to force it to update its ARP cache table.

To test it (on _black_)
```sh
[vagrant@blackhat ~]$ cd /tmp/ft_malcom
[vagrant@blackhat ft_malcom]$ make
[...]
[vagrant@blackhat ft_malcom]$ sudo ./ft_malcom -v -f <targetted IP> <spoofed IP>
```