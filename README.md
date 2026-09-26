# Arduino FM Radio Receiver with Real-Time Audio FFT Visualizer

An interactive Arduino project that combines an **Si4703 FM Radio Tuner** with an **ILI9341 TFT Display** to provide live frequency display, automatic station name lookup, and a real-time FFT audio visualizer.

---

## 🌟 Features

* **FM Tuner Integration**: Powered by the Si4703 chip for radio signal processing.
* **Station Name Lookup**: Preset station mapping for UK radio channels (e.g., *BBC Radio 1–4*, *Capital FM*, *Heart FM*, *Classic FM*) with automatic fallback to "FM Station".
* **ILI9341 TFT Display**: Displays live tuning updates, frequencies, and visuals in landscape orientation.
* **Real-Time FFT Visualizer**: Uses Fast Fourier Transform (`arduinoFFT`) to process incoming audio signals from an analog pin (`A6`) at ~12 FPS:
  * **Bar Graph (Left)**: Green spectrum analyzer bars.
  * **Waveform Line (Right)**: Blue signal line visualizer.
* **Serial Control Interface**: Easily tune frequencies UP or DOWN using simple commands (`U` / `D`) via the Serial Monitor at 115200 baud.

---

## 🛠️ Hardware Requirements

* **Arduino Board** (e.g., Uno, Nano, Mega)
* **Si4703 FM Radio Breakout Module**
* **ILI9341 2.4" or 2.8" SPI TFT Display**
* **Audio Source Cable** (Connected from Si4703 Audio Out to Arduino `A6`)
* **Connecting Wires & Breadboard**

---

## 📌 Pin Configuration

### **ILI9341 TFT Display (SPI)**
| TFT Pin | Arduino Pin | Description |
| :--- | :--- | :--- |
| **CS** | `10` | Chip Select |
| **DC** | `9` | Data / Command |
| **MOSI** | `11` | SPI Master Out Slave In |
| **CLK** | `13` | SPI Clock |
| **MISO** | `12` | SPI Master In Slave Out |
| **RST** | `-1` / Unused | Reset pin (connected directly to MCU reset if needed) |

### **Si4703 FM Radio Module**
| Si4703 Pin | Arduino Pin | Description |
| :--- | :--- | :--- |
| **RST** | `A3` | Reset |
| **SDA** | `A4` | I2C Data |
| **SCL** | `A5` | I2C Clock |
| **GPIO2** | `2` | External interrupt line |

### **Audio Sampling**
| Connection | Arduino Pin | Description |
| :--- | :--- | :--- |
| **Audio Line In** | `A6` | Analog input for audio FFT analysis |

---

## 📚 Required Libraries

Ensure the following libraries are installed via the **Arduino Library Manager**:

1. [Wire](https://www.arduino.cc/en/Reference/Wire) (Built-in)
2. [SPI](https://www.arduino.cc/en/reference/SPI) (Built-in)
3. **Adafruit GFX Library** (`Adafruit_GFX.h`)
4. **Adafruit ILI9341** (`Adafruit_ILI9341.h`)
5. **SparkFun Si4703 Arduino Library** (`SparkFunSi4703.h`)
6. **arduinoFFT** by Enrique Condes (`arduinoFFT.h`)

---

## 🕹️ How to Use

1. **Upload the Code**: Flash the sketch onto your Arduino board.
2. **Open Serial Monitor**:
   * Set baud rate to **115200**.
   * Type **`U`** and press **Enter** to tune up by `0.1 MHz`.
   * Type **`D`** and press **Enter** to tune down by `0.1 MHz`.
3. **Watch the Display**: The display will update the current channel name/frequency and render live audio spectrum graphics.
