# sshguard-contrib
Additional sshguard tools to manage the blacklists.

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

### sshguard-reprieve

To release a blocked IP address from the blacklist

```shell
$ ./sshguard-reprieve
Usage: sshguard-reprieve <blacklist file> <ip address>
```
