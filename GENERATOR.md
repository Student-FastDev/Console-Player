### Language: 
- [English](#english)
- [Polski](#polski) 

---

### English

#### How to Use `videoToTextColor.py`

1. Before using the script, **unpack** the `miscFiles.rar` located in the `Generator/` directory. It contains essential files like `LIT`, `LUT.npy`, and `color.pkl`, which are required for proper functioning.
   
2. Ensure all dependencies are installed by running:
   ```bash
   pip install -r requirements.txt
   ```

3. To use the generator script, simply run the following command, where `<video_file>` is your input video file:
   ```bash
   python3 videoToTextColor.py <video_file>
   ```

4. The script will process the video file frame by frame and generate an ASCII art output with colors. The resulting data will be saved in a header file `data.h`.

Make sure to have Python and the required packages installed before proceeding.

---

### Polski

#### Jak Używać `videoToTextColor.py`

1. Przed uruchomieniem skryptu, **rozpakuj** plik `miscFiles.rar` znajdujący się w katalogu `Generator/`. Zawiera on niezbędne pliki, takie jak `LIT`, `LUT.npy`, i `color.pkl`, które są wymagane do poprawnego działania.

2. Upewnij się, że wszystkie zależności są zainstalowane, uruchamiając:
   ```bash
   pip install -r requirements.txt
   ```

3. Aby użyć generatora, uruchom poniższe polecenie, gdzie `<video_file>` to plik wideo wejściowy:
   ```bash
   python3 videoToTextColor.py <video_file>
   ```

4. Skrypt przetworzy plik wideo klatka po klatce i wygeneruje wyjściowe dane ASCII z kolorami. Wynikowe dane zostaną zapisane w pliku nagłówkowym `data.h`.

Upewnij się, że masz zainstalowany Python oraz wymagane pakiety, zanim rozpoczniesz.
