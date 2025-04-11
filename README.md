# Spacefight

![](spacefight.png)

This was my first attempt creating a very simple game, it ended out ok
as a neat little highscore game. And now after 11 years it got some
minor fixes so it builds without warnings and a README file!

In order for you to build it, you will need a C++ compiler and the
following libraries. (see instructions.)

-   SDL-1.2
-   SDL-image1.2
-   SDL-mixer1.2
-   SDL-ttf1.2
-   libPhysFS

Build instructions for debian/ubuntu/mint etc.

``` shell
sudo apt install build-essential libphysfs-dev \
     libsdl1.2-dev libsdl-mixer1.2-dev  \
     libsdl-image1.2-dev libsdl-gfx1.2-dev \
     libsdl-ttf2.0-dev

# Get the code
git clone  git@github.com:davidwik/spacefight.git

cd spacefight/
# Compile and link
make

# Enjoy
./spacefight

```
