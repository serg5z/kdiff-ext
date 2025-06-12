# Contributing to kdiff-ext

Thank you for your interest in contributing to **kdiff-ext**! We welcome contributions of all kinds, including bug reports, feature requests, code improvements, documentation updates, and packaging scripts.

---

## 🧰 Requirements

Before contributing, please ensure you have the following installed:

* Qt 5 (Core, Widgets)
* KDE Frameworks 5: I18n, KIO, CoreAddons, WidgetsAddons
* CMake ≥ 3.16
* Meld or another diff tool (optional, for testing)

---

## 🛠 Development Setup

```bash
git clone https://github.com/YOUR_USERNAME/kdiff-ext.git
cd kdiff-ext
cmake -B build -GNinja -DCMAKE_INSTALL_PREFIX=/usr
ninja -C build
sudo ninja -C build install
```

You can launch the configuration tool with:

```bash
kdiff-ext-config
```

---

## 🚀 How to Contribute

1. **Fork the repository** and clone your fork.
2. **Create a branch** for your feature or fix:

   ```bash
   git checkout -b feature/my-new-feature
   ```
3. **Make your changes** and commit them:

   ```bash
   git commit -am "Add new feature or fix"
   ```
4. **Push to your fork**:

   ```bash
   git push origin feature/my-new-feature
   ```
5. **Open a Pull Request** from your forked repository.

---

## ✅ Guidelines

* Use clear, descriptive commit messages.
* Match the code style of existing files.
* Test your changes in Dolphin.
* Update or add documentation where necessary.

---

## 🐞 Bug Reports

If you encounter an issue:

* Provide steps to reproduce the problem.
* Include logs or screenshots if applicable.
* Mention your OS and KDE/Qt versions.

---

## 📝 License

By contributing, you agree that your code will be released under the same license as this project.

---

Thank you for contributing to **kdiff-ext**! 🙌

