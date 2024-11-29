# This project is a fork of a fork

Based on the excellent work of
https://github.com/xperiments-in/xtouch/forks
and
https://github.com/Adaaks/XTouch-5-Inch

Changes from original version:

- Show which color is in which slot (AMS or External) and which slot is currently loaded
  -Fetch current time and Show ETA (currently german timezone, can be changed via timezones.json in SDcard Root, https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv)
- Fix bug when switchting to and from printer control screen
- Check machine homing before doing manual movements
- Show Filament type in AMS slots an enable Load/Unload of AMS slots
- Enable AndroidOTA for firmware-updates via WiFi

TODO- Proper Readme

# Setup

## Required Tools and Preparation

- All tools and preparation in Xperiments-in's [original version](https://github.com/xperiments-in/xtouch?tab=readme-ov-file#required-tools-and-preparation)

- A 5" ESP32 screen (below versions are the only ones that have been tested)
  - [Old version](https://www.aliexpress.com/item/1005006625220768.html)
  - [New version](https://www.aliexpress.com/item/1005006715794302.html)

### 1. Generate provisioning file

Use Xperiments-in's [Chrome Extension](https://github.com/xperiments-in/xtouch?tab=readme-ov-file#step-3-install-the-chrome-extension) to get a `provisioning.json` file.

### 2. Generate config file

Use Xperiments-in's [Config Generator](https://github.com/xperiments-in/xtouch?tab=readme-ov-file#step-2-flash-the-firmware) to get a `config.json` file

### 3. Get printer info files

Find out what the IP of your 3D printer is (commonly has the hostname of `espressif`)

Use Adaaks's [fork](https://adaksxtouch.netlify.app/) to get a zip file containing `printer.json`, `printer-ips.json` and `printer-pair.json`

### 4. Install XTouch firmware

Use Adaaks's [fork](https://adaksxtouch.netlify.app/) to install the XTouch firmware. (either P1 or A1)

### 5. Download latest firmware

Latest [.bin](https://github.com/thunderbolt93/P1STouch-5-Inch-AMS/releases) firmware file

### 6. Prepare SD card

Copy the `provisioning.json` and `config.json` files to the root of your SD card.

Copy the **entire UNZIPPED** xtouch folder containing the `printer.json` and `printer-ips.json` files to the SD card.

Copy the latest `.bin` firmware file to the root of your SD card.

Make sure to rename the .bin file to `firmware.bin`.

### 7. Insert the SD card into the 5" ESP32 screen and power it on

It should come to life and start working

<br>

# Configuration

## Timezones

If you need to set the timezone of your display, you will need to edit a file on the SD card.

The timezone file should be added into the root directory of your SD card and called `timezones.json`

The timezone file is a JSON file with two keys:

- ntp_server: The IP address or hostname of a chosen [NTP server](https://gist.github.com/mutin-sa/eea1c396b1e610a2da1e5550d94b0453)
- timezone: A string that defines the timezone. See [here](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones) for more information and [here](https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv) for a list of timezone values.
- 12hFormat: Set to `0` if you want 24 hour time, or set to `1` if you want 12 hour time.

Example Timezones file:

```
{
  "ntp_server":"de.pool.ntp.org",
  "timezone":"CET-1CEST,M3.5.0,M10.5.0/3",
  "12hFormat":0
}
```
