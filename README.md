# CookieCollector-3DS-
A short Cookie Clicker-like app for the 3DS Family homebrew. Built using devkitPro in C.

# Usage

Grab a release file from the releases page, or compile the code yourself. Place the 3DSX and SDMH in /root/3DS/games/CookieCollector/. Make sure /3ds/data/CookieCollector/ exists, or it may not start up.

Your files should look like this:

    /root

        /3DS

            /games
            
                /CookieCollector

                    CookieCollector.3dsx

                    CookieCollector.smdh
                    
            /data
            
                /CookieCollector
                
                    user.txt

Run the CookieCollector.3DSX file in the New-HBMenu, from an entrypoint of your choice. This supports Rosalina. You can select a title of your choice to run this 3DSX from, as a CIA build does not exist at the moment.

# Compilation

Clone the repo, and unzip it somewhere. Make a new directory labelled 'source', and place 'main.c' in there. CD to the root of the repo, and run 'make'. Once it has finished, it will produce an ELF and a 3DSX file of the same name. Grab the SDMH from the release page, and then use that instead of the generated one.

This assumes you have installed the necessary libraries and DevkitPro.


# Credits

Credits to:

The Machinump's for making readable timer code.

LiquidFenrir on the homebrew discord for suffering through my mistakes and helping me with my mental sanity when it came to saving a file

Swiftloke and Realtime on the homebrew discord for helping me understand fopen more.
