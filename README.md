# kdiff-ext

**kdiff-ext** is a Dolphin file manager extension that adds context menu actions to compare files using an external diff tool (e.g. `meld`). It includes support for:

* Comparing two selected files
* Remembering files in an MRU (Most Recently Used) list
* Comparing with the most recent remembered file
* MRU submenu with icons and a "Clear MRU List" option
* Configurable diff tool and MRU size via a GUI

---

## 👷 Features

* **Compare Selected Files**: When two files are selected, compare them with the configured diff tool.
* **Remember**: Add one or more files to the MRU list.
* **Compare with MRU Head**: Compare the selected file with the most recently remembered file.
* **MRU Submenu**: Access and compare with any file from the recent list.
* **Configuration Utility**: Set the diff tool path and limit MRU size (1–64).

---

## 🧱 Requirements

* Qt 5 (Core, Widgets)
* KDE Frameworks 5 (KIO, I18n, CoreAddons, WidgetsAddons)
* CMake ≥ 3.16
* Meld or another diff tool (default: `meld`)

---

## 🥪 Build & Install

```bash
git clone https://github.com/YOUR_USERNAME/kdiff-ext.git
cd kdiff-ext
cmake -B build -GNinja -DCMAKE_INSTALL_PREFIX=/usr
ninja -C build
sudo ninja -C build install
```

> On Debian-based distros, install dependencies:

```bash
sudo apt install cmake ninja-build qtbase5-dev \
    extra-cmake-modules libkf5i18n-dev libkf5coreaddons-dev \
    libkf5kio-dev libkf5widgetsaddons-dev
```

---

## 🧠 Configuration

Run the configuration utility to set the diff tool and MRU list size:

```bash
kdiff-ext-config
```

---

## 📦 Packaging

To create a source tarball:

```bash
cmake -B build
cd build
cpack --config CPackSourceConfig.cmake
```

---

## 📜 License

BSD

---

## 📩 Authors

* \[Sergey Zorin] – initial development

