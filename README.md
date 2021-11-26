ft_malcom
=======

An [ARP spoofing](https://en.wikipedia.org/wiki/ARP_spoofing) program developped in C language.

**IMPORTANT:** This program has been developped for educationnal purpose, do not use it in a public network.

## Concept

_ARP spoofing_ is used to sniff network transmitted packets in the [Man-in-the-middle](https://en.wikipedia.org/wiki/Man-in-the-middle_attack) attack.

It's a vulnerability exploit of the ARP (_Address Resolution Protocol_) protocol, that change the intended target of
a network communication.

## Start a test environment

### Requirements

In order to use this program safely in a virtual network, you'll have to download & install 
both _[VirtualBox](https://www.virtualbox.org/)_ and _[Vagrant](https://www.vagrantup.com/)_.

### Install the environnement

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