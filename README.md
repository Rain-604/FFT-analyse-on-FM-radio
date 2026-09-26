# Arduino FM Radio Receiver with Real-Time Audio FFT Visualizer

An interactive Arduino project that combines an **Si4703 FM Radio Tuner**[cite: 1] with an **ILI9341 TFT Display**[cite: 1] to provide live frequency display, automatic station name lookup[cite: 1], and a real-time FFT audio visualizer[cite: 1].

---

## 🌟 Features

* **FM Tuner Integration**: Powered by the Si4703 chip for radio signal processing[cite: 1].
* **Station Name Lookup**: Preset station mapping for UK radio channels (e.g., *BBC Radio 1–4*, *Capital FM*, *Heart FM*, *Classic FM*) with automatic fallback to "FM Station"[cite: 1].
* **ILI9341 TFT Display**: Displays live tuning updates, frequencies, and visuals in landscape orientation[cite: 1].
* **Real-Time FFT Visualizer**: Uses Fast Fourier Transform (`arduinoFFT`) to process incoming audio signals from an analog pin (`A6`) at ~12 FPS[cite: 1]:
  * **Bar Graph (Left)**: Green spectrum analyzer bars[cite: 1].
  * **Waveform Line (Right)**: Blue signal line visualizer[cite: 1].
* **Serial Control Interface**: Easily tune frequencies UP or DOWN using simple commands (`U` / `D`) via the Serial Monitor at 115200 baud[cite: 1].

---

## 🛠️ Hardware Requirements

* **Arduino Board** (e.g., Uno, Nano, Mega)
* **Si4703 FM Radio Breakout Module**[cite: 1]
* **ILI9341 2.4" or 2.8" SPI TFT Display**[cite: 1]
* **Audio Source Cable** (Connected from Si4703 Audio Out to Arduino `A6`)[cite: 1]
* **Connecting Wires & Breadboard**

---

## 📌 Pin Configuration

### **ILI9341 TFT Display (SPI)**
| TFT Pin | Arduino Pin | Description |
| :--- | :--- | :--- |
| **CS** | `10` | Chip Select[cite: 1] |
| **DC** | `9` | Data / Command[cite: 1] |
| **MOSI** | `11` | SPI Master Out Slave In[cite: 1] |
| **CLK** | `13` | SPI Clock[cite: 1] |
| **MISO** | `12` | SPI Master In Slave Out[cite: 1] |
| **RST** | `-1` / Unused | Reset pin (connected directly to MCU reset if needed)[cite: 1] |

### **Si4703 FM Radio Module**
| Si4703 Pin | Arduino Pin | Description |
| :--- | :--- | :--- |
| **RST** | `A3` | Reset[cite: 1] |
| **SDA** | `A4` | I2C Data[cite: 1] |
| **SCL** | `A5` | I2C Clock[cite: 1] |
| **GPIO2** | `2` | External interrupt line[cite: 1] |

### **Audio Sampling**
| Connection | Arduino Pin | Description |
| :--- | :--- | :--- |
| **Audio Line In** | `A6` | Analog input for audio FFT analysis[cite: 1] |

---

## 📚 Required Libraries

Ensure the following libraries are installed via the **Arduino Library Manager**:

1. [Wire](https://www.arduino.cc/en/Reference/Wire) (Built-in)[cite: 1]
2. [SPI](https://www.arduino.cc/en/reference/SPI) (Built-in)[cite: 1]
3. **Adafruit GFX Library** (`Adafruit_GFX.h`)[cite: 1]
4. **Adafruit ILI9341** (`Adafruit_ILI9341.h`)[cite: 1]
5. **SparkFun Si4703 Arduino Library** (`SparkFunSi4703.h`)[cite: 1]
6. **arduinoFFT** by Enrique Condes (`arduinoFFT.h`)[cite: 1]

---

## 🕹️ How to Use

1. **Upload the Code**: Flash the sketch onto your Arduino board[cite: 1].
2. **Open Serial Monitor**:
   * Set baud rate to **115200**[cite: 1].
   * Type **`U`** and press **Enter** to tune up by `0.1 MHz`[cite: 1].
   * Type **`D`** and press **Enter** to tune down by `0.1 MHz`[cite: 1].
3. **Watch the Display**: The display will update the current channel name/frequency and render live audio spectrum graphics[cite: 1].
