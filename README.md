# Shinima Pidgin Plugin

<p align="right">
   <a href="COPYING">
   <img src="https://img.shields.io/badge/license-GPLv3-brightgreen.svg?style=flat">
   </a>
</p>

This is the plugin that allows the Pidgin messenger to show inline images after links if they're pointing to some images.

<p align="center">
	<img src="http://nickey.ru/img/shinima-pidgin-plugin/shinima.png">
</p>

To prepare configure script, run `autogen.sh` file from the project root. You'll need the `libtool`, `aclocal`, `automake` and `autoconf` to run it. After `autogen.sh`, run the traditional commands

```bash
./configure
make
make install
```

You'll need the `libpurple-dev`, `pidgin-dev`, `libglib2.0-dev` and `libsoup2.4-dev` to compile it on Ubuntu. Set up appropriate libs if you using other distro.

After installing you sould be able to see plugin in Pidgin plugins list(restart may be nessesary). Then just ask somebody to send you an image url and get some fun.
