# Translator for KDE KRunner (Plasma 6)

![Screenshot Runner](../../wiki/screenshot/interface.png)

This is a plugin for Plasma 6 KRunner. It's a translator and it translates text. Currently [Google Translate](https://translate.google.com/), [Bing Translator](https://www.bing.com/translator), [youdao](http://fanyi.youdao.com/), and [Baidu Fanyi](https://fanyi.baidu.com/) are supported. By clicking on the corresponding icon, the translation can be copied or read aloud.

## Packages

[![Logo Arch Linux](../../wiki/logos/arch_linux.png)](https://aur.archlinux.org/packages/plasma6-runners-translator)

Pre-built packages for recent distro releases (ubuntu, debian, fedora, opensuse) are available on the [GitHub Releases page](https://github.com/naraesk/krunner-translator/releases).

## Install Packages

`translate-shell` is required for the default key-less Google engine, Bing, and audio playback.

### Ubuntu 25.04+

`translate-shell` is packaged in Ubuntu `multiverse`. Ubuntu usually enables this by default, but enabling it explicitly keeps package installs reliable:

```sh
sudo add-apt-repository multiverse
sudo apt update
sudo apt install ./krunner-translator-ubuntu-amd64.deb
```

Replace the file name with the package you downloaded from the release page.

### Debian trixie

The plugin package installs directly, but `translate-shell` is only available from Debian `contrib`, which is not enabled in stock sources. If you want Google/Bing/audio support, enable `contrib` first and then install the package:

```sh
sudo editor /etc/apt/sources.list.d/debian.sources
```

Add `contrib` to each `Components:` line, then run:

```sh
sudo apt update
sudo apt install ./krunner-translator-debian-amd64.deb
```

See the Debian sources format reference for the exact file structure: <https://wiki.debian.org/SourcesList>

### Fedora 42

```sh
sudo dnf install ./krunner-translator-fedora-amd64.rpm
```

### openSUSE Tumbleweed

```sh
sudo zypper install ./krunner-translator-opensuse-amd64.rpm
```

Replace the file names above with the package matching your distro and architecture.

## Building from source

1. Clone this repo, `cd` into it, and run `./install.sh`
2. To uninstall, run `./uninstall.sh`

OR, if you prefer to build manually,

1. Install the dependencies listed below
2. Clone this repo, `cd` into it, and run
```sh
cmake -B build
cmake --build build --parallel --config Release
sudo cmake --install build --config Release
killall -q krunner  # or systemctl --user restart plasma-krunner
```
3. To uninstall, run
```sh
sudo cmake --build build --target uninstall
killall -q krunner  # or systemctl --user restart plasma-krunner
```

### Ubuntu Dependencies

Note: Requires Ubuntu 25.04 (Plucky) or newer.

```
translate-shell build-essential cmake extra-cmake-modules qt6-base-dev libkf6runner-dev libkf6i18n-dev libkf6coreaddons-dev libkf6config-dev libkf6configwidgets-dev libkf6kcmutils-dev
```

### Fedora/openSUSE Dependencies

```
translate-shell cmake extra-cmake-modules cmake(Qt6Core) cmake(Qt6Gui) cmake(Qt6Widgets) cmake(Qt6Network) cmake(KF6Runner) cmake(KF6I18n) cmake(KF6CoreAddons) cmake(KF6Config) cmake(KF6ConfigWidgets) cmake(KF6KCMUtils)
```

## Configuration

For being able to use Youdao and Baidu, an API key is required. You have to obtain a key yourself by following these steps:

### Youdao
1. Register at https://ai.youdao.com/
2. Get an API key and an API secret from Application Manager
3. Copy the key to configuration dialog

### Baidu
1. Register at http://api.fanyi.baidu.com/
2. Get an API key and an API secret from Consoles
3. Copy the key to configuration dialog

## Usage

A list of all language codes you can find [here](https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes).

### Search preferences

Open the runner settings with the configure button next to *Translator* in KRunner (or *System Settings → Search → Plasma Search → Translator*). The following search preferences are available:

- **Default source language** – used when no source language is typed (default: *English*).
- **Alternative source language** – used when the target language equals the default source language, so that typing only the target language translates from the other language (default: *German*).
- **Default target language** – used by queries that start with a trigger phrase and do not name a target language (default: *German*).
- **Trigger phrases** – comma-separated prefixes that opt into translation without typing a language code (default: `tr, transl, translate`). Matching is case-insensitive and only matches whole words. `tr` shadows the Turkish language code; remove it if you translate into Turkish often.

### Trigger phrases

Syntax: `<trigger> <searchterm>` or `<trigger> <targetlang> <searchterm>` or `<trigger> <sourcelang>-<targetlang> <searchterm>`

With the default settings (`tr`, source *en*, target *de*):

*tr hello* → *en-de hello*
*tr es hola* → *en-es hola*
*tr en es hello* → *en-es hello*
*tr en-de house* → *en-de house*

### Specify source and target language

Syntax: `<sourcelang>-<targetlang> <searchterm>`

*en-de house* will translate *house* into german (*de*)

### Use default source language

Syntax: `<targetlang> <searchterm>`

Default source language: *English (en)*
Alternative source language: *German (de)*

*de soccer* → *en-de soccer*
*en blau* → *de-en blau*
*fr house* → *en-fr house*
