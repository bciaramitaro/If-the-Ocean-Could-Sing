# If-the-Ocean-Could-Sing

An interactive sound installation where conductive textiles become touch interfaces for an underwater soundscape. Built with Arduino and Max/MSP, participants shape a living ocean of sound through direct contact with fabric surfaces, each touch layering new audio into the space.

**Project documentation:** [bellaciaramitaro.com/if-the-ocean-could-sing](https://www.bellaciaramitaro.com/if-the-ocean-could-sing)

---

## Overview

The system works in two parts:

**Arduino (`Sonic_Oceans_Arduino.ino`)** reads five touch inputs across analog pins A0–A4 using the ADCTouch library, which simulates capacitive sensing in software — no dedicated touch hardware required. Each pin maintains a rolling average of 100 readings to smooth noise, and a touch is registered when a new reading exceeds that average by a multiplier of 1.2. The state of each sensor (0 or 1) is streamed over serial at 9600 baud as a space-separated list (e.g. `1 0 0 1 0`), with a new line after each cycle. Values must be separated by spaces — not commas or periods — as this is the only delimiter that allows the data to parse correctly into individual channels in Max.

**Max/MSP (`MAX_Sound_Installation.maxpat`)** receives the serial stream, parses it into five individual values using the same character-delimiter pipeline as the previous project (`serial` → `sel 13 10` → `zl group` → `itoa` → `fromsymbol` → `unpack`), and routes each value to its corresponding audio channel. Each channel plays a looping `.aif` audio file via `playlist~` at a set volume. When a touch is detected (value > 0.9), a `onebang` gate triggers the sound to fade in; after a delay (5–10 seconds depending on the channel), the volume fades back out over 2 seconds. A background ambient track (`backgrond again!!!.aif`) loops continuously as the base layer.

The six audio files are:

| Channel | File | Role |
|---------|------|------|
| Background | `backgrond again!!!.aif` | Continuous ambient base |
| Touch 1 | `sound_1.aif` | Triggered layer |
| Touch 2 | `sound_2.aif` | Triggered layer |
| Touch 3 | `sound_3.aif` | Triggered layer |
| Touch 4 | `sound_4.aif` | Triggered layer |
| Touch 5 | `sound_5.aif` | Triggered layer |

---

## Setup

### Hardware Requirements

- Arduino (Uno or compatible)
- 5 conductive textile or fabric touch pads
- Jumper wires
- USB cable for Arduino-to-computer serial connection
- Computer running Max/MSP 8+
- Audio output (speakers or headphones)

### Wiring

Connect each conductive textile pad to an analog pin on the Arduino. No additional components are required — the ADCTouch library reads capacitance directly from the analog pins.

| Touch Pad | Arduino Pin |
|-----------|-------------|
| Pad 1     | A0          |
| Pad 2     | A1          |
| Pad 3     | A2          |
| Pad 4     | A3          |
| Pad 5     | A4          |

For best results, connect each pad with a short wire and ensure the conductive material has a consistent surface area. Larger fabric pads will give more reliable readings.

### Arduino Setup

1. Install the [ADCTouch library](https://github.com/martin2250/ADCTouch) via the Arduino Library Manager.
2. Open `Sonic_Oceans_Arduino.ino` in the Arduino IDE.
3. If touch sensitivity is too high or too low, adjust the `multiplier` value (default `1.2`). Increase it to require firmer contact; decrease it for more sensitivity.
4. Upload the sketch to your Arduino.
5. Open the Serial Monitor (set to **9600 baud**) to confirm five space-separated values (0s and 1s) are streaming correctly when you touch the pads.

### Max/MSP Setup

1. Open `MAX_Sound_Installation.maxpat` in Max/MSP 8 or later.
2. **Connect to the correct serial port.** The patch uses a `serial` object configured for port `i` at 9600 baud. Update this to match the port your Arduino is connected to. Send a `print` message to the serial object to list available ports.
3. **Relink the audio files.** Each `playlist~` object references files from a local path. Replace these with the correct paths to your own audio files:
   - `backgrond again!!!.aif` (background loop)
   - `sound_1.aif` through `sound_5.aif` (touch-triggered layers)
4. **Open the gates.** Each audio channel uses a `onebang` gate that must be opened manually on first run. Click the bang button labeled "bang here to open the gate" in each channel before starting.
5. Turn on the toggle to start the metro and begin polling the serial port.
6. Enable Max's audio engine (DSP toggle or `ctrl+/`) to activate sound output.

### Adjusting Touch Behaviour

Each of the five touch channels has its own fade-in and fade-out timing controlled by `delay` and `line` objects. Default values are:

| Channel | Fade-in volume | Hold delay | Fade-out |
|---------|---------------|------------|----------|
| 1       | 88            | 5s         | 2s       |
| 2       | 90            | 5s         | 2s       |
| 3       | 80 (start 50) | 5s         | 2s       |
| 4       | 112           | 5s         | 2s       |
| 5       | 95 (start 75) | 10s        | 2s       |

These can be adjusted directly in the patch by modifying the message boxes and delay values connected to each channel's `line` object.
