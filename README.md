# Fullscreen Clock

A fullscreen digital clock for Linux, written in C using SDL2. Designed for simple, distraction-free time display.

## Features

* Fullscreen with no window decorations
* Displays current time in large 24-hour format (HH\:MM)
* Displays current date below the time (e.g., "Saturday, April 5")
* Press `[Esc]` or `[Q]` to quit
* Press `[Space]` to flip the display horizontally (mirror image)

## Requirements

* SDL2
* SDL2\_ttf

### Install dependencies (Debian/Ubuntu):

```bash
sudo apt install libsdl2-dev libsdl2-ttf-dev
```

## Build

Use the provided Makefile:

```bash
make
```

This will compile the program into the `fullscreen_clock` binary.

## Run

```bash
./fullscreen_clock
```

## Install

To make the program available in your user environment:

```bash
make install
```

This installs it to `~/.local/bin/fullscreen_clock`.

## Desktop Launcher

To integrate with your desktop environment:

1. Copy the compiled binary:

   ```bash
   cp fullscreen_clock ~/.local/bin/
   ```

2. Copy the icon:

   ```bash
   cp fullscreen_clock.png ~/.local/share/icons/fullscreen_clock-icon.png
   ```

3. Copy the desktop entry:

   ```bash
   cp fullscreen_clock.desktop ~/.local/share/applications/
   ```

Ensure the `.desktop` file uses the full path to the binary or a relative one that matches your `$PATH`.

## License

This project is licensed under the GNU General Public License v3.0 (GPLv3). See the LICENSE file for details.

---

Feel free to fork and adapt this project for wall displays, kiosks, or digital signage setups!

