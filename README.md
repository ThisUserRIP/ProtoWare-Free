# ⚠️ WARNING: This project is no longer supported
# 🛡️ ProtoWare-Free [ANTICHEATER Edition]

**ProtoWare-Free** is a free open-source **internal rage cheat** for **Blockade** (Unity IL2CPP + EAC). Features include aimbot, ESP, visuals, movement hacks, and a clean ImGui-based menu.

---

## ✨ Features

* **AIM** — Aimbot with smart target selection.
* **VISUALS** — Box ESP, snaplines, hit notifications, and killfeed.
* **ADVANTAGE** — Speedhack, fly, no-recoil, and other misc enhancements.
* **UI** — Custom in-game menu (Default key: **INSERT**).
* **SYSTEM** — Config system and hotkeys support.

---

## 🛠️ How to Build

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/ThisUserRIP/ProtoWare-Free.git](https://github.com/ThisUserRIP/ProtoWare-Free.git)
    cd ProtoWare-Free
    ```
2.  Open `ProtoWare.sln` in **Visual Studio 2022**.
3.  Set configuration: **Release**.
4.  Set platform: **x64**.
5.  Build the solution (**Ctrl+Shift+B** or *Build → Build Solution*).

> **Result:** `ProtoWare.dll` will appear in `x64/Release/` (or your custom output path).

---

## 🚀 How to Use

1.  Start **Blockade** (ensure EAC is unrunning).
2.  **Recommended:** Prepare an EAC bypass (edit `settings.json` in the game folder or use known spoof values from UC threads).
    *Example JSON fragment:*
    ```json
    {
      "title": "BLOCKADE",
      "executable": "Blockade.exe",
      "productid": "213132"
    }
    ```
3.  Inject `ProtoWare.dll` into `Blockade.exe` using any injector (Xenos, Extreme Injector, Process Hacker, etc.).
4.  Press **INSERT** to open the menu.
5.  Configure features in the **AIM / VISUALS / ADVANTAGE** tabs.

*Configs are saved to and loaded from the `/config` folder.*

---

## ⚠️ DISCLAIMER

* **Use at your own risk.**
* The author (**ThisUserRIP**) is not responsible for any bans, account losses, hardware issues, anti-cheat detections, legal consequences, or ToS violations.
* Your account will most likely be **permanently banned** if detected.
* For **educational and research purposes only**.
