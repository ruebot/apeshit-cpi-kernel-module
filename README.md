♫ Apeshit Simians - Shaved Ape Drape
===============================

by [Apeshit Simians](http://soundcloud.com/apeshit-simians) (Boutros Boutros Gorilla, Surnom de Gorille, and Gorilla Monpoon)


Shaved Ape Drape - The Kernel Module Edition
--------------------------------------------------

Welcome to the most unnecessarily complicated Apeshit Simian track release format yet. 

In this repository, you will be able to compile your own kernel module, create a 
`/dev/netcat` device and redirect its output into an audio player.

```
ogg123 - < /dev/netcat
```

This repository contains the album's track data in source files, that (for complexity's sake) came from a `.wav` files that was recorded with a Tascam DR-05 at the Silver Dollar Room on March 21, 2014. The `.ogg` file was encoded from the `.wav` file. 
24-track analog tape.

Building
--------
We've only tested this on Ubuntu Linux. Sure, it's real easy to grab another operating system ISO 
and test it out, but after a day toiling in the bitmines, who has the energy?

Other people report:

* @NicolasCARPi says it works on Arch 64-bit / kernel 3.14.1-1-ARCH. You heard it here first!
* Intrepid explorer @jfilip [feels good about his 64-bit Fedora 20 install](https://gist.github.com/jfilip/408ee178a4379bf06c45)

First, install some dependencies:

```
sudo apt-get install build-essential vorbis-tools linux-headers-$(uname -r)
```

Check out the repo:

```
git clone https://github.com/ruebot/apeshit-cpi-kernel-module.git
cd apeshit-cpi-kernel-module
```

Next, build the module by running:

```
make
```

Building will take a long time.  Hang with it.  Building also requires several gigabytes of memory.  We're not totally sure why, but we think it is because because the compiler is making lots of copies of several large, static arrays that contain track data.

Listening
---------

After you build, run you need to load the module and see if it is working, so you can run:

```
sudo insmod apeshit.ko
dmesg
```

You should see output like the following from `dmesg`:

```
[ 2606.528153] [netcat]: Apeshit - Shaved Ape Drape - Kernel Module Edition - 2014
[ 2606.528153] [netcat]: Apeshit Simians are Boutros Boutros Gorilla, Surnom de Gorille, and Gorilla Monpoon
[ 2606.528153] [netcat]: 'ogg123 - < /dev/netcat' to play.
```

Finally, put on some headphones, and run:

```
ogg123 - < /dev/netcat 
```

Track information will show up in the output of `dmesg`:

```
[  612.411529] [netcat]: Now playing track 1 - 
```

If you've read this far, god help us all, and thank @usrbinnc for letting us stand on the shoulder of giants!

People insane enough to contribute (thanks!!) -- 
---------

* @mark-bi added support for auto-creating our /dev/netcat device. Thanks, Mark!
* @arfar pointed out that not everyone wants to clone public repos over SSH, and updated the clone instructions to https. Thanks!
* @jmtd simplified the command to play audio by removing the extra instance of cat. Thanks!
* @gregkh for making our module coherent with standard Linux style and cleaning up some other loose ends.
