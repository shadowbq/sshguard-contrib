# sshguard-contrib

Additional sshguard tools to manage the blacklists.

[![Build Status](https://travis-ci.org/shadowbq/sshguard-contrib.svg?branch=master)](https://travis-ci.org/shadowbq/sshguard-contrib)

The SSHGuard project is located at [http://www.sshguard.net/]

## Compiling

You will need `cmake` to compile the binary

```shell
git clone https://github.com/shadowbq/sshguard-contrib.git
cd sshguard-contrib
cmake ./; make
```

## Installing

Copy the binaries to a location in your path

```shell
cp sshguard-dump /usr/sbin/
cp sshguard-reprieve /usr/sbin/
cp sshguard-dump-ips /usr/sbin/
```

## Usage

### sshguard-dump

To quickly dump the blacklist and entry metadata

```shell
$ ./sshguard-dump
Usage: sshguard-dump <blacklist file>
```

Example Output

```shell
$ sshguard-dump /var/log/sshguard.db 
Current Blacklist:
list_size: 1097
Entry, ip, count, service, last seen
0, 103.41.124.109, 4, 100, Mon Feb  2 13:18:11 2015
1, 222.186.58.181, 4, 100, Mon Feb  2 12:44:10 2015
2, 195.154.169.120, 4, 100, Mon Feb  2 05:57:21 2015
3, 62.210.214.156, 4, 100, Sun Feb  1 21:57:29 2015
4, 222.161.4.147, 4, 100, Sun Feb  1 11:48:03 2015
5, 115.231.218.130, 4, 100, Sat Jan 31 17:21:54 2015
[..]
```

### sshguard-reprieve

To release a blocked IP address from the blacklist

```shell
$ ./sshguard-reprieve
Usage: sshguard-reprieve <blacklist file> <ip address>
```
