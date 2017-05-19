# CookieCollector-3DS-
A short Cookie Clicker-like app for the 3DS Family homebrew. Built using devkitPro in C.

# Usage

This may not compile, as the code is very old. Grab a release file from the releases page, or compile the code yourself. Place the 3DSX and SDMH in /root/3DS/CookieCollector/.

Your files should look like this:

    /root

        /3DS

            /CookieCollector

                CookieCollector.3dsx

                CookieCollector.smdh

Run the CookieCollector.3DSX file in the Homebrew launcher, from an entrypoint of your choice. Have fun or whatever.

# Compilation

Clone the repo, and unzip it somewhere. Make a new directory labelled 'source', and place 'main.c' in there. CD to the root of the repo, and run 'make'. Once it has finished, it will produce an ELF and a 3DSX file of the same name. Grab the SDMH from the release page, and then use that instead of the generated one.

This assumes you have installed the necessary libraries and DevkitPro.
