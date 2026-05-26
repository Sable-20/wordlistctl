## Description

Script to fetch, install, update and search wordlist archives from websites
offering wordlists with more than 6400 wordlists available.

In the latest version of the Blackarch Linux it has been added to
**/usr/share/wordlists/** directory.

## Installation

Download the tar file from the `Releases` page. 

```
tar -xvf <release.tar.xz>
sudo ./install.sh
```

## Usage

```
wordlistctl
```

This will launch a TUI that has a list of all the wordlists in the repository. Use the up and down arrow keys to navigate the list. (Search will be implemented in later versions). Press `c` to open the configuration where you can change the user agent, download directory, worker count and whether or not to decompress the file. (not fully implemented yet).

## Get Involved

You can get in touch with the BlackArch Linux team. Just check out the following:

**Please, send us pull requests!**

**Web:** https://www.blackarch.org/

**Mail:** team@blackarch.org

**IRC:** [irc://irc.freenode.net/blackarch](irc://irc.freenode.net/blackarch)
