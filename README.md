# Shinima Pidgin Plugin

This is the plugin that allows the Pidgin messenger to show inline images after links if they're pointing to some images.

To prepare configure script, run `autogen.sh` file from the project root. You'll need the `libtool`, `aclocal`, `automake` and `autoconf` to run it. After `autogen.sh`, run the traditional commands

```bash
./configure
make
make install
```

After installing you sould be able to see plugin in Pidgin plugins list(restart may be nessesary). Then just ask somebody to send you an image url and get some fun.
